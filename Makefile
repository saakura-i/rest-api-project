all:
	g++ -pthread $(filter-out RunTest.cpp, $(wildcard *.cpp)) -o run

RunTest:
	g++ -pthread $(filter-out main.cpp, $(wildcard *.cpp)) -o RunTest

run:
	./run

unit-tests: RunTest
	./RunTest

clean:
	rm -f run RunTest