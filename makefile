CC=g++
flags=-std=c++0x -pthread
boost=-I /usr/local/boost_1_63_0

all:
	g++ -g -std=c++11 main.cpp Valve.cpp Valve_Parser.cpp CLI.cpp -o valve_program -L/home/pi/bcm2835-1.50/src/ -lbcm2835

clean:
	rm valve_program
