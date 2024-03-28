obj-m := ramhd_mq.o
KERNELDIR := /lib/modules/$(shell uname -r)/build
#KERNELDIR := /home/xuesong/linux/raspberrypi/target/kbld
PWD := $(shell pwd)

CFLAGS_ramhd_mq.o = -I$(src)

default:
	$(MAKE)  -C $(KERNELDIR) M=$(PWD) modules
clean:
	$(MAKE)  -C $(KERNELDIR) M=$(PWD) clean
