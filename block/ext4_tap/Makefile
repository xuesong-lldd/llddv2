obj-m := ext4tap.o
KERNELDIR := /lib/modules/$(shell uname -r)/build
KBUILD_EXTRA_SYMBOLS := /home/dennis/llddv2/block/blk_req/Module.symvers
KBUILD_EXTMOD := /home/dennis/llddv2/block/blk_req
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
