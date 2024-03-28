obj-m := led_demo.o
KERNELDIR := /home/xuesong/linux/raspberrypi/target/kbld 
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
