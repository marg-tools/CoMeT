TUNE=base
EXT=sniper-x86_64-gcc43
NUMBER=481
NAME=wrf
SOURCES= wrf_num_bytes_between.c pack_utils.c module_driver_constants.F90 \
	 module_domain.F90 module_integrate.F90 module_timing.F90 \
	 module_configure.F90 module_tiles.F90 module_machine.F90 \
	 module_nesting.F90 module_wrf_error.F90 module_state_description.F90 \
	 module_sm.F90 module_io.F90 module_dm_stubs.F90 \
	 module_quilt_outbuf_ops.F90 module_io_quilt.F90 module_bc.F90 \
	 module_io_wrf.F90 module_date_time.F90 module_io_domain.F90 \
	 module_bc_time_utilities.F90 module_model_constants.F90 \
	 module_soil_pre.F90 module_bl_mrf.F90 module_sf_myjsfc.F90 \
	 module_bl_myjpbl.F90 module_bl_ysu.F90 module_cu_bmj.F90 \
	 module_mp_kessler.F90 module_mp_ncloud5.F90 module_ra_sw.F90 \
	 module_sf_sfclay.F90 module_cu_kf.F90 module_cu_kfeta.F90 \
	 module_mp_lin.F90 module_mp_wsm3.F90 module_mp_wsm5.F90 \
	 module_mp_wsm6.F90 module_surface_driver.F90 module_cu_gd.F90 \
	 module_sf_sfcdiags.F90 module_ra_gsfcsw.F90 module_sf_slab.F90 \
	 module_sf_noahlsm.F90 module_sf_ruclsm.F90 module_mp_ncloud3.F90 \
	 module_mp_etanew.F90 module_ra_rrtm.F90 module_ra_gfdleta.F90 \
	 module_physics_init.F90 module_physics_addtendc.F90 \
	 module_solvedebug_em.F90 module_bc_em.F90 module_advect_em.F90 \
	 module_diffusion_em.F90 module_small_step_em.F90 \
	 module_big_step_utilities_em.F90 module_em.F90 module_init_utilities.F90 \
	 module_optional_si_input.F90 ESMF_Alarm.F90 ESMF_Base.F90 \
	 ESMF_BaseTime.F90 ESMF_Calendar.F90 ESMF_Clock.F90 ESMF_Fraction.F90 \
	 ESMF_Mod.F90 ESMF_Time.F90 ESMF_TimeInterval.F90 Meat.F90 \
	 wrf_shutdown.F90 collect_on_comm.c mediation_integrate.F90 \
	 mediation_feedback_domain.F90 mediation_force_domain.F90 \
	 mediation_interp_domain.F90 mediation_wrfmain.F90 wrf_auxhist1in.F90 \
	 wrf_auxhist1out.F90 wrf_auxhist2in.F90 wrf_auxhist2out.F90 \
	 wrf_auxhist3in.F90 wrf_auxhist3out.F90 wrf_auxhist4in.F90 \
	 wrf_auxhist4out.F90 wrf_auxhist5in.F90 wrf_auxhist5out.F90 \
	 wrf_auxinput1in.F90 wrf_auxinput1out.F90 wrf_auxinput2in.F90 \
	 wrf_auxinput2out.F90 wrf_auxinput3in.F90 wrf_auxinput3out.F90 \
	 wrf_auxinput4in.F90 wrf_auxinput4out.F90 wrf_auxinput5in.F90 \
	 wrf_auxinput5out.F90 wrf_bdyin.F90 wrf_bdyout.F90 wrf_histin.F90 \
	 wrf_histout.F90 wrf_inputin.F90 wrf_inputout.F90 wrf_restartin.F90 \
	 wrf_restartout.F90 couple_or_uncouple_em.F90 interp_domain_em.F90 \
	 interp_fcn.F90 nest_init_utils.F90 set_timekeeping.F90 sint.F90 \
	 solve_interface.F90 start_domain.F90 module_pbl_driver.F90 \
	 module_radiation_driver.F90 module_cumulus_driver.F90 \
	 module_microphysics_driver.F90 solve_em.F90 start_em.F90 \
	 internal_header_util.F90 io_int.F90 init_modules_em.F90 init_modules.F90 \
	 wrf_io.f90 field_routines.f90 wrf.F90 netcdf/attr.c netcdf/dim.c \
	 netcdf/error.c netcdf/fort-attio.c netcdf/fort-control.c \
	 netcdf/fort-dim.c netcdf/fort-genatt.c netcdf/fort-geninq.c \
	 netcdf/fort-genvar.c netcdf/fort-lib.c netcdf/fort-misc.c \
	 netcdf/fort-v2compat.c netcdf/fort-var1io.c netcdf/fort-varaio.c \
	 netcdf/fort-vario.c netcdf/fort-varmio.c netcdf/fort-varsio.c \
	 netcdf/libvers.c netcdf/nc.c netcdf/ncx.c netcdf/posixio.c \
	 netcdf/putget.c netcdf/string.c netcdf/v1hpg.c netcdf/v2i.c netcdf/var.c \
	 netcdf/typeSizes.f90 netcdf/netcdf.f90
