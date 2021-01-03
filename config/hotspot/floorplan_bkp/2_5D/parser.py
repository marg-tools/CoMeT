#!/usr/bin/python
import re
import numpy as np
import pylab as pl
import matplotlib.pyplot as plt
import subprocess
import os 
import math
import sys

np.set_printoptions(threshold=np.inf)

# ----------------------------- Function definition is here -------------
def printme( str ):
    # This prints a passed string into this function
    print str
    return;

def PositionLast (x,s):
    for i, v in enumerate(reversed(s)):
        if v == x:
            last = len(s) - i - 1
            return last
    return -1


# ----------------------------- MAIN PROGRAM -----------------------------  

#Usage
# Example : ./parser.py tmp_streamcluster 128 1 0.0001 0
# Example : ./parser.py <SniperLog> <#Banks> <Enable Hotspot Simulation> <Bank_Leakage> <Type_Of_Memory_Stack>

# ----------------------------- CONFIG PARAMS -----------------------------  
# Parameters for sniper simulation 
_enable = 1
_disable = 0 
sniper_run          =   _disable            # Do you want to run sniper                         [IMP] 
sniper_command      = "../../run-sniper --benchmarks=parsec-streamcluster-test-1,parsec-streamcluster-test-1,parsec-streamcluster-test-1,parsec-streamcluster-test-1,parsec-streamcluster-test-1,parsec-streamcluster-test-1,parsec-streamcluster-test-1,parsec-streamcluster-test-1,parsec-streamcluster-test-1,parsec-streamcluster-test-1,parsec-streamcluster-test-1,parsec-streamcluster-test-1,parsec-streamcluster-test-1,parsec-streamcluster-test-1,parsec-streamcluster-test-1,parsec-streamcluster-test-1 -c gainestown --no-roi"
sniper_run_log      = sys.argv[1]
#sniper_run_log     = "tmpE_ck_exact_3Dr_16"

# Parameters for calculating the number of bank accesses (and refresh)
bank_size = 64                                      # in Mb, 64MB partition = 512Mb partition, 8MB partition = 64Mb partition.
no_columns = 1                                      # in Kilo
no_bits_per_column = 8                              # 8 bits per column. Hence 8Kb row buffer.
no_rows= bank_size/no_columns/no_bits_per_column    # in Kilo, number of rows per bank
t_refi  = 7.8                                       # refresh interval time in uS
# t_refw  = 64                                      # refresh window in mS       
no_refesh_commands_in_t_refw = 8                    # in Kilo, 8K refresh commands are issued in a refresh window, one in each interval    
rows_refreshed_in_refresh_interval = no_rows/no_refesh_commands_in_t_refw  # for 512Mb bank, 8 rows per refresh => for 64Mb bank, 1 rows per refresh

number_of_banks = int(sys.argv[2])
user_min_time_stamp = 0                     # user_min_time_stamp = 1 
user_initial_accesses = ""                  # user_initial_accesses = "11,0,0,1,22,2,15,2" 
for bnk in range(number_of_banks):
    user_initial_accesses   =  user_initial_accesses + "0,"
#user_min_time_stamp = 0                        # user_min_time_stamp = 1 
#user_initial_accesses = "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"      # user_initial_accesses = "11,0,0,1,22,2,15,2" 


figure_output = _disable            # Do you want to generate graphs: access rate, power[IMP]
output_folder="outputs"             # Figures are stored in output folder

# Parameters for calculating the number of core power 
type_of_stack = int(sys.argv[5])    # 2 : 2D, 1 : WIO, 0: HMC/HBM 
_WIO = 1
_HMC = 0
_2D = 2
number_of_cores = 16 
core_figure_output = _disable       # Do you want to generate graphs: access rate, power[IMP]
timestep_core = 10                  # Should be in sync with sniper scripts 

# Parameters for calculating the average power
energy_per_access = 20.55           # in nJ. From CACTI3DD, 10,7.57,1.855*7 + 7.57 = 20.55........ Should be 15.15 nJ -> 3.7 pJ/bit 
energy_per_refresh_access= 3.55     # in nJ. From CACTI3DD, 4
timestep = 20                       # in uS. Should be in sync with hotspot.config (sampling_intvl)
                                    # Only INTEGRAL multiples of 10uS allowed.

