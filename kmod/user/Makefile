CC=gcc
CFLAGS=-g -O2
OBJS = load_kmod.o
%.o:%.c
	$(CC) -c -o $@ $< $(CFLAGS)
load_kmod: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f load_kmod *.o
