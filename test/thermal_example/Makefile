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
	#Modify the gainestown_DDR config file parameter as per the following architecture configurations
	#- gainestown_DDR - 4x4 core and an external 4x4 bank DDR main memory (2D memory). It invokes two different hotspot runs to estimate temperatures for core and memory separately.
	#- gainestown_3Dmem - 4x4 core and an external 4x4x8 banks 3D main memory. It invokes two different hotspot runs to estimate temperatures for core and memory separately.
	#- gainestown_2_5D - 4x4 core and a 4x4x8 banks 3D main memory integrated on the same die (2.5D architecture). It invokes a single hotspot run and simulates core and memory together.
	#- gainestown_3D - 4x4 core on top of a 4x4x8 banks 3D main memory. It invokes a single hotspot run and simulates core and memory together.
	
	../../run-sniper -v -s memTherm_core -n 4 -c gainestown_3D -- ./$(TARGET) -p 4
	#../../run-sniper -v -s memTherm -s energystats -n 64 -c gainestown_my3D -- ./$(TARGET) -p 16

CLEAN_EXTRA=viz hotspot/ *.log *.init energystats-temp.* *.trace tmp
