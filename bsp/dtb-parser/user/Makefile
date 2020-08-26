CC=gcc
CFLAGS=-g -O2
OBJS = dtb_parser.o
%.o:%.c
	$(CC) -c -o $@ $< $(CFLAGS)
dtbp: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f dtbp *.o
