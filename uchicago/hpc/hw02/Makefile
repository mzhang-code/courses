
CXX = mpic++

.PHONY: default all clean 

TARGET = $(P2A) $(P2B) $(P3)

P2A = mset_a
P2B = mset_b
P3 = p3

default: all 

all: $(TARGET)

# $(TARGET): $(OBJ)
# 	$(CXX) -lm $(OBJ) -o $@

$(P2A):
	$(CXX) p2_mpi_a.c -o $@

$(P2B):
	$(CXX) p2_mpi_b.c -o $@

$(P3):
	$(CXX) p3.c -o $@


clean: 
	rm -f *.o $(TARGET)
