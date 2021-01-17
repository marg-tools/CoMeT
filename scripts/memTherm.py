"""
memTherm.py

Write a trace of deltas for an arbitrary statistic.
First argument is the name of the statistic (<component-name>[.<subcomponent>].<stat-name>)
Second argument is either a filename, or none to write to standard output
Third argument is the interval size in nanoseconds (default is 10000)
"""

import sys, os, sim

NUM_BANKS=int(sim.config.get('mem3D/num_banks'))
NUM_LC=int(sim.config.get('mem3D/num_lc'))

bank_size=int(sim.config.get('mem3D/bank_size'))
no_columns = 1                                      # in Kilo
no_bits_per_column = 8                              # 8 bits per column. Hence 8Kb row buffer.
no_rows= bank_size/no_columns/no_bits_per_column    # in Kilo, number of rows per bank
energy_per_access = float(sim.config.get('mem3D/energy_per_access'))
logic_core_power = float(sim.config.get('mem3D/logic_core_power'))
energy_per_refresh_access = float(sim.config.get('mem3D/energy_per_refresh_access'))
sampling_interval = int(sim.config.get('hotspot/sampling_interval'))    #time in ns
timestep = sampling_interval/1000                       # in uS. Should be in sync with hotspot.config (sampling_intvl)
t_refi = float(sim.config.get('mem3D/t_refi'))
no_refesh_commands_in_t_refw = int(sim.config.get('mem3D/no_refesh_commands_in_t_refw'))
rows_refreshed_in_refresh_interval = no_rows/no_refesh_commands_in_t_refw  # for 512Mb bank, 8 rows per refresh => for 64Mb bank, 1 rows per refresh
bank_static_power = 0

#define constants
_enable = 1
_disable = 0
_WIO = 1
_HMC = 0
_2D = 2
is_2_5d = 0
type_of_stack = _HMC

# Core Floorplan info
cores_in_x = 4 
cores_in_y = 4 
#core_printing_pattern = [6,3,5,1,4,0,7,2]
core_printing_pattern = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
# core_printing_pattern = [0]
error_peak_power = 50
error_default_power = 7.12345 

# Logic Floorplan info (only for HMC)
logic_cores_in_x = 4 
logic_cores_in_y = 4 
logic_printing_pattern = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
#logic_avg_power = float(sys.argv[7]) # 0.448 * 0.8 * percentBW

# Bank Floorplan info
number_of_banks = NUM_BANKS
banks_in_x = int(sim.config.get('mem3D/banks_in_x'))
banks_in_y = int(sim.config.get('mem3D/banks_in_y'))
banks_in_z = number_of_banks/banks_in_x/banks_in_y  
#banks_in_z = 2
#bank_printing_pattern = [6,3,5,1,4,0,7,2]
bank_printing_pattern = [] 

# generate some variables according to the 3D memory architecture used
if type_of_stack== _WIO:
    mem_name = "WIO/"
if type_of_stack== _HMC:
    mem_name = "HMC/"
if type_of_stack== _2D:
    mem_name = "2D/"

for bnk in range(number_of_banks):
    bank_printing_pattern.append(bnk)

if type_of_stack== _2D:
    hotspot_test_dir    =   "hotspot/test" + "0" + "/" + mem_name 
else:
    if is_2_5d== _disable:
        hotspot_test_dir    =   "hotspot/test" + str(banks_in_z) + "/" + mem_name 
    else:
        hotspot_test_dir    =   "hotspot/test_2_5_D" + str(banks_in_z) + "/" + mem_name 

#hotspot integration starts
#parse various settings from the config file and assign to local variables
hotspot_path = sim.config.get('hotspot/tool_path')
hotspot_config_path = sim.config.get('hotspot/config_path') 
executable = hotspot_path + 'hotspot'
power_trace_file = sim.config.get('hotspot/power_trace_file')
full_power_trace_file = sim.config.get('hotspot/full_power_trace_file')
temperature_trace_file = sim.config.get('hotspot/temperature_trace_file')
full_temperature_trace_file = sim.config.get('hotspot/full_temperature_trace_file')
init_file_external = hotspot_config_path + hotspot_test_dir + sim.config.get('hotspot/init_file_external')
init_file = sim.config.get('hotspot/init_file')

hotspot_config_file      =   hotspot_config_path + hotspot_test_dir  + sim.config.get('hotspot/hotspot_config_file')
hotspot_floorplan_file   =   sim.config.get('hotspot/hotspot_floorplan_file')
hotspot_floorplan_folder   = hotspot_config_path + sim.config.get('hotspot/hotspot_floorplan_folder')
hotspot_layer_file  =   hotspot_config_path + hotspot_test_dir  + sim.config.get('hotspot/hotspot_layer_file')

