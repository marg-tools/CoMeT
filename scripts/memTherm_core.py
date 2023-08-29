"""
memTherm_core.py

"""

import sys, os, sim
import reliability as rlb

LOW_POWER = 0
NORMAL_POWER = 1

bank_size=int(sim.config.get('memory/bank_size'))
no_columns = 1                                      # in Kilo
no_bits_per_column = 8                              # 8 bits per column. Hence 8Kb row buffer.
no_rows= bank_size/no_columns/no_bits_per_column    # in Kilo, number of rows per bank
energy_per_read_access = float(sim.config.get('memory/energy_per_read_access'))
energy_per_write_access = float(sim.config.get('memory/energy_per_write_access'))
logic_core_power = float(sim.config.get('memory/logic_core_power'))
energy_per_refresh_access = float(sim.config.get('memory/energy_per_refresh_access'))
sampling_interval = int(sim.config.get('hotspot/sampling_interval'))    #time in ns
interval_sec = sampling_interval * 1e-9
timestep = sampling_interval/1000                       # in uS. Should be in sync with hotspot.config (sampling_intvl)
t_refi = float(sim.config.get('memory/t_refi'))
no_refesh_commands_in_t_refw = int(sim.config.get('memory/no_refesh_commands_in_t_refw'))
rows_refreshed_in_refresh_interval = no_rows/no_refesh_commands_in_t_refw  # for 512Mb bank, 8 rows per refresh => for 64Mb bank, 1 rows per refresh
bank_static_power = 0
core_thermal_enabled = sim.config.get("core_thermal/enabled")

mem_dtm = sim.config.get('scheduler/open/dram/dtm')
lpm_dynamic_power = float(sim.config.get('perf_model/dram/lowpower/lpm_dynamic_power'))
lpm_leakage_power = float(sim.config.get('perf_model/dram/lowpower/lpm_leakage_power'))

core_frequency_min = float(sim.config.get('perf_model/core/min_frequency'))*1000
core_frequency_max = float(sim.config.get('perf_model/core/max_frequency'))*1000
core_frequency_step = float(sim.config.get('perf_model/core/frequency_step_size'))*1000

#define constants
#_enable = 1
#_disable = 0
#_WIO = 1
#_HMC = 0
#_2D = 2
#is_2_5d = sim.config.get_bool('memory/is_2_5d')
type_of_stack = sim.config.get('memory/type_of_stack')

# Core Floorplan info
cores_in_x = int(sim.config.get('memory/cores_in_x'))
cores_in_y = int(sim.config.get('memory/cores_in_y'))
cores_in_z = int(sim.config.get('memory/cores_in_z'))
NUM_CORES=int(sim.config.get('general/total_cores'))
#core_printing_pattern = [6,3,5,1,4,0,7,2]
#core_printing_pattern = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
# core_printing_pattern = [0]

# Bank Floorplan info
banks_in_x = int(sim.config.get('memory/banks_in_x'))
banks_in_y = int(sim.config.get('memory/banks_in_y'))
banks_in_z = int(sim.config.get('memory/banks_in_z'))
NUM_BANKS=int(sim.config.get('memory/num_banks'))
#number_of_banks = NUM_BANKS
#banks_in_z = number_of_banks/banks_in_x/banks_in_y  
#banks_in_z = 2
#bank_printing_pattern = [6,3,5,1,4,0,7,2]
#bank_printing_pattern = [] 

# Logic Floorplan info (only for 3Dmem)
logic_cores_in_x = banks_in_x
logic_cores_in_y = banks_in_y
NUM_LC = logic_cores_in_x * logic_cores_in_y


# generate some variables according to the 3D memory architecture used
#if type_of_stack== "3D":
#    mem_name = "3D/"
#if type_of_stack== "3Dmem" or type_of_stack=="2.5D":
#    mem_name = "3Dmem/"
#if type_of_stack== "DDR":
#    mem_name = "DDR/"
#
#for bnk in range(number_of_banks):
#    bank_printing_pattern.append(bnk)

#if (sim.config.get('hotspot/hotspot_test_dir') == 'default'):
#    if type_of_stack== "DDR":
#        hotspot_test_dir    =   "hotspot/test" + "0" + "/" + mem_name 
#    else:
#        if type_of_stack== "2.5D":
#            hotspot_test_dir    =   "hotspot/test_2_5_D" + str(banks_in_z) + "/" + mem_name 
#        else:
#            hotspot_test_dir    =   "hotspot/test" + str(banks_in_z) + "/" + mem_name 
#else:
#    hotspot_test_dir = sim.config.get('hotspot/hotspot_test_dir')

#hotspot integration starts
#parse various settings from the config file and assign to local variables
#hotspot_path = sim.config.get('hotspot/tool_path')
#hotspot_config_path = sim.config.get('hotspot/config_path') 
hotspot_path = os.path.join(os.getenv('SNIPER_ROOT'), sim.config.get('hotspot/tool_path'))
executable = hotspot_path + 'hotspot'

