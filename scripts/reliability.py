"""
reliability.py
"""

import sys, os, sim

# get general config options
output_dir = sim.config.get('general/output_dir')

# get reliability config options
enabled             = True if sim.config.get('reliability/enabled') =='true' else False
separate_traces     = True if sim.config.get('reliability/separate_core_mem_trace') =='true' else False
reliability_exec    = os.path.join(os.getenv('SNIPER_ROOT'), sim.config.get('reliability/reliability_executable'))
acceleration_factor = sim.config.get('reliability/acceleration_factor')

# combined files
comb_temperature_trace_file = sim.config.get('hotspot/log_files/combined_insttemperature_trace_file')
comb_sum_file               = sim.config.get('reliability/log_files/sum_file')
comb_instant_trace_file     = sim.config.get('reliability/log_files/instant_trace_file')
comb_periodic_trace_file    = sim.config.get('reliability/log_files/periodic_trace_file')

# Core files
c_temperature_trace_file = sim.config.get('hotspot/log_files_core/temperature_trace_file')
c_sum_file               = sim.config.get('reliability/log_files_core/sum_file')
c_rvalue_trace_file      = sim.config.get('reliability/log_files_core/rvalue_trace_file')
c_full_rvalue_trace_file = sim.config.get('reliability/log_files_core/full_rvalue_trace_file')

# Memory files
m_temperature_trace_file = sim.config.get('hotspot/log_files_mem/temperature_trace_file')
m_sum_file               = sim.config.get('reliability/log_files_mem/sum_file')
m_rvalue_trace_file      = sim.config.get('reliability/log_files_mem/rvalue_trace_file')
m_full_rvalue_trace_file = sim.config.get('reliability/log_files_mem/full_rvalue_trace_file')


def write_headers(trace_file, full_trace_file, sum_file, header):
    header = header.strip()
    header_len = len(header.split('\t'))
    with open(trace_file, "w") as f:
        f.write("%s\n" %(header))
    f.close()
    with open(full_trace_file, "w") as f:
        f.write("%s\n" %(header))
    f.close()
    with open(sum_file, "w") as f:
        f.write("0.0\t"*header_len+"\n")
    f.close()

def init_reliability_files(combined_header, ptrace_header):
    if separate_traces:
        with open(c_temperature_trace_file) as hf:
            core_header  = hf.readline() # we get the core header from the temperature trace file
            write_headers(c_rvalue_trace_file, c_full_rvalue_trace_file, c_sum_file, core_header)
        hf.close()

        write_headers(m_rvalue_trace_file, m_full_rvalue_trace_file, m_sum_file, ptrace_header)
    else:
        write_headers(comb_instant_trace_file, comb_periodic_trace_file, comb_sum_file, combined_header)

def clean_reliability_files():
    for f in [comb_sum_file, comb_instant_trace_file, comb_periodic_trace_file,
              c_sum_file, c_rvalue_trace_file, c_full_rvalue_trace_file,
              m_sum_file, m_rvalue_trace_file, m_full_rvalue_trace_file]:
            if os.path.exists(f):
                os.remove(f)

def execute_reliability(delta_t_ms, temperature_trace_file, sum_file, instant_trace_file, periodic_trace_file):
    # Setup call to reliability binary `reliability_external`.
    reliability_cmd = "{} {} {} {} {} {}".format(
            reliability_exec, delta_t_ms, temperature_trace_file,
            sum_file, instant_trace_file, acceleration_factor)

    print("DEBUG: executing: {}".format(reliability_cmd))
    os.system(reliability_cmd)

    # Copy current rvalues to periodic log.
    with open(instant_trace_file) as current_rval:
        current_rval.readline()  # Skip header
        with open(periodic_trace_file, 'a') as rvalues:
            rvalues.write(current_rval.readline())


def update_reliability_values(delta_t):
    # Update the reliability values of the cores.
    # Wearout is calculated using on the temperatures in the file
    # `instant_temperatures` (in celsius) over the time period `delta_t` (in
    # seconds)

    delta_t_ms = delta_t/1e12

    if separate_traces:
        execute_reliability(delta_t_ms, c_temperature_trace_file, c_sum_file,
                            c_rvalue_trace_file, c_full_rvalue_trace_file)
        execute_reliability(delta_t_ms, m_temperature_trace_file, m_sum_file,
                            m_rvalue_trace_file, m_full_rvalue_trace_file)
    else:
        execute_reliability(delta_t_ms, comb_temperature_trace_file,
                            comb_sum_file, comb_instant_trace_file,
                            comb_periodic_trace_file)