# Output Parameters for hotspot simulation
hotspot_steady_temp_file = sim.config.get('hotspot/hotspot_steady_temp_file')
hotspot_grid_steady_file = sim.config.get('hotspot/hotspot_grid_steady_file')
hotspot_all_transient_file = sim.config.get('hotspot/all_transient_file')

#Basic idea of the flow is:
#Generate power trace using access trace from sniper in a periodic manner.
#Invoke hotspot to generate temperature trace for the corresponding power trace. 
#The generated transient temperature trace (all_transient_file) is used as an init file for the next iteration

hotspot_command = executable  \
                  + ' -f ' + hotspot_floorplan_file \
                  + ' -c ' + hotspot_config_file \
                  + ' -init_file ' + init_file \
                  + ' -p ' + power_trace_file \
                  + ' -o ' + temperature_trace_file \
                  + ' -model_secondary 1 -model_type grid -detailed_3D on' \
                  + ' -grid_layer_file ' + hotspot_layer_file \
                  + ' -steady_file ' + hotspot_steady_temp_file \
                  + ' -all_transient_file ' + hotspot_all_transient_file \
                  + ' -grid_steady_file ' + hotspot_grid_steady_file \
                  + ' -steady_state_print_disable 1 ' \
                  + ' -l 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, ' \
                  # + ' -sampling_intvl ' + sampling_interval \
print hotspot_command                  

os.system("echo copying files for first run")
os.system("ls -l " + init_file_external)
os.system("cp " + init_file_external + " " + init_file)
os.system('mkdir -p hotspot')
os.system("cp -r " + hotspot_floorplan_folder + " " + './hotspot')
os.system("rm -f " + full_temperature_trace_file)
os.system("rm -f " + full_power_trace_file)

#generates ptrace header as per the memory floorplan and architecture
def gen_ptrace_header():
    # For a 2by1 ptrace with four layers header should be B0_0    B0_1    B0_0    B0_1    B0_0    B0_1    B0_0    B0_1
    # For WIO: core is at the top, whereas for HMC, 2.5D config. the HMC is at the bottom.
    # Creating Header
    ptrace_header = ''
    if is_2_5d==_enable:
        # ptrace_header=ptrace_header + "I0" + "\t" 
        for x in range(0,cores_in_x):
            for y in range(0,cores_in_y):
                ptrace_header=ptrace_header + "C" + str(x) + "_" + str(y) + "\t" 
    
    if type_of_stack== _HMC:
        for x in range(0,logic_cores_in_x):
            for y in range(0,logic_cores_in_y):
                ptrace_header=ptrace_header + "LC" + str(x) + "_" + str(y) + "\t" 
    
    if is_2_5d==_enable:
        for x in range(1,4):
            ptrace_header=ptrace_header + "X" + str(x) + "\t" 
                
    for z in range(0,banks_in_z):
        for x in range(0,banks_in_x):
            for y in range(0,banks_in_y):
                    #                atrace_header=atrace_header + "B" + str(x) + "_" + str(y) + "\t" 
                if type_of_stack== _WIO or type_of_stack== _HMC:
                    ptrace_header=ptrace_header + "B" + str(x) + "_" + str(y) + "\t" 
        if is_2_5d==_enable:
            for x in range(0,4):
                ptrace_header=ptrace_header + "X" + str(x) + "\t" 
    
    if type_of_stack==_WIO or type_of_stack ==_2D:
        for x in range(0,cores_in_x):
            for y in range(0,cores_in_y):
                ptrace_header=ptrace_header + "C" + str(x) + "_" + str(y) + "\t" 
    with open("%s" %(power_trace_file), "w") as f:
        f.write("%s\n" %(ptrace_header))
    f.close()
    return ptrace_header
    

