CROSS_COMPILE := 
CROSS := 			$(CROSS)

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

obj-m += 			nxmain.o
nxmain-objs := 		init/startup.o \
					init/godown.o \
					workqueue/queue_ng.o

all: clean
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean.bak:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

clean:
	rm -rf *.o modules.order Module.symvers *.ko *.cmd .tmp_versions .*.cmd *mod.c \
init/*.o init/modules.order init/Module.symvers init/*.ko init/*.cmd init/.tmp_versions init/.*.cmd init/*mod.c \
workqueue/*.o workqueue/modules.order workqueue/Module.symvers workqueue/*.ko workqueue/*.cmd workqueue/.tmp_versions \
workqueue/.*.cmd workqueue/*mod.c
