obj-m := kpro3.o

all:
	make -C /usr/src/kernels/`uname -r`-x86_64 M=`pwd` V=1

.PHONY: ins rm rei clean
ins:
	insmod kpro3.ko

rm:
	rmmod kpro3.ko

rei:
	rmmod kpro3.ko
	insmod kpro3.ko

clean:
	rm -fr *.ko *.mod.ko *.o *.mod.c Module.symvers .*.cmd .tmp_versions
