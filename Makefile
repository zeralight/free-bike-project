CXXFLAGS = $(tulip-config --cxxflags)
LIBS = $(tulip-config --libs)

all:
	g++ -std=c++14 $(CXXFLAGS) *.cpp $(LIBS)
