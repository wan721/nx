CROSS_COMPILE	:=
CROSS 			:=	$(CROSS)

obj-m 			+=	nxmodules.o
nxmodules-objs	:=	app_proc.o bstr_proc.o debug_proc.o misc_proc.o \
					proc_handle.o sys_proc.o conf_proc.o

all: clean
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean.bak:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

clean:
	rm -rf *.o modules.order Module.symvers *.ko *.cmd .tmp_versions .*.cmd *mod.c
