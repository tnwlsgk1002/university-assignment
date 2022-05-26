CC = gcc
CFLAGS = -g -Wall
LIBS = -lpthread
INCLUDE =
OBJS = hw3.o
TARGET = hw3

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)
.c.o:
	$(CC) -c $(CFLAGS) $*.c $(INCLUDE)
clean:
	rm $(OBJS) $(TARGET)

hw3.o: hw3.c
