APP = hello
LIB = libevil.so

all: build

build: $(APP) $(LIB)

$(APP): hello.c
	gcc $< -o $@

$(LIB): evil.c
	gcc -shared -fPIC $< -o $@

.PHONY: clean

clean:
	rm -f hello $(APP) $(LIB)
