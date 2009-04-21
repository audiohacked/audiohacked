#include <usb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "psx.h"

#define MY_HAVE_USB_CONFIG 0
#define MY_HAVE_ALTIFACE 0

int init_mcrw(usb_dev_handle *udev)
{
	int ret;
	ret = usb_claim_interface(udev, 0);
	if (ret)
	{
		perror("usb_claim_interface");
	}
	
	#if MY_HAVE_USB_CONFIG
	ret = usb_set_configuration(udev, 1);
	if (ret)
	{
		perror("usb_set_configuration");
	}
	#endif

	#if MY_HAVE_ALTIFACE
	ret = usb_set_altinterface(udev, 0);
	if (ret)
	{
		perror("usb_set_altinterface");
	}
	#endif

	return 0;
}

int cleanup_mcrw(usb_dev_handle *udev)
{
	int ret;
	
	ret = usb_release_interface(udev, 0);
	if (ret)
	{
		perror("usb_release_interface");
	}

	return 0;
}

int open_mcrw(usb_dev_handle *udev)
{
	int ret;
	unsigned char wbuf[4] = {0x81, 0x11, 0x00, 0x00};
	unsigned char rbuf[2];
	ret = usb_bulk_write(udev, 0x02, wbuf, sizeof(wbuf), 1000);
	ret = usb_bulk_read(udev, 0x81, rbuf, sizeof(rbuf), 1000);
	return 0;
}

int close_mcrw(usb_dev_handle *udev)
{
	int ret;
	unsigned char wbuf[4] = {0xaa, 0x42, 0x04, 0x00};
	ret = usb_bulk_write(udev, 0x02, wbuf, sizeof(wbuf), 1000);
	return 0;
}

