import collections
import diskcache
import gzip
import io
import os
import re
try:
    from config import RESULTS_FOLDER
except ImportError:
    from ..config import RESULTS_FOLDER

HERE = os.path.dirname(os.path.abspath(__file__))
RESULT_DIRS = [RESULTS_FOLDER]
NAME_REGEX = r'results_(\d+-\d+-\d+_\d+.\d+)_([a-zA-Z0-9_\.\+]*)_((splash2|parsec)-.*)'


cache = diskcache.Cache(directory=os.path.join(HERE, 'cache'))


def get_runs():
    for result_dir in RESULT_DIRS:
        if os.path.exists(result_dir):
            for dirname in os.listdir(result_dir):
                if dirname.startswith('results_'):
                    yield dirname


def find_run(run):
    for result_dir in RESULT_DIRS:
        candidate = os.path.join(result_dir, run)
        if os.path.exists(candidate):
            return candidate
    raise Exception('could not find run')


def _open_file(run, filename):
    for base_dir in RESULT_DIRS:
        full_filename = os.path.join(base_dir, run, filename)
        if os.path.exists(full_filename):
            return open(full_filename, 'r', encoding="utf-8")

        gzip_filename = '{}.gz'.format(full_filename)
        if os.path.exists(gzip_filename):
            return io.TextIOWrapper(gzip.open(gzip_filename, 'r'), encoding="utf-8")
    raise Exception('file does not exist')


def get_date(run):
    m = re.search(NAME_REGEX, run)
    return m.group(1)


def get_config(run):
    m = re.search(NAME_REGEX, run)
    return m.group(2)


def get_tasks(run):
    m = re.search(NAME_REGEX, run)
    tasks = m.group(3).split(',')
    return ', '.join(t[t.find('-')+1:] for t in tasks)


def has_properly_finished(run):
    return get_average_response_time(run) is not None


@cache.memoize()
def get_total_simulation_time(run):
    with _open_file(run, 'sim.out') as f:
        for line in f:
            tokens = line.split()
            if tokens[0] == 'Time':
                return int(tokens[3])
    return '-'


@cache.memoize()
def get_average_response_time(run):
    with _open_file(run, 'execution.log') as f:
        for line in f:
            m = re.search(r'Average Response Time \(ns\)\s+:\s+(\d+)', line)
            if m is not None:
                return int(m.group(1))


@cache.memoize()
def get_individual_response_times(run):
    resp_times = {}
    with _open_file(run, 'execution.log') as f:
        for line in f:
            m = re.search(r'Task (\d+) \(Response/Service/Wait\) Time \(ns\)\s+:\s+(\d+)\s+(\d+)\s+(\d+)', line)
            if m is not None:
                task = int(m.group(1))
                resp = int(m.group(2))
                resp_times[task] = resp
    keys = sorted(resp_times.keys())
    if len(keys) == 0:
        return '-'
    elif keys != list(range(max(keys)+1)):
        raise Exception('task(s) missing: {}'.format(', '.join(map(str, sorted(list(set(range(max(keys)+1)) - set(keys)))))))
    else:
        return [resp_times[task] for task in keys]


def _get_traces(run, filename, multiplicator=1):
    traces = []

    with _open_file(run, filename) as f:
        f.readline()
        for line in f:
            vs = [multiplicator * float(v) for v in line.split()]
            traces.append(vs)

    return list(zip(*traces))


def _get_header(run, filename):
    with _open_file(run, filename) as f:
        header = f.readline().split()
    return header


def _get_named_traces(run, filename, multiplicator=1):
    traces = []

    with _open_file(run, filename) as f:
        header = f.readline().split()
        for line in f:
            vs = [multiplicator * float(v) for v in line.split()]
            traces.append(vs)
    traces = list(zip(*traces))

    return collections.OrderedDict((h, t) for h, t in zip(header, traces))


def get_core_power_traces(run):
    header = _get_header(run, 'combined_power.trace')
    assert all(h.startswith('C') for h in header[:count_cores(run)])  # simple check for order or header
    traces = _get_traces(run, 'combined_power.trace')
    return traces[:count_cores(run)]


def get_memory_power_traces(run):
    header = _get_header(run, 'combined_power.trace')
    start = count_cores(run)
    if has_L3_cache(run):
        start += 1 # skip L3 header
    assert all(h.startswith('B') for h in header[start:])  # simple check for order or header
    traces = _get_traces(run, 'combined_power.trace')
    return traces[start:]

def get_L3_power_trace(run):
    header = _get_header(run, 'combined_power.trace')
    assert header[count_cores(run)].startswith('L3')  # simple check for order or header
    traces = _get_traces(run, 'combined_power.trace')
    return traces[count_cores(run)]


