#include <usb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "psx.h"
#include "ps2.h"

//#ifndef PS2_PAGESIZE
#define PS2_PAGESIZE 512
//#endif

//#ifndef PS2_FRAMESIZE
#define PS2_FRAMESIZE 128
//#endif

int mc2rw_card_auth(usb_dev_handle *udev)
{
	int i=0, ret=0;
	unsigned char temp[256], *auth;
	unsigned char auth6[] = {0xaa, 0x42, 0x0D, 0x00, 0x81, 0xF0, 0x06, 0x00, 0x00, 0x0E, 0xa3, 0xb3, 0xa0, 0x31, 0x19, 0x5b, 0x9c, 0x3f, 0x60, 0x00, 0x00};
	unsigned char auth7[] = {0xaa, 0x42, 0x0D, 0x00, 0x81, 0xF0, 0x07, 0x00, 0x00, 0x0E, 0xa9, 0xc7, 0x01, 0xeb, 0x9b, 0x34, 0xda, 0x69, 0x98, 0x00, 0x00};
	unsigned char auth11[] = {0xaa, 0x42, 0x0D, 0x00, 0x81, 0xF0, 0x0B, 0x0E, 0xc8, 0xe0, 0x72, 0xce, 0x96, 0x31, 0xdc, 0x21, 0xce, 0x00, 0x00};
	
	for (i=0; i<21; i++)
	{
		unsigned char auth[] = {0xaa, 0x42, 0x05, 0x00, 0x81, 0xF0, i, 0x00, 0x00};
		switch(i)
		{
		case 6:
			ret = usb_bulk_write(udev, 0x02, auth6, sizeof(auth6), 1000);
			ret = usb_bulk_read(udev, 0x81, temp, sizeof(temp), 1000);
			break;
		case 7:
			ret = usb_bulk_write(udev, 0x02, auth7, sizeof(auth7), 1000);
			ret = usb_bulk_read(udev, 0x81, temp, sizeof(temp), 1000);
			break;
		case 11:
			ret = usb_bulk_write(udev, 0x02, auth11, sizeof(auth11), 1000);
			ret = usb_bulk_read(udev, 0x81, temp, sizeof(temp), 1000);
			break;
		default:
			ret = usb_bulk_write(udev, 0x02, auth, sizeof(auth), 1000);
			ret = usb_bulk_read(udev, 0x81, temp, sizeof(temp), 1000);
		}

	}
	return 0;
}

int mc2rw_reset_auth(usb_dev_handle *udev)
{
	int i=0, ret=0;
	unsigned char temp[256],
		cmd[]={0xaa, 0x42, 0x05, 0x00, 0x81, 0xF3, 0x00, 0x00, 0x00};
	
	ret = usb_bulk_write(udev, 0x02, cmd, sizeof(cmd), 1000);
	ret = usb_bulk_read(udev, 0x81, temp, sizeof(temp), 1000);
	mcrw_debug(temp, ret);
	ret = usb_bulk_write(udev, 0x02, cmd, sizeof(cmd), 1000);
	ret = usb_bulk_read(udev, 0x81, temp, sizeof(temp), 1000);
	mcrw_debug(temp, ret);
	unsigned char cmd_f7[] = {0xaa, 0x42, 0x05, 0x00, 0x81, 0xF7, 0x01, 0x00, 0x00};
	ret = usb_bulk_write(udev, 0x02, cmd_f7, sizeof(cmd_f7), 1000);
	ret = usb_bulk_read(udev, 0x81, temp, sizeof(temp), 1000);
	mcrw_debug(temp, ret);

	return 0;
}
int mc2rw_get_terminator(usb_dev_handle *udev)
{
	int i=0, ret=0;
	unsigned char temp[256],
		cmd[]={0xaa, 0x42, 0x05, 0x00, 0x81, 0x28, 0x00, 0x00, 0x00};
	
	ret = usb_bulk_write(udev, 0x02, cmd, sizeof(cmd), 1000);
	ret = usb_bulk_read(udev, 0x81, temp, sizeof(temp), 1000);
	mcrw_debug(temp, ret);

	return 0;
}

int mc2rw_set_terminator(usb_dev_handle *udev, unsigned char new)
{
	int i=0, ret=0;
	unsigned char temp[256],
		cmd[]={0xaa, 0x42, 0x05, 0x00, 0x81, 0x27, new, 0x00, 0x00};
	
	ret = usb_bulk_write(udev, 0x02, cmd, sizeof(cmd), 1000);
	ret = usb_bulk_read(udev, 0x81, temp, sizeof(temp), 1000);
	mcrw_debug(temp, ret);
	
	return 0;
}

int mc2rw_read_spec(usb_dev_handle *udev)
{
	int i=0, ret=0;
	unsigned char temp[256],
		cmd[148]={0xaa, 0x42, 0x05, 0x00, 0x81, 0x26, 0x5a, 0x00, 0x00};
	
	ret = usb_bulk_write(udev, 0x02, cmd, sizeof(cmd), 1000);
	ret = usb_bulk_read(udev, 0x81, temp, sizeof(temp), 1000);
	mcrw_debug(temp, ret);
	return 0;
}