# Parameters for getting the power trace for hotspot
# Bank Floorplan info
banks_in_x = 4
banks_in_y = 4
banks_in_z = number_of_banks/banks_in_x/banks_in_y  
#banks_in_z = 2
#bank_printing_pattern = [6,3,5,1,4,0,7,2]
bank_printing_pattern = [] 
for bnk in range(number_of_banks):
    bank_printing_pattern.append(bnk)
#bank_printing_pattern = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31]
# Bank Static Power info
bank_static_power = float(sys.argv[4])               # Total power = Static + Dynamic. Temperature dependent static power should be calculated in HOTSPOT.

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
logic_avg_power = float(sys.argv[7]) # 0.448 * 0.8 * percentBW
#logic_avg_power = 0.375 # 7 * percentBW/16
# mult - 0.0066
# col -  0.3151

# Parameters for hotspot simulation 
hotspot_run         =   int(sys.argv[3])           # Do you want to run hotspot                        [IMP]
is_2_5d = int(sys.argv[6])    # 1 : 2.5D, 0 : 3D stacked memory (processor temp. doesnot effect memory temperature)

if type_of_stack== _WIO:
    mem_name = "WIO/"
if type_of_stack== _HMC:
    mem_name = "HMC/"
if type_of_stack== _2D:
    mem_name = "2D/"
#hotspot_tool        =   "/home/siddhulokesh/HotSpot-6.0/hotspot"
hotspot_tool        =   "/home/siddhulokesh/HotSpot-6.0_SLU/hotspot"
# /home/siddhulokesh/HotSpot-6.0_SLU/hotspot

if type_of_stack== _2D:
    hotspot_test_dir    =   "hotspot/test" + "0"                + "/" + mem_name 
else:
    if is_2_5d== _disable:
        hotspot_test_dir    =   "hotspot/test" + str(banks_in_z)    + "/" + mem_name 
    else:
        hotspot_test_dir    =   "hotspot/test_2_5_D" + str(banks_in_z)    + "/" + mem_name 
	
# hotspot_test_dir    =   "hotspot/test2/"
# Input Parameters for hotspot simulation
hotspot_config      =   hotspot_test_dir  + "/hotspot.config"
hotspot_floorplan   =   "hotspot/floorplan/4by4.flp"
hotspot_layer_file  =   hotspot_test_dir  + "/4by4.lcf"

# Output Parameters for hotspot simulation
hotspot_steady_temp =   hotspot_test_dir  + "/4by4.steady"
hotspot_grid_steady =   hotspot_test_dir  + "/gcc.grid.steady"

# Parameters for printing temperature traces  
figure_temperature_output = _disable            # Do you want to generate graphs for temperature         [IMP]

# /home/siddhulokesh/HotSpot-6.0_SLU/hotspot -c hotspot/test_2_5_D8/HMC//hotspot.config  -f hotspot/floorplan/4by4.flp -p 4by4.ptrace -o 4by4.ttrace -model_type grid -detailed_3D on -grid_layer_file hotspot/test_2_5_D8/HMC//4by4.lcf -steady_file hotspot/test_2_5_D8/HMC//4by4.steady -grid_steady_file hotspot/test_2_5_D8/HMC//gcc.grid.steady

# ----------------------------- ACTUAL CODE -----------------------------  

# ------------------------------------------------------------------------------------------------------------
# Do an sniper simulation 

if sniper_run == _enable:  
    print "Doing an sniper simulation"
    bashCommand = "%s > %s" %(sniper_command,sniper_run_log)
    print bashCommand 
    process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
    # Interact with process: Send data to stdin. Read data from stdout and stderr, until end-of-file is reached. Wait for process to terminate. 
    (output, err) = process.communicate()
     ## Wait for bashCommand to terminate. Get return returncode ##
    p_status = process.wait()
    print output

# ------------------------------------------------------------------------------------------------------------
# Bank access calculation

