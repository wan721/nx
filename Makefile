CROSS_COMPILE := 
CROSS := 			$(CROSS)

obj-m += 			nxmain.o
nxmain-objs := 		init/startup.o \
					init/godown.o \
					workqueue/queue_ng.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

