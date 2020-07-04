obj-m := kpro1.o kpro2.o kpro3.o

all:
	make -C /usr/src/kernels/2.6.18-53.5AXS3custom-x86_64 M=`pwd` V=1

.PHONY: ins rm rei clean
ins:
	insmod kpro1.ko

rm:
	rmmod kpro1.ko

rei:
	rmmod kpro1.ko
	insmod kpro1.ko

clean:
	rm -f *.ko *.mod.ko *.o *.mod.c Module.symvers
