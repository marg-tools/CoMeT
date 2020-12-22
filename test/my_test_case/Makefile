TARGET=test
include ../shared/Makefile.shared

CFLAGS=-O0 -std=c99 $(SNIPER_CFLAGS)

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -lm $(SNIPER_LDFLAGS) -o $(TARGET)

run_$(TARGET):
	../../run-sniper -v -n 1 -c gainestown   -- ./$(TARGET)
#       ../../record-trace -o strided_access  -- ./strided_access -p 1 #For generating fft.sift file, to view this file, use ../../sift/siftdump  fft.sift | less

CLEAN_EXTRA=viz
