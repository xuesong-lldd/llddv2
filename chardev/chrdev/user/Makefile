CC=gcc
CFLAGS=-g -O2
TARGET = main
OBJS = $(TARGET).o
%.o:%.c
	$(CC) -c -o $@ $< $(CFLAGS)
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJS)