input_file = sniper_run_log
list_time_stamp = []
list_last_index = [] 
list_bank_counts= []
list_line_num = []
list_last_index_line_number = []
list_core_static_energies = []
list_core_dynamic_energies = []

line_num = 0 
iteration_count = 1

with open("%s" %(input_file)) as origin_file:
    for line in origin_file:
        if "@&" in line:
            time_stamp  =   line.split('\t')[1]
            # print time_stamp
            list_time_stamp.append(int(time_stamp))
            # reads       = line.split('\t')[2]
            # writes      = line.split('\t')[3]
            # accesses    = line.split('\t')[4]
            # addresses   = line.split('\t')[5]
            # bank        = line.split('\t')[6]
            bank_counts = line.split('\t')[7]
            # print bank_counts 
            list_bank_counts.append(bank_counts)
            # print iteration_count
            # iteration_count = iteration_count + 1

        if "core.energy-static" in line:
            text = re.search('static] (.*)', line).group(1)
            list_core_static_energies.append(text)
        if "core.energy-dynamic" in line:
            text = re.search('dynamic] (.*)', line).group(1)
            list_core_dynamic_energies.append(text)
            # print line 
        line_num = line_num + 1

# print list_core_static_energies
# print list_core_dynamic_energies

#    print list_time_stamp
#    print "Last index of 0 is"
#    print PositionLast(0,list_time_stamp)

min_time_stamp = user_min_time_stamp
max_time_stamp = max(list_time_stamp)
# max_time_stamp = 414400 # Remember 0 is also a time stamp 
# print max_time_stamp 

timestamp_array = [0 for x in range(int(math.ceil( (max_time_stamp - min_time_stamp + 1)/timestep )))]
for index in range(0,int(math.ceil( (max_time_stamp - min_time_stamp + 1)/timestep ))):
        timestamp_array[index] = index*timestep + min_time_stamp

if type_of_stack== _WIO or type_of_stack== _HMC or type_of_stack ==_2D:
    print "Bank access calculation"
    list_phase_wise_bank_counts=np.zeros((int (math.ceil( (max_time_stamp - min_time_stamp + 1)/timestep )),number_of_banks))
    for bnk in range(0,number_of_banks):
        list_phase_wise_bank_counts[0][bnk] = int(list_bank_counts[0].split(',')[bnk]) - int(user_initial_accesses.split(',')[bnk])

    for index in range(1,int(math.ceil( (max_time_stamp - min_time_stamp + 1)/timestep ))):
        print index
        for bnk in range(0,number_of_banks):
            list_phase_wise_bank_counts[index][bnk] = int(list_bank_counts[index].split(',')[bnk])

# print list_phase_wise_bank_counts
# print len(list_phase_wise_bank_counts)
#print list_phase_wise_bank_counts[:,0]

# T = range(M.shape[0])
# Make an array of X-Axis 

if figure_output == _enable:
    if not os.path.exists(output_folder):
            os.makedirs(output_folder)
    if type_of_stack== _WIO or type_of_stack== _HMC or type_of_stack ==_2D:
        print "Print bank access graphs"
        bank_num = 0;
        for i in bank_printing_pattern:
    #    for i in range(number_of_banks):
            plt.plot(timestamp_array, list_phase_wise_bank_counts[:,i])
            plt.title('Bank %d accesses versus time %d-%d micro-seconds' % (bank_num,min_time_stamp,max_time_stamp) )
            plt.xlabel('Time (in microseconds)')
            plt.ylabel('Bank Access Counts')
            plt.savefig('%s/Bank_%d_Access.png' % (output_folder,bank_num))
            bank_num = bank_num  + 1
        plt.clf()
# plt.show()

# ------------------------------------------------------------------------------------------------------------
# Core access calculation

