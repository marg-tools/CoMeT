"""
memTherm.py

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
#_enable = 1
#_disable = 0
#_WIO = 1
#_HMC = 0
#_2D = 2
#is_2_5d = sim.config.get_bool('mem3D/is_2_5d')
type_of_stack = sim.config.get('mem3D/type_of_stack')

# Core Floorplan info
cores_in_x = int(sim.config.get('mem3D/cores_in_x'))
cores_in_y = int(sim.config.get('mem3D/cores_in_y'))
#core_printing_pattern = [6,3,5,1,4,0,7,2]
#core_printing_pattern = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
# core_printing_pattern = [0]

# Logic Floorplan info (only for HMC)
logic_cores_in_x = int(sim.config.get('mem3D/logic_cores_in_x'))
logic_cores_in_y = int(sim.config.get('mem3D/logic_cores_in_y'))
#logic_printing_pattern = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
#logic_avg_power = float(sys.argv[7]) # 0.448 * 0.8 * percentBW

# Bank Floorplan info
number_of_banks = NUM_BANKS
banks_in_x = int(sim.config.get('mem3D/banks_in_x'))
banks_in_y = int(sim.config.get('mem3D/banks_in_y'))
banks_in_z = int(sim.config.get('mem3D/banks_in_z'))
#banks_in_z = number_of_banks/banks_in_x/banks_in_y  
#banks_in_z = 2
#bank_printing_pattern = [6,3,5,1,4,0,7,2]
#bank_printing_pattern = [] 

# generate some variables according to the 3D memory architecture used
if type_of_stack== "_WIO":
    mem_name = "WIO/"
if type_of_stack== "_HMC" or type_of_stack=="_2_5D":
    mem_name = "HMC/"
if type_of_stack== "_2D":
    mem_name = "2D/"

#for bnk in range(number_of_banks):
#    bank_printing_pattern.append(bnk)

if (sim.config.get('hotspot/hotspot_test_dir') == 'default'):
    if type_of_stack== "_2D":
        hotspot_test_dir    =   "hotspot/test" + "0" + "/" + mem_name 
    else:
        if type_of_stack== "_2_5D":
            hotspot_test_dir    =   "hotspot/test_2_5_D" + str(banks_in_z) + "/" + mem_name 
        else:
            hotspot_test_dir    =   "hotspot/test" + str(banks_in_z) + "/" + mem_name 
else:
    hotspot_test_dir = sim.config.get('hotspot/hotspot_test_dir')

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
#Generate power trace using access trace from sniper in a periodic manner (for memories).
#The power trace of core is generated through the mcpat script.
#The power trace of core is combined with memory power trace for WIO and 2.5D architectures, else used separately in another hotspot run
#Invoke hotspot to generate temperature trace for the corresponding power trace. 
#The generated transient temperature trace (all_transient_file) is used as an init file for the next iteration

hotspot_command = executable  \
                  + ' -f ' + hotspot_floorplan_file \
                  + ' -c ' + hotspot_config_file \
                  + ' -init_file ' + init_file \
                  + ' -p ' + power_trace_file \
                  + ' -o ' + temperature_trace_file \
                  + ' -model_secondary 1 -model_type grid ' \
                  + ' -steady_file ' + hotspot_steady_temp_file \
                  + ' -all_transient_file ' + hotspot_all_transient_file \
                  + ' -grid_steady_file ' + hotspot_grid_steady_file \
                  + ' -steady_state_print_disable 1 ' \
                  + ' -l 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, ' \
                  + ' -memory_type ' + type_of_stack \
                  #+ ' -sampling_intvl ' + sampling_interval 

#if type_of_stack!="_2D":
hotspot_command = hotspot_command + ' -grid_layer_file ' + hotspot_layer_file \
                        +' -detailed_3D on'
print hotspot_command                  

c_hotspot_config_path = sim.config.get('hotspot_c/config_path') 
c_init_file_external = c_hotspot_config_path + "/hotspot/" + sim.config.get('hotspot_c/init_file_external')
c_init_file = sim.config.get('hotspot_c/init_file')

#initialization and setting up files
os.system("echo copying files for first run")
os.system("ls -l " + init_file_external)
os.system("cp " + init_file_external + " " + init_file)
os.system("ls -l " + c_init_file_external)
os.system("cp " + c_init_file_external + " " + c_init_file)
os.system('mkdir -p hotspot')
os.system("cp -r " + hotspot_floorplan_folder + " " + './hotspot')
os.system("rm -f " + full_temperature_trace_file)
os.system("rm -f " + full_power_trace_file)

#generates ptrace header as per the memory floorplan and architecture
#2D:    B0_0 B0_1 ... B3_3
#HMC:   LC0_0 LC0_1 ... LC3_3 (logic core), B0_0 B0_1 ... B3_3 (layer0),  B0_0 B0_1 ... B3_3 (layer1), ...
#WIO:   B0_0 B0_1 ... B3_3 (layer0),  B0_0 B0_1 ... B3_3 (layer1), ..., C0_0 C0_1 ... C3_3 (top layer core)
#2.5D   C0_0 C0_1 ... C3_3 (core part), LC0_0 LC0_1 ... LC3_3 (logic core base), X1, X2, X3, B0_0 B0_1 ... B3_3, X0, X1, X2, X3 (layer0),  B0_0 B0_1 ... B3_3, X0, X1, X2, X3 (layer1), ...
def gen_ptrace_header():
    # For a 2by1 ptrace with four layers header should be B0_0    B0_1    B0_0    B0_1    B0_0    B0_1    B0_0    B0_1
    # For WIO: core is at the top, whereas for HMC, 2.5D config. the HMC is at the bottom.
    # Creating Header
    ptrace_header = ''
    if type_of_stack=="_2_5D":
        # ptrace_header=ptrace_header + "I0" + "\t" 
        for x in range(0,cores_in_x):
            for y in range(0,cores_in_y):
                ptrace_header=ptrace_header + "C" + str(x) + "_" + str(y) + "\t" 
    
    if type_of_stack== "_HMC" or type_of_stack== "_2_5D":
        for x in range(0,logic_cores_in_x):
            for y in range(0,logic_cores_in_y):
                ptrace_header=ptrace_header + "LC" + str(x) + "_" + str(y) + "\t" 
    
    if type_of_stack=="_2_5D":
        for x in range(1,4):
            ptrace_header=ptrace_header + "X" + str(x) + "\t" 
                
    for z in range(0,banks_in_z):
        for x in range(0,banks_in_x):
            for y in range(0,banks_in_y):
                    #                atrace_header=atrace_header + "B" + str(x) + "_" + str(y) + "\t" 
                #if type_of_stack== "_WIO" or type_of_stack== "_HMC" or type_of_stack=="_2D":
                ptrace_header=ptrace_header + "B" + str(x) + "_" + str(y) + "\t" 
        if type_of_stack=="_2_5D":
            for x in range(0,4):
                ptrace_header=ptrace_header + "X" + str(x) + "\t" 
    
    if type_of_stack=="_WIO":
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
    stat_write = 'dram.bank_write_access_counter'       #from sniper C-code
    stat_read = 'dram.bank_read_access_counter'       #from sniper C-code
    self.stat_name_read = stat_read
    self.stat_name_write = stat_write
    stat_component_rd, stat_name_read = stat_read.rsplit('.', 1)
    stat_component_wr, stat_name_write = stat_write.rsplit('.', 1)

    if filename:
      self.fd = file(os.path.join(sim.config.output_dir, filename), 'w')
      self.isTerminal = False
    else:
      self.fd = sys.stdout
      self.isTerminal = True
    #create an instance for core power computation
    self.ES = EnergyStats()

    self.sd = sim.util.StatsDelta()
    self.stats = {
      'time': [ self.getStatsGetter('performance_model', core, 'elapsed_time') for core in range(sim.config.ncores) ],
      'ffwd_time': [ self.getStatsGetter('fastforward_performance_model', core, 'fastforwarded_time') for core in range(sim.config.ncores) ],
      'stat_rd': [ self.getStatsGetter(stat_component_rd, core, stat_name_read) for core in range(NUM_BANKS) ],
      'stat_wr': [ self.getStatsGetter(stat_component_wr, core, stat_name_write) for core in range(NUM_BANKS) ],
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

    #cleanup older log files
    c_full_power_trace_file = sim.config.get('hotspot_c/full_power_trace_file')
    c_full_temperature_trace_file = sim.config.get('hotspot_c/full_temperature_trace_file')
    os.system("rm -f " + c_full_power_trace_file)
    os.system("rm -f " + c_full_temperature_trace_file)

   #return access rates of various memory banks
  def get_access_rates(self, time, time_delta):
    if self.isTerminal:
      self.fd.write('[STAT:%s] ' % self.stat_name_read)
      self.fd.write('[STAT:%s] ' % self.stat_name_write)
#    self.fd.write('%u' % (time / 1e6)) # Time in ns
    access_rates = [0 for number in xrange(NUM_BANKS)]
    #print self.stats['stat'][0].__dict__	#prints the fields of the object
    for bank in range(NUM_BANKS):
      statdiff_wr = self.stats['stat_wr'][bank].last
      statdiff_rd = self.stats['stat_rd'][bank].last
      access_rates[bank] = statdiff_rd + statdiff_wr
      value = statdiff_wr + statdiff_rd
      self.fd.write(' %u' % value)
    self.fd.write('\n')
#    print access_rates
    return access_rates

    # calculate power trace using access rate and other parameters
  def calc_power_trace(self, time, time_delta):
    accesses = self.get_access_rates(time, time_delta)
#    print accesses
    avg_no_refresh_intervals_in_timestep =  timestep/t_refi                                                     # 20/7.8 = 2.56 refreshes on an average 
    avg_no_refresh_rows_in_timestep = avg_no_refresh_intervals_in_timestep * rows_refreshed_in_refresh_interval # 2.56*8 rows refreshed = 20.48 refreshes 
    refresh_energy_in_timestep =  avg_no_refresh_rows_in_timestep * energy_per_refresh_access                   # 20.48 * 100 nJ = 2048 nJ, 100 nJ (say) is the energy per refresh access
    avg_refresh_power = refresh_energy_in_timestep/(timestep*1000)
    bank_power_trace = [0 for number in xrange(NUM_BANKS)]
     #total power = access_count*energy per access + leakage power + refresh power
    #calculate bank power for each bank using access traces
    for bank in range(NUM_BANKS):
      bank_power_trace[bank] = (accesses[bank] * energy_per_access)/(timestep*1000) + bank_static_power + avg_refresh_power
      bank_power_trace[bank] = round(bank_power_trace[bank], 3)
    logic_power_trace = ''
    #create logic_core power array. applicable only for HMC and 2.5D memory
    if (type_of_stack=="_2_5D" or type_of_stack=="_HMC"):
        logic_power_trace = [logic_core_power for number in xrange(NUM_LC)]
    power_trace = ''
    # convert power trace into a concatenated string for formated output
    #for 2.5D, read the core power from the core power trace file and include in the total power trace
    if (type_of_stack == "_2_5D"):
        c_power_trace_file = sim.config.get('hotspot_c/power_trace_file')
        with open(c_power_trace_file, 'r') as power_file:
            power_file.readline()  # ignore first line that contains the header
            c_power_data=power_file.readline()  # ignore first line that contains the header
        power_file.close()
        power_trace = power_trace + c_power_data 
    #print logic power trace to the main power_trace
    for p in logic_power_trace:
        power_trace = power_trace + str(p) + '\t'
    #add X1, X2, X3 to the power trace for 2.5D
    if (type_of_stack == "_2_5D"):
        for x in range(1,4):
            power_trace = power_trace + str(0.00) + '\t'
     #add bank power into the main power trace
    for bank in range(len(bank_power_trace)):
            #add 0 power for X0, X1, X2, X3 for 2.5D
        if (type_of_stack == "_2_5D" and bank%(banks_in_x*banks_in_y)==0 and bank>0):
            power_trace = power_trace + str(0.00) + '\t'
            power_trace = power_trace + str(0.00) + '\t'
            power_trace = power_trace + str(0.00) + '\t'
            power_trace = power_trace + str(0.00) + '\t'
        #add bank power trace for all type of memories
        power_trace = power_trace + str(bank_power_trace[bank]) + '\t'
    #add 0 power for X0, X1, X2, X3 for 2.5D at last
    if (type_of_stack == "_2_5D"):
        for x in range(0,4):
            power_trace = power_trace + str(0.00) + '\t'
    c_power_data = ""
      #read core power and add to main power trace at last for WIO
    if (type_of_stack == "_WIO"):
        c_power_trace_file = sim.config.get('hotspot_c/power_trace_file')
        with open(c_power_trace_file, 'r') as power_file:
            power_file.readline()  # ignore first line that contains the header
            c_power_data=power_file.readline()  # ignore first line that contains the header
        power_file.close()
        #print c_power_data

    power_trace = power_trace + c_power_data + "\r\n"
    ptrace_header = gen_ptrace_header()
   #write power information into the trace file for use by hotspot
    with open("%s" %(power_trace_file), "w") as f:
        f.write("%s\n" %(ptrace_header))
        f.write("%s" %(power_trace))
    f.close()
    return power_trace

  def execute_core_hotspot(self):
     #the function to execute core hotspot separately. It is called only for HMC and 2D arch.
    c_full_power_trace_file = sim.config.get('hotspot_c/full_power_trace_file')
    c_power_trace_file = sim.config.get('hotspot_c/power_trace_file')
    c_full_temperature_trace_file = sim.config.get('hotspot_c/full_temperature_trace_file')
    c_temperature_trace_file = sim.config.get('hotspot_c/temperature_trace_file')
    c_hotspot_path = sim.config.get('hotspot_c/tool_path')
    c_hotspot_config_path = sim.config.get('hotspot_c/config_path') 
    c_executable = c_hotspot_path + 'hotspot'
    c_init_file_external = c_hotspot_config_path + "/hotspot/" + sim.config.get('hotspot_c/init_file_external')
    c_init_file = sim.config.get('hotspot_c/init_file')
    
    c_hotspot_config_file      =   c_hotspot_config_path + "/hotspot/" + sim.config.get('hotspot_c/hotspot_config_file')
    c_hotspot_floorplan_file   =   sim.config.get('hotspot_c/hotspot_floorplan_file')
    c_hotspot_floorplan_folder   = c_hotspot_config_path + sim.config.get('hotspot_c/hotspot_floorplan_folder')
 #  hotspot_steady_temp_file = config.get('hotspot_c/hotspot_steady_temp_file')
 #  hotspot_grid_steady_file = config.get('hotspot_c/hotspot_grid_steady_file')
 #  hotspot_all_transient_file = config.get('hotspot_c/all_transient_file')

    sampling_interval = int(sim.config.get('hotspot_c/sampling_interval'))    #time in ns

    c_powerLogFileName = file(c_full_power_trace_file, 'a');
    #c_powerInstantaneousFileName = file(c_power_trace_file, 'r');
    if (sim.config.get("core_thermal/enabled") == 'true'):
     c_thermalLogFileName = file(c_full_temperature_trace_file, 'a');
    
    needInitializing = os.stat(c_full_power_trace_file).st_size == 0
    if (sim.config.get("core_thermal/enabled") == 'true'):
     c_interval_s = sampling_interval * 1e-9

     c_hotspot_binary = c_executable
     c_hotspot_args = c_executable  \
                    + ' -c '+ c_hotspot_config_file \
                    + ' -f ' + c_hotspot_floorplan_file \
                    + ' -sampling_intvl ' + str(c_interval_s) \
                    + ' -p ' + c_power_trace_file \
                    + ' -o ' + c_temperature_trace_file
     if not needInitializing:
         c_hotspot_args += ' -init_file ' + c_init_file

     #print hotspot_binary, hotspot_args
#     c_temperatures = subprocess.check_output([hotspot_binary] + hotspot_args)
     print c_hotspot_args
     os.system(c_hotspot_args + "> tmp")
     os.system("cp -f tmp " + c_init_file)

     with open(c_temperature_trace_file, 'r') as instTemperatureFile:
       instTemperatureFile.readline()  # ignore first line that contains the header
       c_thermalLogFileName.write(instTemperatureFile.readline())
     c_thermalLogFileName.close()
          

  #def combine_power_traces(self):


  # invokes hotspot to generate the temperature trace
  def calc_temperature_trace(self, time, time_delta):
#   print power_trace
    #invoke energystats function to compute core power trace
    self.ES.periodic(time, time_delta)
    #execute hotspot separately for core in case of HMC and 2D memories
    if (sim.config.get("core_thermal/enabled") == 'true' and (type_of_stack=="_HMC" or type_of_stack=="_2D")):
        self.execute_core_hotspot()
     #calculate memory power trace (combines with core trace in case of WIO and 2.5D within function)
    self.calc_power_trace(time, time_delta)
     #invoke the memory hotspot. It will include core parts automatically for WIO and 2.5D
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

      
def build_dvfs_table(tech):
  # Build a table of (frequency, voltage) pairs.
  # Frequencies should be from high to low, and end with zero (or the lowest possible frequency)
  if tech <= 22:
    # Even technology nodes smaller than 22nm should use the DVFS levels of 22nm.
    # This is the voltage reported to McPAT.
    # McPAT does not support technology nodes smaller than 22nm and is operated at 22nm.
    # The scaling is then done in tools/mcpat.py.
    def v(f):
      return 0.6 + f / 4000.0 * 0.8
    return [ (f, v(f))  for f in reversed(range(0, 4000+1, 100))]
  elif tech == 45:
    return [ (2000, 1.2), (1800, 1.1), (1500, 1.0), (1000, 0.9), (0, 0.8) ]
  else:
    raise ValueError('No DVFS table available for %d nm technology node' % tech)

class EnergyStats:
  def __init__(self):
    #args = dict(enumerate((args or '').split(':')))
    #interval_ns = long(args.get(0, None) or 1000000) # Default power update every 1 ms
    #sim.util.Every(interval_ns * sim.util.Time.NS, self.periodic, roi_only = True)
    self.dvfs_table = build_dvfs_table(int(sim.config.get('power/technology_node')))
    #
    self.name_last = None
    #initializing time_last_power to a small value to avoid skipping of first power calculation
    self.time_last_power = -1 * sim.util.Time.NS        
    self.time_last_energy = 0
    self.in_stats_write = False
    self.power = {}
    self.energy = {}
    self.update()       #call the update function once dummy during init to preset various variables

  def periodic(self, time, time_delta):
    self.update()

  def hook_pre_stat_write(self, prefix):
    if not self.in_stats_write:
      self.update()

  def hook_sim_end(self):
    if self.name_last:
      sim.util.db_delete(self.name_last, True)

  def update(self):
    if sim.stats.time() == self.time_last_power:
      # Time did not advance: don't recompute
      return
    if not self.power or (sim.stats.time() - self.time_last_power >= 10 * sim.util.Time.US):
      # Time advanced significantly, or no power result yet: compute power
      #   Save snapshot
      current = 'energystats-temp%s' % ('B' if self.name_last and self.name_last[-1] == 'A' else 'A')
      self.in_stats_write = True
      sim.stats.write(current)
      self.in_stats_write = False
      #   If we also have a previous snapshot: update power
      if self.name_last:
        power = self.run_power(self.name_last, current)
        #self.update_power(power)
      #   Clean up previous last
      if self.name_last:
        sim.util.db_delete(self.name_last)
      #   Update new last
      self.name_last = current
      self.time_last_power = sim.stats.time()
    # Increment energy
    #self.update_energy()

  def get_vdd_from_freq(self, f):
    # Assume self.dvfs_table is sorted from highest frequency to lowest
    for _f, _v in self.dvfs_table:
      if f >= _f:
        return _v
    assert ValueError('Could not find a Vdd for invalid frequency %f' % f)

  def gen_config(self, outputbase):
    freq = [ sim.dvfs.get_frequency(core) for core in range(sim.config.ncores) ]
    vdd = [ self.get_vdd_from_freq(f) for f in freq ]
    configfile = outputbase+'.cfg'
    cfg = open(configfile, 'w')
    cfg.write('''
[perf_model/core]
frequency[] = %s
[power]
vdd[] = %s
    ''' % (','.join(map(lambda f: '%f' % (f / 1000.), freq)), ','.join(map(str, vdd))))
    cfg.close()
    return configfile

  def run_power(self, name0, name1):
    outputbase = os.path.join(sim.config.output_dir, 'energystats-temp')

    configfile = self.gen_config(outputbase)

    os.system('unset PYTHONHOME; %s -d %s -o %s -c %s --partial=%s:%s --no-graph --no-text' % (
      os.path.join(os.getenv('SNIPER_ROOT'), 'tools/mcpat.py'),
      sim.config.output_dir,
      outputbase,
      configfile,
      name0, name1
    ))

    result = {}
    execfile(outputbase + '.py', {}, result)
    return result['power']

sim.util.register(memTherm())
