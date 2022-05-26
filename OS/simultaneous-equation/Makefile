CC = gcc
CFLAGS = -Wall -g
LIBS =
INCLUDE =
OBJS = hw1.o
TARGET = hw1

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)
.c.o:
	$(CC) -c $(CFLAGS) $*.c $(INCLUDE)
clean:
	rm $(OBJS) $(TARGET)

hw1.o: hw1.c