if type_of_stack==_WIO or type_of_stack ==_2D or is_2_5d==_enable:
    print "Core access calculation"

    list_phase_wise_core_static_energies=np.zeros((int (math.ceil( (max_time_stamp - min_time_stamp + 1)/timestep_core)),number_of_cores))
    list_phase_wise_core_dynamic_energies=np.zeros((int (math.ceil( (max_time_stamp - min_time_stamp + 1)/timestep_core)),number_of_cores))

    for core in range(0,number_of_cores):
        list_phase_wise_core_static_energies[0][core] = int(int(float(list_core_static_energies[1].split(' ')[core + 1]))/2)
        list_phase_wise_core_static_energies[1][core] = int(int(float(list_core_static_energies[1].split(' ')[core + 1]))/2)
        
        list_phase_wise_core_dynamic_energies[0][core] = int(int(float(list_core_dynamic_energies[1].split(' ')[core + 1]))/2)
        list_phase_wise_core_dynamic_energies[1][core] = int(int(float(list_core_dynamic_energies[1].split(' ')[core + 1]))/2)

    #print len (list_core_static_energies)
    #print max_time_stamp 
    #print min_time_stamp 
    #print timestep_core 
    # print int (math.ceil( (max_time_stamp - min_time_stamp + 1)/timestep_core ))
    # for index in range(2,len (list_core_static_energies)):
    for index in range(2,int(math.ceil( (max_time_stamp - min_time_stamp + 1)/timestep_core))):
        # print index
        for core in range(0,number_of_cores):
            # print core
            list_phase_wise_core_static_energies[index][core] = int(float((list_core_static_energies[index].split(' ')[core+1])))
            list_phase_wise_core_dynamic_energies[index][core] = int(float((list_core_dynamic_energies[index].split(' ')[core+1])))

    #print list_phase_wise_core_static_energies
    #print list_phase_wise_core_dynamic_energies

# ------------------------------------------------------------------------------------------------------------


# Average power  = (#events*Eevent)/timestep								    # For a 512Mb Bank => 8 rows refreshed 
avg_no_refresh_intervals_in_timestep =  timestep/t_refi                                                     # 20/7.8 = 2.56 refreshes on an average 
avg_no_refresh_rows_in_timestep = avg_no_refresh_intervals_in_timestep * rows_refreshed_in_refresh_interval # 2.56*8 rows refreshed = 20.48 refreshes 
refresh_energy_in_timestep =  avg_no_refresh_rows_in_timestep * energy_per_refresh_access                   # 20.48 * 100 nJ = 2048 nJ, 100 nJ (say) is the energy per refresh access
avg_refresh_power = refresh_energy_in_timestep/(timestep*1000)                                              # (2048 nJ)/(20us) = (2048 nJ)/(20 000ns) = 102.4 mW 
# print avg_refresh_power  

if type_of_stack== _WIO or type_of_stack== _HMC:
    print "Average bank power calculation"
    list_phase_wise_bank_avg_power=np.zeros(( int(math.ceil( (max_time_stamp - min_time_stamp + 1)/timestep )) , number_of_banks)) 
    for index in range(0,int (math.ceil( (max_time_stamp - min_time_stamp + 1)/timestep ))):
        for bnk in range(0,number_of_banks):
            list_phase_wise_bank_avg_power[index][bnk] = (list_phase_wise_bank_counts[index][bnk] * energy_per_access)/(timestep*1000) + bank_static_power + avg_refresh_power   

# print list_phase_wise_bank_avg_power

if figure_output == _enable:  
    if not os.path.exists(output_folder):
            os.makedirs(output_folder)
    if type_of_stack== _WIO or type_of_stack== _HMC:
        print "Print average power graphs"
        bank_num = 0;
        for i in bank_printing_pattern:
    #    for i in range(number_of_banks):
            plt.plot(timestamp_array, list_phase_wise_bank_avg_power[:,i])
            plt.title('Bank %d average power versus time %d-%d micro-seconds' % (bank_num,min_time_stamp,max_time_stamp) )
            plt.xlabel('Time (in microseconds)')
            plt.ylabel('Average Power (in microwatts)')
            plt.savefig('%s/Bank_%d_Power.png' % (output_folder,bank_num))
            bank_num = bank_num  + 1
            plt.clf()
# ------------------------------------------------------------------------------------------------------------

