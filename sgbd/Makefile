TLPFLAGS = `tulip-config --cxxflags` 
TLPLIBS = `tulip-config --libs` 
GPPFLAGS = -std=c++14 -fdiagnostics-color -g

all: test

%.o: %.cpp 
	g++ $(GPPFLAGS) $(TLPFLAGS) -c $<

test: test.o DBTools.o Tools.o Relation.o Entity.o GraphWrite.o DatabaseImpl.o Result.o ResultImpl.o
	g++ $(GPPFLAGS) $(TLPLIBS) $(TLPSUP) $^ -o test

testDatabase: testDatabase.o DBTools.o Tools.o Relation.o Entity.o GraphWrite.o Database.o DatabaseImpl.o Result.o ResultImpl.o
	g++ $(GPPFLAGS) $(TLPLIBS) $^ -o testDatabase

clean:
	rm -f *~ *.o
