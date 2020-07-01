BASEINCLUDE:= /lib/modules/$(shell uname -r)/build
oob-objs	:= oob_test.o
dfree-objs	:= free_test.o
uaf-objs	:= uaf_test.o
loob-objs	:= loob_test.o

obj-m	:= oob.o dfree.o uaf.o loob.o

all :
	$(MAKE) -C $(BASEINCLUDE) M=$(PWD) modules;

clean :
	$(MAKE) -C $(BASEINCLUDE) M=$(PWD) clean;
	rm -rf *.ko