# Average power  = (Core Energy)/timestep_core
if type_of_stack==_WIO or type_of_stack ==_2D or is_2_5d==_enable:
    print "Average Core power calculation"

    timestep_ratio = int(timestep/timestep_core);

    # list_phase_wise_core_avg_power=np.zeros((int (math.ceil( (max_time_stamp - min_time_stamp + 1)/timestep_core)),number_of_cores))
    # for index in range(0,int(math.ceil( (max_time_stamp - min_time_stamp + 1)/timestep_core))):
    #     for core in range(0,number_of_cores):
    #         list_phase_wise_core_avg_power[index][core] = (list_phase_wise_core_static_energies[index][core] + list_phase_wise_core_dynamic_energies[index][core])/(1000000)
    # print list_phase_wise_core_avg_power

    list_phase_wise_core_avg_power=np.zeros((int (math.ceil( (max_time_stamp - min_time_stamp + 1)/timestep)),number_of_cores))
    for index in range(0,int(math.ceil( (max_time_stamp - min_time_stamp + 1)/timestep))):
        for core in range(0,number_of_cores):
            temp_sum = 0
            for ts in range(0,timestep_ratio):
                temp_sum = temp_sum + (list_phase_wise_core_static_energies[index*timestep_ratio + ts][core] + list_phase_wise_core_dynamic_energies[index *timestep_ratio+ ts][core])/(1000000)
            list_phase_wise_core_avg_power[index][core] = temp_sum/timestep_ratio
            if list_phase_wise_core_avg_power[index][core] > error_peak_power:  
              print "Very high power returned from McPaT. Please check." 
              print "Power = %f in core = %d at time = %d" %(list_phase_wise_core_avg_power[index][core], core, index)
              # if list_phase_wise_core_avg_power[index][core] >=  100 and list_phase_wise_core_avg_power[index][core]  < 1000: 
              #   divisor= 10 
              # if list_phase_wise_core_avg_power[index][core] >=  1000 and list_phase_wise_core_avg_power[index][core]  < 10000:
              #   divisor= 100 
              # if list_phase_wise_core_avg_power[index][core] >=  10000 and list_phase_wise_core_avg_power[index][core]  < 100000:
              #   divisor= 1000
              list_phase_wise_core_avg_power[index][core] = error_default_power
              print "Approximating to %f" %list_phase_wise_core_avg_power[index][core] 

    # print list_phase_wise_core_avg_power

# ------------------------------------------------------------------------------------------------------------


# ------------------------------------------------------------------------------------------------------------
# Outputting the power trace for hotspot 

output_power_trace = str(banks_in_y)  + "by" + str(banks_in_x) + ".ptrace"  # "2by1.ptrace"
atrace_header = ""
ptrace_header = "" 
ptrace_data = ""
b_ptrace_data = ""

print "Writing output_power_trace %s" % (output_power_trace)

# For a 2by1 ptrace with four layers header should be B0_0    B0_1    B0_0    B0_1    B0_0    B0_1    B0_0    B0_1
# For WIO: core is at the top, whereas for HMC, 2.5D config. the HMC is at the bottom.
# Creating Header
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
            atrace_header=atrace_header + "B" + str(x) + "_" + str(y) + "\t" 
            if type_of_stack== _WIO or type_of_stack== _HMC:
                ptrace_header=ptrace_header + "B" + str(x) + "_" + str(y) + "\t" 
    if is_2_5d==_enable:
        for x in range(0,4):
            ptrace_header=ptrace_header + "X" + str(x) + "\t" 

if type_of_stack==_WIO or type_of_stack ==_2D:
    for x in range(0,cores_in_x):
        for y in range(0,cores_in_y):
            ptrace_header=ptrace_header + "C" + str(x) + "_" + str(y) + "\t" 

# Creating Printing Data
for index in range(0,int (math.ceil( (max_time_stamp - min_time_stamp + 1)/timestep ))):
#    for bnk in range(0,number_of_banks):
    # print index
    if is_2_5d==_enable:
        # ptrace_data = ptrace_data + str(round(0,3)) + "\t" 
        for core in core_printing_pattern:
            ptrace_data = ptrace_data + str(round(list_phase_wise_core_avg_power[index][core],3) * 1.0) + "\t" 
            #if core%16==15 or core%16==11 or core%16==7 or core%16==3:
            #    ptrace_data = ptrace_data + str(round(list_phase_wise_core_avg_power[index][core],3) * 0.0) + "\t" 
            #else:
            #    ptrace_data = ptrace_data + str(round(list_phase_wise_core_avg_power[index][core],3) * 1.0) + "\t" 