EXEBASE=wrf
NEED_MATH=
BENCHLANG=F C
ONESTEP=
FONESTEP=

BENCH_FLAGS      = -I. -I./netcdf/include
BENCH_FPPFLAGS   = -w -m literal.pm -I. -DINTIO -DIWORDSIZE=4 -DRWORDSIZE=4 -DLWORDSIZE=4 -DNETCDF -DEM_CORE=1 -DNMM_CORE=0 -DCOAMPS_CORE=0 -DEXP_CORE=0 -DF90_STANDALONE -DCONFIG_BUF_LEN=8192 -DMAX_DOMAINS_F=21 -DNO_NAMELIST_PRINT
CC               = /usr/bin/gcc
COPTIMIZE        = -O3 -fno-strict-aliasing
CPORTABILITY     = -DSPEC_CPU_CASE_FLAG -DSPEC_CPU_LINUX
CXX              = /usr/bin/g++
CXXOPTIMIZE      = -O3 -fno-strict-aliasing
FC               = /usr/bin/gfortran
FOPTIMIZE        = -O3 -fno-strict-aliasing
FPBASE           = yes
OS               = unix
PORTABILITY      = -DSPEC_CPU_LP64
absolutely_no_locking = 0
abstol           = 0.01
action           = BUILD
allow_extension_override = 0
backup_config    = 1
baseexe          = wrf
basepeak         = 0
benchdir         = benchspec
benchmark        = 481.wrf
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
command_add_redirect = 0
commanderrfile   = speccmds.err
commandexe       = wrf_base.sniper-x86_64-gcc43
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
fake             = 0
feedback         = 1
flag_url_base    = http://www.spec.org/auto/cpu2006/flags/
floatcompare     = 
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
ignore_errors    = yes
ignore_sigint    = 0
ignorecase       = 
info_wrap_columns = 50
inputdir         = input
iteration        = -1
iterations       = 3
keeptmp          = 0
license_num      = 0
line_width       = 0
locking          = 1
log              = CPU2006
log_line_width   = 0
log_timestamp    = 0
logname          = /scratch/tcarlson/cpu2006/result/CPU2006.006.log
lognum           = 006
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
name             = wrf
need_math        = 
no_input_handler = close
no_monitor       = 
note_preenv      = 0
notes_wrap_columns = 0
notes_wrap_indent =   
num              = 481
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
path             = /scratch/tcarlson/cpu2006/benchspec/CPU2006/481.wrf
plain_train      = 1
preenv           = 1
prefix           = 
prepared_by      = 
ranks            = 1
rate             = 0
realuser         = your name here
rebuild          = 0
reftime          = reftime
reltol           = 0.05
reportable       = 1
resultdir        = result
review           = 0
run              = all
rundir           = run
runspec          = /scratch/tcarlson/cpu2006/bin/runspec -a BUILD -c linux64-sniper-x86_64-gcc43 all
safe_eval        = 1
section_specifier_fatal = 1
sendmail         = /usr/sbin/sendmail
setpgrp_enabled  = 1
setprocgroup     = 1
shrate           = 0
sigint           = 2
size             = ref
size_class       = ref
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
tester           = 
top              = /scratch/tcarlson/cpu2006
train_with       = train
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
OUTPUT_RMFILES   = rsl.out.0000
