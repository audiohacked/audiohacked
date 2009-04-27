#include <usb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "psx.h"
#include "ps2.h"

//#ifndef PS2_PAGESIZE
#define PS2_PAGESIZE 512
#define PS2_FRAMESIZE 128
#define USB_FRAMESIZE 144
//#endif
int nullify_array(char *array)
{
	int i=0;
	for (i=0; i<sizeof(array); i++)
	{
		array[i] = 0x00;
	}
	return 0;
}

int mc2rw_read_set_sector(usb_dev_handle *udev, int page)
{
	int xor=0, wret=0, rret=0, i=0, j=0;
	unsigned char temp_data[USB_FRAMESIZE],
	start_read_cmd[13] = 
		{0xaa, 0x42, 0x09, 0x00, 0x81, 0x23};
	
	nullify_array(temp_data);

	for (xor=0, i=0, j=0; i<25, j<4; i=i+8,j++)
	{
		xor ^= (page>>i)&0xFF;
		start_read_cmd[6+j] = (page>>i)&0xFF;
	}
	start_read_cmd[10] = xor;
	start_read_cmd[11] = 0x00;
	start_read_cmd[12] = 0x00;
	
	mcrw_debug(start_read_cmd, sizeof(start_read_cmd));

	/* start read page */
	//printf("Starting Read Page\n");
	wret = usb_bulk_write(udev, 0x02, start_read_cmd, sizeof(start_read_cmd), 1000);
	rret = usb_bulk_read(udev, 0x81, temp_data, sizeof(temp_data), 1000);
	mcrw_debug(temp_data, USB_FRAMESIZE);
	//if (wret != sizeof(start_read_cmd)) printf("Error!\n");
	//if (temp_data[0] == 0x55 && temp_data[1] == 0xaf) printf("Valid Set Sector Return!\n");
	return 0;
}

int mc2rw_read_ecc(usb_dev_handle *udev)
{
	int wret=0, rret=0;
	unsigned char temp_data[USB_FRAMESIZE],
		ecc_read_cmd[148] = {0xaa, 0x42, 0x90, 0x00, 0x81, 0x43, 0x10, 0x00, 0x00};
	/* ecc read */
	//printf("ECC Read Data\n");
	wret = usb_bulk_write(udev, 0x02, ecc_read_cmd, sizeof(ecc_read_cmd), 1000);
	rret = usb_bulk_read(udev, 0x81, temp_data, sizeof(temp_data), 1000);
	mcrw_debug(temp_data, rret);
	
	return 0;
}

int mc2rw_read_commit(usb_dev_handle *udev)
{
	int wret=0, rret=0;
	unsigned char temp_data[USB_FRAMESIZE],
		end_read_cmd[] = {0xaa, 0x42, 0x04, 0x00, 0x81, 0x81, 0x00, 0x00};
	/* end read page */
	//printf("End Read Page\n");
	wret = usb_bulk_write(udev, 0x02, end_read_cmd, sizeof(end_read_cmd), 1000);
	rret = usb_bulk_read(udev, 0x81, temp_data, sizeof(temp_data), 1000);
	mcrw_debug(temp_data, rret);
	//if (wret != sizeof(end_read_cmd)) printf("Error! ret: %d, size: %d\n", ret, sizeof(end_read_cmd));
	return 0;
}

unsigned char *mc2rw_read_page(usb_dev_handle *udev, int page)
{
	int i=0, p=0, wret=0, rret=0;
	int prev_size;
	static unsigned char data_p[PS2_PAGESIZE], temp_data[USB_FRAMESIZE];
	struct psx_usb_read_receive_buf receive_data;

	mcrw_addr_debug(page);

	mc2rw_read_set_sector(udev, page);

	//printf("Reading Data\n");
	/* read data */
	for (p=0; p<4; p++)
	{	
		unsigned char send_data[148] = {0xaa, 0x42, 0x90, 0x00, 0x81, 0x43, 0x80, 0x00, 0x00};
		wret = usb_bulk_write(udev, 0x02, send_data, sizeof(send_data), 1000);
		//if (ret != sizeof(send_data)) printf("Error!\n");
		rret = usb_bulk_read(udev, 0x81, temp_data, sizeof(temp_data), 1000);
		
		//printf("segment: &(data_p[%d]) = 0x%X\n", USB_FRAMESIZE*p, &(data_p[USB_FRAMESIZE*p]));
		memcpy(&(data_p[rret*p]), temp_data, rret);
	}
	mcrw_debug(data_p, sizeof(data_p));

	mc2rw_read_ecc(udev);
	mc2rw_read_commit(udev);

	return data_p;
}

