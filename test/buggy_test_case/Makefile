TARGET=test
include ../shared/Makefile.shared

CFLAGS=-O0 -std=c99 $(SNIPER_CFLAGS)

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -lm $(SNIPER_LDFLAGS) -o $(TARGET)

target: 
	./run.sh

run_$(TARGET): target
	../../run-sniper -v -s memTherm_core -c gainestown_3Dmem -n 4 --traces=test1_pipe.sift,test2_pipe.sift,test3_pipe.sift,test4_pipe.sift


CLEAN_EXTRA=viz hotspot/ *.log *.init energystats-temp.* *.trace tmp logfile *.sift
