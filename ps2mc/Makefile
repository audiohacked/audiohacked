SRCS =	psx_usb.c \
	ps1_mc.c \
	ps1_info.c \
	ps2_mc.c \
	usb_adaptor.c 

OBJS = $(SRCS:.c=.o)
CFLAGS = -D__MCRW_DEBUG__
PROJ_CFLAGS = $(CFLAGS) -g -I/opt/local/include
TARGET = mcadaptor_test
PROJ_LDFLAGS = -lusb -L/opt/local/lib
CC = gcc
RM = rm
RM_OPTS = -rf
VI = vim
GDB = gdb

default: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(PROJ_CFLAGS) $(PROJ_LDFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(PROJ_CFLAGS) -c $< -o $@

clean:
	$(RM) $(RM_OPTS) $(TARGET) $(OBJS)
edit:
	$(VI) $(SRCS)

test: $(TARGET)
	./$(TARGET)

libusb-test: testlibusb.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@
