#include <usb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "psx.h"
#include "ps1.h"

#define PS1_PAGESIZE 128

unsigned char *mc1rw_read_page(usb_dev_handle *udev, int page)
{
	int i, xor=0, ret;
	static unsigned char data_f[128];
	struct psx_usb_read_send_buf send_data = {
		.usb_ctrl = {0xaa, 0x42, 0x8c, 0x00},
		.psx_cmd_ctrl = {0x81, 0x52},
		.receive_header_chk = {0x00, 0x00},
		.read_addr = {(page>>8)&0xff, page&0xff},
		.receive_cmd_ack = 0x00,
		.receive_start_flag = 0x00,
		.receive_read_addr = {0x00, 0x00},
		.receive_xor = 0x00,
		.receive_end_flag = 0x00,
	};
	struct psx_usb_read_receive_buf receive_data;

	mcrw_addr_debug(page);

	for (i=0; i<128; i++) /* receive data */
		send_data.receive_read_data[i] = 0x00;
	
	ret = usb_bulk_write(udev, 0x02, (char *)&send_data, sizeof(send_data), 1000);
	ret = usb_bulk_read(udev, 0x81, (char *)&receive_data, sizeof(receive_data), 1000);

	mcrw_debug(receive_data.data, sizeof(receive_data.data));
	
	/*if ((receive_data.header_chk[0] != 0x5a)&&(receive_data.header_chk[1] != 0x5d))
	{
		printf("Error invalid USB header returned!\n");
		return NULL;
	}*/

///*
	if ((receive_data.cmd_ack != 0x5c)&&(receive_data.start_data_flag != 0x5d))
	{
		printf("Error invalid MC header returned!\n");
		return NULL;
	}

	if ((receive_data.read_addr[0] != ((page>>8)&0xff)) && (receive_data.read_addr[1] != (page&0xff)))
	{
		printf("Error invalid address returned!\n");
		return NULL;
	}

	xor ^= ((page>>8)&0xff);
	xor ^= (page&0xff);
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
//*/
	memcpy(data_f, receive_data.data, 128);
	return data_f;
}

unsigned char *mc1rw_read_block(usb_dev_handle *udev, int block)
{	int i=0, j=0;
	static unsigned char data_b[8192], *data_f;

	for (i=0; i<64; i++)
	{
		data_f = mc1rw_read_page(udev, (block*64)+i);
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

int mc1rw_write_save2file(usb_dev_handle *udev, int start_block, int save_length, char* filename)
{
	int i=0;
	unsigned char *data = NULL;
	FILE *f = fopen(filename, "wb");


	for (i=0; i<save_length; i++)
	{
		data = mc1rw_read_block(udev, start_block+i);
		fwrite(data, 8192, 1, f);
		fflush(f);
	}

	fclose(f);

	return 0;
}

int mc1rw_write_mc2file(usb_dev_handle *udev, char *filename)
{
	int i=0;
	
	unsigned char *data = NULL;
	FILE *f = fopen(filename, "wb");

	for(i=0; i<0x400; i++)
	{
		data = mc1rw_read_page(udev, i);
		fwrite(data, 0x80, 1, f);
		fflush(f);
	}

	fclose(f);

	return 0;
}

int mc1rw_write_block(usb_dev_handle *udev, int block, char* data_b)
{
	int i=0, j=0, ret=0;
	unsigned char data_p[64][128];
	for (i=0; i<64; i++)
		for (j=0; j<128; j++)
			data_p[i][j] = data_b[(i*128)+j];

	for (i=0; i<64; i++)
	{
		ret = mc1rw_write_page(udev, (block*64)+i, data_p[i] );
		if (ret == -1)
		{
			return -1;
		}
		usleep(250000);
		//sleep(1);
	}
	return 0;
}

int mc1rw_write_page(usb_dev_handle *udev, int page, char* data_f)
{
	int ret=0, i=0;
	struct psx_usb_write_receive_buf receive_data;
	int xor = 0;
	
	mcrw_addr_debug(page);

	xor ^= (page>>8)&0xff;
	xor ^= page&0xff;
	for (i=0; i<PS1_PAGESIZE; i++)
		xor ^= data_f[i];
	
	/* populate data buffer */
	struct psx_usb_write_send_buf send_data = {
		.usb_ctrl = {0xaa, 0x42, sizeof(struct psx_usb_write_send_buf)-4, 0x00},
		.psx_cmd_ctrl = {0x81, 0x57},
		.receive_header_chk = {0x00, 0x00},
		.write_addr = {(page>>8)&0xff, page&0xff},
		//.write_data[128]
		//.write_xor
		.receive_end_mark = {0x00, 0x00},
		.receive_end_flag = 0x00
		};
	for (i=0; i<PS1_PAGESIZE; i++)
		send_data.write_data[i] = data_f[i];
	send_data.write_xor = (unsigned char)xor;
	mcrw_debug((char*)&send_data, sizeof(send_data));	
	
	ret = usb_bulk_write(udev, 0x02, (char*)&send_data, sizeof(send_data), 10000);
	ret = usb_bulk_read(udev, 0x81, (char*)&receive_data, sizeof(receive_data), 10000);

	mcrw_debug((char*)&receive_data, sizeof(receive_data));
	if(receive_data.header_chk[0] != 0x5a && receive_data.header_chk[1] != 0x5d)
		printf("Error invalid Header!\n");

	if (receive_data.end_mark[0] != 0x5c && receive_data.end_mark[1] != 0x5d)
		printf("Error invalid End Mark!\n");
	
	if (receive_data.end_data_flag != 0x47)
		printf("Error invalid End Data Flag!\n");

	return (int)((unsigned char)xor);
}