hotspot_config_path = os.getenv('SNIPER_ROOT') + '/' 
#hotspot_config_path = os.path.join(os.getenv('SNIPER_ROOT'), "/") 
if sim.config.get('hotspot/init_file_external_mem') == "None":
    init_file_external = "None"
else:
    init_file_external = hotspot_config_path + sim.config.get('hotspot/init_file_external_mem')
if sim.config.get('hotspot/init_file_external_core') == "None":
    c_init_file_external = "None"
else:
    c_init_file_external = hotspot_config_path + sim.config.get('hotspot/init_file_external_core')
hotspot_config_file      =   hotspot_config_path + sim.config.get('hotspot/hotspot_config_file_mem')
c_hotspot_config_file      =   hotspot_config_path + sim.config.get('hotspot/hotspot_config_file_core')
#hotspot_floorplan_file   =   sim.config.get('hotspot/floorplan_file')
hotspot_floorplan_folder   = hotspot_config_path + sim.config.get('hotspot/floorplan_folder')
hotspot_layer_file  =   hotspot_config_path + sim.config.get('hotspot/layer_file_mem')
c_hotspot_layer_file  =   hotspot_config_path + sim.config.get('hotspot/layer_file_core')

# Output Parameters for hotspot simulation
combined_temperature_trace_file = sim.config.get('hotspot/log_files/combined_temperature_trace_file')
combined_insttemperature_trace_file = sim.config.get('hotspot/log_files/combined_insttemperature_trace_file')
combined_power_trace_file = sim.config.get('hotspot/log_files/combined_power_trace_file')
combined_instpower_trace_file = sim.config.get('hotspot/log_files/combined_instpower_trace_file')
combined_power_trace_file_total = combined_power_trace_file.replace(".","_total.")       #appending _total to the power trace with leakage power
combined_instpower_trace_file_total = 'tmmpFile_power1'
#memory related files
hotspot_steady_temp_file = sim.config.get('hotspot/log_files_mem/steady_temp_file')
hotspot_grid_steady_file = sim.config.get('hotspot/log_files_mem/grid_steady_file')
hotspot_all_transient_file = sim.config.get('hotspot/log_files_mem/all_transient_file')
power_trace_file = sim.config.get('hotspot/log_files_mem/power_trace_file')
power_trace_file_total = 'tmmpFile_power2'
bank_mode_trace_file = sim.config.get('scheduler/open/dram/dtm/bank_mode_trace_file') # For low power mode.
full_bank_mode_trace_file = sim.config.get('scheduler/open/dram/dtm/full_bank_mode_trace_file') # For low power mode.
full_power_trace_file = sim.config.get('hotspot/log_files_mem/full_power_trace_file')
temperature_trace_file = sim.config.get('hotspot/log_files_mem/temperature_trace_file')
full_temperature_trace_file = sim.config.get('hotspot/log_files_mem/full_temperature_trace_file')
init_file = sim.config.get('hotspot/log_files_mem/init_file')

#core related files
c_hotspot_steady_temp_file = sim.config.get('hotspot/log_files_core/steady_temp_file')
c_hotspot_grid_steady_file = sim.config.get('hotspot/log_files_core/grid_steady_file')
c_hotspot_all_transient_file = sim.config.get('hotspot/log_files_core/all_transient_file')
c_full_power_trace_file = sim.config.get('hotspot/log_files_core/full_power_trace_file')
c_power_trace_file = sim.config.get('hotspot/log_files_core/power_trace_file')
c_power_trace_file_total = 'tmmpFile_power3'
c_full_temperature_trace_file = sim.config.get('hotspot/log_files_core/full_temperature_trace_file')
c_temperature_trace_file = sim.config.get('hotspot/log_files_core/temperature_trace_file')
c_init_file = sim.config.get('hotspot/log_files_core/init_file')

#Basic idea of the flow is:
#Generate power trace using access trace from sniper in a periodic manner (for memories).
#The power trace of core is generated through the mcpat script.
#The power trace of core is combined with memory power trace for 3D and 2.5D architectures, else used separately in another hotspot run
#Invoke hotspot to generate temperature trace for the corresponding power trace. 
#The generated transient temperature trace (all_transient_file) is used as an init file for the next iteration

hotspot_command = executable  \
                  + ' -c ' + hotspot_config_file \
                  + ' -p ' + power_trace_file \
				  + ' -pTot ' + power_trace_file_total \
                  + ' -o ' + temperature_trace_file \
                  + ' -model_secondary 1 -model_type grid ' \
                  + ' -steady_file ' + hotspot_steady_temp_file \
                  + ' -all_transient_file ' + hotspot_all_transient_file \
                  + ' -grid_steady_file ' + hotspot_grid_steady_file \
                  + ' -steady_state_print_disable 1 ' \
                  + ' -l 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, ' \
                  + ' -type ' + type_of_stack \
                  + ' -sampling_intvl ' + str(interval_sec) \
                  + ' -grid_layer_file ' + hotspot_layer_file \
                  + ' -detailed_3D on'
