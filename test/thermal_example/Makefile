TARGET=test
include ../shared/Makefile.shared

CFLAGS=-O0 -std=c99 $(SNIPER_CFLAGS)

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -lm $(SNIPER_LDFLAGS) -o $(TARGET)

run_$(TARGET):
	# ../../run-sniper -v -n 1 -c gainestown -- ./$(TARGET)    ##original command by shailja
	#../../run-sniper -v -n 1 -c gainestown --roi -- ./$(TARGET)
#       ../../record-trace -o strided_access  -- ./strided_access -p 1 #For generating fft.sift file, to view this file, use ../../sift/siftdump  fft.sift | less
	#../../run-sniper -v -s energystats -n 64 -c gainestown_my3D -- ./$(TARGET) -p 16
	../../run-sniper -v -s memTherm -s energystats -n 64 -c gainestown_my3D -- ./$(TARGET) -p 16
	#../../run-sniper -v -s dramCountTrace -n 16 -c gainestown_my3D -- ./$(TARGET) -p 16

CLEAN_EXTRA=viz
