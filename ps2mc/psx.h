#ifndef __PSX_USB_H
#define __PSX_USB_H

int init_mcrw(usb_dev_handle *udev);
int cleanup_mcrw(usb_dev_handle *udev);
int open_mcrw(usb_dev_handle *udev);
int close_mcrw(usb_dev_handle *udev);

struct psx_usb_read_send_buf
{
	unsigned char usb_ctrl[4];
	unsigned char psx_cmd_ctrl[2];
	unsigned char receive_header_chk[2];
	unsigned char read_addr[2];
	unsigned char receive_cmd_ack;
	unsigned char receive_start_flag;
	unsigned char receive_read_addr[2];
	unsigned char receive_read_data[128];
	unsigned char receive_xor;
	unsigned char receive_end_flag;
};

struct psx_usb_read_receive_buf
{
	unsigned char usb_ctrl[4];
	unsigned char unused1[2];
	unsigned char header_chk[2];
	unsigned char unused2[2];
	unsigned char cmd_ack;
	unsigned char start_data_flag;
	unsigned char read_addr[2];
	unsigned char data[128];
	unsigned char data_xor;
	unsigned char end_data_flag;
};

struct psx_usb_write_send_buf
{
	unsigned char usb_ctrl[4];
	unsigned char psx_cmd_ctrl[2];
	unsigned char receive_header_chk[2];
	unsigned char write_addr[2];
	unsigned char write_data[128];
	unsigned char write_xor;
	unsigned char receive_end_mark[2];
	unsigned char receive_end_flag;
};

struct psx_usb_write_receive_buf
{
	unsigned char usb_ctrl[4];
	unsigned char unused1[2];
	unsigned char header_chk[2];
	unsigned char unused2;
	unsigned char write_addr[2];
	unsigned char write_data[128];
	unsigned char end_mark[2];
	unsigned char end_data_flag;
};

#endif /* __PSX_USB_H */

