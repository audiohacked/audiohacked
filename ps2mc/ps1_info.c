#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <usb.h>

#include "ps1.h"

struct header_page *read_ps1_mc_info(usb_dev_handle *udev)
{
	return (struct header_page *)mc1rw_read_page(udev, 0);
}

struct directory_page *read_ps1_mc_block_info(usb_dev_handle *udev, int block)
{
	return (struct directory_page *)mc1rw_read_page(udev, block);
}

int print_ps1_block_info(struct directory_page data, int info_block_num)
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
	printf("Block %d Info: \n", info_block_num);
	printf("\tBlock Availiable: ");
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
	default:
		printf("Unknown\n");
	}

	/*
	switch((unsigned)data.reserved[0])
	{
	case 0x00:
	case 0xFF:
		break;
	}
	*/

	printf("\tUsed blocks: %d\n", (data.use/0x2000));
	if (data.link_order == 0xFFFF) printf("\tLink Order: last\n");
	else printf("\tLink Order: %d\n", data.link_order);
	printf("\tCountry Code: %.2s\n", &data.country_code);
	printf("\tProduct Code: %.10s\n", &data.product_code);
	printf("\tIdentifier: %.8s\n", &data.identifier);
	printf("\tBlock Info XOR Code: 0x%02x\n", data.xor_code);

	return 0;
}
