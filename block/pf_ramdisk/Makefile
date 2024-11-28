obj-m := pf_ramdisk.o
KERNELDIR := /lib/modules/$(shell uname -r)/build
CFLAGS_pf_ramdisk.o = -I$(src)

PWD := $(shell pwd)
default:
	$(MAKE)  -C $(KERNELDIR) M=$(PWD) modules
clean:
	$(MAKE)  -C $(KERNELDIR) M=$(PWD) clean
