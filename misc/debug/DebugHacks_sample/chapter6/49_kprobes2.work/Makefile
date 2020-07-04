obj-m := kpro1.o

all:
	make -C /usr/src/kernels/`uname -r`-x86_64 M=`pwd` V=1

.PHONY: ins rm rei clean
ins:
	insmod kpro1.ko

rm:
	rmmod kpro1.ko

rei:
	rmmod kpro1.ko
	insmod kpro1.ko

clean:
	rm -fr *.ko *.mod.ko *.o *.mod.c Module.symvers .*.cmd .tmp_versions
