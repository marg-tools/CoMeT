TUNE=base
EXT=sniper-x86_64-gcc43
NUMBER=436
NAME=cactusADM
SOURCES= PreLoop.F StaggeredLeapfrog1a.F StaggeredLeapfrog1a_TS.F \
	 StaggeredLeapfrog2.F planewaves.F teukwaves.F datestamp.c regex.c \
	 PUGH/GHExtension.c PUGH/FinishReceiveGA.c PUGH/Startup.c PUGH/Evolve.c \
	 PUGH/Storage.c PUGH/SetupGroup.c PUGH/PostSendGA.c PUGH/SetupPGH.c \
	 PUGH/SetupPGV.c PUGH/LoadAware.c PUGH/Comm.c PUGH/cctk_ThornBindings.c \
	 PUGH/Overloadables.c PUGH/PughUtils.c PUGH/PostReceiveGA.c \
	 Time/Courant.c Time/Initialise.c Time/cctk_ThornBindings.c Time/Given.c \
	 Time/Simple.c Cactus/ScheduleTraverse.c Cactus/Groups.c Cactus/Dummies.c \
	 Cactus/File.c Cactus/CactusDefaultEvolve.c Cactus/BinaryTree.c \
	 Cactus/Hash.c Cactus/Malloc.c Cactus/CactusTimers.c \
	 Cactus/CallStartupFunctions.c Cactus/FortranBindingsIO.c \
	 Cactus/ConfigData.c Cactus/CactusDefaultMainLoopIndex.c Cactus/Misc.c \
	 Cactus/CactusDefaultComm.c Cactus/Cache.c Cactus/RegisterKeyedFunction.c \
	 Cactus/Subsystems.c Cactus/FortranWrappers.c Cactus/Network.c \
	 Cactus/Stagger.c Cactus/CactusDefaultInitialise.c Cactus/Time.c \
	 Cactus/Expression.c Cactus/CactusSync.c Cactus/ProcessCommandLine.c \
	 Cactus/WarnLevel.c Cactus/CommandLine.c Cactus/Coord.c \
	 Cactus/ScheduleInterface.c Cactus/MainUtils.c Cactus/Reduction.c \
	 Cactus/GHExtensions.c Cactus/StoreHandledData.c Cactus/ShutdownCactus.c \
	 Cactus/ProcessEnvironment.c Cactus/getopt.c Cactus/ParseFile.c \
	 Cactus/OverloadIO.c Cactus/StoreKeyedData.c Cactus/getopt1.c \
	 Cactus/CactusDefaultShutdown.c Cactus/Banner.c Cactus/Termination.c \
	 Cactus/ProcessParameterDatabase.c Cactus/ActiveThorns.c Cactus/String.c \
	 Cactus/SetupCache.c Cactus/Table.c Cactus/DebugDefines.c Cactus/Interp.c \
	 Cactus/Parameters.c Cactus/GroupsOnGH.c Cactus/InitialiseCactus.c \
	 Cactus/IOMethods.c Cactus/flesh.c Cactus/ScheduleCreater.c \
	 Cactus/SetParams.c Cactus/cctk_ThornBindings.c Cactus/OverloadComm.c \
	 Cactus/Names.c Cactus/InitialiseDataStructures.c Cactus/StringList.c \
	 Cactus/DefaultTimers.c Cactus/StoreNamedData.c Cactus/ScheduleSorter.c \
	 Cactus/Complex.c Cactus/OverloadMain.c Cactus/Traverse.c \
	 Cactus/SKBinTree.c Cactus/snprintf.c IOUtil/CheckpointRecovery.c \
	 IOUtil/Utils.c IOUtil/AdvertisedFiles.c IOUtil/Startup.c \
	 IOUtil/cctk_ThornBindings.c IDLinearWaves/cctk_ThornBindings.c \
	 BenchADMsrc/Startup.c BenchADMsrc/ParamCheck.c \
	 BenchADMsrc/cctk_ThornBindings.c \
	 CactusBindings/ParameterRecoveryEinstein.c \
	 CactusBindings/ParameterRecoveryCactus.c CactusBindings/TIME_private.c \
	 CactusBindings/OverloadThorns.c CactusBindings/Cactus.c \
	 CactusBindings/PUGH_Register.c CactusBindings/EINSTEIN_restricted.c \
	 CactusBindings/ParameterRecoveryIOASCII.c CactusBindings/IOASCII.c \
	 CactusBindings/CreateTimeParameters.c \
	 CactusBindings/BOUNDARY_restricted.c \
	 CactusBindings/CreateIOBasicParameters.c CactusBindings/Global.c \
	 CactusBindings/ParameterRecoveryPUGH.c CactusBindings/EINSTEIN_private.c \
	 CactusBindings/CARTGRID3D_private.c \
	 CactusBindings/BindingsParameterRecovery.c CactusBindings/PUGH.c \
	 CactusBindings/ParameterRecoveryPUGHSlab.c CactusBindings/SchedulePUGH.c \
	 CactusBindings/IOUtil_Register.c CactusBindings/TIME_restricted.c \
	 CactusBindings/Cactus_FortranWrapper.c \
	 CactusBindings/ParameterRecoveryTime.c \
	 CactusBindings/BenchADM_FortranWrapper.c \
	 CactusBindings/IOASCII_private.c CactusBindings/PUGHReduce.c \
	 CactusBindings/CACTUS_private.c CactusBindings/Time.c \
	 CactusBindings/ScheduleTime.c CactusBindings/Boundary_Register.c \
	 CactusBindings/PUGHReduce_Register.c \
	 CactusBindings/CreateEinsteinParameters.c \
	 CactusBindings/BindingsSchedule.c \
	 CactusBindings/CreateIOASCIIParameters.c \
	 CactusBindings/CreatePUGHParameters.c CactusBindings/BENCHADM_private.c \
	 CactusBindings/CreateBenchADMParameters.c \
	 CactusBindings/CreateIOUtilParameters.c \
	 CactusBindings/CreateCartGrid3DParameters.c \
	 CactusBindings/IDLINEARWAVES_private.c CactusBindings/Boundary.c \
	 CactusBindings/Einstein.c CactusBindings/CreateIDLinearWavesParameters.c \
	 CactusBindings/ParameterRecoveryBenchADM.c \
	 CactusBindings/ParameterRecoveryIOBasic.c CactusBindings/PUGH_private.c \
	 CactusBindings/ScheduleIOASCII.c CactusBindings/PUGHSlab_Register.c \
	 CactusBindings/ScheduleBoundary.c \
	 CactusBindings/CreatePUGHReduceParameters.c CactusBindings/IOBasic.c \
	 CactusBindings/ScheduleEinstein.c \
	 CactusBindings/ParameterRecoveryPUGHReduce.c CactusBindings/CartGrid3D.c \
	 CactusBindings/IOASCII_Register.c \
	 CactusBindings/IDLinearWaves_FortranWrapper.c \
	 CactusBindings/PUGH_FortranWrapper.c \
	 CactusBindings/ScheduleIDLinearWaves.c \
	 CactusBindings/DummyThornFunctions.c \
	 CactusBindings/CreateBoundaryParameters.c CactusBindings/IO_restricted.c \
	 CactusBindings/PUGHSlab.c CactusBindings/BenchADM_Register.c \
	 CactusBindings/CartGrid3D_Register.c CactusBindings/SchedulePUGHSlab.c \
	 CactusBindings/ParameterRecoveryIDLinearWaves.c \
	 CactusBindings/IOBASIC_private.c CactusBindings/SchedulePUGHReduce.c \
	 CactusBindings/PUGHReduce_FortranWrapper.c \
	 CactusBindings/ScheduleIOUtil.c CactusBindings/Einstein_Register.c \
	 CactusBindings/CreateCactusParameters.c CactusBindings/Time_Register.c \
	 CactusBindings/IOBasic_FortranWrapper.c \
	 CactusBindings/CreatePUGHSlabParameters.c \
	 CactusBindings/CACTUS_restricted.c CactusBindings/BindingsVariables.c \
	 CactusBindings/IsOverloaded.c CactusBindings/Cactus_Register.c \
	 CactusBindings/Einstein_FortranWrapper.c \
	 CactusBindings/ParameterRecoveryIOUtil.c CactusBindings/IOUtil.c \
	 CactusBindings/ParameterRecoveryCartGrid3D.c \
	 CactusBindings/PUGHSlab_FortranWrapper.c \
	 CactusBindings/BENCHADM_restricted.c CactusBindings/BindingsParameters.c \
	 CactusBindings/CartGrid3D_FortranWrapper.c \
	 CactusBindings/RegisterThornFunctions.c \
	 CactusBindings/Boundary_FortranWrapper.c \
	 CactusBindings/ScheduleIOBasic.c CactusBindings/BenchADM.c \
	 CactusBindings/IOBasic_Register.c CactusBindings/IDLinearWaves.c \
	 CactusBindings/Time_FortranWrapper.c \
	 CactusBindings/IDLinearWaves_Register.c \
	 CactusBindings/IOASCII_FortranWrapper.c \
	 CactusBindings/ScheduleBenchADM.c CactusBindings/ScheduleCactus.c \
	 CactusBindings/ImplementationBindings.c \
	 CactusBindings/DRIVER_restricted.c \
	 CactusBindings/IOUtil_FortranWrapper.c \
	 CactusBindings/ScheduleCartGrid3D.c \
	 CactusBindings/FortranThornFunctions.c CactusBindings/GRID_restricted.c \
	 CactusBindings/ParameterRecoveryBoundary.c CartGrid3D/SymmetryWrappers.c \
	 CartGrid3D/GHExtension.c CartGrid3D/DecodeSymParameters.c \
	 CartGrid3D/SetSymmetry.c CartGrid3D/Startup.c CartGrid3D/CartGrid3D.c \
	 CartGrid3D/Symmetry.c CartGrid3D/ParamCheck.c \
	 CartGrid3D/cctk_ThornBindings.c Einstein/Courant.c \
	 Einstein/InitialEinstein.c Einstein/MaskInit.c Einstein/Slicing.c \
	 Einstein/InitialFlat.c Einstein/carttosphere.c Einstein/InitSymBound.c \
	 Einstein/LapseInits.c Einstein/cctk_ThornBindings.c \
	 Einstein/ShiftInits.c Einstein/evaltrK.c Einstein/ConfPhys.c \
	 PUGHReduce/ReductionNormInf.c PUGHReduce/ReductionMax.c \
	 PUGHReduce/ReductionMin.c PUGHReduce/ReductionSum.c PUGHReduce/Startup.c \
	 PUGHReduce/Reduction.c PUGHReduce/ReductionNorm1.c \
	 PUGHReduce/ReductionNorm2.c PUGHReduce/cctk_ThornBindings.c \
	 Boundary/FlatBoundary.c Boundary/ScalarBoundary.c \
	 Boundary/RadiationBoundary.c Boundary/RobinBoundary.c \
	 Boundary/CopyBoundary.c Boundary/cctk_ThornBindings.c \
	 PUGHSlab/DatatypeConversion.c PUGHSlab/GetHyperslab.c PUGHSlab/Mapping.c \
	 PUGHSlab/Hyperslab.c PUGHSlab/cctk_ThornBindings.c \
	 PUGHSlab/NewHyperslab.c IOASCII/Output1D.c IOASCII/Output2D.c \
	 IOASCII/Output3D.c IOASCII/Startup.c IOASCII/cctk_ThornBindings.c \
	 IOASCII/ChooseOutput.c IOASCII/Write1D.c IOASCII/Write2D.c \
	 IOASCII/Write3D.c IOBasic/WriteScalar.c IOBasic/OutputScalar.c \
	 IOBasic/OutputInfo.c IOBasic/Startup.c IOBasic/WriteInfo.c \
	 IOBasic/cctk_ThornBindings.c
