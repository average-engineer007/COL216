CC = g++
CFLAGS = -Wall -Wextra --pedantic
LDFLAGS =

# Source files
SRCS = main.cpp
SRCS += # Add other source files if any

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = cacheSim

OUTPUT_FILE = output.txt

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(EXEC) $(OUTPUT_FILE)
