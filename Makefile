# Define compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g
BUILD_DIR = build
SRC = src
SCHEDULER = scheduler
MEMORY = memory


# Target executable name
TARGET = $(BUILD_DIR)/main

# Object files needed to build the executable
OBJ = $(BUILD_DIR)/main.o $(BUILD_DIR)/shell.o $(BUILD_DIR)/pcb.o $(BUILD_DIR)/fcfs.o  $(BUILD_DIR)/sjf.o $(BUILD_DIR)/srtf.o $(BUILD_DIR)/priority.o \
$(BUILD_DIR)/round_robin.o $(BUILD_DIR)/gantt.o

# Default target to build the project
all: $(TARGET)

# Link object files together into the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Compile main.c (depends on ic.h because it includes it)
$(BUILD_DIR)/main.o: main.c $(SRC)/shell.h $(SCHEDULER)/pcb.h $(SCHEDULER)/fcfs.h $(SCHEDULER)/scheduler.h
	$(CC) $(CFLAGS) -c main.c -o $(BUILD_DIR)/main.o

# Compile ic.c (depends on ic.h)
#ic.o: ic.c ic.h
#	$(CC) $(CFLAGS) -c ic.c

$(BUILD_DIR)/shell.o: $(SRC)/shell.c $(SRC)/shell.h
	$(CC) $(CFLAGS) -c $(SRC)/shell.c -o $(BUILD_DIR)/shell.o


$(BUILD_DIR)/pcb.o: $(SCHEDULER)/pcb.c $(SCHEDULER)/pcb.h
	$(CC) $(CFLAGS) -c $(SCHEDULER)/pcb.c -o $(BUILD_DIR)/pcb.o

$(BUILD_DIR)/fcfs.o: $(SCHEDULER)/fcfs.c $(SCHEDULER)/fcfs.h $(SCHEDULER)/pcb.h
	$(CC) $(CFLAGS) -c $(SCHEDULER)/fcfs.c -o $(BUILD_DIR)/fcfs.o

$(BUILD_DIR)/sjf.o: $(SCHEDULER)/sjf.c $(SCHEDULER)/scheduler.h $(SCHEDULER)/pcb.h
	$(CC) $(CFLAGS) -c $(SCHEDULER)/sjf.c -o $(BUILD_DIR)/sjf.o

$(BUILD_DIR)/srtf.o: $(SCHEDULER)/srtf.c $(SCHEDULER)/scheduler.h $(SCHEDULER)/pcb.h
	$(CC) $(CFLAGS) -c $(SCHEDULER)/srtf.c -o $(BUILD_DIR)/srtf.o

$(BUILD_DIR)/priority.o: $(SCHEDULER)/priority.c $(SCHEDULER)/scheduler.h $(SCHEDULER)/pcb.h
	$(CC) $(CFLAGS) -c $(SCHEDULER)/priority.c -o $(BUILD_DIR)/priority.o

$(BUILD_DIR)/round_robin.o: $(SCHEDULER)/round_robin.c $(SCHEDULER)/scheduler.h $(SCHEDULER)/pcb.h $(SCHEDULER)/gantt.h
	$(CC) $(CFLAGS) -c $(SCHEDULER)/round_robin.c -o $(BUILD_DIR)/round_robin.o

$(BUILD_DIR)/gantt.o: $(SCHEDULER)/gantt.c $(SCHEDULER)/gantt.h 
	$(CC) $(CFLAGS) -c $(SCHEDULER)/gantt.c -o $(BUILD_DIR)/gantt.o

run: $(TARGET)
	./$(TARGET)


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET) $(BUILD_DIR)  *.exe 


.PHONY: all run clean