all: myexp test

logger.o: logger.cpp logger.h CS149intrin.h CS149intrin.cpp
	g++ $(CXXFLAGS) -c logger.cpp

CS149intrin.o: CS149intrin.cpp CS149intrin.h logger.cpp logger.h
	g++ $(CXXFLAGS) -c CS149intrin.cpp

myexp: CS149intrin.o logger.o main.cpp
	g++ $(CXXFLAGS) logger.o CS149intrin.o main.cpp -o myexp

test: CS149intrin.o logger.o test.cpp
	g++ $(CXXFLAGS) logger.o CS149intrin.o test.cpp -o test

clean:
	rm -f *.o myexp *~
