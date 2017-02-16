TLPFLAGS = `tulip-config --cxxflags` 
TLPLIBS = `tulip-config --libs` 
GPPFLAGS = -std=c++14 -fdiagnostics-color -g

all: test

%.o: %.cpp 
	g++ $(GPPFLAGS) $(TLPFLAGS) -c $<

test: test.o DBTools.o Entity.o
	g++ $(GPPFLAGS) $(TLPLIBS) $(TLPSUP) $^ -o test

clean:
	rm -f *~ *.o
