
obj-m += pm_qos_req.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
modules_install:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules_install
