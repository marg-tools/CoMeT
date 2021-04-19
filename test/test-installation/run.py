import os
import subprocess
import sys
import shutil

TEST_CASE_PATH = os.getcwd()
#print(TEST_CASE_PATH)
SNIPER_ROOT = os.path.dirname(os.path.dirname(TEST_CASE_PATH))
#print(SNIPER_ROOT)
TEST_CASE = os.path.join(TEST_CASE_PATH, 'test.c')
#print(TEST_CASE)
TEST_CASE_EXEC = os.path.join(TEST_CASE_PATH, 'test')
#print(TEST_CASE_EXEC)
CoMeT_RESULTS = os.path.join(TEST_CASE_PATH, 'comet_results')

if not os.path.exists(CoMeT_RESULTS):
    os.mkdir(CoMeT_RESULTS)

NUMBER_CORES = 16
CONFIG_DDR = 'gainestown_DDR'
CONFIG_3Dmem = 'gainestown_3Dmem'
CONFIG_2_5D = 'gainestown_2_5D'
CONFIG_3D = 'gainestown_3D'

def save_result(cfg, result_dir, console_output):
    filenames = ['all_transient_mem.init', 'combined_instpower.trace', 'combined_insttemperature.trace', 'combined_power.trace', 'combined_temperature.trace', 'energystats-temp.cfg', 
            'energystats-temp.py', 'energystats-temp.txt', 'energystats-temp.xml', 'full_power_core.trace', 'full_power_mem.trace', 'full_temperature_mem.trace', 'grid_steady_mem.log'
            , 'InstantaneousCPIStack.log', 'PeriodicCPIStack.log', 'PeriodicFrequency.log', 'PeriodicVdd.log', 'power_core.trace', 'power_mem.trace', 'sim.cfg', 'sim.info',
            'sim.out', 'sim.scripts.py', 'sim.stats.sqlite3', 'steady_temperature_mem.log', 'temperature_core.init', 'temperature_mem.init', 'temperature_mem.trace', 'temperature_core.trace', 'tmp']
    
    log_file = open(os.path.join(result_dir, 'simulation.log'), 'w+') 
    log_file.write(console_output) 
    for filename in filenames:
        if os.path.exists(os.path.join(TEST_CASE_PATH, filename)):
            shutil.move(os.path.join(TEST_CASE_PATH, filename), result_dir)
    shutil.move(os.path.join(TEST_CASE_PATH, 'hotspot'), result_dir)

def run(cfg):
    print('Running test case with configuration {}'.format(cfg))

    command_line = os.path.join(SNIPER_ROOT, 'run-sniper')

    args = '-v -s memTherm_core -n {num_cores} -c {config} -- {test_case}'  \
        .format(num_cores=NUMBER_CORES,
                config=cfg,
                test_case=TEST_CASE_EXEC)

    console_output = ''
    print(args)
    
    p = subprocess.Popen([command_line] + args.split(' '), stdout=subprocess.PIPE, stderr=subprocess.STDOUT, bufsize=1, cwd=TEST_CASE_PATH)
    with p.stdout:
        for line in iter(p.stdout.readline, b''):
            linestr = line.decode('utf-8')
            console_output += linestr
            print(linestr, end='')
    p.wait()

    if p.returncode != 0:
        raise Exception('return code != 0')

    result_dir = os.path.join(CoMeT_RESULTS, cfg)
    if not os.path.exists(result_dir):
        os.mkdir(result_dir)
    print('\n')
    print('Finished running test case with configuration {}.cfg'.format(cfg))

    save_result(cfg, result_dir, console_output)
    print('Result saved in {}'.format(result_dir))
    print('\n')

def auto_test():
    test_configs = [CONFIG_DDR, CONFIG_3Dmem, CONFIG_2_5D, CONFIG_3D]

    for config in test_configs:  
        run(config)
    
    print('\nTEST FOR ALL FOUR CONFIGURATIONS COMPLETED. PLEASE CHECK "comet_results" FOLDER\n')

def main():
    auto_test()


if __name__ == '__main__':
    main()

