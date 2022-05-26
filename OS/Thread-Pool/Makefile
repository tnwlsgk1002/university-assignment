CC = gcc
CFLAGS = -g -Wall
LIBS = -lpthread
INCLUDE =
OBJS = hw4.o
TARGET = hw4

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)
.c.o:
	$(CC) -c $(CFLAGS) $*.c $(INCLUDE)
clean:
	rm $(OBJS) $(TARGET)

hw4.o: hw4.c