EXEBASE=cactusADM
NEED_MATH=yes
BENCHLANG=F C
ONESTEP=
FONESTEP=

BENCH_CFLAGS     = -Iinclude -I../include -DCCODE
BENCH_CXXFLAGS   = -Iinclude -I../include -DCCODE
CC               = /usr/bin/gcc
COPTIMIZE        = -O3 -fno-strict-aliasing
CXX              = /usr/bin/g++
CXXOPTIMIZE      = -O3 -fno-strict-aliasing
FC               = /usr/bin/gfortran
FOPTIMIZE        = -O3 -fno-strict-aliasing
FPBASE           = yes
OS               = unix
PORTABILITY      = -DSPEC_CPU_LP64
absolutely_no_locking = 0
action           = validate
allow_extension_override = 0
backup_config    = 1
baseexe          = cactusADM
basepeak         = 0
benchdir         = benchspec
benchmark        = 436.cactusADM
binary           = 
bindir           = exe
build_in_build_dir = 1
builddir         = build
bundleaction     = 
bundlename       = 
calctol          = 0
changedmd5       = 0
check_integrity  = 0
check_md5        = 1
check_version    = 1
clcopies         = 1
command_add_redirect = 0
commanderrfile   = speccmds.err
commandexe       = cactusADM_base.sniper-x86_64-gcc43
commandfile      = speccmds.cmd
commandoutfile   = speccmds.out
commandstdoutfile = speccmds.stdout
compareerrfile   = compare.err
comparefile      = compare.cmd
compareoutfile   = compare.out
comparestdoutfile = compare.stdout
compile_error    = 0
compwhite        = 
configdir        = config
configpath       = /scratch/tcarlson/cpu2006/config/linux64-sniper-x86_64-gcc43.cfg
copies           = 1
datadir          = data
delay            = 0
deletebinaries   = 0
deletework       = 0
difflines        = 10
dirprot          = 511
endian           = 12345678
env_vars         = 0
exitvals         = spec_exit
expand_notes     = 0
expid            = 
ext              = sniper-x86_64-gcc43
fake             = 1
feedback         = 1
flag_url_base    = http://www.spec.org/auto/cpu2006/flags/
floatcompare     = 1
help             = 0
http_proxy       = 
http_timeout     = 30
hw_avail         = Dec-9999
hw_cpu_char      = 
hw_cpu_mhz       = 3000
hw_cpu_name      = AMD Opteron 256
hw_disk          = SATA
hw_fpu           = Integrated
hw_memory        = 2 GB (2 x 1GB DDR333 CL2.5)
hw_model         = Tyan Thunder KKQS Pro (S4882)
hw_nchips        = 1
hw_ncores        = 1
hw_ncoresperchip = 1
hw_ncpuorder     = 1 chip
hw_nthreadspercore = 1
hw_ocache        = None
hw_other         = None
hw_pcache        = 64 KB I + 64 KB D on chip per chip
hw_scache        = 1 MB I+D on chip per chip
hw_tcache        = None
hw_vendor        = Tyan
ignore_errors    = 0
ignore_sigint    = 0
ignorecase       = 
info_wrap_columns = 50
inputdir         = input
iteration        = -1
iterations       = 1
keeptmp          = 0
license_num      = 0
line_width       = 0
locking          = 1
log              = CPU2006
log_line_width   = 0
log_timestamp    = 0
logname          = /scratch/tcarlson/cpu2006/result/CPU2006.008.log
lognum           = 008
mach             = default
mail_reports     = all
mailcompress     = 0
mailmethod       = smtp
mailport         = 25
mailserver       = 127.0.0.1
mailto           = 
make             = specmake
make_no_clobber  = 0
makeflags        = 
max_active_compares = 0
mean_anyway      = 0
min_report_runs  = 3
minimize_builddirs = 0
minimize_rundirs = 0
name             = cactusADM
need_math        = yes
no_input_handler = close
no_monitor       = 
note_preenv      = 0
notes_wrap_columns = 0
notes_wrap_indent =   
num              = 436
obiwan           = 
os_exe_ext       = 
output           = asc
output_format    = asc
output_root      = 
outputdir        = output
parallel_setup   = 1
parallel_setup_prefork = 
parallel_setup_type = fork
parallel_test    = 0
parallel_test_submit = 0
path             = /scratch/tcarlson/cpu2006/benchspec/CPU2006/436.cactusADM
plain_train      = 1
preenv           = 1
prefix           = 
prepared_by      = 
ranks            = 1
rate             = 0
realuser         = your name here
rebuild          = 1
reftime          = reftime
reportable       = 0
resultdir        = result
review           = 0
run              = all
rundir           = run
runspec          = /scratch/tcarlson/cpu2006/bin/runspec -a run --fake all -c linux64-sniper-x86_64-gcc43.cfg
safe_eval        = 1
section_specifier_fatal = 1
sendmail         = /usr/sbin/sendmail
setpgrp_enabled  = 1
setprocgroup     = 1
shrate           = 0
sigint           = 2
size             = test
size_class       = test
skipabstol       = 
skipobiwan       = 
skipreltol       = 
skiptol          = 
smarttune        = base
specdiff         = specdiff
specmake         = Makefile.YYYtArGeTYYYspec
specrun          = specinvoke
speed            = 0
srcalt           = 
srcdir           = src
stagger          = 10
strict_rundir_verify = 1
sw_avail         = Mar-2008
sw_base_ptrsize  = 64-bit
sw_compiler      = gcc, g++ & gfortran 4.3.0 (for AMD64)
sw_file          = ext3
sw_os            = SUSE Linux Enterprise Server 10 (x86_64) SP1, Kernel 2.6.16.46-0.12-smp
sw_other         = None
sw_peak_ptrsize  = Not Applicable
sw_state         = Runlevel 3 (Full multiuser with network)
sysinfo_program  = 
table            = 1
teeout           = yes
teerunout        = yes
test_date        = Sep-2011
test_sponsor     = Turbo Computers
testaddedbytools3660 = 1
tester           = 
top              = /scratch/tcarlson/cpu2006
train_with       = train
trainaddedbytools3660 = 1
tune             = base
uid              = 10170
unbuffer         = 1
update-flags     = 0
use_submit_for_speed = 0
username         = tcarlson
vendor           = anon
vendor_makefiles = 0
verbose          = 5
version          = 0
version_url      = http://www.spec.org/auto/cpu2006/current_version
worklist         = list
OUTPUT_RMFILES   = benchADM.out
