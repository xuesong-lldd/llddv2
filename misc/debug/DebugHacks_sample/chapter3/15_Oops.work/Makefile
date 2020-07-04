obj-m := demo.o

all:
	make -C /usr/src/kernels/2.6.18-53.5AXS3custom-x86_64 M=`pwd` V=1

.PHONY: ins rm rei clean

clean:
	rm -fr *.ko *.mod.ko *.o *.mod.c Module.symvers .*.cmd .tmp_versions
