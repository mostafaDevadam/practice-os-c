# Define compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g
BUILD_DIR = build
SRC = src
SCHEDULER = scheduler
MEMORY = memory
CONCURRENCY = concurrency
DEADLOCK = deadlock
MULTI_CPU_SCHEDULER = multi_cpu_scheduler
FILE_SYSTEM = file_system

# Target executable name
TARGET = $(BUILD_DIR)/main

# Object files needed to build the executable
OBJ = $(BUILD_DIR)/main.o $(BUILD_DIR)/shell.o $(BUILD_DIR)/pcb.o $(BUILD_DIR)/fcfs.o  $(BUILD_DIR)/sjf.o $(BUILD_DIR)/srtf.o $(BUILD_DIR)/priority.o \
$(BUILD_DIR)/round_robin.o $(BUILD_DIR)/gantt.o \
$(BUILD_DIR)/memory.o $(BUILD_DIR)/backing_store.o $(BUILD_DIR)/page_table.o \
$(BUILD_DIR)/tlb.o $(BUILD_DIR)/replacement.o $(BUILD_DIR)/mem_statistics.o \
$(BUILD_DIR)/utils.o $(BUILD_DIR)/sleeping_barber.o $(BUILD_DIR)/readers_writers.o $(BUILD_DIR)/producer_consumer.o \
$(BUILD_DIR)/dining_philosophers.o \
$(BUILD_DIR)/banker.o $(BUILD_DIR)/utils_d.o $(BUILD_DIR)/avoidance.o $(BUILD_DIR)/detection.o $(BUILD_DIR)/display.o $(BUILD_DIR)/input.o $(BUILD_DIR)/prevention.o \
$(BUILD_DIR)/m_pcb.o $(BUILD_DIR)/m_cpu.o $(BUILD_DIR)/m_scheduler.o $(BUILD_DIR)/m_utils.o $(BUILD_DIR)/m_input.o $(BUILD_DIR)/m_queue.o \
$(BUILD_DIR)/m_fcfs.o $(BUILD_DIR)/m_sjf.o  $(BUILD_DIR)/m_round_robin.o $(BUILD_DIR)/m_priority.o $(BUILD_DIR)/m_gantt.o \
$(BUILD_DIR)/m_statistics.o \
$(BUILD_DIR)/disk.o $(BUILD_DIR)/superblock.o $(BUILD_DIR)/bitmap.o $(BUILD_DIR)/inode.o $(BUILD_DIR)/directory.o \
$(BUILD_DIR)/file.o $(BUILD_DIR)/fs.o $(BUILD_DIR)/cache.o $(BUILD_DIR)/path.o
# Default target to build the project
all: $(BUILD_DIR) $(TARGET)

# Link object files together into the final executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Compile main.c (depends on ic.h because it includes it)
$(BUILD_DIR)/main.o: main.c $(SRC)/shell.h $(SCHEDULER)/pcb.h $(SCHEDULER)/fcfs.h $(SCHEDULER)/scheduler.h  \
$(MEMORY)/memory.h $(MEMORY)/page_table.h $(MEMORY)/tlb.h  $(MEMORY)/replacement.h  $(MEMORY)/mem_statistics.h  \
$(CONCURRENCY)/utils.h $(CONCURRENCY)/sleeping_barber.h $(CONCURRENCY)/readers_writers.h  $(CONCURRENCY)/producer_consumer.h  \
$(CONCURRENCY)/dining_philosophers.h \
$(DEADLOCK)/banker.h $(DEADLOCK)/utils_d.h $(DEADLOCK)/avoidance.h $(DEADLOCK)/detection.h $(DEADLOCK)/display.h $(DEADLOCK)/input.h $(DEADLOCK)/prevention.h \
$(MULTI_CPU_SCHEDULER)/m_pcb.h $(MULTI_CPU_SCHEDULER)/m_cpu.h $(MULTI_CPU_SCHEDULER)/m_scheduler.h $(MULTI_CPU_SCHEDULER)/m_utils.h \
$(MULTI_CPU_SCHEDULER)/m_input.h $(MULTI_CPU_SCHEDULER)/m_queue.h $(MULTI_CPU_SCHEDULER)/m_fcfs.h $(MULTI_CPU_SCHEDULER)/m_sjf.h \
$(MULTI_CPU_SCHEDULER)/m_round_robin.h $(MULTI_CPU_SCHEDULER)/m_priority.h $(MULTI_CPU_SCHEDULER)/m_gantt.h \
$(MULTI_CPU_SCHEDULER)/m_statistics.h \
$(FILE_SYSTEM)/disk.h $(FILE_SYSTEM)/superblock.h $(FILE_SYSTEM)/bitmap.h $(FILE_SYSTEM)/inode.h $(FILE_SYSTEM)/directory.h \
$(FILE_SYSTEM)/file.h $(FILE_SYSTEM)/fs.h $(FILE_SYSTEM)/cache.h $(FILE_SYSTEM)/path.h
	$(CC) $(CFLAGS) -c main.c -o $(BUILD_DIR)/main.o 

