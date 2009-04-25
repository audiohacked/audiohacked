#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "psx.h"
#include "ps1.h"
#include "ps2.h"

int write_cmd(usb_dev_handle *udev, char *cmd, int page);

/*
 * unsigned char mycmd[][] = {
	{0x81
	{0xaa, 0x42, 0x04, 0x00, 0x81, 0x11,
*/
int main(void)
{
	usb_dev_handle *udev = NULL;
	char string[256];
	int ret, i;

	udev = find_mcrw();

	if (udev)
	{
		init_mcrw(udev);
		/* open device for transfer */
		open_mcrw(udev);

		/* send/receive data */
		//unsigned char mycmd1[] = {0x81, 0x11, 0x00, 0x00};
		//write_cmd(udev, mycmd1, 0);
		
		//unsigned char mycmd2[] = {0xaa, 0x42, 0x04, 0x00, 0x81, 0x11, 0x00, 0x00};
		//write_cmd(udev, mycmd2, 0);
		
		//unsigned char mycmd3[] = {0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		//write_cmd(udev, mycmd3, 0);
		
		//unsigned char mycmd4[] = {0xaa, 0x42, 0x0d, 0x00, 0x81, 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		//write_cmd(udev, mycmd4, 0);
		
		/*
		for (i=0; i<15; i++)
		{
			struct directory_page *ps1 = read_ps1_mc_block_info(udev, i+1);
			print_ps1_block_info(*ps1, i+1);
		}
		*/
		//mc1rw_write_mc2file(udev, "save_ps1.bin");
		//mc1rw_read_page(udev, 0);

		/* when we're done close device */
		close_mcrw(udev);
		cleanup_mcrw(udev);
		usb_close(udev);
	}
	printf("DONE!\n");
	return 0;
}

int write_cmd(usb_dev_handle *udev, char *cmd, int page)
{
	int ret=0, i=0;

	unsigned char receive_data[64];
        ret = usb_bulk_write(udev, 0x02, cmd, sizeof(cmd), 10000);
	ret = usb_bulk_read(udev, 0x81, receive_data, sizeof(receive_data), 10000);

	printf("DEBUG: ");
	for (i=0; i<ret; i++)
	{
		printf("%02x ", receive_data[i]);
	}
	printf("\n");

	return 0;
}


