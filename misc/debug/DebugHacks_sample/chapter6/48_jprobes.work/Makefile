obj-m := jpro1.o jpro2.o

KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules	

.PHONY: ins rm rei clean
ins:
	insmod jpro1.ko

rm:
	rmmod jpro1.ko

rei:
	rmmod jpro1.ko
	insmod jpro1.ko

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
