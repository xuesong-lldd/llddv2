obj-m := tap_pstate.o
#KERNELDIR := /home/xuesong/linux/raspberrypi/target/kbld
KERNELDIR := /home/xuesong/linux/rt/ori-bld
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
