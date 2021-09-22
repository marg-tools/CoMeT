TARGET=test
include ../shared/Makefile.shared

CFLAGS=-O0 -std=c99 $(SNIPER_CFLAGS)

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -lm $(SNIPER_LDFLAGS) -o $(TARGET)

run_$(TARGET):
	../../run-sniper -v -n 1 -c gainestown_3Dmem -- ./$(TARGET)

CLEAN_EXTRA=viz
