"""
reliability.py
"""

import sys, os, sim

# get general config options
output_dir = sim.config.get('general/output_dir')
vth = float(sim.config.get('power/vth'))
vdd_file = 'InstantVdd.log'

# get reliability config options
enabled              = True if sim.config.get('reliability/enabled') =='true' else False
separate_traces      = False if sim.config.get('core_power/tp') =='true' else True
acceleration_factor  = sim.config.get('reliability/acceleration_factor')
delta_v_scale_factor = float(sim.config.get('reliability/delta_v_scale_factor'))
reliability_exec     = os.path.join(os.getenv('SNIPER_ROOT'), sim.config.get('reliability/reliability_executable'))

# combined files
comb_temperature_trace_file = sim.config.get('hotspot/log_files/combined_insttemperature_trace_file')
comb_state_file             = sim.config.get('reliability/log_files/state_file')
comb_delta_v_file           = sim.config.get('reliability/log_files/delta_v_file')
comb_instant_trace_file     = sim.config.get('reliability/log_files/instant_trace_file')
comb_periodic_trace_file    = sim.config.get('reliability/log_files/periodic_trace_file')

# Core files
c_temperature_trace_file = sim.config.get('hotspot/log_files_core/temperature_trace_file')
c_state_file             = sim.config.get('reliability/log_files_core/state_file')
c_delta_v_file           = sim.config.get('reliability/log_files_core/delta_v_file')
c_rvalue_trace_file      = sim.config.get('reliability/log_files_core/rvalue_trace_file')
c_full_rvalue_trace_file = sim.config.get('reliability/log_files_core/full_rvalue_trace_file')

# Memory files
m_temperature_trace_file = sim.config.get('hotspot/log_files_mem/temperature_trace_file')
m_state_file             = sim.config.get('reliability/log_files_mem/state_file')
m_delta_v_file           = sim.config.get('reliability/log_files_mem/delta_v_file')
m_rvalue_trace_file      = sim.config.get('reliability/log_files_mem/rvalue_trace_file')
m_full_rvalue_trace_file = sim.config.get('reliability/log_files_mem/full_rvalue_trace_file')


def write_headers(trace_file, full_trace_file, state_file, delta_v_file, header):
    # create instant, periodic and state trace files with the given header
    header = header.strip()
    header_len = len(header.split('\t'))
    with open(trace_file, "w") as f:
        f.write("%s\n" %(header))
    with open(full_trace_file, "w") as f:
        f.write("%s\n" %(header))
    with open(state_file, "w") as f:
        f.write("0.0\t"*header_len+"\n")
    with open(delta_v_file, "w") as f:
        f.write("0.0\t"*header_len+"\n")

def init_reliability_files(combined_header, ptrace_header):
    # Initialise separate trace files
    with open(c_temperature_trace_file) as hf:
        # we get the subcore header from the temperature trace file
        core_header = hf.readline() 
        write_headers(c_rvalue_trace_file, c_full_rvalue_trace_file, c_state_file, c_delta_v_file, core_header)
    hf.close()
    write_headers(m_rvalue_trace_file, m_full_rvalue_trace_file, m_state_file, m_delta_v_file, ptrace_header)

    # Initialise combined trace files
    if separate_traces:
        combined_header += 'tmp\t'*80 # TODO: dont hardcode this!
    write_headers(comb_instant_trace_file, comb_periodic_trace_file, comb_state_file, comb_delta_v_file, combined_header)

def clean_reliability_files():
    # Remove existing trace files
    for f in [comb_state_file, comb_instant_trace_file, comb_periodic_trace_file, comb_delta_v_file,
              c_state_file, c_rvalue_trace_file, c_full_rvalue_trace_file, c_delta_v_file,
              m_state_file, m_rvalue_trace_file, m_full_rvalue_trace_file, m_delta_v_file]:
            if os.path.exists(f):
                os.remove(f)

def target_freqs(freqs):
    with open(comb_delta_v_file, 'r') as file:
        delta_v = map(lambda x: float(x), file.readline().strip().split('\t'))
    with open(vdd_file, 'r') as file:
        file.readline() # ignore header
        vdd = map(lambda x: float(x), file.readline().strip().split('\t'))

    # based on equation (1) from
    # Rathore et al. (2019): LifeGuard: A Reinforcement Learning-Based Task 
    # Mapping Strategy for Performance-Centric Aging Management
    def new_f(f, i):
        return f / (1 - (delta_v[i] * delta_v_scale_factor)/(vdd[i] - vth))

    return [new_f(f, i) for i, f in enumerate(freqs)]

def execute_reliability(delta_t_ms, timestamp_ms, temperature_trace_file, vdd_trace_file, state_file, delta_v_file, instant_trace_file, periodic_trace_file):
    # Setup call to reliability binary `reliability_external`.
    reliability_cmd = "{} {} {} {} {} {} {} {} {}".format(
            reliability_exec, delta_t_ms, timestamp_ms, temperature_trace_file,
            vdd_trace_file, state_file, delta_v_file, instant_trace_file, 
            acceleration_factor)

    print("[Reliability]: executing {}".format(reliability_cmd))
    os.system(reliability_cmd)

    # Copy current rvalues to periodic log.
    with open(instant_trace_file) as current_rval:
        current_rval.readline()  # Skip header
        with open(periodic_trace_file, 'a') as rvalues:
            rvalues.write(current_rval.readline())

def write_vdd_file(vdd_filename, reference_file, value, mode):
    with open(reference_file, 'r') as ref:
        ref.readline() # ignore header
        data_len = len(ref.readline().split('\t'))
    with open(vdd_file, 'r') as current_vdd:
        with open(vdd_filename, 'w') as new_vdd:
            header = current_vdd.readline()
            data = current_vdd.readline().strip()
            header_len = len(header.split('\t'))
            new_vdd.write(header)
            if mode == 'combined':
                new_vdd.write(data+'\t')
                for _ in range(data_len-header_len):
                    new_vdd.write(value + '\t')
            elif mode == 'core':
                for _ in range(data_len):
                    new_vdd.write(data.split('\t')[0] + '\t')
            elif mode == 'mem':
                for _ in range(data_len):
                    new_vdd.write(value + '\t')
            else: 
                raise(Exception('Invalid mode in call to function write_vdd_file'))
            new_vdd.write('\n')
    return vdd_filename

def update_reliability_values(delta_t, timestamp):
    # Update the reliability values of the cores.

    delta_t_ms = delta_t/sim.util.Time.MS
    timestamp_ms = timestamp/sim.util.Time.MS

    comb_vdd_file = write_vdd_file('combined_InstantVdd.log', comb_temperature_trace_file, '0.8', 'combined')
    execute_reliability(delta_t_ms, timestamp_ms, comb_temperature_trace_file,
                        comb_vdd_file, comb_state_file, comb_delta_v_file,
                        comb_instant_trace_file, comb_periodic_trace_file)
    if separate_traces:
        c_vdd_file = write_vdd_file('InstantVdd_core.log', c_temperature_trace_file, '0.8', 'core')
        m_vdd_file = write_vdd_file('InstantVdd_mem.log', m_temperature_trace_file, '0.8', 'mem')
        execute_reliability(delta_t_ms, timestamp_ms, c_temperature_trace_file,
                            c_vdd_file, c_state_file, c_delta_v_file,
                            c_rvalue_trace_file, c_full_rvalue_trace_file)
        execute_reliability(delta_t_ms, timestamp_ms, m_temperature_trace_file,
                            m_vdd_file, m_state_file, m_delta_v_file,
                            m_rvalue_trace_file, m_full_rvalue_trace_file)
