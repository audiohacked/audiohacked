#include <usb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "usb_adaptor.h"
#include "psx_usb.h"
#include "ps1_mc.h"

unsigned int read_check_header[] = {
	0x5a, 0x5d,
	0x5c, 0x5d,
	0x47
};

char *mc1rw_read_frame(usb_dev_handle *udev, int frame)
{
	int i, xor=0, ret;
	struct usb_bulk_buf temp;
	unsigned char cmd_read_addr[2] = {(frame >> 8) & 0xff, frame & 0xff};
	static unsigned char send_data[144], data_f[128];

	printf("Frame Address: %02x %02x\n", cmd_read_addr[0], cmd_read_addr[1]);
	for (i=0; i<8; i++) /* send header */
		send_data[i] = mcrw_cmd[CMD_MC1_READ].data[i];

	for (; i<10; i++) /* send address */
		send_data[i] = cmd_read_addr[i];

	for (; i<11; i++) /* receive command ack */
		send_data[i] = 0x00;

	for (; i<12; i++) /* receive start of data flag */
		send_data[i] = 0x00;

	for (; i<14; i++) /* receive read address */
		send_data[i] = 0x00;
	
	for (; i<142; i++) /* receive data */
		send_data[i] = 0x00;
	
	for (; i<143; i++) /* receive xor */
		send_data[i] = 0x00;

	for (; i<144; i++) /* receive end of data flag */
		send_data[i] = 0x00;

	ret = usb_bulk_write(udev, 0x02, send_data, sizeof(send_data), 1000);
	ret = usb_bulk_read(udev, 0x81, temp.data, sizeof(temp.data), 1000);
	
	
	for (i=0; i<128; i++)
	{
		data_f[i] = temp.data[14+i];
	}

#ifdef __MCRW_DEBUG__
	printf("DEBUG: \n\t");
	for (i=0; i<sizeof(temp.data); i++)
	{
		printf("%02x ", temp.data[i]);
	}
	printf("\n");
#endif
	/*if ((temp.data[6] != 0x5a)&&(temp.data[7] != 0x5d))
	{
		printf("Error invalid USB header returned!\n");
		return NULL;
	}*/
	if ((temp.data[10] != 0x5c)&&(temp.data[11] != 0x5d))
	{
		printf("Error invalid MC header returned!\n");
		return NULL;
	}
	if ((temp.data[12] != cmd_read_addr[0])&&(temp.data[13] != cmd_read_addr[1]))
	{
		printf("Error invalid address returned!\n");
		return NULL;
	}

	xor ^= cmd_read_addr[0];
	xor ^= cmd_read_addr[1];
	for(i=0; i<128; i++)
	{
		xor ^= data_f[i];
	}

	if (xor != temp.data[142])
	{
		printf("Error invalid Checksum! Gen: %02x, Ret: %02x\n", xor, temp.data[143]);
		return NULL;
	}
	if (temp.data[143] != 0x47)
	{
		printf("Error invalid end flag returned!\n");
		return NULL;
	}

	return data_f;
}

int mc1rw_write_frame(int frame, char* data_f)
{
	return 0;
}

char *mc1rw_read_block(usb_dev_handle *udev, int block)
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

