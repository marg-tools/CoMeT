import collections
import os
import sys
HERE = os.path.dirname(os.path.abspath(__file__))
SIMULATIONCONTROL = os.path.dirname(HERE)
sys.path.append(SIMULATIONCONTROL)

import matplotlib as mpl
mpl.use('Agg')
import math
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns

import resultlib


def smoothen(data, k):
    return list(np.convolve(data, np.ones((k,))/k, mode='same'))


def interleave(list, k):
    stride = math.ceil(len(list) / k)
    for start in range(stride):
        for i in range(k):
            ix = start + stride * i
            if ix < len(list):
                yield list[ix]
        

def set_color_palette(num_colors):
    if num_colors > 0:
        pal = list(interleave(sns.color_palette("hls", num_colors), 1))
        sns.set_palette(pal)


def plot_core_trace(run, name, title, ylabel, traces_function, active_cores, yMin=None, yMax=None, smooth=None, force_recreate=False, xlabel='Epoch'):
    def f():
        try:
            traces = traces_function()
        except KeyboardInterrupt:
            raise
        return collections.OrderedDict(('Core {}'.format(core), traces[core]) for core in active_cores)
    plot_named_traces(run, name, title, ylabel, f, yMin=yMin, yMax=yMax, smooth=smooth, force_recreate=force_recreate, xlabel=xlabel)


def plot_named_traces(run, name, title, ylabel, traces_function, yMin=None, yMax=None, smooth=None, force_recreate=False, xlabel='Epoch'):
    filename = os.path.join(resultlib.find_run(run), '{}.png'.format(name))

    if not os.path.exists(filename) or force_recreate:
        try:
            traces = traces_function()
        except KeyboardInterrupt:
            raise

        set_color_palette(len(traces))

        plt.figure(figsize=(14,10))
        tracelen = 0
        for name, trace in traces.items():
            valid_trace = [value for value in trace if value is not None]
            if len(valid_trace) > 0:
                #if yMin is not None:
                #    yMin = min(yMin, min(valid_trace) * 1.1)
                #if yMax is not None:
                #    yMax = max(yMax, max(valid_trace) * 1.1)
                tracelen = len(trace)
                if smooth is not None:
                    trace = smoothen(trace, smooth)
                plt.plot(trace, label=name)
        if yMin is not None:
            plt.ylim(bottom=yMin)
        if yMax is not None:
            plt.ylim(top=yMax)

        plt.title('{} {}'.format(title, run))
        plt.legend()
        plt.xlabel(xlabel)
        plt.ylabel(ylabel)
        plt.grid()
        plt.grid(which='minor', linestyle=':')
        plt.minorticks_on()
        plt.savefig(filename, bbox_inches='tight')
        plt.close()


def plot_cpi_stack_trace(run, active_cores, force_recreate=False):
    blacklist = ['imbalance', 'sync', 'total', 'rs_full', 'serial', 'smt', 'mem-l4', 'mem-dram-cache', 'dvfs-transition', 'other']
    parts = [part for part in resultlib.get_cpi_stack_trace_parts(run) if not any(b in part for b in blacklist)]
    traces = {part: resultlib.get_cpi_stack_part_trace(run, part) for part in parts}

    set_color_palette(len(parts))

    for core in active_cores:
        name = 'cpi-stack-trace-c{}'.format(core)
        title = 'cpi-stack-trace Core {}'.format(core)
        filename = os.path.join(resultlib.find_run(run), '{}.png'.format(name))
        if not os.path.exists(filename) or force_recreate:
            fig = plt.figure(figsize=(14,10))
            ax = fig.add_subplot(1, 1, 1)

            stacktrace = [traces[part][core] for part in parts]
            xs = range(len(stacktrace[0]))
            plt.stackplot(xs, stacktrace, labels=parts)
            plt.ylim(bottom=0, top=6)
            plt.title('{} {}'.format(title, run))

            handles, labels = ax.get_legend_handles_labels()
            ax.legend(handles[::-1], labels[::-1], loc='upper left', bbox_to_anchor=(1, 1))
            
            plt.grid()
            plt.grid(which='minor', linestyle=':')
            plt.minorticks_on()
            plt.savefig(filename, bbox_inches='tight')
            plt.close()


def create_plots(run, force_recreate=False):
    print('creating plots for {}'.format(run))
    active_cores = resultlib.get_active_cores(run)

    plot_core_trace(run, 'frequency', 'Frequency', 'Frequency (GHz)', lambda: resultlib.get_core_freq_traces(run), active_cores, yMin=0, yMax=4.1e9, force_recreate=force_recreate)
    plot_core_trace(run, 'core_temperature', 'Core temperature', 'Core Temperature (C)', lambda: resultlib.get_core_temperature_traces(run), active_cores, yMin=45, yMax=100, force_recreate=force_recreate)
    plot_named_traces(run, 'all_temperatures', 'All temperatures', 'Temperature (C)', lambda: resultlib.get_all_temperature_traces(run), yMin=45, yMax=100, force_recreate=force_recreate)
    plot_core_trace(run, 'core_rvalues', 'Core R-values', 'Reliability', lambda: resultlib.get_rvalues_traces(run), active_cores, force_recreate=force_recreate, xlabel='time (ms) * acceleration factor')
    plot_named_traces(run, 'all_rvalues', 'All R-values', 'Reliability', lambda: resultlib.get_all_rvalues_traces(run), force_recreate=force_recreate, xlabel='time (ms) * acceleration factor')
    plot_core_trace(run, 'core_power', 'Core power', 'Power (W)', lambda: resultlib.get_core_power_traces(run), active_cores, yMin=0, force_recreate=force_recreate)
    plot_core_trace(run, 'core_utilization', 'Core utilization', 'Core Utilization', lambda: resultlib.get_core_utilization_traces(run), active_cores, yMin=0, force_recreate=force_recreate)
    plot_core_trace(run, 'cpi', 'CPI', 'CPI', lambda: resultlib.get_cpi_traces(run), active_cores, yMin=0, force_recreate=force_recreate)
    plot_core_trace(run, 'ips', 'IPS', 'IPS', lambda: resultlib.get_ips_traces(run), active_cores, yMin=0, yMax=8e9, force_recreate=force_recreate)
    # plot_core_trace(run, 'ipssmooth', 'Smoothed IPS', 'IPS', lambda: resultlib.get_ips_traces(run), active_cores, yMin=0, yMax=8e9, smooth=10, force_recreate=force_recreate)
    plot_cpi_stack_trace(run, active_cores, force_recreate=force_recreate)


if __name__ == '__main__':
    for run in sorted(resultlib.get_runs())[::-1]:
        create_plots(run)
