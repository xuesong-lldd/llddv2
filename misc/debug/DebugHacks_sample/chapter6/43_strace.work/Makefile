EXECS = st1 st2 st1g
all: $(EXECS)

st1g: st1.c
	$(CC) -o $@ -g $<

.PNOHY: clean
clean:
	rm -f $(EXECS)
