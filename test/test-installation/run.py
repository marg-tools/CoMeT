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
ENABLE_VIDEO_GENERATION = 1

if not os.path.exists(CoMeT_RESULTS):
    os.mkdir(CoMeT_RESULTS)

NUMBER_CORES = 4
CONFIG_DDR = 'gainestown_DDR'
CONFIG_3Dmem = 'gainestown_3Dmem'
CONFIG_2_5D = 'gainestown_2_5D'
CONFIG_3D = 'gainestown_3D'
CONFIG_3D_8_CORES = 'gainestown_3D_8core_2L'
CONFIG3Dmem_8_CORES = 'gainestown_3Dmem_8core_2L'

test_summary = ''
pass_count = 0
test_configs = [CONFIG_3Dmem, CONFIG_DDR, CONFIG_2_5D, CONFIG_3D, CONFIG_3D_8_CORES, CONFIG3Dmem_8_CORES]



def save_result(cfg, result_dir, console_output):
    filenames = ['all_transient_mem.init', 'combined_instpower.trace', 'combined_insttemperature.trace', 'combined_power.trace', 'combined_temperature.trace', 'energystats-temp.cfg', 
            'energystats-temp.py', 'energystats-temp.txt', 'energystats-temp.xml', 'full_power_core.trace', 'full_power_mem.trace', 'full_temperature_mem.trace', 'grid_steady_mem.log'
            , 'InstantaneousCPIStack.log', 'PeriodicCPIStack.log', 'PeriodicFrequency.log', 'PeriodicVdd.log', 'power_core.trace', 'power_mem.trace', 'sim.cfg', 'sim.info',
            'sim.out', 'sim.scripts.py', 'sim.stats.sqlite3', 'steady_temperature_mem.log', 'temperature_core.init', 'temperature_mem.init', 'temperature_mem.trace', 
            'temperature_core.trace', 'tmp', 'steady_temperature_core.log', 'all_transient_core.init', 'grid_steady_core.log']
    
    log_file = open(os.path.join(result_dir, 'simulation.log'), 'w+') 
    log_file.write(console_output)
    
    for filename in filenames:
        if os.path.exists(os.path.join(TEST_CASE_PATH, filename)):
            shutil.move(os.path.join(TEST_CASE_PATH, filename), os.path.join(result_dir, filename))

    if os.path.exists(os.path.join(result_dir, 'hotspot/')):
        shutil.rmtree(os.path.join(result_dir, 'hotspot/'))
    os.makedirs(os.path.join(result_dir, 'hotspot/'))

    shutil.move(os.path.join(TEST_CASE_PATH, 'hotspot'), os.path.join(result_dir, 'hotspot'))

def test_thermal_feature(cfg):
    global test_summary
    global pass_count

    print('Running test case with configuration {}'.format(cfg))
    print('---------------------------------------------------')

    test_case_result = ''
    command_line = os.path.join(SNIPER_ROOT, 'run-sniper')

    args = '-v -s memTherm_core -n {num_cores} -c {config} -- {test_case}'  \
        .format(num_cores=NUMBER_CORES,
                config=cfg,
                test_case=TEST_CASE_EXEC)

    console_output = ''
    print(command_line, args)
    
    p = subprocess.Popen([command_line] + args.split(' '), stdout=subprocess.PIPE, stderr=subprocess.STDOUT, cwd=TEST_CASE_PATH)
    with p.stdout:
        for line in iter(p.stdout.readline, b''):
            linestr = line.decode('utf-8')
            console_output += linestr
    linestr.rsplit("\n",4)[0]
    p.wait()

    print('\n')
    print('Finished running test case with configuration {}.cfg'.format(cfg))
    result_dir = os.path.join(CoMeT_RESULTS, cfg)
    if not os.path.exists(result_dir):
        os.mkdir(result_dir)
 
    if not os.path.exists(os.path.join(TEST_CASE_PATH, 'sim.cfg')):
        shutil.rmtree(result_dir)
        os.mkdir(result_dir)
        if not os.path.exists(os.path.join(result_dir, 'error_log')):
            f = open(os.path.join(result_dir, 'error_log'), 'w+')
            f.write(console_output)        
        test_case_result += 'Test case failed for configuration {}.cfg. Check {} for details.'.format(cfg,os.path.join(result_dir, 'error_log'))
        print(test_case_result)
        print('\n')
        test_summary += test_case_result
        test_summary += '\n'
        return 0
        
    test_case_result = 'Test case passed for configuration {}.cfg'.format(cfg)
    print(test_case_result)
    test_summary += test_case_result
    test_summary += '\n'
    pass_count += 1
    save_result(cfg, result_dir, console_output)
    print('Simulation result saved in {}'.format(result_dir))
    print('\n')

