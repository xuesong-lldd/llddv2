ALL: foo prog lib1.so
lib1.so: lib1.c
	gcc -Wall -fPIC  -Wcast-align -c -o lib1.o lib1.c
	gcc -o ./lib1.so -Wl,-Bsymbolic -shared -Wl,-Bdynamic -ldl lib1.o

foo: foo.c
	gcc -o $@ -ggdb $< -ldl

prog: prog.c
	gcc -o $@ -ggdb $< -ldl

clean:
	-rm -f ./prog ./foo ./lib1.so ./lib1.o
