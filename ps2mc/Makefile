SRCS = device.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -g
TARGET = mcadaptor_test
LDFLAGS = -lusb
CC = gcc
RM = rm
RM_OPTS = -rf
VI = vim
GDB = gdb

default: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(RM_OPTS) $(TARGET) $(OBJS)
edit:
	$(VI) $(SRCS)

test: $(TARGET)
	./$(TARGET)

libusb-test: testlibusb.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@
