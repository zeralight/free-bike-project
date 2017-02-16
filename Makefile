CXXFLAGS = $(tulip-config --cxxflags)
LIBS = $(tulip-config --libs)

%.o: %.cpp
	g++ -std=c++11 $(CXXFLAGS) -c $< $(LIBS)

clean:
	rm *.o
