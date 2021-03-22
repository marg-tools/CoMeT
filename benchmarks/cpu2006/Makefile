POST=base.sniper-x86_64
FILES=CPU2006/400.perlbench/exe/perlbench_$(POST) CPU2006/401.bzip2/exe/bzip2_$(POST) CPU2006/403.gcc/exe/gcc_$(POST) CPU2006/410.bwaves/exe/bwaves_$(POST) CPU2006/416.gamess/exe/gamess_$(POST) CPU2006/429.mcf/exe/mcf_$(POST) CPU2006/433.milc/exe/milc_$(POST) CPU2006/434.zeusmp/exe/zeusmp_$(POST) CPU2006/435.gromacs/exe/gromacs_$(POST) CPU2006/436.cactusADM/exe/cactusADM_$(POST) CPU2006/437.leslie3d/exe/leslie3d_$(POST) CPU2006/444.namd/exe/namd_$(POST) CPU2006/445.gobmk/exe/gobmk_$(POST) CPU2006/447.dealII/exe/dealII_$(POST) CPU2006/450.soplex/exe/soplex_$(POST) CPU2006/453.povray/exe/povray_$(POST) CPU2006/454.calculix/exe/calculix_$(POST) CPU2006/456.hmmer/exe/hmmer_$(POST) CPU2006/458.sjeng/exe/sjeng_$(POST) CPU2006/459.GemsFDTD/exe/GemsFDTD_$(POST) CPU2006/462.libquantum/exe/libquantum_$(POST) CPU2006/464.h264ref/exe/h264ref_$(POST) CPU2006/465.tonto/exe/tonto_$(POST) CPU2006/470.lbm/exe/lbm_$(POST) CPU2006/471.omnetpp/exe/omnetpp_$(POST) CPU2006/473.astar/exe/astar_$(POST) CPU2006/481.wrf/exe/wrf_$(POST) CPU2006/482.sphinx3/exe/sphinx3_$(POST) CPU2006/483.xalancbmk/exe/xalancbmk_$(POST)

include ../tools/hooks/buildconf.makefile
ifeq ($(USE_ICC),1)
  all:
	echo "Makefile.spec hardcoded to gcc but we're in icc mode, SPEC2006 benchmark suite will not be supported"
else
  all: deps compile $(FILES)
endif

include ../tools/scripts/env.makefile
export SPEC:=$(BENCHMARKS_ROOT)/cpu2006
export SPECPERLLIB:=$(SPEC)/bin:$(SPEC)/bin/lib
export PATH:=$(SPEC)/bin:$(PATH)

deps: CPU2006/999.specrand/src/specrand.c
CPU2006/999.specrand/src/specrand.c:
	@echo
	@echo SPEC CPU2006 sources not found. To build the CPU2006 benchmarks for Sniper, first run
	@echo benchmarks$$ ./install_cpu2006 PATH_TO_CPU2006_DVD
	@echo
	@false

compile:
	make -C CPU2006/400.perlbench/src
	make -C CPU2006/401.bzip2/src
	make -C CPU2006/403.gcc/src
	make -C CPU2006/410.bwaves/src
	make -C CPU2006/416.gamess/src
	make -C CPU2006/429.mcf/src
	make -C CPU2006/433.milc/src
	make -C CPU2006/434.zeusmp/src
	make -C CPU2006/435.gromacs/src
	make -C CPU2006/436.cactusADM/src
	make -C CPU2006/437.leslie3d/src
	make -C CPU2006/444.namd/src
	make -C CPU2006/445.gobmk/src
	make -C CPU2006/447.dealII/src
	make -C CPU2006/450.soplex/src
	make -C CPU2006/453.povray/src
	make -C CPU2006/454.calculix/src
	make -C CPU2006/456.hmmer/src
	make -C CPU2006/458.sjeng/src
	make -C CPU2006/459.GemsFDTD/src
	make -C CPU2006/462.libquantum/src
	make -C CPU2006/464.h264ref/src
	make -C CPU2006/465.tonto/src
	make -C CPU2006/470.lbm/src
	make -C CPU2006/471.omnetpp/src
	make -C CPU2006/473.astar/src
	make -C CPU2006/481.wrf/src
	make -C CPU2006/482.sphinx3/src
	make -C CPU2006/483.xalancbmk/src