def get_core_temperature_traces(run):
    header = _get_header(run, 'combined_temperature.trace')
    assert all(h.startswith('C') for h in header[:count_cores(run)])  # simple check for order or header
    traces = _get_traces(run, 'combined_temperature.trace')
    return traces[:count_cores(run)]


def get_memory_temperature_traces(run):
    header = _get_header(run, 'combined_temperature.trace')
    start = count_cores(run)
    if has_L3_cache(run):
        start += 1 # skip L3 header
    assert all(h.startswith('B') for h in header[start:])  # simple check for order or header
    traces = _get_traces(run, 'combined_temperature.trace')
    return traces[start:]


def get_core_peak_temperature_traces(run):
    traces = get_core_temperature_traces(run)
    peak = []
    for values in zip(*traces):
        peak.append(max(values))
    return [peak]

def get_L3_temperature_trace(run):
    header = _get_header(run, 'combined_temperature.trace')
    assert header[count_cores(run)].startswith('L3')  # simple check for order or header
    traces = _get_traces(run, 'combined_temperature.trace')
    return traces[count_cores(run)]

def get_all_temperature_traces(run):
    traces = _get_named_traces(run, 'combined_temperature.trace')
    return traces


@cache.memoize()
def get_cpi_stack_trace_parts(run):
    parts = []
    with _open_file(run, 'PeriodicCPIStack.log') as f:
        f.readline()
        for line in f:
            part = line.split()[0]
            if part not in parts:
                parts.append(part)
    assert len(parts) > 0, 'empty PeriodicCPIStack.log'
    return parts


def get_cpi_stack_part_trace(run, part='total'):
    traces = []

    trace_values = []
    with _open_file(run, 'PeriodicCPIStack.log') as f:
        f.readline()
        for line in f:
            if line.startswith(part + '\t'):
                items = line.split()[1:]
                if items == ['-']:
                    ps = [0] * count_cores(run)
                else:
                    ps = [float(value) for value in items]
                trace_values.append(ps)

    return list(zip(*trace_values))


def _add_traces(trace1, trace2):
    assert len(trace1) == len(trace2), 'number of cores differs: {} != {}'.format(len(trace1), len(trace2))
    traces = []
    for t1, t2 in zip(trace1, trace2):
        assert len(t1) == len(t2), 'length of traces differ: {} != {}'.format(len(t1), len(t2))
        traces.append([v1 + v2 for v1, v2 in zip(t1, t2)])
    return traces


def _divide_traces(numerator, denominator):
    assert len(numerator) == len(denominator), 'number of cores differs: {} != {}'.format(len(numerator), len(denominator))
    traces = []
    for num, den in zip(numerator, denominator):
        assert len(num) == len(den), 'length of traces differ: {} != {}'.format(len(num), len(den))
        traces.append([n / d if d != 0 else None for n, d in zip(num, den)])
    return traces


def get_ips_traces(run):
    return _divide_traces(get_core_freq_traces(run), get_cpi_traces(run, raw=True))


def get_cpi_traces(run, raw=False):
    traces = list(map(list, get_cpi_stack_part_trace(run, 'total')))
    if not raw:
        w = 2
        for trace in traces:
            drop = [i for i in range(len(trace)) if any(t > 20 for t in trace[max(i-w,0):min(i+w,len(trace))])]
            for i in drop:
                trace[i] = None
    return traces


def get_core_freq_traces(run):
    return _get_traces(run, 'PeriodicFrequency.log', multiplicator=1e9)


def get_core_utilization_traces(run):
    cpi = None
    for part in get_cpi_stack_trace_parts(run):
        blacklist = ['total', 'mem', 'ifetch', 'sync', 'dvfs-transition', 'imbalance', 'other']
        if all(b not in part for b in blacklist):
            part_trace = get_cpi_stack_part_trace(run, part)
            if cpi is None:
                cpi = part_trace
            else:
                cpi = _add_traces(cpi, part_trace)
    assert cpi is not None, 'no valid CPI stack parts found to calculate utilization'
    return _divide_traces(cpi, get_cpi_stack_part_trace(run, 'total'))


@cache.memoize()
def count_cores(run):
    return len(get_core_freq_traces(run))


@cache.memoize()
def get_active_cores(run):
    utilization_traces = get_core_utilization_traces(run)
    return [i for i, utilization in enumerate(utilization_traces) if max(utilization) > 0.01]

def has_L3_cache(run):
    header = _get_header(run, 'combined_temperature.trace')
    return 'L3' in header