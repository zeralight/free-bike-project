TLPFLAGS = `tulip-config-debug --cxxflags` 
TLPLIBS = `tulip-config-debug --libs` 
GPPFLAGS = -std=c++14 -fdiagnostics-color -g -fPIC
TLPSUP = -L/home/raptapia/Documents/logiciels/Tulip-4.9.0/install-debug/lib/ -lyajl-tulip-4.9 -ltess2-tulip-4.9

%.o: %.cpp 
	g++ -I. $(GPPFLAGS) $(TLPFLAGS) $(TLPSUP) -c $<

test: test.o DBTools.o Tools.o Relation.o Entity.o GraphWrite.o DatabaseImpl.o Result.o ResultImpl.o
	g++ $(GPPFLAGS) $(TLPLIBS) $(TLPSUP) $^ -o test

testDatabase: testDatabase.o DBTools.o Tools.o Relation.o Entity.o GraphRead.o GraphWrite.o Database.o DatabaseImpl.o Result.o ResultImpl.o
	g++ $(GPPFLAGS) $(TLPLIBS) $(TLPSUP) $^ -o testDatabase

lib: DBTools.o Tools.o Relation.o Entity.o GraphRead.o GraphWrite.o Database.o DatabaseImpl.o Result.o ResultImpl.o
	g++ -shared -fPIC $^ -o libgraphdb.so

clean:
	rm -f *~ *.o .so	
