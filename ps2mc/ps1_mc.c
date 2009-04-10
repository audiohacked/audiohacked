#include <usb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "usb_adaptor.h"
#include "psx_usb.h"
#include "ps1_mc.h"

char *mc1rw_read_frame(usb_dev_handle *udev, int frame)
{
	int i, xor, ret;
	struct usb_bulk_buf temp;
	unsigned char cmd_read_addr[2] = {(frame >> 8) & 0xff, frame & 0xff};
	static unsigned char send_data[140], data_f[128];

	for (i=0; i<4; i++) /* send header */
		send_data[i] = mcrw_cmd[CMD_MC1_READ].data[i];

	for (; i<6; i++) /* send address */
		send_data[i] = cmd_read_addr[i];

	for (; i<7; i++) /* receive command ack */
		send_data[i] = 0x00;

	for (; i<8; i++) /* receive start of data flag */
		send_data[i] = 0x00;

	for (; i<10; i++) /* receive read address */
		send_data[i] = 0x00;
	
	for (; i<138; i++) /* receive data */
		send_data[i] = 0x00;
	
	for (; i<139; i++) /* receive xor */
		send_data[i] = 0x00;

	for (; i<140; i++) /* receive end of data flag */
		send_data[i] = 0x00;

	ret = usb_bulk_write(udev, 0x02, send_data, sizeof(send_data), 1000);
	ret = usb_bulk_read(udev, 0x81, temp.data, temp.length, 1000); 
	print_bulk_buffer(&temp, ret);

	return data_f;
}

int mc1rw_write_frame(int frame, char* data_f)
{
	return 0;
}

char *mc1rw_read_block(usb_dev_handle *udev, int block)
{	int i, j;
	static unsigned char data_b[8192], *data_f;
	for (i=0; i<64; i++)
	{
		data_f = mc1rw_read_frame(udev, (block*64)+i);
		if (data_f != NULL)
		{
			for (j=0; j<128; j++)
				data_b[(i*128)+j] = data_f[j];
		}
		else return NULL;
	}
	return data_b;
}

int mc1rw_write_block(int block, char* data_b)
{
	return 0;
}

