all: calc0 calc debug.so

calc0: calc.c
	$(CC) -O0 -g $< -o $@

calc: calc.c
	$(CC) -O2 -g $< -o $@

debug.so: debug.c
	$(CC) -O2 -g -shared -fPIC $< -o $@

.PNOHY: clean
clean:
	rm -f calc0 calc debug.so

