CFLAGS = -std=c++11  

all: main.bin
main.bin: main.o Commands.o Config_Message.o Bridge.o Network.o
	g++ $(CFLAGS) -o main.bin main.o Commands.o Config_Message.o Bridge.o Network.o
Bridge.o: Bridge.cpp
	g++ $(CFLAGS) -c Bridge.cpp
Commands.o: Commands.cpp
	g++ $(CFLAGS) -c Commands.cpp
Config_Message.o: Config_Message.cpp
	g++ $(CFLAGS) -c Config_Message.cpp
Network.o: Network.cpp
	g++ $(CFLAGS) -c Network.cpp
main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp