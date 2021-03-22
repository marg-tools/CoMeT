include tools/scripts/env.makefile
ifeq ($(BENCHMARKS_ROOT),)
$(error "Error: The BENCHMARKS_ROOT environment variable is not set.")
endif
ifeq ($(SNIPER_ROOT),)
$(error "Error: The SNIPER_ROOT environment variable is not set.")
endif

.PHONY: all clean dependencies

all: dependencies
	make -C tools/hooks
	make -C splash2
	make -C parsec
	make -C cpu2006
	make -C npb
	make -C local

clean:
	make -C tools/hooks clean
	make -C splash2 clean
	make -C parsec clean
	make -C cpu2006 clean
	make -C npb clean
	make -C local clean

dependencies:
	$(BENCHMARKS_ROOT)/tools/scripts/checkdependencies.py
