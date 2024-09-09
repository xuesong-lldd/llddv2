obj-m := pf_ramdisk.o
KERNELDIR := /home/xuesong/linux/rt/ori-bld
CFLAGS_pf_ramdisk.o = -I$(src)

PWD := $(shell pwd)
default:
	$(MAKE)  -C $(KERNELDIR) M=$(PWD) modules
clean:
	$(MAKE)  -C $(KERNELDIR) M=$(PWD) clean
