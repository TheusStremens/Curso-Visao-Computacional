CXX = g++

CXXFLAGS = -Wall -std=c++14 -O3 -ffast-math

LDFLAGS = `pkg-config --libs opencv`

INCLUDE = `pkg-config --cflags opencv` -I $(CURDIR)/include

all: mat.out canais_mat.out

##################
### Compilados ###
##################

# Aula 01
build/mat.o: Aula-01/mat.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDE)
build/canais_mat.o: Aula-01/canais_mat.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDE)

###################
### Executaveis ###
###################

# Aula 01
mat.out: build/mat.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
canais_mat.out: build/canais_mat.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	@rm -f build/*.o *.out