#                  + ' -f ' + hotspot_floorplan_file \

if mem_dtm != "off":
  hotspot_command += ' -bm '+ bank_mode_trace_file
               
#if type_of_stack!="DDR":
#hotspot_command = hotspot_command + ' -grid_layer_file ' + hotspot_layer_file \
#                        +' -detailed_3D on'
print hotspot_command                  

c_hotspot_config_path = hotspot_config_path
#c_init_file_external = c_hotspot_config_path + sim.config.get('hotspot/init_file_external_core')
#c_init_file = sim.config.get('hotspot/log_files_core/init_file')

#initialization and setting up files
os.system("echo copying files for first run")
if (init_file_external != "None"):
    os.system("ls -l " + init_file_external)
    os.system("cp " + init_file_external + " " + init_file)
if (c_init_file_external != "None"):
    os.system("ls -l " + c_init_file_external)
    os.system("cp " + c_init_file_external + " " + c_init_file)
os.system('mkdir -p hotspot')
os.system("cp -r " + hotspot_floorplan_folder + " " + './hotspot')
os.system("rm -f " + full_temperature_trace_file)
os.system("rm -f " + full_power_trace_file)
os.system("rm -f " + c_full_power_trace_file)
os.system("rm -f " + c_full_temperature_trace_file)
os.system("rm -f " + full_bank_mode_trace_file)
for filename in ('PeriodicCPIStack.log', 'PeriodicFrequency.log', 'PeriodicVdd.log',):
  open(filename, 'w') # empties the file

def gen_mem_header():
    """
    Return header for memory banks.
    Similar to gen_ptrace_header, but will not write to file and will not include other components than memory.
    """
    # For a 2by1 ptrace with four layers header should be B0_0    B0_1    B0_0    B0_1    B0_0    B0_1    B0_0    B0_1
    # For 3D: core is at the top, whereas for 3Dmem, 2.5D config. the 3Dmem is at the bottom.
    # Creating Header
    mem_header = ''

    for b in range(NUM_BANKS):
      mem_header = mem_header + "B_" + str(b) + "\t"

    # for z in range(0,banks_in_z):
    #     for x in range(0,banks_in_x):
    #         for y in range(0,banks_in_y):
    #                 #                atrace_header=atrace_header + "B" + str(x) + "_" + str(y) + "\t" 
    #             #if type_of_stack== "3D" or type_of_stack== "3Dmem" or type_of_stack=="DDR":
    #             bank_number = z*banks_in_x*banks_in_y + x*banks_in_y + y
    #             mem_header = mem_header + "B_" + str(bank_number) + "\t" 
    #             #ptrace_header=ptrace_header + "B" + str(x) + "_" + str(y) + "\t" 
   
    return mem_header

