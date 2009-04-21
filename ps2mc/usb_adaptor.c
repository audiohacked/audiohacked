#include <usb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "psx.h"
#include "ps1.h"
#include "ps2.h"

struct usb_bus *bus;
struct usb_device *dev;

int main(void)
{
	usb_dev_handle *udev = NULL;
	char string[256];
	int ret, i;

	usb_init();
	usb_find_busses();
	usb_find_devices();

	for (bus = usb_busses; bus; bus = bus->next)
	{
		for (dev = bus->devices; dev; dev = dev->next)
		{
			if ((dev->descriptor.idVendor == 0x054c)&&(dev->descriptor.idProduct == 0x02ea)) {
				printf("Found PS2-to-USB Memory Card Adaptor at bus-dir: %s, bus-file: %s, VendorId: %04X, ProductId: %04X\n",
					bus->dirname, dev->filename, dev->descriptor.idVendor, dev->descriptor.idProduct);
				udev = usb_open(dev);
				break;
			}
			else
			{
				printf("bus: %s; PS2-to-USB Memeory Card Adaptor not found!\n", bus->dirname);
			}
		}
		if (udev != NULL) {
			break;
		}
	}

	if (udev)
	{
		init_mcrw(udev);

		/* open device for transfer */
		open_mcrw(udev);

		/* send/receive data */
		///*
		for (i=0; i<15; i++)
		{
			struct directory_frame *ps1 = read_ps1_mc_block_info(udev, i+1);
			print_ps1_block_info(*ps1, i+1);
		}
		///*/
		//read_ps1_mc_info(udev);

		/* when we're done close device */
		close_mcrw(udev);
		
		cleanup_mcrw(udev);
		usb_close(udev);
	}
	printf("DONE!\n");
	return 0;
}

