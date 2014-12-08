obj-m			+=	nxmain.o

nxmain-objs		:=	startup.o		\
					godown.o

ccflags-y		+=	-g

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