#generates ptrace header as per the memory floorplan and architecture
#DDR:    B0_0 B0_1 ... B3_3
#3Dmem:   LC0_0 LC0_1 ... LC3_3 (logic core), B0_0 B0_1 ... B3_3 (layer0),  B0_0 B0_1 ... B3_3 (layer1), ...
#3D:   B0_0 B0_1 ... B3_3 (layer0),  B0_0 B0_1 ... B3_3 (layer1), ..., C0_0 C0_1 ... C3_3 (top layer core)
#2.5D   C0_0 C0_1 ... C3_3 (core part), LC0_0 LC0_1 ... LC3_3 (logic core base), X1, X2, X3, B0_0 B0_1 ... B3_3, X1, X2, X3 (layer0),  B0_0 B0_1 ... B3_3, X1, X2, X3 (layer1), ...
def gen_ptrace_header():
    # For a 2by1 ptrace with four layers header should be B0_0    B0_1    B0_0    B0_1    B0_0    B0_1    B0_0    B0_1
    # For 3D: core is at the top, whereas for 3Dmem, 2.5D config. the 3Dmem is at the bottom.
    # Creating Header
    ptrace_header = ''
    if type_of_stack=="2.5D":
        # ptrace_header=ptrace_header + "I0" + "\t" 
        for x in range(0,cores_in_x):
            for y in range(0,cores_in_y):
                ptrace_header=ptrace_header + "C_" + str(x*cores_in_y + y) + "\t" 
                #ptrace_header=ptrace_header + "C" + str(x) + "_" + str(y) + "\t" 
    
    if type_of_stack== "3Dmem" or type_of_stack== "2.5D":
        for x in range(0,logic_cores_in_x):
            for y in range(0,logic_cores_in_y):
                ptrace_header=ptrace_header + "LC_" + str(x*logic_cores_in_y + y) + "\t" 
                #ptrace_header=ptrace_header + "LC" + str(x) + "_" + str(y) + "\t" 
    
    if type_of_stack=="2.5D":
        for x in range(1,4):
            ptrace_header=ptrace_header + "X" + str(x) + "\t" 
                
    for z in range(0,banks_in_z):
        for x in range(0,banks_in_x):
            for y in range(0,banks_in_y):
                    #                atrace_header=atrace_header + "B" + str(x) + "_" + str(y) + "\t" 
                #if type_of_stack== "3D" or type_of_stack== "3Dmem" or type_of_stack=="DDR":
                bank_number = z*banks_in_x*banks_in_y + x*banks_in_y + y
                ptrace_header=ptrace_header + "B_" + str(bank_number) + "\t" 
                #ptrace_header=ptrace_header + "B" + str(x) + "_" + str(y) + "\t" 
        if type_of_stack=="2.5D":
            for x in range(1,4):
                ptrace_header=ptrace_header + "X" + str(x) + "\t" 
    
    if type_of_stack=="3D":
        for z in range(0,cores_in_z):
            for x in range(0,cores_in_x):
                for y in range(0,cores_in_y):
                    core_number = z*cores_in_x*cores_in_y + x*cores_in_y + y
                    ptrace_header=ptrace_header + "C_" + str(core_number) + "\t" 
                    #ptrace_header=ptrace_header + "C" + str(x) + "_" + str(y) + "\t" 

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
    
    if mem_dtm != 'off': 
      stat_write_lowpower = 'dram.bank_write_access_counter_lowpower'       #from sniper C-code
      stat_read_lowpower = 'dram.bank_read_access_counter_lowpower'       #from sniper C-code
      self.stat_name_read_lowpower = stat_read_lowpower
      self.stat_name_write_lowpower= stat_write_lowpower
      stat_component_rd_lowpower, stat_name_read_lowpower = stat_read_lowpower.rsplit('.', 1)
      stat_component_wr_lowpower, stat_name_write_lowpower = stat_write_lowpower.rsplit('.', 1)

    stat_bank_mode = 'dram.bank_mode'
    self.stat_name_bank_mode = stat_bank_mode
    stat_component_bank_mode, stat_name_bank_mode = stat_bank_mode.rsplit('.', 1)

    if filename:
      self.fd = file(os.path.join(sim.config.output_dir, filename), 'w')
      self.isTerminal = False
    else:
      self.fd = sys.stdout
      self.isTerminal = True
    #create an instance for core power computation
    self.ES = EnergyStats()

    self.sd = sim.util.StatsDelta()

    if mem_dtm != 'off':
      self.stats = {
        'time': [ self.getStatsGetter('performance_model', core, 'elapsed_time') for core in range(sim.config.ncores) ],
        'ffwd_time': [ self.getStatsGetter('fastforward_performance_model', core, 'fastforwarded_time') for core in range(sim.config.ncores) ],
        'stat_rd': [ self.getStatsGetter(stat_component_rd, bank, stat_name_read) for bank in range(NUM_BANKS) ],
        'stat_wr': [ self.getStatsGetter(stat_component_wr, bank, stat_name_write) for bank in range(NUM_BANKS) ],
        'stat_rd_lowpower': [ self.getStatsGetter(stat_component_rd_lowpower, bank, stat_name_read_lowpower) for bank in range(NUM_BANKS) ],
        'stat_wr_lowpower': [ self.getStatsGetter(stat_component_wr_lowpower, bank, stat_name_write_lowpower) for bank in range(NUM_BANKS) ],
        'stat_bank_mode': [ self.getStatsGetter(stat_component_bank_mode, bank, stat_name_bank_mode) for bank in range(NUM_BANKS)],
      }
    else:
      self.stats = {
      'time': [ self.getStatsGetter('performance_model', core, 'elapsed_time') for core in range(sim.config.ncores) ],
      'ffwd_time': [ self.getStatsGetter('fastforward_performance_model', core, 'fastforwarded_time') for core in range(sim.config.ncores) ],
      'stat_rd': [ self.getStatsGetter(stat_component_rd, bank, stat_name_read) for bank in range(NUM_BANKS) ],
      'stat_wr': [ self.getStatsGetter(stat_component_wr, bank, stat_name_write) for bank in range(NUM_BANKS) ],
      'stat_bank_mode': [ self.getStatsGetter(stat_component_bank_mode, bank, stat_name_bank_mode) for bank in range(NUM_BANKS)],
      }
    #print the initial header into different log/trace files
    gen_ptrace_header()
    ptrace_header = gen_ptrace_header()
    with open(full_temperature_trace_file, "w") as f:
        f.write("%s\n" %(ptrace_header))
    f.close()
    combined_header = self.gen_combined_trace_header()
    with open(combined_temperature_trace_file, "w") as f:
        f.write("%s\n" %(combined_header))
    f.close()
    with open(combined_power_trace_file, "w") as f:
        f.write("%s\n" %(combined_header))
    f.close()
    with open(combined_power_trace_file_total, "w") as f:
        f.write("%s\n" %(combined_header))
    f.close()
    with open(full_power_trace_file, "w") as f:
        f.write("%s\n" %(ptrace_header))
    f.close()

    if rlb.enabled:
        rlb.clean_reliability_files()
        rlb.init_reliability_files(combined_header, ptrace_header)

    mem_header = gen_mem_header()
    with open(full_bank_mode_trace_file, "w") as f:
        f.write("%s\n" %(mem_header))
    f.close()
    #setup to invoke the hotspot tool every interval_ns time and invoke calc_temperature_trace function
    sim.util.Every(interval_ns * sim.util.Time.NS, self.calc_temperature_trace, statsdelta = self.sd, roi_only = True)


  def get_bank_modes(self, time, time_delta):
    """
    Return status of memory banks and prints to output.
    """
    if self.isTerminal:
      self.fd.write('[STAT:%s] ' % self.stat_name_bank_mode)
    bank_mode = [1 for _ in range(NUM_BANKS)]
    for bank in range(NUM_BANKS):
      bank_mode[bank] = int(self.stats['stat_bank_mode'][bank].last)
      self.fd.write(' %u' % bank_mode[bank])
    self.fd.write('\n')
    return bank_mode

   #return access rates of various memory banks
  def get_access_rates(self, time, time_delta):
    if self.isTerminal:
      self.fd.write('[STAT:%s] ' % self.stat_name_read)
