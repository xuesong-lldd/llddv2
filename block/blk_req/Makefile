obj-m := ramhd_req.o
KERNELDIR := /lib/modules/$(shell uname -r)/build
#KERNELDIR := /home/dennis/embedded/raspi4b/linux
PWD := $(shell pwd)

default:
	$(MAKE)  -C $(KERNELDIR) M=$(PWD) modules
clean:
	$(MAKE)  -C $(KERNELDIR) M=$(PWD) clean
