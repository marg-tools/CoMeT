TARGET=test_var_latency
include ../shared/Makefile.shared

CFLAGS=-O0 -std=c99 $(SNIPER_CFLAGS)

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -lm $(SNIPER_LDFLAGS) -o $(TARGET)

run_$(TARGET):
	../../run-sniper -v -n 4 -c gainestown_3D_cacti --cacti 3DDRAM_customized -- ./$(TARGET) -p 16

CLEAN_EXTRA=viz hotspot/ *.log *.init energystats-temp.* *.trace tmp cacti_output.cfg
