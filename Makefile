
SRC_DIR = ./src
BUILD_DIR = ./build
INC_DIR = ./include
CXXFLAGS = -std=c++11
OBJ_DIR = $(BUILD_DIR)/obj

all: server client

server: server.o
	g++ $(OBJ_DIR)/server.o -o $(BUILD_DIR)/server
	
server.o:
	g++ $(CXXFLAGS) -c $(SRC_DIR)/server.cpp -o $(OBJ_DIR)/server.o -I $(INC_DIR)

client: client.o
	g++ $(OBJ_DIR)/client.o -o $(BUILD_DIR)/client
	
client.o: 
	g++ -c $(SRC_DIR)/client.cpp -o $(OBJ_DIR)/client.o -I $(INC_DIR)

clean: 
	rm $(OBJ_DIR)/*.o
	echo Clean done.