def test_video_generation_feature(cfg):
   
    global pass_count 
    global test_summary
    console_output = ''
    test_case_result = ''
    SAMPLING_INTERVAL = 1
    BANKS_IN_Z = 8
    CORES_IN_Z = 1
    ARCH_TYPE = cfg.strip("gainestown_")
    if ARCH_TYPE == "DDR":
        BANKS_IN_Z = 1
    if ARCH_TYPE == "2_5D":
        ARCH_TYPE = "2.5D"
    if ARCH_TYPE == "3D_8core_2L":
        CORES_IN_Z = 2
        ARCH_TYPE = "3D"
    if ARCH_TYPE == "3Dmem_8core_2L":
        CORES_IN_Z = 2
        ARCH_TYPE = "3Dmem"

    if ENABLE_VIDEO_GENERATION:   
        if os.path.exists(os.path.join(os.path.join(CoMeT_RESULTS, cfg), 'combined_temperature.trace')):
            command_line = os.path.join(SNIPER_ROOT, 'scripts/heatView.py')

            video_dir = os.path.join(os.path.join(CoMeT_RESULTS, cfg), 'video')
            if os.path.exists(video_dir):
                shutil.rmtree(video_dir)
            os.mkdir(video_dir)
    
            args = '-t {trace_file} -o {video_dest} -s {sampling_interval} --arch_type {arch} --banks_in_z {banks_z} --cores_in_z {cores_z}'  \
                .format(trace_file=os.path.join(os.path.join(CoMeT_RESULTS, cfg), 'combined_temperature.trace'),
                        video_dest=video_dir,
                        sampling_interval=SAMPLING_INTERVAL,
                        arch=ARCH_TYPE,
                        banks_z=BANKS_IN_Z,
                        cores_z=CORES_IN_Z)
            print('Generating video for {}\n'.format(cfg))

            p = subprocess.Popen(['python3', command_line] + args.split(' '), stdout=subprocess.PIPE, stderr=subprocess.STDOUT, bufsize=1, cwd=TEST_CASE_PATH)
            with p.stdout:
                for line in iter(p.stdout.readline, b''):
                    linestr = line.decode('utf-8')
                    console_output += linestr
            p.wait()

            dir = os.listdir(video_dir)
            if len(dir) == 0:
                error_log = open(os.path.join(os.path.join(CoMeT_RESULTS, cfg), 'video_gen_error.log'), 'w+')
                error_log.write(console_output)
                test_case_result += 'Video generation failed for configuration {}.cfg. Please check {} for details.'.format(cfg,os.path.join(os.path.join(CoMeT_RESULTS, cfg), 'video_gen_error.log'))
                print(test_case_result)
                print('\n')
                test_summary += test_case_result
                test_summary += '\n'
                return 0
            else:
                pass_count += 1
                video_log_file = open(os.path.join(os.path.join(CoMeT_RESULTS, cfg), 'video_generation.log'), 'w+')
                video_log_file.write(console_output)
                test_summary += 'Video generated for {} and saved {}'.format(cfg, video_dir)
                test_summary += '\n'
                print('Video for {} saved in {}\n'.format(cfg, video_dir))
        else:
            test_summary += 'Video for {} cannot be generated due to unsuccessful simulation.\n'.format(cfg)
            test_summary += '\n'
            print('Video for {} cannot be generated due to unsuccessful simulation.\n'.format(cfg))
    else:
        print("Video generation disabled. Skipping testing this feature.\n")


def auto_test():
    global test_summary
    global pass_count

    for config in test_configs:  
        test_thermal_feature(config)
        test_video_generation_feature(config)
    
    f = open("test_summary.txt", "w")
    f.write("Summary of CoMet Features\n")
    f.write("=========================\n")
    f.write(test_summary)
    f.write("\n{} of 12 cases passed".format(pass_count))

    print('\nTest for all four configurations and video generation completed. Please check test_summary for details\n')
    print('Simulation results and videos stored in comet_results.\n')

def main():
    auto_test()


if __name__ == '__main__':
    main()

