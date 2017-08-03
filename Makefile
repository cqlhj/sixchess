CPP      = g++ 
OBJ      = main.o six.o ai.o
LINKOBJ  = main.o six.o ai.o
BIN      = six
CXXFLAGS = -std=c++11

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)

six.o: six.cpp
	$(CPP) -c six.cpp -o six.o $(CXXFLAGS)

ai.o: ai.cpp
	$(CPP) -c ai.cpp -o ai.o $(CXXFLAGS)
clean:
	rm -rf $(OBJ) $(BIN)
