#include <usb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_BULK_BUF 64
#define MY_HAVE_USB_CONFIG 1
#define MY_HAVE_ALTIFACE 1

enum
{
	CMD_OPEN_DEV,
	CMD_CLOSE_DEV,
	CMD_SET_CONF,
	CMD_GET_CONF,
	CMD_CHECK,
	CMD_MC1_READ,
	CMD_MC1_WRITE,
	CMD_MC2_READ,
	CMD_MC2_WRITE,
	CMD_MC2_ERASE
};
struct usb_bulk_buf {
	uint8_t cmd_len;
	uint8_t cmd[MAX_BULK_BUF];
} mcrw_cmd[] = {
	{4, {0x81, 0x11, 0x00, 0x00}}, /* mcOpenDevice */
	{4, {0xaa, 0x42, 0x04, 0x00}}, /* mcCloseDevice */
	{1, {0x00}}, /* mcSetConfig */
	{1, {0x00}}, /* mcGetConfig */
	{1, {0x00}}, /* mcCheck */
	{1, {0x00}}, /* mcReadSector */
	{1, {0x00}}, /* mcWriteSector */
	{1, {0x00}}, /* mc2ReadPage */
	{1, {0x00}}, /* mc2WritePage */
	{1, {0x00}}, /* mc2EraseBlock */
	 
	{7, {0xaa, 0x42, 0x03, 0x00, 0x81, 0x52, 0x00}},
	{8, {0xaa, 0x42, 0x04, 0x00, 0x81, 0x11, 0x00, 0x00}},
	{8, {0xaa, 0x42, 0x05, 0x00, 0x81, 0xf3, 0x51, 0x00}}
};

uint8_t mc2rw_cmd[][8] = {
	{0xaa, 0x42, 0x04, 0x00, 0x81, 0x11, 0x00, 0x00},
	{0xaa, 0x42, 0x05, 0x00, 0x81, 0xf3, 0x51, 0x00},
};

uint8_t mc2rw_response[][MAX_BULK_BUF] = {
	{0x55, 0xaf},
	{0x55, 0x5a, 0x05, 0x00, 0xff, 0xff, 0xff, 0x2b},
};

struct usb_bulk_buf bulk_in_buf; // IN to the host; while OUT of the host
uint8_t interrupt_in_buf;
struct usb_bus *bus;
struct usb_device *dev;

int print_bulk_buffer(int returned_byte_count)
{	unsigned int i=0;

	//if (returned_byte_count < 0) return -1;
	bulk_in_buf.cmd_len = returned_byte_count;
	printf("Bytes read: %d, bytes: ", returned_byte_count);
	for (i=0; i<bulk_in_buf.cmd_len; i++)
		printf("%02x ", bulk_in_buf.cmd[i]);
	printf("\n");

	return 0;
}

int setup_mcrw(usb_dev_handle *udev)
{
	int ret;
	ret = usb_claim_interface(udev, 0);
	if (ret)
	{
		perror("usb_claim_interface");
	}
	
	#if MY_HAVE_USB_CONFIG
	ret = usb_set_configuration(udev, 1);
	if (ret)
	{
		perror("usb_set_configuration");
	}
	#endif

	#if MY_HAVE_ALTIFACE
	ret = usb_set_altinterface(udev, 0);
	if (ret)
	{
		perror("usb_set_altinterface");
	}
	#endif

	return 0;
}

int cleanup_mcrw(usb_dev_handle *udev)
{
	int ret;
	
	ret = usb_release_interface(udev, 0);
	if (ret)
	{
		perror("usb_release_interface");
	}

	return 0;
}

int mcrw_send(usb_dev_handle *udev, int usb_cmd)
{
	int ret_bytes=0;
	//uint8_t *bulk_in_buf;
	
	//bulk_in_buf = malloc(sizeof(uint8_t)*MAX_BULK_BUF);
	
	ret_bytes = usb_bulk_write(udev, 0x02, mcrw_cmd[usb_cmd].cmd, mcrw_cmd[usb_cmd].cmd_len, 1000);
	if (ret_bytes<0)
	{
		perror("usb_bulk_write");
	}
	else
	{
		printf("Bytes written: %d\n", ret_bytes); 
	}

	ret_bytes = usb_bulk_read(udev, 0x81, bulk_in_buf.cmd, sizeof(bulk_in_buf.cmd), 1000);
	if (ret_bytes<0)
	{
		perror("usb_bulk_read");
	}
	else
	{
		print_bulk_buffer(ret_bytes);
	}

	return 0;
}

int main(void)
{
	usb_dev_handle *udev;
	char string[256];
	int ret;

	usb_init();
	usb_find_busses();
	usb_find_devices();

	for (bus = usb_busses; bus; bus = bus->next)
	{
		for (dev = bus->devices; dev; dev = dev->next)
		{
			if ((dev->descriptor.idVendor == 0x054c)&&(dev->descriptor.idProduct == 0x02ea)) {
				printf("Found PS2-to-USB Memory Card Adaptor at bus-dir: %s, bus-file: %s, VendorId: %04X, ProductId: %04X\n",
					bus->dirname, dev->filename, dev->descriptor.idVendor, dev->descriptor.idProduct);
				udev = usb_open(dev);
				break;
			}
		}
	}

	if (udev)
	{
		setup_mcrw(udev);

		ret = mcrw_send(udev, CMD_OPEN_DEV);
		if (ret)
		{
			perror("MCRW_start");
		}
		//mcrw_send(udev, CMD_TWO);
		mcrw_send(udev, CMD_CLOSE_DEV);
		
		cleanup_mcrw(udev);
		usb_close(udev);
	}
	printf("DONE!\n");
	return 0;
}

