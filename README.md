<!-- # *CoMeT*: Integrated <ins>Co</ins>re and <ins>Me</ins>mory <ins>T</ins>hermal Simulation Toolchain for 2D, 2.5D, and 3D Processors-->
# *CoMeT*: An Integrated Interval Thermal Simulation Toolchain for 2D, 2.5D, and 3D Processor-Memory Systems

With the growing power density in both cores and memories (esp. 3D), thermal issues significantly impact performance and reliability. Thus, increasingly researchers have become interested in understanding the performance, power, and thermal effects of the proposed changes in hardware and software. *CoMeT* is an integrated <ins>Co</ins>re and <ins>Me</ins>mory <ins>T</ins>hermal simulation toolchain, providing performance, power, and temperature parameters at regular intervals (epoch) for both cores and memory. It enables computer architects to evaluate various core and main memory integration options (3D, 2.5D, 2D) and analyze runtime management policies. 

*CoMeT* extends the Sniper multicore performance simulator's source code to provide DRAM access information per memory bank (at regular intervals). It emits the access count for reads and writes separately, which can be helpful for memories having asymmetric read/write energy and delay (e.g., NVM). Periodically, using McPAT and CACTI, the core and memory power are computed and fed to HotSpot for (temperature-dependent leakage power-aware) thermal analysis. A thermal management policy monitors the temperature and, in the case of core or memory heating, it redistributes/reduces the power, then the performance simulation is resumed.

