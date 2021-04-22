# 3D-Mem-Therm-I

With the growing power density in both processors and memories (esp. 3D), thermal issues significantly impact application performance. Thus, increasingly researchers have become interested in understanding the performance, power, and thermal effects of the proposed changes in hardware and software.

3D-Mem-Therm-I is an architectural simulation tool for processors and memory. It supports various main memory types and its integration to processors (2D DDR, 3D memory, 2.5D integration, and 3D integration of core and memory). It integrates Sniper (performance simulator for x86), McPAT (power model for processors), CACTI3DD (power model for memory), and HotSpot (thermal simulator) to periodically provide designers - performance, power, and thermal information for processor and memory.  

# Part 1
- We have extended the source code of Sniper multicore simulator developed by the Performance Lab research group at Ghent University, Belgium. This code extension provides us with DRAM access information per memory bank at a periodic interval (unlike Sniper which gives a total count of DRAM accesses). It emits the access count for read and write separately, which can be useful for memories having asymmetric read/write energy and delay (e.g., NVM).
- We also integrated it to periodically invoke HotSpot thermal simulator (leakage aware and supports 2D/3D memory as well). The access trace of memory is passed to HotSpot, which generates the temperature trace of the 3D memory. The core is also simulated for temperature.
- The tool also generates a video showing the thermal pattern for various time steps.

# Getting Started

- Installation
	- sudo dpkg --add-architecture i386
	- sudo apt-get install binutils build-essential curl git libboost-dev libbz2-dev libc6:i386 libncurses5:i386 libsqlite3-dev libstdc++6:i386 python wget zlib1g-dev
	- sudo apt-get install ffmpeg python-matplotlib (optional step - if thermal trace video generation is required)

- Compile
	- In the main folder, make # or use 'make -j N' where N is the number of cores in your machine to use parallel make
	- Go to the hotspot\_tool folder and run 'make' to compile the hotspot tool for memory temperature estimation
	- Go to the hotspot\_c\_tool folder and run 'make' to compile the hotspot tool for core temperature estimation
	- Configure the path of the hotspot tool and config directory in the config file (search for tool\_path and config\_path variables)

- Running an application 
	- cd test/app\_name
	- make run

- To see the DRAM accesses per memory bank, please use the application my\_test\_case inside test folder
	- To use this feature the application should be long enough to run for atleast 1 ms.
	- cd test/dram-access-trace
	- make run
- Sample output: Apart from Sniper messages and commandline, we see a detailed bank level trace for DRAM accesses. Please note the output like shown below in the terminal output.

```
   	Time	#READs	#WRITEs	#Access		Bank Counters


@& 	1000	8368	0	8368		1044, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1043, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1046, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1044, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1050, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1046, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1046, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1049, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 

@& 	2000	8010	0	8010		1002, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1002, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 


```
	- Multiple files containing simulation outputs will be generated (sim.cfg, sim.out etc)
	- If we sum the #Access per epoch, the number is same as "num dram accesses" under "DRAM summary" in sim.out file
	- If you are able to verify this, then you have successfully setup the system.


- To run the application on 32/48 cores with 16 channels
	- Use gainestown\_16channel\_32cores.cfg and gainestown\_16channel\_48cores.cfg respectively
	- For 32 cores, we are required to launch n=32 application instances so we collect and play back traces simultaneously on 32 different cores
	- To run on 32 cores with 16 DRAM channels architecture
		- cd test/multiple\_core
		- make run
		- The total number of DRAM accesses in detailed trace should match with number of DRAM accesses in sim.out file

- Understanding the output
	- To see the output corresponding to number of DRAM read/write accesses per bank, the application should run for atleast 1 ms. This is due to length of epoch that we use for counting the DRAM accesses and some other delays.
	- The output of `make run` displays the time interval in which a DRAM access was made, #reads and #writes and also reports the number of DRAM accesses directed to a particular bank.


