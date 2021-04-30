TARGET=test
include ../shared/Makefile.shared

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -lm $(SNIPER_LDFLAGS) -o $(TARGET)

target:
	python3 run.py

run_$(TARGET): target

CLEAN_EXTRA=viz hotspot/ *.log *.init energystats-temp.* *.trace tmp comet_results test_summary.txt