## Features
[//]: # "(*CoMeT* is an integrated thermal simulation toolchain for cores and memory. It integrates Sniper (performance simulator for x86), McPAT (power model for cores), CACTI3DD (power model for memory), and HotSpot (thermal simulator) to provide designers - performance, power, and thermal information, at regular intervals for both core and memory." 

Following are the salient features:
1. Supports various main memory types and their integration to cores (2D off-chip DDR, 3D off-chip memory, 2.5D integration, and 3D stacking of core and memory).
2. Has a built-in temperature video generation tool, namely *HeatView*, which supports all core-memory configurations. Additionally, for 3D architectures, a video with a layer-wise 2D view is generated.
3. A default thermal management policy with an *OnDemand governer* and *open scheduler* is included to quick-start the design process. Designers can easily modify the default policy and evaluate different thermal management approaches.
4. To ease user development and reduce debugging, *CoMET* provides an automatic build verification test suite (smoke testing) that checks critical functionalities across various architectures. Users can easily add test cases to the smoke tests.
5. Provides an automated grid-based floorplan generator (*floorplanlib*), which supports the generation of 2D, 2.5D, and 3D floorplans.
6. Supports PARSEC, SPLASH-2, and SPEC CPU2017 benchmark suites. Users can also run their benchmarks.
7. Using the *SimulationControl* feature, users can run simulations in batch mode, taking the list of workloads (mixes of benchmarks) and configurations as input. Further, to enable detailed output analysis, *SimulationControl* generates additional outputs, such as performance, power, temperature variation (versus time) graphs, and detailed CPI bar charts. 


## Publication

### CoMeT: An Integrated Interval Thermal Simulation Toolchain for 2D, 2.5 D, and 3D Processor-Memory Systems

Details of CoMeT can be found in our TACO 2022 paper, and please consider citing this paper in your work if you find this tool useful in your research.

> Lokesh Siddhu, Rajesh Kedia, Shailja Pandey, Martin Rapp, Anuj Pathania, Jörg Henkel, and Preeti Ranjan Panda. **"CoMeT: An Integrated Interval Thermal Simulation Toolchain for 2D, 2.5 D, and 3D Processor-Memory Systems"**. *"ACM Transactions on Architecture and Code Optimization"* Volume 19 Issue 3 Article No.: 44 pp 1–25 https://doi.org/10.1145/3532185.

[ACM DL](https://dl.acm.org/doi/full/10.1145/3532185) 

## The CoMeT User Manual

Please refer to [CoMeT User Manual](https://github.com/marg-tools/CoMeT/blob/main/The%20CoMeT%20User%20Manaual.pdf) to learn how to write custom scheduling policies that perform thermal-aware Dynamic Voltage Frequency Scaling (DVFS), Memory Low-Power Mode, Task Mappings, and Task Migrations.


## 1 - Getting Started (Installation)


### Installing Basic Tools

`sudo apt install git make python gcc` 

### Cloning the repo

`git clone https://github.com/marg-tools/CoMeT.git` 

### PinPlay
Download and extract Pinplay 3.2 to the root *CoMeT* directory as ```pin_kit```
```sh
wget --user-agent="Mozilla"  https://www.intel.com/content/dam/develop/external/us/en/protected/pinplay-drdebug-3.2-pin-3.2-81205-gcc-linux.tar.gz
tar xf pinplay-drdebug-3.2-pin-3.2-81205-gcc-linux.tar.gz
mv pinplay-drdebug-3.2-pin-3.2-81205-gcc-linux pin_kit
```

### Docker
*CoMeT* compiles and runs inside a Docker container. Therefore, we need to download & install Docker. For more info: https://docs.docker.com/engine/install/ubuntu/

### Running a Docker image
After installing Docker, let us now create a `container` using the `Dockerfile`.
```sh
cd docker
make # build the Docker image
make run # starts running the Docker image. Please ignore "docker groups: cannot find name for group id 1000"
cd .. # return to the base Sniper directory (while running inside of Docker)
```

### Compiling Sniper
```sh
make
```


### Compiling HotSpot
Let us compile the [HotSpot] simulator, which shipped with *CoMeT*.
```sh
cd hotspot_tool/
make
cd ..
```

## 2 - Running an Application


```sh
cd test/thermal_example
make run | tee logfile # Runs application, displays DRAM bank accesses, outputs temperature files
```

<!-- - To see the DRAM accesses per memory bank, please use the application my\_test\_case inside test folder
    - To use this feature, the application should to run for atleast 1 ms as we collect trace at every 1 ms.
    - cd test/dram-access-trace
    - make run
-->

- The output of `make run` displays the time interval or epoch (in µs) in which DRAM access was made, #reads and #writes, and reports the number of DRAM accesses directed to a particular bank. Further, detailed power, temperature traces at epoch level are generated. 

- To enable the above performance, power, and temperature outputs, we have added `-s memTherm_core` and `-c gainestown_3D` in the Sniper run command (please see *Makefile*). The above flags can be used to enable *CoMeT* simulation for any Sniper compatible executable.


- **Sample output:** Apart from Sniper messages and command line, we see a detailed bank-level trace for DRAM accesses. Please note the terminal output with the default epoch of 1 ms (= 1000 µs) shown below.

```sh
    Time    #READs  #WRITEs #Access Address     #BANK   Bank Counters

@&  1000    10455   8710    19165       144, 132, 151, 162, 149, 160, 144, 130, 145, 140, 143, 164, 147, 158, 145, 133, 142, 131, 148, 156, 144, 155, 140, 134, 147, 129, 143, 162, 147, 167, 139, 129, 140, 130, 156, 155, 144, 153, 144, 138, 156, 137, 155, 157, 150, 169, 145, 142, 152, 137, 156, 157, 144, 156, 138, 136, 147, 127, 142, 160, 147, 160, 142, 129, 138, 133, 151, 156, 145, 155, 143, 135, 145, 129, 144, 157, 143, 162, 143, 130, 144, 129, 149, 170, 147, 164, 144, 128, 145, 132, 144, 155, 149, 164, 146, 133, 275, 254, 280, 282, 143, 163, 150, 134, 152, 125, 146, 166, 141, 164, 143, 126, 142, 130, 146, 153, 139, 156, 144, 136, 150, 126, 139, 156, 148, 165, 148, 130, 

@&  2000    15742   12212   27954       206, 188, 225, 249, 240, 267, 197, 164, 229, 219, 201, 225, 193, 196, 244, 235, 205, 191, 226, 246, 241, 264, 196, 167, 229, 217, 202, 220, 193, 196, 244, 235, 205, 191, 226, 246, 241, 264, 196, 167, 236, 218, 208, 225, 196, 205, 248, 240, 212, 193, 233, 251, 241, 267, 197, 165, 230, 215, 202, 223, 193, 199, 245, 233, 206, 189, 226, 249, 241, 267, 197, 165, 230, 220, 202, 218, 188, 202, 250, 230, 211, 196, 223, 251, 241, 265, 200, 170, 229, 222, 203, 216, 190, 203, 255, 236, 215, 193, 231, 250, 244, 264, 199, 167, 234, 215, 197, 229, 194, 196, 244, 236, 204, 191, 228, 247, 242, 264, 196, 168, 233, 211, 199, 227, 196, 200, 249, 239, 
.
.
.
.
Total number of DRAM read requests = 48989 

Total number of DRAM write requests = 32774
```
- Sum of DRAM read requests and write requests equals *num dram accesses* in *sim.out* file.
    - You can also specify --roi flag in config file to obtain DRAM access trace for a region of interest.

- **Selected useful files:** Multiple files containing simulation outputs will be generated (*sim.cfg*, *sim.out*, etc.), but the useful ones are described below, these files would have \_mem and\_core suffix (instead of prefix *combined_*) to indicate if they are for memory or core temperature simulation:
    - *combined_temperature.trace* - the temperature trace of core and memory at periodic intervals combined together.
    - *combined_power.trace* - the power trace of core and memory at periodic intervals combined together.
    - *full_temperature.trace* (core and mem) - the temperature trace at periodic intervals for various banks and logic cores in the 3D memory. core trace is not generated in case of a 2.5D and 3D architecture.
    - *logfile* - the simulation output from the terminal. bank\_access\_counter lists the access counts for different banks.

*If you are able to verify this, then you have **successfully run** an application.*

<!-- 
## 3 - Understanding the *CoMeT* output

- To see the output corresponding to number of DRAM read/write accesses per bank, the application should run for atleast 1 ms. This is due to length of epoch that we use for counting the DRAM accesses and some other delays.

 -->

## 3 - *CoMeT* Features


### 3.1 Support for various Core-Memory Integrations

<details>
<summary>Click here to open details</summary>

*CoMeT* can be configured for various memory and core configurations. 

We show changing input configuration, from stacked (core + 3D memory) to off-chip 3D memory, for the *thermal_example* test case. 

```sh
#Change to appropriate working directory
cd test/thermal_example

#Change configuration from gainestown_3D to gainestown_3Dmem. Can be done in a text editor also.
sed -i 's/-c gainestown_3D/-c gainestown_3Dmem/g' Makefile

#Running CoMeT
make run > logfile
```

- **Setting up input configuration:** Open Makefile and change the config file used (specified with -c option in the sniper command). The options are as follows:

    - gainestown_DDR - 2x2 core and an external 4x4 bank DDR main memory (2D memory).<!--It invokes two different hotspot runs to estimate temperatures for core and memory separately.-->
    - gainestown_3Dmem - 2x2 core and an external 4x4x8 banks 3D main memory.<!-- It invokes two different hotspot runs to estimate temperatures for core and memory separately.-->
    - gainestown_2_5D - 2x2 core and a 4x4x8 banks 3D main memory integrated on the same die (2.5D architecture).<!-- It invokes a single hotspot run and simulates core and memory together.-->
    - gainestown_3D - 2x2 core on top of a 4x4x8 banks 3D main memory.<!-- It invokes a single hotspot run and simulates core and memory together.-->

<!-- 
Open Makefile and use appropriate config file (pre-designed) as per the following descriptions. The parameter `type_of_stack` in the config file controls the architecture type.
    - gainestown_DDR - 2x2 core and an external 4x4 bank DDR main memory (2D memory). It invokes two different hotspot runs to estimate temperatures for core and memory separately.
    - gainestown_3Dmem - 2x2 core and an external 4x4x8 banks 3D main memory. It invokes two different hotspot runs to estimate temperatures for core and memory separately.
    - gainestown_2_5D - 2x2 core and a 4x4x8 banks 3D main memory integrated on the same die (2.5D architecture). It invokes a single hotspot run and simulates core and memory together.
    - gainestown_3D - 2x2 core on top of a 4x4x8 banks 3D main memory. It invokes a single hotspot run and simulates core and memory together.
     -->

</details>


### 3.2 HeatView: A temperature video generation tool

<details>
<summary>Click here to open details</summary>

- To generate the thermal trace video (for stacked 4-core and 3D, 8 layer, 128 bank memory architechure), please run `python3 ../../../scripts/heatView.py --cores_in_x 2 --cores_in_y 2 --cores_in_z 1 --banks_in_x 4 --banks_in_y 4 --banks_in_z 8 --arch_type 3D --traceFile combined_temperature.trace --output maps`. The video will be an avi file generated in the maps folder using the *combined_temperature.trace*. Detailed command line arguments for *HeatView* are given below.

```
Usage: python3 heatView.py arguments
Switches and command-line arguments: 
     --cores_in_x: Number of cores in x dimension (default 4)
     --cores_in_y: Number of cores in y dimension (default 4)
     --cores_in_z: Number of cores in z dimension (default 1)
     --banks_in_x: Number of memory banks in x dimension (default 4)
     --banks_in_y: Number of memory banks in y dimension (default 4)
     --banks_in_z: Number of memory banks in z dimension (default 8)
     --arch_type: Architecture type = 3D or no3D (default no3D)
     --plot_type: Generated view = 3D or 2D (default 3D)
     --layer_to_view: Layer number to view in 3D plot (starting from 0) (default 0)
     --type_to_view: Layer type to view in 3D plot (CORE or MEMORY) (default MEMORY)
     --verbose (or -v): Enable verbose output
     --inverted_view (or -i): Enable inverted view (heat sink on bottom)
     --debug: Enable debug priting
     --tmin: Minimum temperature to use for scale (default 65 deg C)
     --tmax: Maximum temperature to use for scale (default 81 deg C)
     --samplingRate (or -s): Sampling rate, specify an integer (default 1)
     --traceFile (or -t): Input trace file (no default value)
     --output (or -o): output directory (default maps)
     --clean (or -c): Clean if directory exists
```
</details>

### 3.3 Dynamic Thermal Management

<details>
<summary>Click here to open details</summary>

Open Scheduler

- features
    - random arrival times of workloads (open system)
    - API for application mapping and DVFS policies
- enable with `type=open` in base.cfg

Configuration Help for Open Scheduler

- task arrival times: use the config parameters in `scheduler/open` in `base.cfg`
- mapping: select logic with `scheduler/open/logic` and configure with additional parameters (`core_mask`, `preferred_core`)
- DVFS: select logic with `scheduler/open/dvfs/logic` and configure accordingly

These policies are implemented in `common/scheduler/policies`.
Mapping policies derive from `MappingPolicy`, DVFS policies derive from `DVFSPolicy`.
After implementing your policy, instantiate it in `SchedulerOpen::initMappingPolicy` / `SchedulerOpen::initDVFSPolicy`.

</details>

### 3.4 Build verification test suite

<details>
<summary>Click here to open details</summary>

- Running automated test suite to ensure working of different features of *CoMeT*
```sh
cd test/test-installation
make run
```
- As each system configuration is successfully simulated, you will see messages as below
    - Running test case with configuration gainestown_3D
    - Finished running test case with configuration gainestown_3D.cfg
    - Test case passed for configuration gainestown_3D.cfg
    - OR Test case failed for configuration gainestown_3D.cfg. Please check test/test-installation/comet_results/gainestown_3D/error_log for details.
    - Video for gainestown_3D saved in test/test-installation/comet_results/gainestown_3D/maps
    - OR Video generation failed for configuration gainestown_3D.cfg. Check test/test-installation/comet_results/gainestown_3D/video_gen_error.log for details.
    - Result saved in test/test-installation/comet_results/gainestown_3D
    - make clean

- After the test finishes successfully, a folder "comet\_results" will be created in the same folder
    - It contains sub-folders, one for each system configurations (DDR, 3Dmem, 3D and 2\_5\_D)
    - Each sub-folder contains architecture simulation files and thermal simulation files for the test case
    - For per epoch DRAM access trace and Sniper log of test case, please refer simulation\_log file
    - For thermal simulation results, please refer to full\_temperature.trace file and other related files

- Video generation
    - If the simulation for a configuration finishes successfully and pre-requisites for generating videos are installed in your host machine, then the video is generated inside "video" folder of that configuration.
    - If the simulation for a configuration crashes, no video is generated. Further, an error\_log is generated for that configuration stating why simulation failed.
    - If the simulation finishes successfully but pre-requisites for generating videos are not met, a file named video\_gen\_error.log is generated to report the error for that configuration.

- Test summary
    - The complete summary of the running the test suite is written to a file named test\_summary.
    - Also, some logs are printed during the execution of test\_suite.

</details>

### 3.5 Automated floorplan generator (floorplanlib)

<details>
<summary>Click here to open details</summary>

### General Usage

The floorplan creation helpers are an optional tool, you can also use your custom floorplans instead.
Usage:
- create floorplans (and layer configuration files, HotSpot configuration files)
- change configuration to reference to the created files (for an example see gainestown_*)

#### Examples

##### off-chip 2D
```bash
python3 floorplanlib/create.py \
    --mode DDR \
    --cores 4x4 --corex 1mm --corey 1mm \
    --banks 8x8 --bankx 0.9mm --banky 0.9mm \
    --out my_2d_floorplan
```

##### off-chip 3D memory
```bash
python3 floorplanlib/create.py \
    --mode 3Dmem \
    --cores 4x4 --corex 1mm --corey 1mm \
    --banks 8x8x2 --bankx 0.9mm --banky 0.9mm \
    --out my_3d_oc_floorplan
```

##### 2.5D (3D memory and 2D core on the same interposer)
```bash
python3 floorplanlib/create.py \
    --mode 2.5D \
    --cores 4x4 --corex 1mm --corey 1mm \
    --banks 8x8x2 --bankx 0.9mm --banky 0.9mm \
    --core_mem_distance 7mm \
    --out my_2.5d_floorplan
```

##### 3D (fully-integrated 3D stack of cores and memory)
```bash
python3 floorplanlib/create.py \
    --mode 3D \
    --cores 4x4 --corex 0.9mm --corey 0.9mm \
    --banks 8x8x4 --bankx 0.45mm --banky 0.45mm \
    --out my_3d_floorplan
```

</details>


### 3.6 Supports PARSEC, SPLASH-2, SPEC 2017, and Deep Neural Networks

<details>
<summary>Click here to open details</summary>

#### Compiling the Benchmarks:
```sh
#setting $GRAPHITE_ROOT to CoMeT's root directory
export GRAPHITE_ROOT=$(pwd)
cd benchmarks
#setting $BENCHMARKS_ROOT to the benchmarks directory
export BENCHMARKS_ROOT=$(pwd)
#compiling the benchmarks
make
#Running the benchmarks
make run
```
<!-- - You are required to 'make' twice for correct compilation -->
- You will see that compilation only passes for PARSEC and SPLASH benchmarks, and fails for SPEC benchmarks. Ignore the failed compilation for SPEC benchmarks.
- For the SPEC 2017 benchmarks,
    - Download the pinballs from the below link
        - https://www.spec.org/cpu2017/research/simpoint.html
    - Create a folder "SPEC" inside test folder
    - Extract the pinballs inside test/SPEC 
    - Run the benchmark. Given below is an example for a 4-core simulation.
    ```
    cd test/SPEC
    ../../../../../run-sniper -v -s memTherm_core -c gainestown_3Dmem -n 4 --pinballs $SIM_PATH,$SIM_PATH,$SIM_PATH,$SIM_PATH
    ```
    - $SIM\_PATH represents path of a specific *.address* for the SPEC benchmark 

#### Running Deep Neural Networks (Darknet Open Source Neural Networks in C)
```sh
cd test/darknet
# Compiling the darknet source code
make
# Running 4 instances of AlexNet on gainestown_3Dmem architecture
# Download alexnet.weights (pre-trained model for AlexNet) from https://pjreddie.com/darknet/imagenet/
./run.sh
```
##### Note
	- Running the entire darknet source code would take days.
	- Insert appropriate region of interest (ROI) markers in the source code, depending on the phase of DNN you want to simulate.
	- Files of interest in darknet framework are inside src folder.
	- Relevant functions -- load_network(), forward_network(), train_classifier(), try_classifier(), predict_classifier()
	- Use SimRoiStart() and SimRoiEnd() to specify ROI.
</details>

### 3.7 Simulation Control
<details>
<summary>Click here to open details</summary>

- features
    - batch run many simulations with different configurations
        - annotate configuration options in config files (e.g., in `base.cfg` or `gainestown_3D.cfg`) with tags following the format `# cfg:<TAG>`
        - specify list of tags per run in `run.py`. Only the associated configuration options will be enabled
        - for an example: see `example` function in `run.py` and `scheduler/open/dvfs/constFreq` in `base.cfg` to run an application at different frequencies
        - IMPORTANT: make sure that all your configuration options have a match in `base.cfg`
    - create plots of temperature, power, etc. over time
    - create video of temperature (with HeatView)
    - API to automatically parse finished runs (`resultlib`)
- usage
    - configure basic settings in `simulationcontrol/config.py`
    - specify your runs in `simulationcontrol/run.py`
    - `python3 run.py`
    - print overview of finished simulations: `python3 parse_results.py`

Quickly list the finished simulations:
```sh
cd simulationcontrol
PYTHONIOENCODING="UTF-8" python3 parse_results.py
```

Each run is stored in a separate directory in the results directory (see 4).
For quick visual check, many plots are automatically generated for you (IPS, power, etc).

To do your own (automated) evaluations, see the `simulationcontrol.resultlib` package for a set of helper functions to parse the results. See the source code of `parse_results.py` for a few examples.
</details>

### 3.8 Running subcore (with component details within a core) simulations
<details>
<summary>Click here to open details</summary>

CoMeT also allows running subcore level simulations if one is interested to find out the hot regions within a core. To enable subcore simulations in CoMeT, do the following:
- In `config/base.cfg`, there is a section named `[core_power]`. Make everything as true except for the tp and l3 being false. These reflect various sub components of the core.
- A single core floorplan template is at ./config/hotspot/3Dmem_subcore/template.flp. We use this template for our simulations. If needed, one can change the dimensions.
- The `floorplanlib` generates multi-core floorplan by repeating these subcore components. A default created floorplan is available (4-core, 3D-ext configuration) in `./config/hotspot/3Dmem_subcore`
      - The extra switch to generate such multi-core floorplan is: --subcore-template config/hotspot/3Dmem_subcore/template.flp
- A default config file is available at `config/gainestown_3Dmem_subcore.cfg`. Use this for the simulation (or create own as per the requirements)
- PLEASE NOTE THAT heatview DOES NOT SUPPORT subcore video generation.


</details>

### 3.9 Running reliability simulations
<details>
<summary>Click here to open details</summary>

CoMeT can simulate the reliability of cores and subcore components. To use this functionality, do the following:

- In `config/base.cfg`, there is a section `[reliability]`. Make `enabled` true to enable reliability simulations.
- If you want to use time warping (stretching epochs to reach low reliability faster), change `acceleration_factor` to a higher value. Please not that this will not give realistic results.
- The same goes for `delta_v_scale_factor`, which can be used to exaggerate changes in threshold voltage.

The resulting reliability statistics will show up in the files listed under the sections `[reliability/log_files]`, `[reliability/log_files_mem]`, and `[reliability/log_files_core]`.

</details>


## Code Acknowledgements

  Sniper: http://snipersim.org
  
  McPat: https://www.hpl.hp.com/research/mcpat/
  
  CACTI: https://hpl.hp.com/research/cacti/
  
  HotSpot: http://lava.cs.virginia.edu/HotSpot/
    
  HotSniper: https://github.com/anujpathania/HotSniper
  
  MatEx: http://ces.itec.kit.edu/846.php
  
  thermallib: https://github.com/ma-rapp/thermallib

  Darknet Open Source Neural Networks in C: https://pjreddie.com/darknet/





