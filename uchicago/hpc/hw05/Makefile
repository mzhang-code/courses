
CC = gcc
NC = nvcc

.PHONY: default all clean 

TARGET = $(P1) $(P2) $(P4) 

P1 = simpson_omp
P2 = mc_omp
P3 = simpson_cu
P4 = mc_cu

default: all 

all: $(TARGET)

$(P1):
	$(CC) -std=c99 -lm -fopenmp simpson_omp.c -o $@

$(P2):
	$(CC) -std=c99 -lm -fopenmp mc_omp.c -o $@

$(P4):
	$(NC) mc.cu -o $@

# $(P2A):
# 	$(CXX) -fopenmp p2_a.c -o $@
# 
# $(P2B):
# 	$(CXX) -fopenmp p2_b.c -o $@


clean: 
	rm -f *.o $(TARGET)