#           ptrace_data = ptrace_data + str(round(0,3)) + "\t" 
    if type_of_stack== _HMC:
        for logic in logic_printing_pattern:
            ptrace_data = ptrace_data + str(round(logic_avg_power,3)* 1.0) + "\t"
            
            #if logic%16==6 or logic%16==7 or logic%16==10 or logic%16==11:
            # if logic%2== 0:
            #    ptrace_data = ptrace_data + str(round(logic_avg_power,3)* 0.0) + "\t"
            #else:
            #    ptrace_data = ptrace_data + str(round(logic_avg_power,3)* 2.0) + "\t"

           #ptrace_data = ptrace_data + str(round(0,3)) + "\t" 
    if is_2_5d==_enable:
        for x in range(1,4):
            ptrace_data = ptrace_data + str(0.000) + "\t" 
    if type_of_stack== _WIO or type_of_stack== _HMC:
        for bnk in bank_printing_pattern:
            if is_2_5d==_enable:
            	if bnk%(banks_in_x * banks_in_y)== 0 and bnk != 0: #banks_in_x*banks_in_y
			for x in range(0,4):
                    		ptrace_data = ptrace_data + str(0.000) + "\t" 
            ptrace_data = ptrace_data + str(round(list_phase_wise_bank_avg_power[index][bnk],3)* 1.0) + "\t" 

            #if bnk%16==6 or bnk%16==7 or bnk%16==10 or bnk%16==11:
            # if bnk%2== 0:
            #     ptrace_data = ptrace_data + str(round(list_phase_wise_bank_avg_power[index][bnk],3)* 0.0) + "\t"
            #else:
            #     ptrace_data = ptrace_data + str(round(list_phase_wise_bank_avg_power[index][bnk],3)* 2.0) + "\t"     

            #ptrace_data = ptrace_data + str(round(0,3)) + "\t" 

    if is_2_5d==_enable:
        for x in range(0,4):
            ptrace_data = ptrace_data + str(0.000) + "\t" 

    if type_of_stack==_WIO or type_of_stack ==_2D:
        for core in core_printing_pattern:
            ptrace_data = ptrace_data + str(round(list_phase_wise_core_avg_power[index][core],3)) + "\t" 
    ptrace_data = ptrace_data +  "\r\n" 

# print ptrace_header 
# print ptrace_data 

with open("%s" %(output_power_trace), "w") as f:
        f.write("%s\n" %(ptrace_header))
        f.write("%s" %(ptrace_data))

# ------------------------------------------------------------------------------------------------------------
# Outputting the bank access trace for debug 

if type_of_stack== _WIO or type_of_stack== _HMC or type_of_stack ==_2D:
    output_access_trace = str(banks_in_y)  + "by" + str(banks_in_x) + ".atrace"  # "2by1.ptrace"
    atrace_data = ""

    print "Writing output_access_trace %s" % (output_access_trace)

    for index in range(0,int (math.ceil( (max_time_stamp - min_time_stamp + 1)/timestep ))):
    #    for bnk in range(0,number_of_banks):
        for bnk in bank_printing_pattern:
            atrace_data = atrace_data + str(int(list_phase_wise_bank_counts[index][bnk])) + "\t" 
        atrace_data = atrace_data +  "\r\n" 

    with open("%s" %(output_access_trace), "w") as f:
            f.write("%s\n" %(atrace_header))
            f.write("%s" %(atrace_data))


