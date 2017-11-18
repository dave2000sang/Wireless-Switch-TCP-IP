
OUT_FILE=solar
OUT=-o $(OUT_FILE)

LIBGPIO = /usr/local/lib

TARGET_HOST = 

export CROSS_COMPILE = 

AS	= $(CROSS_COMPILE)as
LD	= $(CROSS_COMPILE)ld
CC	= $(CROSS_COMPILE)gcc
CPP	= $(CC) -E
CXX	= $(CROSS_COMPILE)g++
AR	= $(CROSS_COMPILE)ar
NM	= $(CROSS_COMPILE)nm
STRIP	= $(CROSS_COMPILE)strip
OBJCOPY	= $(CROSS_COMPILE)objcopy
OBJDUMP	= $(CROSS_COMPILE)objdump

LIBS = $(LIBBASE) $(LIBHOST) $(LIBBASE) -L$(LIBGPIO)


INC_FILE=$(wildcard ./*.h)

SRC_FILE=$(wildcard ./*.cpp)

OBJ_FILE=$(patsubst %.cpp, %.o,$(SRC_FILE))

INCLUDE=-I. -I./include/linux -I./include/can

CC_OPTS=$(INCLUDE) -c -Wall -Werror -fomit-frame-pointer -Dlinux_gnu -DLINUX -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE
#CC_OPTS += -static
CC_OPTS+= -g -DTARGETMIPS -mlong-calls
CC_OPTS+=$(CFLAG_COM)

LINK_OPTS= -lc -lrt -lm -lstdc++ -lpthread -lrt -lwiringPi

all: $(OBJ_FILE)
	$(CXX) $(OUT) $(OBJ_FILE) $(LIBDIR) $(LIBS) $(LINK_OPTS)
	$(STRIP) $(OUT_FILE)

$(OBJ_FILE): %.o : %.cpp $(INC_FILE) ./Makefile
	$(CXX) $(CC_OPTS) $(OPTS) -o $@ $<

clean:
	rm -f $(OUT_FILE)
	rm -f $(OBJ_FILE)


