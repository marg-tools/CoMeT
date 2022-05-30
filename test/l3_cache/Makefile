include ../shared/Makefile.shared

# Options: test, simdev, simsmall, simmedium, simlarge, native
BENCHMARK_IN=simlarge
BENCHMARK_CMD=parsecmgmt -c gcc-sniper -a run -n 4 -i $(BENCHMARK_IN)

benchmark: benchmark_stacked

benchmark_stacked:
	../../run-sniper -v -s memTherm_core -n 4 -c l3_stacked -- $(BENCHMARK_CMD)

benchmark_non-stacked:
	../../run-sniper -v -s memTherm_core -n 4 -c l3_non-stacked -- $(BENCHMARK_CMD)

plot_stacked:
	python3 ../../scripts/heatView.py --arch_type=3D --traceFile=combined_temperature.trace --output maps_stacked --cache_l3 --cache_l3_stacked --tmin 40 --tmax 60 
plot_non-stacked:
	python3 ../../scripts/heatView.py --arch_type=3D --traceFile=combined_temperature.trace --output maps_nonstacked --cache_l3 --cache_l3_width 1 --tmin 40 --tmax 60 

CLEAN_EXTRA=viz hotspot/ *.log *.init energystats-temp.* *.trace tmp maps/
