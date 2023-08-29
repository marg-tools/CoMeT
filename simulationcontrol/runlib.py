import datetime
import difflib
import math
import os
import gzip
import platform
import random
import re
import shutil
import subprocess
import traceback
import sys

import config
from resultlib.plot import create_plots

HERE = os.path.dirname(os.path.abspath(__file__))
SNIPER_BASE = os.path.dirname(HERE)
BENCHMARKS = os.path.join(SNIPER_BASE, 'benchmarks')
BATCH_START = datetime.datetime.now().strftime('%Y-%m-%d_%H.%M')


def change_configuration_files(configuration_tags):
    seen = set()
    for filename in os.listdir(os.path.join(SNIPER_BASE, 'config')):
        if filename.endswith('.cfg'):
            full_filename = os.path.join(SNIPER_BASE, 'config', filename)
            with open(full_filename, 'r') as f:
                content = f.read()

            new_content = ''
            for line in content.splitlines():
                m = re.match('.*cfg:(!?)([a-zA-Z_\\.0-9]+)$', line)
                if m:
                    inverted = m.group(1) == '!'
                    include = inverted ^ (m.group(2) in configuration_tags)
                    included = line[0] != '#'
                    if include and not included:
                        line = line[1:]
                    elif not include and included:
                        line = '#' + line
                    if m.group(2) in configuration_tags:
                        seen.add(m.group(2))
                new_content += line
                new_content += '\n'

            if content != new_content:
                print('changing', full_filename)
                print(''.join(difflib.unified_diff(content.splitlines(keepends=True), new_content.splitlines(keepends=True))), end='')
                with open(full_filename, 'w') as f:
                    f.write(new_content)
    not_seen = set(configuration_tags) - seen
    if not_seen:
        print('WARNING: these configuration options have no match in base.cfg and have no effect: {}'.format(', '.join(not_seen)))
        input('Please press enter to continue...')


def create_video(run):
    args = [
        os.path.join(SNIPER_BASE, 'scripts', 'heatView.py'),
        '--cores_in_x', str(config.NUMBER_CORES_X),
        '--cores_in_y', str(config.NUMBER_CORES_Y),
        '--cores_in_z', str(config.NUMBER_CORES_Z),
        '--banks_in_x', str(config.NUMBER_MEM_BANKS_X),
        '--banks_in_y', str(config.NUMBER_MEM_BANKS_Y),
        '--banks_in_z', str(config.NUMBER_MEM_BANKS_Z),
        '--arch_type', config.ARCH_TYPE,
        '--plot_type', '3D' if config.VIDEO_PLOT_3D else '2D',
        '--layer_to_view', str(config.VIDEO_BREAKOUT_LAYER),
        '--type_to_view', config.VIDEO_BREAKOUT_TYPE,
        '--samplingRate', '1',
        '--traceFile', os.path.join(BENCHMARKS, 'combined_temperature.trace'),
        '--output', os.path.join(config.RESULTS_FOLDER, run, 'video'),
        '--clean',
    ]
    if config.VIDEO_INVERTED_VIEW:
        args.append('--inverted_view')
    if config.VIDEO_EXPLICIT_TMIN is not None:
        args.extend(['--tmin', str(config.VIDEO_EXPLICIT_TMIN)])
    if config.VIDEO_EXPLICIT_TMAX is not None:
        args.extend(['--tmax', str(config.VIDEO_EXPLICIT_TMAX)])

    subprocess.check_call(args)


def save_output(configuration_tags, benchmark, console_output, started, ended):
    benchmark_text = benchmark
    if len(benchmark_text) > 100:
        benchmark_text = benchmark_text[:100] + '__etc'
    run = 'results_{}_{}_{}'.format(BATCH_START, '+'.join(configuration_tags), benchmark_text)
    directory = os.path.join(config.RESULTS_FOLDER, run)
    if not os.path.exists(directory):
        os.makedirs(directory)
    with gzip.open(os.path.join(directory, 'execution.log.gz'), 'w') as f:
        f.write(console_output.encode('utf-8'))
    with open(os.path.join(directory, 'executioninfo.txt'), 'w') as f:
        f.write('started:    {}\n'.format(started.strftime('%Y-%m-%d %H:%M:%S')))
        f.write('ended:      {}\n'.format(ended.strftime('%Y-%m-%d %H:%M:%S')))
        f.write('duration:   {}\n'.format(ended - started))
        f.write('host:       {}\n'.format(platform.node()))
        f.write('tasks:      {}\n'.format(benchmark))
    for f in ('sim.cfg',
              'sim.info',
              'sim.out',
              'sim.stats.sqlite3'):
        shutil.copy(os.path.join(BENCHMARKS, f), directory)
    for f in ('combined_power.trace',  # this contains power of cores and memory banks
              'full_power_mem.trace',  # this contains power of memory banks and logic cores (memory controllers)
              'full_power_core.trace',  # this contains power of cores (included for consistency)
              'combined_temperature.trace',
              'combined_rvalue.trace',
              'full_rvalue_mem.trace',
              'full_rvalue_core.trace',
              'PeriodicFrequency.log',
              'PeriodicVdd.log',
              'PeriodicCPIStack.log',):
        with open(os.path.join(BENCHMARKS, f), 'rb') as f_in, gzip.open('{}.gz'.format(os.path.join(directory, f)), 'wb') as f_out:
            shutil.copyfileobj(f_in, f_out)
    create_plots(run)
    create_video(run)