# Compile ic.c (depends on ic.h)
#ic.o: ic.c ic.h
#	$(CC) $(CFLAGS) -c ic.c

$(BUILD_DIR)/shell.o: $(SRC)/shell.c $(SRC)/shell.h
	$(CC) $(CFLAGS) -c $(SRC)/shell.c -o $(BUILD_DIR)/shell.o

# scheduler

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

# memory

$(BUILD_DIR)/memory.o: $(MEMORY)/memory.c $(MEMORY)/memory.h 
	$(CC) $(CFLAGS) -c $(MEMORY)/memory.c -o $(BUILD_DIR)/memory.o	

$(BUILD_DIR)/backing_store.o: $(MEMORY)/backing_store.c $(MEMORY)/memory.h 
	$(CC) $(CFLAGS) -c $(MEMORY)/backing_store.c -o $(BUILD_DIR)/backing_store.o	

$(BUILD_DIR)/page_table.o: $(MEMORY)/page_table.c $(MEMORY)/page_table.h 
	$(CC) $(CFLAGS) -c $(MEMORY)/page_table.c -o $(BUILD_DIR)/page_table.o	

$(BUILD_DIR)/tlb.o: $(MEMORY)/tlb.c $(MEMORY)/tlb.h 
	$(CC) $(CFLAGS) -c $(MEMORY)/tlb.c -o $(BUILD_DIR)/tlb.o	

$(BUILD_DIR)/replacement.o: $(MEMORY)/replacement.c $(MEMORY)/replacement.h 
	$(CC) $(CFLAGS) -c $(MEMORY)/replacement.c -o $(BUILD_DIR)/replacement.o

$(BUILD_DIR)/mem_statistics.o: $(MEMORY)/mem_statistics.c $(MEMORY)/mem_statistics.h 
	$(CC) $(CFLAGS) -c $(MEMORY)/mem_statistics.c -o $(BUILD_DIR)/mem_statistics.o

# concurrency
$(BUILD_DIR)/utils.o: $(CONCURRENCY)/utils.c $(CONCURRENCY)/utils.h 
	$(CC) $(CFLAGS) -c $(CONCURRENCY)/utils.c -o $(BUILD_DIR)/utils.o

$(BUILD_DIR)/sleeping_barber.o: $(CONCURRENCY)/sleeping_barber.c $(CONCURRENCY)/sleeping_barber.h 
	$(CC) $(CFLAGS) -c $(CONCURRENCY)/sleeping_barber.c -o $(BUILD_DIR)/sleeping_barber.o

$(BUILD_DIR)/readers_writers.o: $(CONCURRENCY)/readers_writers.c $(CONCURRENCY)/readers_writers.h 
	$(CC) $(CFLAGS) -c $(CONCURRENCY)/readers_writers.c -o $(BUILD_DIR)/readers_writers.o

$(BUILD_DIR)/producer_consumer.o: $(CONCURRENCY)/producer_consumer.c $(CONCURRENCY)/producer_consumer.h 
	$(CC) $(CFLAGS) -c $(CONCURRENCY)/producer_consumer.c -o $(BUILD_DIR)/producer_consumer.o

$(BUILD_DIR)/dining_philosophers.o: $(CONCURRENCY)/dining_philosophers.c $(CONCURRENCY)/dining_philosophers.h 
	$(CC) $(CFLAGS) -c $(CONCURRENCY)/dining_philosophers.c -o $(BUILD_DIR)/dining_philosophers.o

#deadlock

$(BUILD_DIR)/banker.o: $(DEADLOCK)/banker.c $(DEADLOCK)/banker.h 
	$(CC) $(CFLAGS) -c $(DEADLOCK)/banker.c -o $(BUILD_DIR)/banker.o


$(BUILD_DIR)/utils_d.o: $(DEADLOCK)/utils_d.c $(DEADLOCK)/utils_d.h $(DEADLOCK)/banker.h 
	$(CC) $(CFLAGS) -c $(DEADLOCK)/utils_d.c -o $(BUILD_DIR)/utils_d.o


$(BUILD_DIR)/avoidance.o: $(DEADLOCK)/avoidance.c $(DEADLOCK)/avoidance.h $(DEADLOCK)/banker.h 
	$(CC) $(CFLAGS) -c $(DEADLOCK)/avoidance.c -o $(BUILD_DIR)/avoidance.o


$(BUILD_DIR)/detection.o: $(DEADLOCK)/detection.c $(DEADLOCK)/detection.h $(DEADLOCK)/banker.h 
	$(CC) $(CFLAGS) -c $(DEADLOCK)/detection.c -o $(BUILD_DIR)/detection.o


