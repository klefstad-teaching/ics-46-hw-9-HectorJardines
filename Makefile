CXX = g++
CXXFLAGS= -ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic

all: dijkstras_main ladder_main

dijkstras_main: src/dijkstras_main.cpp lib/dijkstras.o
	$(CXX) $(CXXFLAGS) src/dijkstras_main.cpp -o dijkstras_main lib/dijkstras.o

ladder_main: src/ladder_main.cpp lib/ladder.o
	$(CXX) $(CXXFLAGS) src/ladder_main.cpp -o ladder_main lib/ladder.o

hw_gtests: gtest/student_gtests.cpp lib/graph.o
	$(CXX) $(CXXFLAGS) -o hw_gtests gtest/student_gtests.cpp -lgtest -lgtest_main -pthread lib/sorter.o

lib/dijkstras.o: src/dijkstras.cpp src/dijkstras.h
	$(CXX) $(CXXFLAGS) -c src/dijkstras.cpp -o lib/dijkstras.o

lib/ladder.o: src/ladder.cpp src/ladder.h
	$(CXX) $(CXXFLAGS) -c src/ladder.cpp -o lib/ladder.o

clean:
	rm -f lib/*.o main