# ------------------------------------------------------------------------------------------------------------
# Outputting the bank power trace for debug 
if type_of_stack== _WIO or type_of_stack== _HMC:
    output_bank_power_trace = str(banks_in_y)  + "by" + str(banks_in_x) + ".bptrace"  # "2by1.ptrace"
    b_ptrace_data = ""

    print "Writing output_bank_power_trace %s" % (output_bank_power_trace)

    for index in range(0,int (math.ceil( (max_time_stamp - min_time_stamp + 1)/timestep ))):
        #    for bnk in range(0,number_of_banks):
        for bnk in bank_printing_pattern:
            b_ptrace_data = b_ptrace_data + str(round(list_phase_wise_bank_avg_power[index][bnk],3))  + "\t" 
        b_ptrace_data = b_ptrace_data +  "\r\n" 

    with open("%s" %(output_bank_power_trace), "w") as f:
            f.write("%s\n" %(atrace_header))
            f.write("%s" %(b_ptrace_data))

# ------------------------------------------------------------------------------------------------------------
# Do an hotspot simulation 

#Inputs
hotspot_ptrace      =   output_power_trace

#Outputs
hotspot_temp_trace  =   str(banks_in_y)  + "by" + str(banks_in_x) + ".ttrace"  # "2by1.ttrace"

if hotspot_run == _enable:  
    print "Doing an hotspot simulation"
    # % (bank_num,min_time_stamp,max_time_stamp)
    bashCommand = "%s -c %s  -f %s -p %s -o %s -model_type grid -detailed_3D on -grid_layer_file %s -steady_file %s -grid_steady_file %s" %(hotspot_tool,hotspot_config,hotspot_floorplan,hotspot_ptrace,hotspot_temp_trace,hotspot_layer_file,hotspot_steady_temp,hotspot_grid_steady)

#    bashCommand = "%s -c %s  -f %s -p %s -o %s -model_type grid -grid_layer_file %s -steady_file %s -grid_steady_file %s" %(hotspot_tool,hotspot_config,hotspot_floorplan,hotspot_ptrace,hotspot_temp_trace,hotspot_layer_file,hotspot_steady_temp,hotspot_grid_steady)

    #bashCommand="ls -lrt hotspot/test/" 
    #bashCommand="echo hello world" 
    print bashCommand 
    process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
    # Interact with process: Send data to stdin. Read data from stdout and stderr, until end-of-file is reached. Wait for process to terminate. 
    (output, err) = process.communicate()
     ## Wait for bashCommand to terminate. Get return returncode ##
    p_status = process.wait()
    print output
    #print "Command exit status/return code : ", p_status
    print "Printed the temperature trace"

# Copy the temperature trace
# TODO: Create analyzable graphs 

# ------------------------------------------------------------------------------------------------------------
# Print graphs of the outputs(transient simulation - ttrace) hotspot simulation.  
# TODO: Create graphs for wide IO and 2D 
#list_phase_wise_bank_avg_temp=np.zeros((int (math.ceil( (max_time_stamp - min_time_stamp + 1)/timestep )),number_of_banks))
#input_temperature_trace = hotspot_temp_trace
#temp_timestamp = 0
#with open("%s" %(input_temperature_trace)) as origin_file:
#    for line in origin_file:
#        if "B0" not in line:
#                for bnk in range(0,number_of_banks):
#                    list_phase_wise_bank_avg_temp[temp_timestamp][bnk] = line.split('\t')[bnk]
#                temp_timestamp = temp_timestamp + 1
#
## print list_phase_wise_bank_avg_temp
#
#if figure_temperature_output == 1:  
#    print "Print graphs of the outputs(transient simulation - ttrace) hotspot simulation"
#    if not os.path.exists(output_folder):
#            os.makedirs(output_folder)
#    bank_num = 0;
#    for i in bank_printing_pattern:
##    for i in range(number_of_banks):
#        plt.plot(timestamp_array, list_phase_wise_bank_avg_temp[:,i])
#        plt.title('Bank %d temperature versus time %d-%d micro-seconds' % (bank_num,min_time_stamp,max_time_stamp) )
#        plt.xlabel('Time (in microseconds)')
#        plt.ylabel('Temperature (in Celsius)')
#        plt.savefig('%s/Bank_%d_Temp.png' % (output_folder,bank_num))
#        bank_num = bank_num  + 1
#        plt.clf()