def run(configuration_tags, benchmark):
    print('running {} with configuration {}'.format(benchmark, '+'.join(configuration_tags)))
    started = datetime.datetime.now()
    change_configuration_files(configuration_tags)

    args = '-n {number_cores} -c {config} --benchmarks={benchmark} --no-roi --sim-end=last -s memTherm_core' \
        .format(number_cores=config.NUMBER_CORES,
                config=config.SNIPER_CONFIG,
                benchmark=benchmark)
    console_output = ''
    print(args)
    run_sniper = os.path.join(BENCHMARKS, 'run-sniper')
    p = subprocess.Popen([run_sniper] + args.split(' '), stdout=subprocess.PIPE, stderr=subprocess.STDOUT, bufsize=1, cwd=BENCHMARKS)
    with p.stdout:
        for line in iter(p.stdout.readline, b''):
            linestr = line.decode('utf-8')
            console_output += linestr
            print(linestr, end='')
    p.wait()

    ended = datetime.datetime.now()

    if p.returncode != 0:
        raise Exception('return code != 0')

    save_output(configuration_tags, benchmark, console_output, started, ended)


def try_run(configuration_tags, benchmark):
    try:
        run(configuration_tags, benchmark)
    except KeyboardInterrupt:
        raise
    except Exception as e:
        for i in range(4):
            print('#' * 80)
        #print(e)
        print(traceback.format_exc())
        for i in range(4):
            print('#' * 80)
        input('Please press enter...')


class Infeasible(Exception):
    pass


def get_instance(benchmark, parallelism, input_set='small'):
    threads = {
        'parsec-blackscholes': [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16],
        'parsec-bodytrack': [3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16],
        'parsec-canneal': [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16],
        'parsec-dedup': [4, 7, 10, 13, 16],
        'parsec-fluidanimate': [2, 3, 0, 5, 0, 0, 0, 9],
        'parsec-streamcluster': [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16],
        'parsec-swaptions': [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16],
        'parsec-x264': [1, 3, 4, 5, 6, 7, 8, 9],
        'splash2-barnes': [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16],
        'splash2-cholesky': [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16],
        'splash2-fft': [1, 2, 0, 4, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 16],
        'splash2-fmm': [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16],
        'splash2-lu.cont': [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16],
        'splash2-lu.ncont': [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16],
        'splash2-ocean.cont': [1, 2, 0, 4, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 16],
        'splash2-ocean.ncont': [1, 2, 0, 4, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 16],
        'splash2-radiosity': [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16],
        'splash2-radix': [1, 2, 0, 4, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 16],
        'splash2-raytrace': [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16],
        'splash2-water.nsq': [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16],
        'splash2-water.sp': [1, 2, 0, 4, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 16],  # other parallelism values run but are suboptimal -> don't allow in the first place
    }
    
    ps = threads[benchmark]
    if parallelism <= 0 or parallelism not in ps:
        raise Infeasible()
    p = ps.index(parallelism) + 1

    if benchmark.startswith('parsec') and not input_set.startswith('sim'):
        input_set = 'sim' + input_set

    return '{}-{}-{}'.format(benchmark, input_set, p)


def get_feasible_parallelisms(benchmark):
    feasible = []
    for p in range(1, 16+1):
        try:
            get_instance(benchmark, p)
            feasible.append(p)
        except Infeasible:
            pass
    return feasible


def get_workload(benchmark, cores, parallelism=None, number_tasks=None, input_set='small'):
    if parallelism is not None:
        number_tasks = math.floor(cores / parallelism)
        return get_workload(benchmark, cores, number_tasks=number_tasks, input_set=input_set)
    elif number_tasks is not None:
        if number_tasks == 0:
            if cores == 0:
                return []
            else:
                raise Infeasible()
        else:
            parallelism = math.ceil(cores / number_tasks)
            for p in reversed(range(1, min(cores, parallelism) + 1)):
                try:
                    b = get_instance(benchmark, p, input_set=input_set)
                    return [b] + get_workload(benchmark, cores - p, number_tasks=number_tasks-1, input_set=input_set)
                except Infeasible:
                    pass
            raise Infeasible()
    else:
        raise Exception('either parallelism or number_tasks needs to be set')
