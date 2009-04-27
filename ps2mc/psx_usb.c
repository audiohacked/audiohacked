#include <usb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "psx.h"

#define MY_HAVE_USB_CONFIG 0
#define MY_HAVE_ALTIFACE 0

usb_dev_handle *find_mcrw(void)
{
	struct usb_bus *bus;
	struct usb_device *dev;

	usb_init();
	usb_find_busses();
	usb_find_devices();

	for( bus = usb_busses; bus; bus = bus->next )
	{
		for( dev = bus->devices; dev; dev = dev->next)
		{
			if ((dev->descriptor.idVendor == 0x054C) && (dev->descriptor.idProduct == 0x02EA))
			{
				printf("Found PS2-to-USB Memory Card Adaptor at bus-dir: %s, dev-file: %s, VendorId: %04X, ProductId: %04X\n",
					bus->dirname, dev->filename, dev->descriptor.idVendor, dev->descriptor.idProduct);
				return usb_open(dev);
			}
			else
			{
				printf("bus: %s; PS2-to-USB Memory Card Adaptor not found!\n", bus->dirname);
			}
		}
	}

	return NULL;
}

int init_mcrw(usb_dev_handle *udev)
{
	int ret;
	ret = usb_claim_interface(udev, 0);
	if (ret)
	{
		perror("usb_claim_interface");
		return -1;
	}
	
	#if MY_HAVE_USB_CONFIG
	ret = usb_set_configuration(udev, 1);
	if (ret)
	{
		perror("usb_set_configuration");
		return -1;
	}
	#endif

	#if MY_HAVE_ALTIFACE
	ret = usb_set_altinterface(udev, 0);
	if (ret)
	{
		perror("usb_set_altinterface");
		return -1;
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
	unsigned char rbuf[2] = {0x00, 0x00};

	do {
		ret = usb_bulk_write(udev, 0x02, wbuf, sizeof(wbuf), 1000);
		ret = usb_bulk_read(udev, 0x81, rbuf, sizeof(rbuf), 1000);
	} while ((rbuf[0] != 0x55)&&(rbuf[1] != 0xaf));

	printf("Valid Open!\n");

	return 0;
}

int close_mcrw(usb_dev_handle *udev)
{
	int ret;
	unsigned char wbuf[4] = {0xaa, 0x42, 0x04, 0x00};
	ret = usb_bulk_write(udev, 0x02, wbuf, sizeof(wbuf), 1000);
	printf("Valid Close!\n");
	return 0;
}

