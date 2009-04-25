#include <usb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "psx.h"
#include "ps2.h"

//unsigned char *mc2rw_

//#ifndef PS2_PAGESIZE
#define PS2_PAGESIZE 512
//#endif

unsigned char *mc2rw_read_page(usb_dev_handle *udev, int page)
{
	int i=0, p=0, ret=0;
	static unsigned char data_p[PS2_PAGESIZE], temp_data[1024];
	struct psx_usb_read_receive_buf receive_data;
	unsigned char start_read_cmd[] = {0xaa, 0x42, 0x06, 0x00, 0x81, 0x23, 0x00, 0x00, (page>>8)&0xFF, page&0xFF};
	unsigned char end_read_cmd[] = {0xaa, 0x42, 0x05, 0x00, 0x81, 0xf3, 0x51, 0x00, 0x00};

	mcrw_addr_debug(page);
	/* start read page */
	printf("Starting Read Page\n");
	ret = usb_bulk_write(udev, 0x02, start_read_cmd, sizeof(start_read_cmd), 1000);
	if (ret != sizeof(start_read_cmd))
		printf("Error!\n");
	ret = usb_bulk_read(udev, 0x81, temp_data, sizeof(temp_data), 1000);
	mcrw_debug(temp_data, ret);

	printf("Reading Data\n");
	/* read data */
	for (p=0; p<(PS2_PAGESIZE/128); p++)
	{
		struct psx_usb_read_send_buf send_data = {
			.usb_ctrl = {0xaa, 0x42, 0x8c, 0x00},
			.psx_cmd_ctrl = {0x81, 0x43},
			.receive_header_chk = {0x00, 0x00},
			.read_addr = {0x00, i}, //{(page>>8)&0xFF, page&0xFF},
			.receive_cmd_ack = 0x00,
			.receive_start_flag = 0x00,
			.receive_read_addr = {0x00, 0x00},
			.receive_xor = 0x00,
			.receive_end_flag = 0x00};

		for(i=0; i<128; i++)
			send_data.receive_read_data[i] = 0x00;

		ret = usb_bulk_write(udev, 0x02, (char *)&send_data, sizeof(send_data), 1000);
		if (ret != sizeof(send_data))
			printf("Error!\n");
		
		ret = usb_bulk_read(udev, 0x81, temp_data, sizeof(temp_data), 1000);
		mcrw_debug(temp_data, ret);
		
		//temp_data[ret+1] = '\0';
		//strncat(data_p, temp_data, ret);
	}
	
	/* end read page */
	printf("End Read Page\n");
	ret = usb_bulk_write(udev, 0x02, end_read_cmd, sizeof(end_read_cmd), 1000);
	if (ret != sizeof(end_read_cmd))
		printf("Error! ret: %d, size: %d\n", ret, sizeof(end_read_cmd));
	ret = usb_bulk_read(udev, 0x81, temp_data, sizeof(temp_data), 1000);
	mcrw_debug(temp_data, ret);

	return data_p;
}

int mc2rw_write(void)
{
	return 0;
}

int mc2rw_erase(void)
{
	return 0;
}
