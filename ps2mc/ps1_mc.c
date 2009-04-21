#include <usb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "psx.h"
#include "ps1.h"

unsigned int read_check_header[] = {
	0x5a, 0x5d,
	0x5c, 0x5d,
	0x47
};

unsigned char *mc1rw_read_frame(usb_dev_handle *udev, int frame)
{
	int i, xor=0, ret;
	static unsigned char data_f[128];
	struct psx_usb_read_send_buf send_data = {
		.usb_ctrl = {0xaa, 0x42, 0x8c, 0x00},
		.psx_cmd_ctrl = {0x81, 0x52},
		.receive_header_chk = {0x00, 0x00},
		.read_addr = {(frame>>8)&0xff, frame&0xff},
		.receive_cmd_ack = 0x00,
		.receive_start_flag = 0x00,
		.receive_read_addr = {0x00, 0x00},
		.receive_xor = 0x00,
		.receive_end_flag = 0x00,
		};
	struct psx_usb_read_receive_buf receive_data;

#ifdef __MCRW_DEBUG__
	printf("Frame Address: %02x %02x\n", (frame >> 8) & 0xff, frame & 0xff);
#endif

	for (i=0; i<128; i++) /* receive data */
		send_data.receive_read_data[i] = 0x00;
	

	ret = usb_bulk_write(udev, 0x02, (char *)&send_data, sizeof(send_data), 1000);
	ret = usb_bulk_read(udev, 0x81, (char *)&receive_data, sizeof(receive_data), 1000);

#ifdef __MCRW_DEBUG__
	printf("DEBUG: ");
	for (i=0; i<sizeof(receive_data.data); i++)
	{
		printf("%02x ", receive_data.data[i]);
	}
	printf("\n");
#endif
	/*
	if ((receive_data.header_chk[0] != 0x5a)&&(receive_data.header_chk[1] != 0x5d))
	{
		printf("Error invalid USB header returned!\n");
		return NULL;
	}
	*/

	if ((receive_data.cmd_ack != 0x5c)&&(receive_data.start_data_flag != 0x5d))
	{
		printf("Error invalid MC header returned!\n");
		return NULL;
	}

	if ((receive_data.read_addr[0] != ((frame>>8)&0xff)) && (receive_data.read_addr[1] != (frame&0xff)))
	{
		printf("Error invalid address returned!\n");
		return NULL;
	}

	xor ^= ((frame>>8)&0xff);
	xor ^= (frame&0xff);
	for(i=0; i<128; i++)
	{
		xor ^= receive_data.data[i];
	}

	if (xor != receive_data.data_xor)
	{
		printf("Error invalid Checksum! Gen: %02x, Ret: %02x\n", xor, receive_data.data_xor);
		return NULL;
	}
	if (receive_data.end_data_flag != 0x47)
	{
		printf("Error invalid end flag returned!\n");
		return NULL;
	}
	memcpy(data_f, receive_data.data, 128);
	return data_f;
}

int mc1rw_write_frame(int frame, char* data_f)
{
	return 0;
}

unsigned char *mc1rw_read_block(usb_dev_handle *udev, int block)
{	int i=0, j=0;
	static unsigned char data_b[8192], *data_f;

	for (i=0; i<64; i++)
	{
		data_f = mc1rw_read_frame(udev, (block*64)+i);
		if (data_f != NULL)
		{
			for (j=0; j<128; j++)
				data_b[(i*128)+j] = data_f[j];
		}
		else
		{
			return NULL;
		}
	}
	return data_b;
}

int mc1rw_write_block(int block, char* data_b)
{
	return 0;
}

