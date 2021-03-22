TUNE=base
EXT=sniper-x86_64-gcc43
NUMBER=454
NAME=calculix
SOURCES= CalculiX.c add_pr.f add_sm_ei.f add_sm_st.f allocation.f \
	 amplitudes.f anisotropic.f beamsections.f bounadd.f boundaries.f \
	 buckles.f calinput.f cfluxes.f changedepterm.f cloads.f conductivities.f \
	 controlss.f couptempdisps.f creeps.f cychards.f cycsymmods.f dasol.f \
	 datest.f datri.f defplasticities.f defplas.f densities.f depvars.f \
	 deuldlag.f dfluxes.f dgesv.f diamtr.f dloads.f dot.f dredu.f dsort.f \
	 dynamics.f dynsolv.f el.f elastics.f elements.f elprints.f envtemp.f \
	 equations.f expansions.f extrapolate.f e_c3d.f e_c3d_th.f e_c3d_rhs.f \
	 fcrit.f films.f finpro.f forcadd.f frd.F frdclose.f frequencies.f fsub.f \
	 fsuper.f gen3delem.f genran.f getnewline.f graph.f headings.f \
	 heattransfers.f hyperel.f hyperelastics.f hyperfoams.f ident.f ident2.f \
	 include.f incplas.f initialconditions.f inputerror.f isorti.f isortid.f \
	 isortidc.f isortii.f isortiid.f label.f linel.f lintemp.f lintemp_th.f \
	 loadadd.f loadaddt.f mafillpr.f mafillsm.f mafillsmcs.f massflowrates.f \
	 matdata_co.f matdata_he.f matdata_tg.f materialdata.f materials.f \
	 modaldampings.f modaldynamics.f mpcs.f nident.f nident2.f near2d.f \
	 noanalysis.f nodalthicknesses.f nodeprints.f nodes.f noelfiles.f \
	 noelsets.f nonlinmpc.f normals.f norshell.f number.f onf.f op.f \
	 openfile.f orientations.f orthonl.f orthotropic.f out.f parser.f \
	 physicalconstants.f planempc.f plastics.f plcopy.f plinterpol.f plmix.f \
	 polynom.f profil.f radflowload.f radiates.f ranewr.f rearrange.f \
	 rectcyl.f renumber.f restartread.f restarts.f restartshort.f \
	 restartwrite.f results.f rhs.f rigidbodies.f rigidmpc.f rootls.f \
	 rubber.f saxpb.f selcycsymmods.f shape3tri.f shape4q.f shape4tet.f \
	 shape6tri.f shape6w.f shape8h.f shape8q.f shape10tet.f shape15w.f \
	 shape20h.f shellsections.f skip.f solidsections.f spcmatch.f \
	 specificheats.f statics.f steps.f stiff2mat.f stop.f str2mat.f \
	 straightmpc.f surfaces.f temperatures.f tempload.f ties.f \
	 transformatrix.f transforms.f ucreep.f uhardening.f umat.f \
	 umat_aniso_creep.f umat_aniso_plas.f umat_elastic_fiber.f \
	 umat_ideal_gas.f umat_lin_iso_el.f umat_single_crystal.f \
	 umat_tension_only.f umat_user.f umpc_mean_rot.f umpc_user.f \
	 usermaterials.f usermpc.f viscos.f wcoef.f writebv.f writeev.f \
	 writeevcs.f writempc.f writesummary.f cascade.c frdcyc.c insert.c \
	 mastruct.c mastructcs.c nonlingeo.c pcgsolver.c preiter.c prespooles.c \
	 profile.c remastruct.c spooles.c strcmp1.c strcpy1.c u_calloc.c \
	 SPOOLES/A2/src/A2_IO.c SPOOLES/A2/src/A2_basics.c \
	 SPOOLES/A2/src/A2_init.c SPOOLES/A2/src/A2_instance.c \
	 SPOOLES/A2/src/A2_norms.c SPOOLES/A2/src/A2_sort.c \
	 SPOOLES/A2/src/A2_util.c SPOOLES/BKL/src/BKL_basics.c \
	 SPOOLES/BKL/src/BKL_evalfcn.c SPOOLES/BKL/src/BKL_exhSearch.c \
	 SPOOLES/BKL/src/BKL_fidmat.c SPOOLES/BKL/src/BKL_init.c \
	 SPOOLES/BKL/src/BKL_util.c SPOOLES/BPG/src/BPG_IO.c \
	 SPOOLES/BPG/src/BPG_basics.c SPOOLES/BPG/src/BPG_init.c \
	 SPOOLES/BPG/src/BPG_makeGraphs.c SPOOLES/BPG/src/BPG_pseudo.c \
	 SPOOLES/Chv/src/Chv_IO.c SPOOLES/Chv/src/Chv_assemble.c \
	 SPOOLES/Chv/src/Chv_basics.c SPOOLES/Chv/src/Chv_copy.c \
	 SPOOLES/Chv/src/Chv_factor.c SPOOLES/Chv/src/Chv_findPivot.c \
	 SPOOLES/Chv/src/Chv_init.c SPOOLES/Chv/src/Chv_instance.c \
	 SPOOLES/Chv/src/Chv_search.c SPOOLES/Chv/src/Chv_swap.c \
	 SPOOLES/Chv/src/Chv_update.c SPOOLES/Chv/src/Chv_util.c \
	 SPOOLES/ChvList/src/ChvList_basics.c SPOOLES/ChvList/src/ChvList_init.c \
	 SPOOLES/ChvList/src/ChvList_util.c \
	 SPOOLES/ChvManager/src/ChvManager_basics.c \
	 SPOOLES/ChvManager/src/ChvManager_init.c \
	 SPOOLES/ChvManager/src/ChvManager_util.c \
	 SPOOLES/DSTree/src/DSTree_basics.c SPOOLES/DSTree/src/DSTree_init.c \
	 SPOOLES/DSTree/src/DSTree_instance.c SPOOLES/DSTree/src/DSTree_stages.c \
	 SPOOLES/DSTree/src/DSTree_util.c SPOOLES/DV/src/DV_IO.c \
	 SPOOLES/DV/src/DV_basics.c SPOOLES/DV/src/DV_init.c \
	 SPOOLES/DV/src/DV_instance.c SPOOLES/DV/src/DV_util.c \
	 SPOOLES/DenseMtx/src/DenseMtx_IO.c \
	 SPOOLES/DenseMtx/src/DenseMtx_basics.c \
	 SPOOLES/DenseMtx/src/DenseMtx_init.c \
	 SPOOLES/DenseMtx/src/DenseMtx_instance.c \
	 SPOOLES/DenseMtx/src/DenseMtx_permute.c \
	 SPOOLES/DenseMtx/src/DenseMtx_util.c SPOOLES/Drand/src/Drand_basics.c \
	 SPOOLES/Drand/src/Drand_init.c SPOOLES/Drand/src/Drand_util.c \
	 SPOOLES/ETree/src/ETree_IO.c SPOOLES/ETree/src/ETree_basics.c \
	 SPOOLES/ETree/src/ETree_compress.c SPOOLES/ETree/src/ETree_init.c \
	 SPOOLES/ETree/src/ETree_instance.c SPOOLES/ETree/src/ETree_permute.c \
	 SPOOLES/ETree/src/ETree_transform.c SPOOLES/ETree/src/ETree_util.c \
	 SPOOLES/FrontMtx/src/FrontMtx_IO.c \
	 SPOOLES/FrontMtx/src/FrontMtx_basics.c \
	 SPOOLES/FrontMtx/src/FrontMtx_factor.c \
	 SPOOLES/FrontMtx/src/FrontMtx_factorUtil.c \
	 SPOOLES/FrontMtx/src/FrontMtx_init.c \
	 SPOOLES/FrontMtx/src/FrontMtx_instance.c \
	 SPOOLES/FrontMtx/src/FrontMtx_loadEntries.c \
	 SPOOLES/FrontMtx/src/FrontMtx_permute.c \
	 SPOOLES/FrontMtx/src/FrontMtx_postProcess.c \
	 SPOOLES/FrontMtx/src/FrontMtx_postponed.c \
	 SPOOLES/FrontMtx/src/FrontMtx_solve.c \
	 SPOOLES/FrontMtx/src/FrontMtx_solveUtil.c \
	 SPOOLES/FrontMtx/src/FrontMtx_split.c \
	 SPOOLES/FrontMtx/src/FrontMtx_storeFront.c \
	 SPOOLES/FrontMtx/src/FrontMtx_update.c \
	 SPOOLES/FrontMtx/src/FrontMtx_util.c SPOOLES/GPart/src/GPart_DDsepInfo.c \
	 SPOOLES/GPart/src/GPart_DDviaFishnet.c \
	 SPOOLES/GPart/src/GPart_DDviaProjection.c \
	 SPOOLES/GPart/src/GPart_RBviaDDsep.c \
	 SPOOLES/GPart/src/GPart_TwoSetViaBKL.c SPOOLES/GPart/src/GPart_basics.c \
	 SPOOLES/GPart/src/GPart_domSegMap.c \
	 SPOOLES/GPart/src/GPart_identifyWideSep.c SPOOLES/GPart/src/GPart_init.c \
	 SPOOLES/GPart/src/GPart_makeYCmap.c \
	 SPOOLES/GPart/src/GPart_smoothBisector.c \
	 SPOOLES/GPart/src/GPart_smoothBy2layers.c \
	 SPOOLES/GPart/src/GPart_smoothYSep.c SPOOLES/GPart/src/GPart_split.c \
	 SPOOLES/GPart/src/GPart_util.c SPOOLES/Graph/src/Graph_IO.c \
	 SPOOLES/Graph/src/Graph_basics.c SPOOLES/Graph/src/Graph_compress.c \
	 SPOOLES/Graph/src/Graph_equivMap.c SPOOLES/Graph/src/Graph_init.c \
	 SPOOLES/Graph/src/Graph_util.c SPOOLES/I2Ohash/src/I2Ohash_basics.c \
	 SPOOLES/I2Ohash/src/I2Ohash_init.c SPOOLES/I2Ohash/src/I2Ohash_util.c \
	 SPOOLES/IIheap/src/IIheap_basics.c SPOOLES/IV/src/IV_IO.c \
	 SPOOLES/IV/src/IV_basics.c SPOOLES/IV/src/IV_init.c \
	 SPOOLES/IV/src/IV_instance.c SPOOLES/IV/src/IV_util.c \
	 SPOOLES/IVL/src/IVL_IO.c SPOOLES/IVL/src/IVL_basics.c \
	 SPOOLES/IVL/src/IVL_init.c SPOOLES/IVL/src/IVL_instance.c \
	 SPOOLES/IVL/src/IVL_listmanip.c SPOOLES/IVL/src/IVL_util.c \
	 SPOOLES/Ideq/src/Ideq_basics.c SPOOLES/Ideq/src/Ideq_resize.c \
	 SPOOLES/Ideq/src/Ideq_util.c SPOOLES/InpMtx/src/InpMtx_IO.c \
	 SPOOLES/InpMtx/src/InpMtx_basics.c SPOOLES/InpMtx/src/InpMtx_fullAdj.c \
	 SPOOLES/InpMtx/src/InpMtx_init.c SPOOLES/InpMtx/src/InpMtx_input.c \
	 SPOOLES/InpMtx/src/InpMtx_instance.c SPOOLES/InpMtx/src/InpMtx_permute.c \
	 SPOOLES/InpMtx/src/InpMtx_util.c SPOOLES/Lock/src/Lock_basics.c \
	 SPOOLES/Lock/src/Lock_init.c SPOOLES/Lock/src/Lock_util.c \
	 SPOOLES/MSMD/src/MSMD_MSMDinfo.c SPOOLES/MSMD/src/MSMD_MSMDvtx.c \
	 SPOOLES/MSMD/src/MSMD_basics.c SPOOLES/MSMD/src/MSMD_cleanReachSet.c \
	 SPOOLES/MSMD/src/MSMD_eliminate.c SPOOLES/MSMD/src/MSMD_findInodes.c \
	 SPOOLES/MSMD/src/MSMD_frontETree.c SPOOLES/MSMD/src/MSMD_init.c \
	 SPOOLES/MSMD/src/MSMD_order.c SPOOLES/MSMD/src/MSMD_update.c \
	 SPOOLES/Network/src/Network_IO.c SPOOLES/Network/src/Network_addArc.c \
	 SPOOLES/Network/src/Network_augmentPath.c \
	 SPOOLES/Network/src/Network_basics.c \
	 SPOOLES/Network/src/Network_findAugmentingPath.c \
	 SPOOLES/Network/src/Network_findMaxFlow.c \
	 SPOOLES/Network/src/Network_findMincut.c \
	 SPOOLES/Network/src/Network_init.c SPOOLES/Pencil/src/Pencil_IO.c \
	 SPOOLES/Pencil/src/Pencil_basics.c SPOOLES/Pencil/src/Pencil_init.c \
	 SPOOLES/SubMtx/src/SubMtx_IO.c SPOOLES/SubMtx/src/SubMtx_basics.c \
	 SPOOLES/SubMtx/src/SubMtx_init.c SPOOLES/SubMtx/src/SubMtx_instance.c \
	 SPOOLES/SubMtx/src/SubMtx_scalevec.c SPOOLES/SubMtx/src/SubMtx_solve.c \
	 SPOOLES/SubMtx/src/SubMtx_solveH.c SPOOLES/SubMtx/src/SubMtx_solveT.c \
	 SPOOLES/SubMtx/src/SubMtx_solveupd.c \
	 SPOOLES/SubMtx/src/SubMtx_solveupdH.c \
	 SPOOLES/SubMtx/src/SubMtx_solveupdT.c SPOOLES/SubMtx/src/SubMtx_sort.c \
	 SPOOLES/SubMtx/src/SubMtx_util.c \
	 SPOOLES/SubMtxList/src/SubMtxList_util.c \
	 SPOOLES/SubMtxManager/src/SubMtxManager_basics.c \
	 SPOOLES/SubMtxManager/src/SubMtxManager_init.c \
	 SPOOLES/SubMtxManager/src/SubMtxManager_util.c \
	 SPOOLES/SymbFac/src/SymbFac_symbfac.c SPOOLES/Tree/src/Tree_IO.c \
	 SPOOLES/Tree/src/Tree_basics.c SPOOLES/Tree/src/Tree_compress.c \
	 SPOOLES/Tree/src/Tree_init.c SPOOLES/Tree/src/Tree_metrics.c \
	 SPOOLES/Tree/src/Tree_perms.c SPOOLES/Tree/src/Tree_util.c \
	 SPOOLES/Utilities/src/Utilities_CV.c \
	 SPOOLES/Utilities/src/Utilities_DV.c \
	 SPOOLES/Utilities/src/Utilities_I2OP.c \
	 SPOOLES/Utilities/src/Utilities_IP.c \
	 SPOOLES/Utilities/src/Utilities_IV.c \
	 SPOOLES/Utilities/src/Utilities_PIV.c \
	 SPOOLES/Utilities/src/Utilities_ZV.c \
	 SPOOLES/Utilities/src/Utilities_iohb.c \
	 SPOOLES/Utilities/src/Utilities_newsort.c \
	 SPOOLES/Utilities/src/Utilities_sortAndCompress.c \
	 SPOOLES/ZV/src/ZV_basics.c SPOOLES/ZV/src/ZV_init.c \
	 SPOOLES/ZV/src/ZV_instance.c \
	 SPOOLES/misc/src/misc_orderViaBestOfNDandMS.c
EXEBASE=calculix
NEED_MATH=yes
BENCHLANG=F C
ONESTEP=
FONESTEP=

BENCH_FLAGS      = -ISPOOLES
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
abstol           = 1e-09
action           = BUILD
allow_extension_override = 0
backup_config    = 1
baseexe          = calculix
basepeak         = 0
benchdir         = benchspec
benchmark        = 454.calculix
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
commandexe       = calculix_base.sniper-x86_64-gcc43
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
name             = calculix
need_math        = yes
no_input_handler = close
no_monitor       = 
note_preenv      = 0
notes_wrap_columns = 0
notes_wrap_indent =   
num              = 454
obiwan           = 1
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
path             = /scratch/tcarlson/cpu2006/benchspec/CPU2006/454.calculix
plain_train      = 1
preenv           = 1
prefix           = 
prepared_by      = 
ranks            = 1
rate             = 0
realuser         = your name here
rebuild          = 0
reftime          = reftime
reltol           = 1e-09
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
OUTPUT_RMFILES   = SPECtestformatmodifier_z.txt stairs.dat