- An example testcase which calls the thermal simulation periodically using hotspot is also created in the thermal\_example folder. The simulation can be configured for various memory and core configurations
	- cd test/thermal\_example
	- open Makefile and use appropriate config file (pre-designed) as per the following descriptions. The parameter `type\_of\_stack` in the config file controls the architecture type.
		- gainestown_DDR - 4x4 core and an external 4x4 bank DDR main memory (2D memory). It invokes two different hotspot runs to estimate temperatures for core and memory separately.
		- gainestown_3Dmem - 4x4 core and an external 4x4x8 banks 3D main memory. It invokes two different hotspot runs to estimate temperatures for core and memory separately.
		- gainestown_2_5D - 4x4 core and a 4x4x8 banks 3D main memory integrated on the same die (2.5D architecture). It invokes a single hotspot run and simulates core and memory together.
		- gainestown_3D - 4x4 core on top of a 4x4x8 banks 3D main memory. It invokes a single hotspot run and simulates core and memory together.
	- `make run > logfile`
	- To generate the thermal trace video, please run `../../scripts/heatView.sh full_temperature_mem.trace maps` . The video will be an avi file generated in the maps folder. Currently the script works only for 3Dmem architecture.
	
    - Multiple files would be generated, but the useful ones are described below (these files would have \_mem and\_core suffix to indicate if they are for memory or core temperature simulation):
	- full\_temperature.trace - the temperature trace at periodic intervals for various banks and logic cores in the 3D memory. core trace is not generated in case of a 2.5D and 3D architecture.
	- logfile - the simulation output from the terminal. bank\_access\_counter lists the access counts for different banks

# Open Scheduler

- features
	- random arrival times of workloads (open system)
	- API for application mapping and DVFS policies
- enable with `type=open` in base.cfg

## Configuration Help for Open Scheduler

- task arrival times: use the config parameters in `scheduler/open` in `base.cfg`
- mapping: select logic with `scheduler/open/logic` and configure with additional parameters (`core_mask`, `preferred_core`)
- DVFS: select logic with `scheduler/open/dvfs/logic` and configure accordingly

# Simulation Control Package

- features
	- batch run many simulations with different configurations
		- annotate configuration options in `base.cfg` with tags following the format `# cfg:<TAG>` (ONLY `base.cfg` supported at the moment)
		- specify list of tags per run in `run.py`. Only the associated configuration options will be enabled
		- for an example: see `example` function in `run.py` and `scheduler/open/dvfs/constFreq` in `base.cfg` to run an application at different frequencies
		- IMPORTANT: make sure that all your configuration options have a match in `base.cfg`
	- create plots of temperature, power, etc. over time
	- API to automatically parse finished runs (`resultlib`)
- usage
	- configure basic settings in `simulationcontrol/config.py`
	- specify your runs in `simulationcontrol/run.py`
	- `python3 run.py`
	- print overview of finished simulations: `python3 parse_results.py`

# Automated Test Suite

- Test suite location
	- cd test/test-installation

- Running automated test suite to ensure working of different features of CoMeT
	- make run
	- As each system configuration is successfully simulated, you will see messages as below
		- Running test case with configuration gainestown_3D
		- Finished running test case with configuration gainestown_3D.cfg
		- Test case passed for configuration gainestown_3D.cfg
			- OR Test case failed for configuration gainestown_3D.cfg. Please check 3D-Mem-Therm-I/test/test-installation/comet_results/gainestown_3D/error_log for details.
		- Video for gainestown_3D saved in /3D-Mem-Therm-I/test/test-installation/comet_results/gainestown_3D/maps
			- OR Video generation failed for configuration gainestown_3D.cfg. Check 3D-Mem-Therm-I/test/test-installation/comet_results/gainestown_3D/video_gen_error.log for details.
		- Result saved in path-to-3D-Mem-Therm-I/test/test-installation/comet_results/gainestown_3D
	- make clean

- After the test finishes successfully, a folder "comet\_results" will be created in the same folder
	- It contains sub-folders, one for each system configurations (DDR, 3Dmem, 3D and 2\_5\_D)
	- Each sub-folder contains architecture simulation files and thermal simulation files for the test case
	- For per epoch DRAM access trace and Sniper log of test case, please refer simulation\_log file
	- For thermal simulation results, please refer to full\_temperature.trace file and other related files

- Video generation
	- If the simulation for a configuration finishes successfully and pre-requisites for generating videos are installed in your host machine, then the video is generated inside "maps" folder of that configuration.
	- If the simulation for a configuration crashes, no video is generated. Further, an error\_log is generated for that configuration stating why simulation failed.
	- If the simulation finishes successfully but pre-requisites for generating videos are not met, a file named video\_gen\_error.log is generated to report the error for that configuration.

- Test summary
	- The complete summary of the running the test suite is written to a file named test\_summary.
	- Also, some logs are printed during the execution of test\_suite.