#    self.fd.write('%u' % (time / 1e6)) # Time in ns
    access_rates_read = [0 for number in xrange(NUM_BANKS)]
    #print self.stats['stat'][0].__dict__	#prints the fields of the object
    for bank in range(NUM_BANKS):
      statdiff_rd = self.stats['stat_rd'][bank].last
      access_rates_read[bank] = statdiff_rd
      self.fd.write(' %u' % statdiff_rd)
    self.fd.write('\n')
#    print access_rates
    if self.isTerminal:
      self.fd.write('[STAT:%s] ' % self.stat_name_write)
    access_rates_write = [0 for number in xrange(NUM_BANKS)]
    #print self.stats['stat'][0].__dict__	#prints the fields of the object
    for bank in range(NUM_BANKS):
      statdiff_wr = self.stats['stat_wr'][bank].last
      access_rates_write[bank] = statdiff_wr
      self.fd.write(' %u' % statdiff_wr)
    self.fd.write('\n')

    if mem_dtm != 'off':
      if self.isTerminal:
        self.fd.write('[STAT:%s] ' % self.stat_name_read_lowpower)
  #    self.fd.write('%u' % (time / 1e6)) # Time in ns
      access_rates_read_lowpower = [0 for number in xrange(NUM_BANKS)]
      #print self.stats['stat'][0].__dict__	#prints the fields of the object
      for bank in range(NUM_BANKS):
        statdiff_rd_lowpower = self.stats['stat_rd_lowpower'][bank].last
        access_rates_read_lowpower[bank] = statdiff_rd_lowpower
        self.fd.write(' %u' % statdiff_rd_lowpower)
      self.fd.write('\n')

      if self.isTerminal:
        self.fd.write('[STAT:%s] ' % self.stat_name_write_lowpower)
      access_rates_write_lowpower = [0 for number in xrange(NUM_BANKS)]
      #print self.stats['stat'][0].__dict__	#prints the fields of the object
      for bank in range(NUM_BANKS):
        statdiff_wr_lowpower = self.stats['stat_wr_lowpower'][bank].last
        access_rates_write_lowpower[bank] = statdiff_wr_lowpower
        self.fd.write(' %u' % statdiff_wr_lowpower)
      self.fd.write('\n')

      return access_rates_read, access_rates_write, access_rates_read_lowpower, access_rates_write_lowpower

    return access_rates_read, access_rates_write, [], []


  def write_bank_mode_trace(self, time, time_delta):
    print("[WRITE BANK MODE TRACE]")
    bank_mode_trace = self.get_bank_modes(time, time_delta)
    bank_mode_trace_string = ""

    for bank in range(NUM_BANKS):
      # print(bank_mode_trace[bank])
      bank_mode_trace_string = bank_mode_trace_string + str(bank_mode_trace[bank]) + '\t'
    bank_mode_trace_string += "\r\n"
    bank_mode_header = gen_mem_header()
    # Write bank mode information into the trace file for use by hotspot.
    with open("%s" %(bank_mode_trace_file), "w") as f:
        f.write("%s\n" %(bank_mode_header))
        f.write("%s" %(bank_mode_trace_string))
    f.close()


  def write_bank_leakage_trace(self, time, time_delta):
    """
    Write a tab separated text file with a row of memory unit headers, 
    and a row of scalars to multiply the memory bank leakage power with.
    """
    bank_mode_trace = self.get_bank_modes(time, time_delta)
    bank_mode_trace_string = ""

    for bank in range(NUM_BANKS):
      leakage = 1.0
      if bank_mode_trace[bank] == LOW_POWER:
        leakage = lpm_leakage_power
      # print(bank_mode_trace[bank])
      bank_mode_trace_string = bank_mode_trace_string + "{:.2f}".format(leakage) + '\t'
    bank_mode_trace_string += "\r\n"
    bank_mode_header = gen_mem_header()
    # Write bank mode information to the trace file for use by hotspot.
    with open("%s" %(bank_mode_trace_file), "w") as f:
        f.write("%s\n" %(bank_mode_header))
        f.write("%s" %(bank_mode_trace_string))
    f.close()


    # calculate power trace using access rate and other parameters
  def calc_power_trace(self, time, time_delta):
    accesses_read, accesses_write, accesses_read_lowpower, accesses_write_lowpower = self.get_access_rates(time, time_delta)
 #    print accesses 

    avg_no_refresh_intervals_in_timestep =  timestep/t_refi                                                     # 20/7.8 = 2.56 refreshes on an average 
    avg_no_refresh_rows_in_timestep = avg_no_refresh_intervals_in_timestep * rows_refreshed_in_refresh_interval # 2.56*8 rows refreshed = 20.48 refreshes 
    refresh_energy_in_timestep =  avg_no_refresh_rows_in_timestep * energy_per_refresh_access                   # 20.48 * 100 nJ = 2048 nJ, 100 nJ (say) is the energy per refresh access
    avg_refresh_power = refresh_energy_in_timestep/(timestep*1000)
    bank_power_trace = [0 for number in xrange(NUM_BANKS)]
     #total power = access_count*energy per access + leakage power + refresh power
    #calculate bank power for each bank using access traces

    for bank in range(NUM_BANKS):
      if mem_dtm != 'off':
        # In case of low power mode, multiply the read and write accesses with the given scale factor.
        normal_power_access = accesses_read[bank] * energy_per_read_access + accesses_write[bank] * energy_per_write_access
        low_power_access    = (accesses_read_lowpower[bank] * energy_per_read_access + accesses_write_lowpower[bank] * energy_per_write_access) * lpm_dynamic_power
        bank_power_trace[bank] =  (normal_power_access + low_power_access) / (timestep*1000) + bank_static_power + avg_refresh_power

      else:
        bank_power_trace[bank] = (accesses_read[bank] * energy_per_read_access + accesses_write[bank] * energy_per_write_access)/(timestep*1000) \
                      + bank_static_power + avg_refresh_power
      bank_power_trace[bank] = round(bank_power_trace[bank], 3)
    logic_power_trace = ''
    #create logic_core power array. applicable only for 3Dmem and 2.5D memory
    if (type_of_stack=="2.5D" or type_of_stack=="3Dmem"):
        logic_power_trace = [logic_core_power for number in xrange(NUM_LC)]
    power_trace = ''
    # convert power trace into a concatenated string for formated output
    #for 2.5D, read the core power from the core power trace file and include in the total power trace
    if (type_of_stack == "2.5D"):
        with open(c_power_trace_file, 'r') as power_file:
            power_file.readline()  # ignore first line that contains the header
            c_power_data=power_file.readline()  # ignore first line that contains the header
        power_file.close()
        power_trace = power_trace + c_power_data 
    #print logic power trace to the main power_trace
    for p in logic_power_trace:
        power_trace = power_trace + str(p) + '\t'
    #add X1, X2, X3 to the power trace for 2.5D
    if (type_of_stack == "2.5D"):
        for x in range(1,4):
            power_trace = power_trace + str(0.00) + '\t'
     #add bank power into the main power trace
    for bank in range(len(bank_power_trace)):
            #add 0 power for X1, X2, X3 for 2.5D
        if (type_of_stack == "2.5D" and bank%(banks_in_x*banks_in_y)==0 and bank>0):
            power_trace = power_trace + str(0.00) + '\t'
            power_trace = power_trace + str(0.00) + '\t'
            power_trace = power_trace + str(0.00) + '\t'
            #power_trace = power_trace + str(0.00) + '\t'
        #add bank power trace for all type of memories
        power_trace = power_trace + str(bank_power_trace[bank]) + '\t'
    #add 0 power for X1, X2, X3 for 2.5D at last
    if (type_of_stack == "2.5D"):
        for x in range(1,4):
            power_trace = power_trace + str(0.00) + '\t'
    c_power_data = ""
      #read core power and add to main power trace at last for 3D
    if (type_of_stack == "3D"):
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

  def execute_core_hotspot(self, vdd_str):
     #the function to execute core hotspot separately. It is called only for 3Dmem and 2D arch.
    c_executable = hotspot_path + 'hotspot'
 #  hotspot_steady_temp_file = config.get('hotspot_c/hotspot_steady_temp_file')
 #  hotspot_grid_steady_file = config.get('hotspot_c/hotspot_grid_steady_file')
 #  hotspot_all_transient_file = config.get('hotspot_c/all_transient_file')

    c_powerLogFileName = file(c_full_power_trace_file, 'a');
    #c_powerInstantaneousFileName = file(c_power_trace_file, 'r');
    if (core_thermal_enabled == 'true'):
     c_thermalLogFileName = file(c_full_temperature_trace_file, 'a');
    
    first_run = (sum(1 for linee in open(combined_temperature_trace_file, 'r')) == 1) 