#The main portion which invokes hotspot to generate temperature.trace
class memTherm:
  def setup(self, args):
    args = dict(enumerate((args or '').split(':')))
    filename = args.get(1, None)
    interval_ns = sampling_interval
    # print interval_ns 
    stat = 'dram.bank_access_counter'       #from sniper C-code
    self.stat_name = stat
    stat_component, stat_name = stat.rsplit('.', 1)

    if filename:
      self.fd = file(os.path.join(sim.config.output_dir, filename), 'w')
      self.isTerminal = False
    else:
      self.fd = sys.stdout
      self.isTerminal = True

    self.sd = sim.util.StatsDelta()
    self.stats = {
      'time': [ self.getStatsGetter('performance_model', core, 'elapsed_time') for core in range(sim.config.ncores) ],
      'ffwd_time': [ self.getStatsGetter('fastforward_performance_model', core, 'fastforwarded_time') for core in range(sim.config.ncores) ],
      'stat': [ self.getStatsGetter(stat_component, core, stat_name) for core in range(NUM_BANKS) ],
    }
    #print the initial header into different log/trace files
    gen_ptrace_header()
    ptrace_header = gen_ptrace_header()
    with open(full_temperature_trace_file, "w") as f:
        f.write("%s\n" %(ptrace_header))
    f.close()
    with open(full_power_trace_file, "w") as f:
        f.write("%s\n" %(ptrace_header))
    f.close()
    #setup to invoke the hotspot tool every interval_ns time and invoke calc_temperature_trace function
    sim.util.Every(interval_ns * sim.util.Time.NS, self.calc_temperature_trace, statsdelta = self.sd, roi_only = True)

    #return access rates of various memory banks
  def periodic(self, time, time_delta):
    if self.isTerminal:
      self.fd.write('[STAT:%s] ' % self.stat_name)
#    self.fd.write('%u' % (time / 1e6)) # Time in ns
    access_rates = [0 for number in xrange(NUM_BANKS)]
    #print self.stats['stat'][0].__dict__	#prints the fields of the object
    for bank in range(NUM_BANKS):
      statdiff = self.stats['stat'][bank].last
      access_rates[bank] = statdiff
      value = statdiff 
      self.fd.write(' %u' % value)
    self.fd.write('\n')
#    print access_rates
    return access_rates

    # calculate power trace using access rate and other parameters
  def calc_power_trace(self, time, time_delta):
    accesses = self.periodic(time, time_delta)
#    print accesses
    avg_no_refresh_intervals_in_timestep =  timestep/t_refi                                                     # 20/7.8 = 2.56 refreshes on an average 
    avg_no_refresh_rows_in_timestep = avg_no_refresh_intervals_in_timestep * rows_refreshed_in_refresh_interval # 2.56*8 rows refreshed = 20.48 refreshes 
    refresh_energy_in_timestep =  avg_no_refresh_rows_in_timestep * energy_per_refresh_access                   # 20.48 * 100 nJ = 2048 nJ, 100 nJ (say) is the energy per refresh access
    avg_refresh_power = refresh_energy_in_timestep/(timestep*1000)
    bank_power_trace = [0 for number in xrange(NUM_BANKS)]
     #total power = access_count*energy per access + leakage power + refresh power
    for bank in range(NUM_BANKS):
      bank_power_trace[bank] = (accesses[bank] * energy_per_access)/(timestep*1000) + bank_static_power + avg_refresh_power
      bank_power_trace[bank] = round(bank_power_trace[bank], 3)
    logic_power_trace = [logic_core_power for number in xrange(NUM_LC)]
    power_trace = ''
    # convert power trace into a concatenated string for formated output
    for p in logic_power_trace:
        power_trace = power_trace + str(p) + '\t'
    for p in bank_power_trace:
        power_trace = power_trace + str(p) + '\t'
    power_trace = power_trace + "\r\n"
    ptrace_header = gen_ptrace_header()
###Needs fixing. currently adding new lines to the older power trace. However, init of previous runs should be done and used for the next iteration
   #write power information into the trace file for use by hotspot
    with open("%s" %(power_trace_file), "w") as f:
        f.write("%s\n" %(ptrace_header))
#    with open("%s" %(power_trace_file), "a") as f:
        f.write("%s" %(power_trace))
    f.close()
    return power_trace

  # invokes hotspot to generate the temperature trace
  def calc_temperature_trace(self, time, time_delta):
#   print power_trace
    self.calc_power_trace(time, time_delta)
    os.system(hotspot_command)
      #concatenate the per interval temperatuer trace into a single file
    os.system("cp " + hotspot_all_transient_file + " " + init_file)
    os.system("tail -1 " + temperature_trace_file + ">>" + full_temperature_trace_file)
    os.system("tail -1 " + power_trace_file + " >>" + full_power_trace_file)


  def getStatsGetter(self, component, core, metric):
    # Some components don't exist (i.e. DRAM reads on cores that don't have a DRAM controller),
    # return a special object that always returns 0 in these cases
    try:
      return self.sd.getter(component, core, metric)
    except:
      class Zero():
        def __init__(self): self.delta = 0
        def update(self): pass
      return Zero()

sim.util.register(memTherm())
