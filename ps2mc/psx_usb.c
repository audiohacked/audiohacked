#include <usb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "usb_adaptor.h"
#include "psx_usb.h"

#define MY_HAVE_USB_CONFIG 0
#define MY_HAVE_ALTIFACE 0

struct usb_bulk_buf mcrw_cmd[] = {
	{4, {0x81, 0x11, 0x00, 0x00}}, /* mcOpenDevice */
	{4, {0xaa, 0x42, 0x04, 0x00}}, /* mcCloseDevice */
	{0, {0x00}}, /* mcSetConfig */
	{0, {0x00}}, /* mcGetConfig */
	{0, {0x00}}, /* mcCheck */
	{4, {0x81, 0x52, 0x00, 0x00}}, /* mcReadSector */
	{4, {0x81, 0x57, 0x00, 0x00}}, /* mcWriteSector */
	{0, {0x00}}, /* mc2ReadPage */
	{0, {0x00}}, /* mc2WritePage */
	{0, {0x00}}, /* mc2EraseBlock */
};

uint8_t mc2rw_response[] = {
	0x55, 0xaf, /* header */
	0x5c, 0x5d, 0x47, /* readFrame: ack, start_flag, end_flag */
	0x5c, 0x5d, /* writeFrame end mark */
};


int print_bulk_buffer(struct usb_bulk_buf *buf, int returned_byte_count)
{
	unsigned int i=0;

	//if (returned_byte_count <= 0) return -1;
	//if (buf.cmd_len != returned_byte_count)
	//{
	//	printf("cmd_len doesn't match returned byte count; invalid read from device.\n");
	//	return -1;
	//}
	printf("Bytes read: %d, bytes: ", returned_byte_count);
	for (i=0; i<(buf->length); i++)
		printf("%02x ", buf->data[i]);
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

	if (mcrw_cmd[usb_cmd].length == 0) return -1;

	ret_bytes = usb_bulk_write(udev, 0x02, mcrw_cmd[usb_cmd].data, mcrw_cmd[usb_cmd].length, 1000);
	if (ret_bytes<0)
	{
		perror("usb_bulk_write");
	}
	else
	{
		printf("Bytes written: %d\n", ret_bytes); 
	}

	return 0;
}

struct usb_bulk_buf mcrw_receive(usb_dev_handle *udev)
{
	int ret_bytes=0;
	struct usb_bulk_buf tmp; // IN to the host; OUT of the host

	ret_bytes = usb_bulk_read(udev, 0x81, tmp.data, sizeof(tmp.data), 1000);
	if (ret_bytes<0)
	{
		perror("usb_bulk_read");
	}
	else
	{
		print_bulk_buffer(&tmp, ret_bytes);
	}

	return tmp;
}
