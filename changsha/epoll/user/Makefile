CC=gcc
CFLAGS=-g -O2
%.o:%.c
	$(CC) -c -o $@ $< $(CFLAGS)
all: epoll select
epoll: epoll.o
	$(CC) -o $@ $^ $(CFLAGS)
select: select.o
	$(CC) -o $@ $^ $(CFLAGS)
.PHONY: clean

clean:
	rm -f epoll select *.o
