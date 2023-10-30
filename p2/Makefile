CXX = g++
C = gcc

SRC_DIR = ./src
INCLUDES = -I./include
LIBRARIES = -L./lib

CFLAGS = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES)
LDFLAGS = $(LIBRARIES)

TARGET = Juego
OBJS = main.o Jugador.o

.PHONY: all clean run

all: $(TARGET)

run: all
	 ./${TARGET}

$(TARGET) : $(OBJS)
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS) -o $@

%.o : $(SRC_DIR)/%.cc
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS) -c -o $@

%.o : $(SRC_DIR)/%.c
	$(C) $^ $(CFLAGS) $(LDFLAGS) -c -o $@

clean:
	rm $(OBJS) $(TARGET)