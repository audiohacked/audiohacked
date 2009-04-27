MAIN_SRC := usb_adaptor.c

PSX_SRC := psx_usb.c \
	psx_debug.c

PS1_SRC := ps1_mc.c \
	ps1_info.c

PS2_SRC := ps2_mc.c \
	ps2_mc_read.c

SRCS = $(PSX_SRC) $(PS1_SRC) $(PS2_SRC) $(MAIN_SRC)

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

default: clean all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(PROJ_CFLAGS) $(PROJ_LDFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(PROJ_CFLAGS) -c $< -o $@

clean:
	$(RM) $(RM_OPTS) $(TARGET) $(OBJS)
edit:
	$(VI) $(MAIN_SRC)

test: $(TARGET)
	./$(TARGET)

libusb-test: testlibusb.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@
