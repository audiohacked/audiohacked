#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <usb.h>

#include "ps1_mc.h"
#include "ps1_info.h"

struct header_frame read_ps1_mc_info(usb_dev_handle *udev)
{
	struct header_frame hinfo;
	static unsigned char *info;
	
	info = mc1rw_read_frame(udev, 0);
	memcpy(&hinfo, &info, 128);

	return hinfo;
}

struct directory_frame read_ps1_mc_block_info(usb_dev_handle *udev, int block)
{
	struct directory_frame block_info;
	static unsigned char *info;
	
	info = mc1rw_read_frame(udev, block);
	memcpy(&block_info, &info, 128);

	return block_info;
}

int print_ps1_block_info(struct directory_frame data)
{
	/*
	 * available blocks:
	 * 	upper 4:
	 * 		A - Available
	 * 		5 - partially used
	 * 		F - Unusable
	 * 	lower 4:
	 * 		0 - Unused
	 * 		1 - There is no link, but one will be here later
	 * 		2 - mid link block
	 * 		3 - terminating link block
	 * 		F - Unusable
	 * 	Example:
	 * 		A0 - open block
	 * 		51 - In use, there will be alink in next block
	 * 		52 - In Use, this is in a link and will link to another
	 * 		53 - In use, this is the last in the link
	 * 		FF - Unusable
	 */
	printf("Block Availiable: ");
	switch(data.available_blocks)
	{
	case 0xa0:
		printf("Open Block\n");
		break;
	case 0x51:
	case 0x52:
	case 0x53:
		printf("In Use\n");
		break;
	case 0xff:
		printf("Unusable\n");
		break;
	}

	switch(data.reserved[0])
	{
	case 0x00:
	case 0xFF:
		break;
	}

	printf("Use byte: %d %d %d\n", data.use[0], data.use[1], data.use[2]);
	printf("Link Order: %d %d\n", data.link_order[0], data.link_order[1]);
	printf("Country Code: %s\n", data.country_code);
	printf("Product Code: %s\n", data.product_code);
	printf("Identifier: %s\n", data.identifier);
	printf("Block Info XOR Code: 0x%02x\n", data.xor_code);

	return 0;
}
