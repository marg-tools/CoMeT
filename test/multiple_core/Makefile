TARGET=test
include ../shared/Makefile.shared

CFLAGS=-O0 -std=c99 $(SNIPER_CFLAGS)

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -lm $(SNIPER_LDFLAGS) -o $(TARGET)

target: 
	./run.sh

run_$(TARGET): target
	../../run-sniper -c gainestown_3Dmem_16channels_32cores -n 32 --traces=test1_pipe.sift,test2_pipe.sift,test3_pipe.sift,test4_pipe.sift,test5_pipe.sift,test6_pipe.sift,test7_pipe.sift,test8_pipe.sift,test9_pipe.sift,test10_pipe.sift,test11_pipe.sift,test12_pipe.sift,test13_pipe.sift,test14_pipe.sift,test15_pipe.sift,test16_pipe.sift,test17_pipe.sift,test18_pipe.sift,test19_pipe.sift,test20_pipe.sift,test21_pipe.sift,test22_pipe.sift,test23_pipe.sift,test24_pipe.sift,test25_pipe.sift,test26_pipe.sift,test27_pipe.sift,test28_pipe.sift,test29_pipe.sift,test30_pipe.sift,test31_pipe.sift,test32_pipe.sift


CLEAN_EXTRA=viz
