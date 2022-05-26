CC = gcc
CFLAGS = -g -Wall
LIBS = -lrt
INCLUDE =
OBJS = hw2.o
TARGET = hw2

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)
.c.o:
	$(CC) -c $(CFLAGS) $*.c $(INCLUDE)
clean:
	rm $(OBJS) $(TARGET)

hw2.o: hw2.c
