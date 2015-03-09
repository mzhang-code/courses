
CXX = g++

.PHONY: default all clean 

TARGET = $(P1) $(P2A) $(P2B)

P1 = p1
P2A = p2a
P2B = p2b

default: all 

all: $(TARGET)

# $(TARGET): $(OBJ)
# 	$(CXX) -lm $(OBJ) -o $@

$(P1):
	$(CXX) p1.c -o $@

$(P2A):
	$(CXX) -fopenmp p2_a.c -o $@

$(P2B):
	$(CXX) -fopenmp p2_b.c -o $@


clean: 
	rm -f *.o $(TARGET)
