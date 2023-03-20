"""
reliability.py
"""

import sys, os, sim

# get general config options
NUM_CORES=int(sim.config.get('general/total_cores'))
NUM_BANKS=int(sim.config.get('memory/num_banks'))
output_dir = sim.config.get('general/output_dir')

# get reliability config options
enabled             = True if sim.config.get('reliability/enabled') =='true' else False
reliability_exec    = os.path.join(os.getenv('SNIPER_ROOT'), sim.config.get('reliability/reliability_executable'))
acceleration_factor = sim.config.get('reliability/acceleration_factor')

# combined files
sum_file            = os.path.join(output_dir, sim.config.get('reliability/log_files/sum_file'))
periodic_trace_file = os.path.join(output_dir, sim.config.get('reliability/log_files/periodic_trace_file'))
instant_trace_file  = os.path.join(output_dir, sim.config.get('reliability/log_files/instant_trace_file'))

def init_reliability_files(combined_header, ptrace_header):
    with open(instant_trace_file, "w") as f:
          f.write("%s\n" %(combined_header))
    f.close()
    with open(periodic_trace_file, "w") as f:
        f.write("%s\n" %(combined_header))
    f.close()

    # data_size = len(combined_header.split('\t'))-1
    data_size = 212 # TODO: temporary value
    with open(sum_file, "w") as f:
        f.write("0.0\t"*data_size+"\n")
    f.close()


def clean_reliability_files():
    # gkothar1
    open(periodic_trace_file, 'w')  # empties the file

    # The following files need to be *removed* not just emptied.
    if os.path.exists(sum_file):
        # print("DEBUG: removing {}".format(sum_file))
        os.remove(sum_file)
    if os.path.exists(instant_trace_file):
        # print("DEBUG: removing {}".format(instant_trace_file))
        os.remove(instant_trace_file)


def update_reliability_values(instant_temperatures, delta_t):
    # Update the reliability values of the cores.
    # Wearout is calculated using on the temperatures in the file
    # `instant_temperatures` (in celsius) over the time period `delta_t` (in
    # seconds)

    # Setup call to reliability binary `reliability_external`.
    delta_t_ms = delta_t/1e12
    temperature_filename = os.path.join(output_dir, instant_temperatures)

    reliability_cmd = "{} {} {} {} {} {}".format(
            reliability_exec, delta_t_ms, temperature_filename,
            sum_file, instant_trace_file, acceleration_factor)

    print("DEBUG: executing: {}".format(reliability_cmd))
    os.system(reliability_cmd)

    # Copy current rvalues to periodic log.
    with open(instant_trace_file) as current_rval:
        current_rval.readline()  # Skip header
        with open(periodic_trace_file, 'a') as rvalues:
            rvalues.write(current_rval.readline())