$(BUILD_DIR)/display.o: $(DEADLOCK)/display.c $(DEADLOCK)/display.h $(DEADLOCK)/banker.h 
	$(CC) $(CFLAGS) -c $(DEADLOCK)/display.c -o $(BUILD_DIR)/display.o


$(BUILD_DIR)/input.o: $(DEADLOCK)/input.c $(DEADLOCK)/input.h $(DEADLOCK)/banker.h 
	$(CC) $(CFLAGS) -c $(DEADLOCK)/input.c -o $(BUILD_DIR)/input.o


$(BUILD_DIR)/prevention.o: $(DEADLOCK)/prevention.c $(DEADLOCK)/prevention.h $(DEADLOCK)/banker.h 
	$(CC) $(CFLAGS) -c $(DEADLOCK)/prevention.c -o $(BUILD_DIR)/prevention.o

# multi_cpu_scheduler

$(BUILD_DIR)/m_pcb.o: $(MULTI_CPU_SCHEDULER)/m_pcb.c $(MULTI_CPU_SCHEDULER)/m_pcb.h  $(SCHEDULER)/pcb.h
	$(CC) $(CFLAGS) -c $(MULTI_CPU_SCHEDULER)/m_pcb.c -o $(BUILD_DIR)/m_pcb.o

$(BUILD_DIR)/m_utils.o: $(MULTI_CPU_SCHEDULER)/m_utils.c $(MULTI_CPU_SCHEDULER)/m_utils.h $(MULTI_CPU_SCHEDULER)/m_pcb.h  $(SCHEDULER)/pcb.h
	$(CC) $(CFLAGS) -c $(MULTI_CPU_SCHEDULER)/m_utils.c -o $(BUILD_DIR)/m_utils.o

$(BUILD_DIR)/m_input.o: $(MULTI_CPU_SCHEDULER)/m_input.c $(MULTI_CPU_SCHEDULER)/m_input.h $(MULTI_CPU_SCHEDULER)/m_pcb.h  $(SCHEDULER)/pcb.h
	$(CC) $(CFLAGS) -c $(MULTI_CPU_SCHEDULER)/m_input.c -o $(BUILD_DIR)/m_input.o


$(BUILD_DIR)/m_queue.o: $(MULTI_CPU_SCHEDULER)/m_queue.c $(MULTI_CPU_SCHEDULER)/m_queue.h $(MULTI_CPU_SCHEDULER)/m_pcb.h  $(SCHEDULER)/pcb.h
	$(CC) $(CFLAGS) -c $(MULTI_CPU_SCHEDULER)/m_queue.c -o $(BUILD_DIR)/m_queue.o

$(BUILD_DIR)/m_cpu.o: $(MULTI_CPU_SCHEDULER)/m_cpu.c $(MULTI_CPU_SCHEDULER)/m_cpu.h $(MULTI_CPU_SCHEDULER)/m_pcb.h $(SCHEDULER)/pcb.h
	$(CC) $(CFLAGS) -c $(MULTI_CPU_SCHEDULER)/m_cpu.c -o $(BUILD_DIR)/m_cpu.o



$(BUILD_DIR)/m_scheduler.o: $(MULTI_CPU_SCHEDULER)/m_scheduler.c $(MULTI_CPU_SCHEDULER)/m_scheduler.h $(MULTI_CPU_SCHEDULER)/m_pcb.h  $(SCHEDULER)/pcb.h
	$(CC) $(CFLAGS) -c $(MULTI_CPU_SCHEDULER)/m_scheduler.c -o $(BUILD_DIR)/m_scheduler.o


$(BUILD_DIR)/m_fcfs.o: $(MULTI_CPU_SCHEDULER)/m_fcfs.c $(MULTI_CPU_SCHEDULER)/m_fcfs.h $(MULTI_CPU_SCHEDULER)/m_queue.h $(MULTI_CPU_SCHEDULER)/m_pcb.h  $(SCHEDULER)/pcb.h $(MULTI_CPU_SCHEDULER)/m_statistics.h
	$(CC) $(CFLAGS) -c $(MULTI_CPU_SCHEDULER)/m_fcfs.c -o $(BUILD_DIR)/m_fcfs.o


$(BUILD_DIR)/m_sjf.o: $(MULTI_CPU_SCHEDULER)/m_sjf.c $(MULTI_CPU_SCHEDULER)/m_sjf.h $(MULTI_CPU_SCHEDULER)/m_cpu.h $(MULTI_CPU_SCHEDULER)/m_pcb.h  $(SCHEDULER)/pcb.h $(MULTI_CPU_SCHEDULER)/m_statistics.h
	$(CC) $(CFLAGS) -c $(MULTI_CPU_SCHEDULER)/m_sjf.c -o $(BUILD_DIR)/m_sjf.o