clean:
	make -C CPU2006/400.perlbench/src clean
	make -C CPU2006/401.bzip2/src clean
	make -C CPU2006/403.gcc/src clean
	make -C CPU2006/410.bwaves/src clean
	make -C CPU2006/416.gamess/src clean
	make -C CPU2006/429.mcf/src clean
	make -C CPU2006/433.milc/src clean
	make -C CPU2006/434.zeusmp/src clean
	make -C CPU2006/435.gromacs/src clean
	make -C CPU2006/436.cactusADM/src clean
	make -C CPU2006/437.leslie3d/src clean
	make -C CPU2006/444.namd/src clean
	make -C CPU2006/445.gobmk/src clean
	make -C CPU2006/447.dealII/src clean
	make -C CPU2006/450.soplex/src clean
	make -C CPU2006/453.povray/src clean
	make -C CPU2006/454.calculix/src clean
	make -C CPU2006/456.hmmer/src clean
	make -C CPU2006/458.sjeng/src clean
	make -C CPU2006/459.GemsFDTD/src clean
	make -C CPU2006/462.libquantum/src clean
	make -C CPU2006/464.h264ref/src clean
	make -C CPU2006/465.tonto/src clean
	make -C CPU2006/470.lbm/src clean
	make -C CPU2006/471.omnetpp/src clean
	make -C CPU2006/473.astar/src clean
	make -C CPU2006/481.wrf/src clean
	make -C CPU2006/482.sphinx3/src clean
	make -C CPU2006/483.xalancbmk/src clean
	rm -rf CPU2006/*/exe

%/exe:
	install -d $@


CPU2006/400.perlbench/exe/perlbench_$(POST): CPU2006/400.perlbench/src/perlbench CPU2006/400.perlbench/exe
	cp $< $@
CPU2006/401.bzip2/exe/bzip2_$(POST): CPU2006/401.bzip2/src/bzip2 CPU2006/401.bzip2/exe
	cp $< $@
CPU2006/403.gcc/exe/gcc_$(POST): CPU2006/403.gcc/src/gcc CPU2006/403.gcc/exe
	cp $< $@
CPU2006/410.bwaves/exe/bwaves_$(POST): CPU2006/410.bwaves/src/bwaves CPU2006/410.bwaves/exe
	cp $< $@
CPU2006/416.gamess/exe/gamess_$(POST): CPU2006/416.gamess/src/gamess CPU2006/416.gamess/exe
	cp $< $@
CPU2006/429.mcf/exe/mcf_$(POST): CPU2006/429.mcf/src/mcf CPU2006/429.mcf/exe
	cp $< $@
CPU2006/433.milc/exe/milc_$(POST): CPU2006/433.milc/src/milc CPU2006/433.milc/exe
	cp $< $@
CPU2006/434.zeusmp/exe/zeusmp_$(POST): CPU2006/434.zeusmp/src/zeusmp CPU2006/434.zeusmp/exe
	cp $< $@
CPU2006/435.gromacs/exe/gromacs_$(POST): CPU2006/435.gromacs/src/gromacs CPU2006/435.gromacs/exe
	cp $< $@
CPU2006/436.cactusADM/exe/cactusADM_$(POST): CPU2006/436.cactusADM/src/cactusADM CPU2006/436.cactusADM/exe
	cp $< $@
CPU2006/437.leslie3d/exe/leslie3d_$(POST): CPU2006/437.leslie3d/src/leslie3d CPU2006/437.leslie3d/exe
	cp $< $@
CPU2006/444.namd/exe/namd_$(POST): CPU2006/444.namd/src/namd CPU2006/444.namd/exe
	cp $< $@
CPU2006/445.gobmk/exe/gobmk_$(POST): CPU2006/445.gobmk/src/gobmk CPU2006/445.gobmk/exe
	cp $< $@
CPU2006/447.dealII/exe/dealII_$(POST): CPU2006/447.dealII/src/dealII CPU2006/447.dealII/exe
	cp $< $@
CPU2006/450.soplex/exe/soplex_$(POST): CPU2006/450.soplex/src/soplex CPU2006/450.soplex/exe
	cp $< $@
CPU2006/453.povray/exe/povray_$(POST): CPU2006/453.povray/src/povray CPU2006/453.povray/exe
	cp $< $@
CPU2006/454.calculix/exe/calculix_$(POST): CPU2006/454.calculix/src/calculix CPU2006/454.calculix/exe
	cp $< $@
CPU2006/456.hmmer/exe/hmmer_$(POST): CPU2006/456.hmmer/src/hmmer CPU2006/456.hmmer/exe
	cp $< $@
CPU2006/458.sjeng/exe/sjeng_$(POST): CPU2006/458.sjeng/src/sjeng CPU2006/458.sjeng/exe
	cp $< $@
CPU2006/459.GemsFDTD/exe/GemsFDTD_$(POST): CPU2006/459.GemsFDTD/src/GemsFDTD CPU2006/459.GemsFDTD/exe
	cp $< $@
CPU2006/462.libquantum/exe/libquantum_$(POST): CPU2006/462.libquantum/src/libquantum CPU2006/462.libquantum/exe
	cp $< $@
CPU2006/464.h264ref/exe/h264ref_$(POST): CPU2006/464.h264ref/src/h264ref CPU2006/464.h264ref/exe
	cp $< $@
CPU2006/465.tonto/exe/tonto_$(POST): CPU2006/465.tonto/src/tonto CPU2006/465.tonto/exe
	cp $< $@
CPU2006/470.lbm/exe/lbm_$(POST): CPU2006/470.lbm/src/lbm CPU2006/470.lbm/exe
	cp $< $@
CPU2006/471.omnetpp/exe/omnetpp_$(POST): CPU2006/471.omnetpp/src/omnetpp CPU2006/471.omnetpp/exe
	cp $< $@
CPU2006/473.astar/exe/astar_$(POST): CPU2006/473.astar/src/astar CPU2006/473.astar/exe
	cp $< $@
CPU2006/481.wrf/exe/wrf_$(POST): CPU2006/481.wrf/src/wrf CPU2006/481.wrf/exe
	cp $< $@
CPU2006/482.sphinx3/exe/sphinx3_$(POST): CPU2006/482.sphinx3/src/sphinx_livepretend CPU2006/482.sphinx3/exe
	cp $< $@
CPU2006/483.xalancbmk/exe/xalancbmk_$(POST): CPU2006/483.xalancbmk/src/Xalan CPU2006/483.xalancbmk/exe
	cp $< $@
