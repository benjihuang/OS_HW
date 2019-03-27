KBUILD_CFLAGS += -w
obj-m += Kernel_Data_Structures.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
unload:
	sudo rmmod Kernel_Data_Structures
load:
	sudo insmod Kernel_Data_Structures.ko
clear:
	sudo dmesg -c
view:
	dmesg