$(BUILD_DIR)/m_round_robin.o: $(MULTI_CPU_SCHEDULER)/m_round_robin.c $(MULTI_CPU_SCHEDULER)/m_round_robin.h $(MULTI_CPU_SCHEDULER)/m_cpu.h $(MULTI_CPU_SCHEDULER)/m_pcb.h  $(SCHEDULER)/pcb.h $(MULTI_CPU_SCHEDULER)/m_statistics.h
	$(CC) $(CFLAGS) -c $(MULTI_CPU_SCHEDULER)/m_round_robin.c -o $(BUILD_DIR)/m_round_robin.o


$(BUILD_DIR)/m_priority.o: $(MULTI_CPU_SCHEDULER)/m_priority.c $(MULTI_CPU_SCHEDULER)/m_priority.h $(MULTI_CPU_SCHEDULER)/m_cpu.h $(MULTI_CPU_SCHEDULER)/m_pcb.h  $(SCHEDULER)/pcb.h $(MULTI_CPU_SCHEDULER)/m_statistics.h
	$(CC) $(CFLAGS) -c $(MULTI_CPU_SCHEDULER)/m_priority.c -o $(BUILD_DIR)/m_priority.o


$(BUILD_DIR)/m_gantt.o: $(MULTI_CPU_SCHEDULER)/m_gantt.c $(MULTI_CPU_SCHEDULER)/m_gantt.h
	$(CC) $(CFLAGS) -c $(MULTI_CPU_SCHEDULER)/m_gantt.c -o $(BUILD_DIR)/m_gantt.o

$(BUILD_DIR)/m_statistics.o: $(MULTI_CPU_SCHEDULER)/m_statistics.c $(MULTI_CPU_SCHEDULER)/m_statistics.h $(MULTI_CPU_SCHEDULER)/m_pcb.h
	$(CC) $(CFLAGS) -c $(MULTI_CPU_SCHEDULER)/m_statistics.c -o $(BUILD_DIR)/m_statistics.o


# file_system : FILE_SYSTEM

$(BUILD_DIR)/disk.o: $(FILE_SYSTEM)/disk.c $(FILE_SYSTEM)/disk.h 
	$(CC) $(CFLAGS) -c $(FILE_SYSTEM)/disk.c -o $(BUILD_DIR)/disk.o

$(BUILD_DIR)/cache.o: $(FILE_SYSTEM)/cache.c $(FILE_SYSTEM)/cache.h 
	$(CC) $(CFLAGS) -c $(FILE_SYSTEM)/cache.c -o $(BUILD_DIR)/cache.o

$(BUILD_DIR)/superblock.o: $(FILE_SYSTEM)/superblock.c $(FILE_SYSTEM)/superblock.h 
	$(CC) $(CFLAGS) -c $(FILE_SYSTEM)/superblock.c -o $(BUILD_DIR)/superblock.o

$(BUILD_DIR)/bitmap.o: $(FILE_SYSTEM)/bitmap.c $(FILE_SYSTEM)/bitmap.h 
	$(CC) $(CFLAGS) -c $(FILE_SYSTEM)/bitmap.c -o $(BUILD_DIR)/bitmap.o

$(BUILD_DIR)/inode.o: $(FILE_SYSTEM)/inode.c $(FILE_SYSTEM)/inode.h 
	$(CC) $(CFLAGS) -c $(FILE_SYSTEM)/inode.c -o $(BUILD_DIR)/inode.o

$(BUILD_DIR)/directory.o: $(FILE_SYSTEM)/directory.c $(FILE_SYSTEM)/directory.h 
	$(CC) $(CFLAGS) -c $(FILE_SYSTEM)/directory.c -o $(BUILD_DIR)/directory.o

$(BUILD_DIR)/file.o: $(FILE_SYSTEM)/file.c $(FILE_SYSTEM)/file.h 
	$(CC) $(CFLAGS) -c $(FILE_SYSTEM)/file.c -o $(BUILD_DIR)/file.o

$(BUILD_DIR)/path.o: $(FILE_SYSTEM)/path.c $(FILE_SYSTEM)/path.h 
	$(CC) $(CFLAGS) -c $(FILE_SYSTEM)/path.c -o $(BUILD_DIR)/path.o

$(BUILD_DIR)/fs.o: $(FILE_SYSTEM)/fs.c $(FILE_SYSTEM)/fs.h 
	$(CC) $(CFLAGS) -c $(FILE_SYSTEM)/fs.c -o $(BUILD_DIR)/fs.o






#
run: $(TARGET)
	./$(TARGET)


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up build files
clean:
	rm -rf $(OBJ) $(TARGET) $(BUILD_DIR) $(CONCURRENCY)/*o $(MEMORY)/*.o  *.exe 


.PHONY: all run clean