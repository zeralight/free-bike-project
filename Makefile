TLPFLAGS = `tulip-config-debug --cxxflags` 
TLPLIBS = `tulip-config-debug --libs` 
GPPFLAGS = -std=c++14 -fdiagnostics-color -g
TLPSUP = -L/home/raptapia/Documents/logiciels/Tulip-4.9.0/install-debug/lib/ -lyajl-tulip-4.9 -ltess2-tulip-4.9

%.o: %.cpp 
	g++ -I./sgbd -I./extraction $(GPPFLAGS) $(TLPFLAGS) $(TLPSUP) -c $<

import: import.o DBTools.o
	g++ $(GPPFLAGS) $(TLPLIBS) $(TLPSUP) $^ -o import

clean:
	rm -f *~ *.o
