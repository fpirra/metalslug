# Para el cliente
#SRC_FILES = src/client_main.cpp $(filter-out src/model/server.cpp, $(wildcard src/model/*.cpp)) $(filter-out src/model/ClientConnection.cpp, $(wildcard src/model/*.cpp)) src/Utils/*.cpp
SRC_FILES = src/client_main.cpp src/Utils/*.cpp src/model/client.cpp src/model/message.cpp src/model/User.cpp src/model/ClientHandler.cpp
INC_FILES = src/model/client.h src/model/message.h src/model/User.h src/Utils/*.h src/model/ClientHandler.h
#INC_FILES = src/*.h -I$(filter-out src/model/server.h, $(wildcard src/model/*.h))
OBJ_NAME = client
CLIENT_DEP =

# Para el server
#SRV_SRC_FILES = $(filter-out src/model/client.cpp, $(wildcard src/model/*.cpp)) $(filter-out src/model/ClientHandler.cpp, $(wildcard src/model/*.cpp)) src/server_main.cpp
SRV_SRC_FILES = src/model/server.cpp src/model/ClientConnection.cpp src/model/message.cpp src/model/UserLoader.cpp src/model/User.cpp src/Utils/Logger.cpp \
src/Utils/SocketUtils.cpp src/Utils/MessageUtils.cpp src/server_main.cpp
#SRV_SRC_FILES = src/model/server.cpp src/server_main.cpp
# SRV_INC = src/model/server.h $(filter-out src/Utils/loremIpsum.cpp, $(wildcard src/Utils/*.cpp)) $(filter-out src/Utils/User.cpp, $(wildcard src/Utils/*.cpp))
SRV_INC = src/model/server.h # src/model/ClientConnection.h src/model/UserLoader.h src/Utils/SocketUtils.h src/Utils/Protocol.h src/model/User.h
SRV_DEP = -pthread
SRV_OBJ_NAME = server

# Para test
TEST_SRC_FILES = test/*.cpp src/model/*.cpp src/Utils/*.cpp
TEST_INC_FILES = src/model/*.h src/Utils/*.h
OBJ_NAME_TEST = run-tests

# General
CC = g++
COMPILER_FLAGS = -w -std=c++11 -g -Wall
LINKER_FLAGS = -pthread -lSDL2 -lSDL2_image -lSDL2main -lyaml-cpp -lSDL2_ttf


all : client server

client : $(SRC_FILES)
	$(CC) -I$(INC_FILES) $(SRC_FILES) $(COMPILER_FLAGS) -o $(OBJ_NAME) -pthread

server : $(SRV_SRC_FILES)
	$(CC) -I$(SRV_INC) $(SRV_SRC_FILES) $(SRV_DEP) $(COMPILER_FLAGS) -o $(SRV_OBJ_NAME)

test : $(SRC_FILES) $(TEST_SRC_FILES)
	$(CC) $(TEST_SRC_FILES) -I$(TEST_INC_FILES) $(COMPILER_FLAGS) -lgtest -o $(OBJ_NAME_TEST)
