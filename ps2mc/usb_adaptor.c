#include <usb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "usb_adaptor.h"
#include "psx_usb.h"
#include "ps1_mc.h"
#include "ps2_mc.h"

struct usb_bus *bus;
struct usb_device *dev;

int main(void)
{
	usb_dev_handle *udev = NULL;
	struct usb_bulk_buf start, data;
	char string[256];
	int ret, i;
	//int block=16, frame=64;
	int block=1, frame=4;

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
		setup_mcrw(udev);

		/* open device for transfer */
		mcrw_send(udev, CMD_OPEN_DEV);
		start = mcrw_receive(udev);

		/* send/receive data */
		mc1rw_read_frame(udev, 1);

		/* when we're done close device */
		mcrw_send(udev, CMD_CLOSE_DEV);
		
		cleanup_mcrw(udev);
		usb_close(udev);
	}
	printf("DONE!\n");
	return 0;
}

