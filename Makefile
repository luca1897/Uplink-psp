TARGET = uplink
OBJS =  main.o common.o draw.o system.o filelist.o run.o net.o


BUILD_PRX = 1
PSP_FW_VERSION=390
PSPLIBSDIR = $(PSPSDK)/..
INCDIR = -I ../../include/
CFLAGS = -O2 -G0 -DDEVHOOK -DPSPFW3XX
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CXXFLAGS)

LIBDIR = -L ../../libs
LDFLAGS =
LIBS=   -lengine -lpspwlan -lglut -lGLU -lGL -lpspvfpu -lm -lstdc++ -lpsppower \
        -lpsprtc -lpspaudio -lpspusb -lpspusbstor \
        -lpspkubridge -lpspsystemctrl_user -lpspgum -lpspgu -lpsphttp -lpspssl \
         -lpsputility -lpspgum -lpspgu

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Uplink
PSPSDK=$(shell psp-config --pspsdk)
include $(PSPSDK)/lib/build.mak

all:
	cp uplink.prx Bin/uplink.prx
