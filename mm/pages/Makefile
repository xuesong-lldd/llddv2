obj-m := tap_page.o
#switch the kernel source on which to build
KERNELDIR := /lib/modules/$(shell uname -r)/build
#KERNELDIR := /lib/modules/5.6.11/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
