# 3D-Mem-Therm-I

With the growing power density in both processors and memories (esp. 3D), thermal issues significantly impact application performance. Thus, increasingly researchers have become interested in understanding the performance, power, and thermal effects of the proposed changes in hardware and software.

3D-Mem-Therm-I is an architectural simulation tool for processors and memory, supporting both 2D and 3D memories. It integrates Sniper (performance simulator for x86), McPAT (power model for processors), CACTI3DD (power model for memory), and HotSpot (thermal simulator) to periodically provide designers - performance, power, and thermal information for processor and memory.  

# Part 1
- We have extended the source code of Sniper multicore simulator developed by the Performance Lab research group at Ghent University, Belgium. This code extension provides us with DRAM access information per memory bank (unlike Sniper which gives a total count of DRAM accesses)

# Getting Started

- Installation
	- sudo dpkg --add-architecture i386
	- sudo apt-get install binutils build-essential curl git libboost-dev libbz2-dev libc6:i386 libncurses5:i386 libsqlite3-dev libstdc++6:i386 python wget zlib1g-dev

- Compile
	- make # or use 'make -j N' where N is the number of cores in your machine to use parallel make

- Running an application 
	- cd test/app\_name
	- make run

- To see the DRAM accesses per memory bank, please use the application my\_test\_case inside test folder
	- To use this feature the application should be long enough to run for atleast 1 ms.
	- cd test/my\_test\_case
	- make run

- To run the application on 16 cores with 16 channels
	- Use gainestown\_my\_3D.cfg
	- cd test/my\_test\_case
	- Edit run-sniper commandline inside Makefile 
		- ../../run-sniper -v -n 1 -c gainestown\_my\_3D  --roi -- ./$(TARGET)
		- We can also enable/disable Sniper's region of interest (roi) flag
	- make run

- Understanding the output
	- To see the output corresponding to number of DRAM read/write accesses per bank, the application should run for atleast 1 ms. This is due to length of epoch that we use for counting the DRAM accesses and some other delays.
	- The output of `make run` displays the time interval in which a DRAM access was made, #reads and #writes and also reports the number of DRAM accesses directed to a particular bank.
