CC=g++
flags=-std=c++0x -pthread
boost=-I /usr/local/boost_1_63_0

networking=Networking/client.cpp Networking/server.cpp Networking/http_req.cpp Networking/http_res.cpp
libs=jsoncpp/jsoncpp.cpp

bcmflags=-L/home/pi/bcm2835-1.50/src/ -lbcm2835

all:
	g++ -g -std=c++11 main.cpp Valve.cpp Valve_Parser.cpp CLI.cpp $(networking) $(libs) -o valve_program $(bcmflags) 

clean:
	rm valve_program
