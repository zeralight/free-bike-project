TLPFLAGS = `tulip-config-debug --cxxflags` 
TLPLIBS = `tulip-config-debug --libs` 
GPPFLAGS = -std=c++14 -fdiagnostics-color -g -fPIC
INCLUDES = -I./sgbd -I./extraction -I.
LIBS = -L./sgbd/ -lgraphdb


extraction.o: extraction/extraction.cpp 
	g++ $(INCLUDES) $(GPPFLAGS) -c $< 

%.o: %.cpp 
	g++ $(INCLUDES) $(GPPFLAGS) $(TLPFLAGS) -c $<

import: testImport.o import.o extraction.o dateInNodes.o
	g++ $(GPPFLAGS) $(LIBS) $(TLPLIBS) $^ -o import

clean:
	rm -f *~ *.o
