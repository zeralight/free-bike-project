CXXFLAGS = $(tulip-config-debug --cxxflags)
LIBS = $(tulip-config-debug --libs)

%.o: %.cpp
	g++ -std=c++11 $(CXXFLAGS) -c $< $(LIBS)
