
CXX = g++ 

.PHONY: default all clean 

TARGET = mat_mul
SRC := p1.cc dgemm.cc
OBJ := ${SRC:.cc=.o}

default: all 

all: $(TARGET)

# $(TARGET): $(OBJ)
# 	$(CXX) -lm $(OBJ) -o $@

$(TARGET):
	$(CXX) p1.cc -o $@

%.o: %.cc
	$(CXX) -lf2c -lm -c $< -o $@ 

clean: 
	rm -f *.o $(TARGET)