#    needInitializing = os.stat(c_full_power_trace_file).st_size == 0
    if (core_thermal_enabled == 'true'):
     c_hotspot_args = c_executable  \
                    + ' -c '+ c_hotspot_config_file \
                    + ' -p ' + c_power_trace_file \
                    + ' -pTot ' + c_power_trace_file_total \
                    + ' -o ' + c_temperature_trace_file \
                    + ' -model_secondary 1 -model_type grid ' \
                    + ' -steady_file ' + c_hotspot_steady_temp_file \
                    + ' -all_transient_file ' + c_hotspot_all_transient_file \
                    + ' -grid_steady_file ' + c_hotspot_grid_steady_file \
                    + ' -steady_state_print_disable 1 ' \
                    + ' -l 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, ' \
                    + ' -type Core ' \
                    + ' -sampling_intvl ' + str(interval_sec) \
                    + ' -grid_layer_file ' + c_hotspot_layer_file \
                    + ' -v ' + vdd_str \
                    + ' -detailed_3D on'
                    #+ ' -f ' + c_hotspot_floorplan_file \
     if (c_init_file_external!= "None") or (not first_run):
         c_hotspot_args += ' -init_file ' + c_init_file

     #print hotspot_binary, hotspot_args
#     c_temperatures = subprocess.check_output([hotspot_binary] + hotspot_args)
     #print c_hotspot_args
     os.system(c_hotspot_args)
     os.system("cp -f " + c_hotspot_all_transient_file + " " + c_init_file)

     with open(c_temperature_trace_file, 'r') as instTemperatureFile:
       instTemperatureFile.readline()  # ignore first line that contains the header
       c_thermalLogFileName.write(instTemperatureFile.readline())
     c_thermalLogFileName.close()
          

  def gen_combined_trace_header(self):
    trace_header = ""
    for x in range(NUM_CORES):
        trace_header = trace_header + "C_" + str(x) + "\t"
    for x in range(NUM_BANKS):
        trace_header = trace_header + "B_" + str(x) + "\t"
    return trace_header

  # this function merges the separate core and mem trace files or reorders a single core+mem trace file, all to a uniform format
  def format_trace_file(self, skip_header, c_inst_trace_file, inst_trace_file, combined_trace_file, combined_instTrace_file):
    if (type_of_stack == "DDR" or type_of_stack == "3Dmem"):        #separate mem and core traces are combined
        with open(c_inst_trace_file, 'r') as core_data_file:
            if (skip_header):
                core_data_file.readline()  # ignore first line that contains the header
            core_data=core_data_file.readline()  
            core_data = core_data.rstrip()
        core_data_file.close()
        with open(inst_trace_file, 'r') as mem_data_file:
            if (skip_header):
                mem_data_file.readline()  # ignore first line that contains the header
            mem_data=mem_data_file.readline()  
            mem_data=mem_data.rstrip()  
        mem_data_file.close()
        if (type_of_stack == "3Dmem"):      #skip the LC entries for a 3D external memory
            mem_data_split = mem_data.split("\t")
            mem_data_split = mem_data_split[NUM_LC:]
            mem_data = "\t".join(mem_data_split)
    elif (type_of_stack == "3D"):        #reorder core and memory columns in a 3D layout
        with open(inst_trace_file, 'r') as data_file:
            if (skip_header):
                data_file.readline()  # ignore first line that contains the header
            data=data_file.readline()  # ignore first line that contains the header
            data=data.rstrip()  
        data_file.close()
        data_split = data.split("\t")
        core_data_split = data_split[NUM_BANKS:]        #extract core temperatures from the line (last few entries)
        core_data = "\t".join(core_data_split)
        mem_data_split = data_split[:NUM_BANKS]         #extract memory temperatures (first few entries)
        mem_data = "\t".join(mem_data_split)
    elif (type_of_stack == "2.5D"):
        with open(inst_trace_file, 'r') as data_file:
            if (skip_header):
                data_file.readline()  # ignore first line that contains the header
            data=data_file.readline()  # ignore first line that contains the header
            data=data.rstrip()  
        data_file.close()
        data_split = data.split("\t")
        core_data_split = data_split[:NUM_CORES]        #extract core temperatures from the line (first few entries)
        core_data = "\t".join(core_data_split)
        mem_portion = data_split[NUM_CORES+NUM_LC+3 : ] # skip the first few entries corresponding to cores, LC, and X1, X2, X3
        banks_per_layer = banks_in_x*banks_in_y
        mem_data_split = []
        for layer in range(banks_in_z):
            start_index = layer*(banks_per_layer+3)         # +4 corresponds to X1,X2,X3
            mem_data_split.extend(mem_portion[start_index:start_index+banks_per_layer])
        mem_data = "\t".join(mem_data_split)

    #finally combine core and memory traces and print to the file
    final_data = core_data + "\t" + mem_data + "\r"
    with open("%s" %(combined_trace_file), "a") as f:
        f.write("%s\n" %(final_data))
    f.close()

    #combined, instantaneous power/temperature file generated
    combined_header = self.gen_combined_trace_header()
    with open("%s" %(combined_instTrace_file), "w") as f:
        f.write("%s\n" %(combined_header))
        f.write("%s\n" %(final_data))
    f.close()

  def get_core_vdd_for_hotspot(self):
    lfreq = [ sim.dvfs.get_frequency(core) for core in range(sim.config.ncores) ]
    if rlb.enabled:
      lvdd = [ self.ES.get_vdd_from_freq(f) for f in rlb.target_freqs(lfreq) ]
    else:
      lvdd = [ self.ES.get_vdd_from_freq(f) for f in lfreq ]
    lvdd = [ v/1.2 for v in lvdd ]          #normalize to 1.2 volts
    lvdd = [ round(v, 1) for v in lvdd ]    #round to 1 digit decimal
    vdd_str = ""
    for v in lvdd:
        vdd_str += str(v)
        vdd_str += ","
    vdd_str = vdd_str[:-1]         #remove last comma as it is extra
    #print lvdd
    #print vdd_str
    return vdd_str



  # invokes hotspot to generate the temperature trace
  def calc_temperature_trace(self, time, time_delta):
