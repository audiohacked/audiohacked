#include <usb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "psx.h"
#include "ps2.h"

int mc2rw_ecc(usb_dev_handle *udev)
{
	int i=0, ret=0;
	unsigned char temp[256],
		cmd[148]={0xaa, 0x42, 0x05, 0x00, 0x81, 0x26, 0x5a, 0x00, 0x00};
	
	ret = usb_bulk_write(udev, 0x02, cmd, sizeof(cmd), 1000);
	ret = usb_bulk_read(udev, 0x81, temp, sizeof(temp), 1000);
	mcrw_debug(temp, ret);
	return 0;
}

