obj-m := rtfifo.o
KERNELDIR := /lib/modules/$(shell uname -r)/build
#KERNELDIR := /home/xuesong/linux/rt/ori-bld
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
