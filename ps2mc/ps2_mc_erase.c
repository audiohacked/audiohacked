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
//#endif

int mc2rw_erase_set_sector(usb_dev_handle *udev, int page)
{


}

int mc2rw_erase_ecc(usb_dev_handle *udev)
{

}

int mc2rw_erase_commit(usb_dev_handle *udev)
{


}

unsigned char *mc2rw_erase_page(usb_dev_handle *udev, int page)
{
	int i=0, p=0, ret=0;
	static unsigned char data_p[PS2_PAGESIZE], temp_data[1024];
	struct psx_usb_read_receive_buf receive_data;

	int xor = 0;
	xor ^= (page>>0)&0xFF;
	xor ^= (page>>8)&0xFF;
	xor ^= (page>>16)&0xFF;
	xor ^= (page>>24)&0xFF;


	unsigned char start_erase_cmd[] = {0xaa, 0x42, 0x09, 0x00, 0x81, 0x23, page&0xFF, (page>>8)&0xFF, (page>>16)&0xFF, (page>>24)&0xFF, xor, 0x00, 0x00};
	unsigned char ecc_erase_cmd[148] = {0xaa, 0x42, 0x90, 0x00, 0x81, 0x43, 0x10, 0x00, 0x00};
	unsigned char end_erase_cmd[] = {0xaa, 0x42, 0x04, 0x00, 0x81, 0x81, 0x00, 0x00};

	mcrw_addr_debug(page);


	//mc2rw_reset_auth(udev);
	//mc2rw_erase_spec(udev);


	/* start erase page */
	printf("Starting Read Page\n");
	ret = usb_bulk_write(udev, 0x02, start_erase_cmd, sizeof(start_erase_cmd), 1000);
	if (ret != sizeof(start_erase_cmd)) printf("Error!\n");
	ret = usb_bulk_read(udev, 0x81, temp_data, sizeof(temp_data), 1000);
	mcrw_debug(temp_data, ret);

	printf("Reading Data\n");
	/* read data */
	for (p=0; p<(PS2_PAGESIZE/PS2_FRAMESIZE); p++)
	{	
		unsigned char send_data[148] = {0xaa, 0x42, 0x90, 0x00, 0x81, 0x43, 0x80, 0x00, 0x00};
		ret = usb_bulk_write(udev, 0x02, send_data, sizeof(send_data), 1000);
		if (ret != sizeof(send_data)) printf("Error!\n");
		ret = usb_bulk_read(udev, 0x81, temp_data, sizeof(temp_data), 1000);
		mcrw_debug(temp_data, ret);
		
		//temp_data[ret+1] = '\0';
		//strncat(data_p, temp_data, ret);
	}
	/* ecc read */
	printf("ECC Read Data\n");
	ret = usb_bulk_write(udev, 0x02, ecc_erase_cmd, sizeof(end_erase_cmd), 1000);
	ret = usb_bulk_read(udev, 0x81, temp_data, sizeof(temp_data), 1000);
	mcrw_debug(temp_data, ret);
	
	/* end read page */
	printf("End Read Page\n");
	ret = usb_bulk_write(udev, 0x02, end_erase_cmd, sizeof(end_erase_cmd), 1000);
	if (ret != sizeof(end_erase_cmd)) printf("Error! ret: %d, size: %d\n", ret, sizeof(end_erase_cmd));
	ret = usb_bulk_read(udev, 0x81, temp_data, sizeof(temp_data), 1000);
	mcrw_debug(temp_data, ret);

	return data_p;
}

