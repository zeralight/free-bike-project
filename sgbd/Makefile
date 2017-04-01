TLPFLAGS = `tulip-config --cxxflags` 
TLPLIBS = `tulip-config --libs` 
GPPFLAGS = -std=c++14 -fdiagnostics-color -g -fPIC

all: test

%.o: %.cpp 
	g++ $(GPPFLAGS) $(TLPFLAGS) -c $<

test: testEntRel testDatabase testPattern testMatch

test%: test%.o DBTools.o DBTools.o Tools.o Relation.o Entity.o GraphRead.o GraphWrite.o Database.o DatabaseImpl.o Result.o ResultImpl.o Pattern.o PatternImpl.o
	g++ $(GPPFLAGS) $(TLPLIBS) $(TLPSUP) $^ -o $@

lib: DBTools.o Tools.o Relation.o Entity.o GraphRead.o GraphWrite.o Database.o DatabaseImpl.o Result.o ResultImpl.o Pattern.o PatternImpl.o
	g++ -shared -fPIC $^ -o libgraphdb.so

clean:
	rm -f *~ *.o