#   print power_trace
    #invoke energystats function to compute core power trace
    self.ES.periodic(time, time_delta)
    vdd_string = self.get_core_vdd_for_hotspot()     #used to scale core leakage power in hotspot

    self.write_bank_leakage_trace(time, time_delta)

    #execute hotspot separately for core in case of 3Dmem and 2D memories
    if (core_thermal_enabled == 'true' and (type_of_stack=="3Dmem" or type_of_stack=="DDR")):
        self.execute_core_hotspot(vdd_string)
     #calculate memory power trace (combines with core trace in case of 3D and 2.5D within function)
    self.calc_power_trace(time, time_delta)
     #invoke the memory hotspot. It will include core parts automatically for 3D and 2.5D
    hcmd = hotspot_command
    hcmd += ' -v ' + vdd_string
    first_run = (sum(1 for linee in open(combined_temperature_trace_file, 'r')) == 1) 
    if (init_file_external!= "None") or (not first_run):
        hcmd += ' -init_file ' + init_file
    os.system(hcmd)
    self.format_trace_file(True, c_temperature_trace_file, temperature_trace_file, combined_temperature_trace_file, combined_insttemperature_trace_file)
    self.format_trace_file(True, c_power_trace_file, power_trace_file, combined_power_trace_file, combined_instpower_trace_file)
    self.format_trace_file(True, c_power_trace_file_total, power_trace_file_total, combined_power_trace_file_total, combined_instpower_trace_file_total)
      #concatenate the per interval temperature trace into a single file

    # Update reliability values of all the cores.
    if rlb.enabled:
        rlb.update_reliability_values(time_delta, time)

    os.system("cp " + hotspot_all_transient_file + " " + init_file)
    os.system("tail -1 " + temperature_trace_file + ">>" + full_temperature_trace_file)
    os.system("tail -1 " + power_trace_file + " >>" + full_power_trace_file)

    os.system("tail -1 " + bank_mode_trace_file + " >>" + full_bank_mode_trace_file)
    os.system("rm -f tmmpFile_*")

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
      return 0.6 + f / core_frequency_max * 0.8
    return [ (f, v(f))  for f in reversed(range(int(core_frequency_min), 
                                                int(core_frequency_max)+1, 
                                                int(core_frequency_step))) ]
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
    if f > core_frequency_max:
      raise ValueError('Could not find a Vdd for invalid frequency %f exceeding the core\'s maximum frequency' % f)
    for _f, _v in self.dvfs_table:
      if f >= _f:
        return _v
    raise ValueError('Could not find a Vdd for invalid frequency %f' % f)

  def gen_config(self, outputbase):
    freq = [ sim.dvfs.get_frequency(core) for core in range(sim.config.ncores) ]
    if rlb.enabled:
      vdd = [ self.get_vdd_from_freq(f) for f in rlb.target_freqs(freq) ]
    else:
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

    os.system('unset PYTHONHOME; %s -d %s -o %s -c %s -t %s --partial=%s:%s --no-graph --no-text' % (
      os.path.join(os.getenv('SNIPER_ROOT'), 'tools/mcpat.py'),
      sim.config.output_dir,
      outputbase,
      configfile,
      'dynamic',
      name0, name1
    ))

    result = {}
    execfile(outputbase + '.py', {}, result)
    return result['power']

sim.util.register(memTherm())
