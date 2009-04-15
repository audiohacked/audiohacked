#ifndef __USB_ADAPTOR_H
#define __USB_ADAPTOR_H

#define MAX_BULK_BUF 144

enum
{
	CMD_OPEN_DEV = 0,
	CMD_CLOSE_DEV,
	CMD_SET_CONF,
	CMD_GET_CONF,
	CMD_CHECK,
	CMD_MC1_READ,
	CMD_MC1_WRITE,
	CMD_MC2_READ,
	CMD_MC2_WRITE,
	CMD_MC2_ERASE,
	CHK_HDR1 = 0,
	CHK_HDR2,
	CHK_ACK,
	CHK_SFL,
	CHK_EFL,
	CHK_EMK1,
	CHK_EMK2,
};

struct usb_bulk_buf
{
	unsigned char length;
	unsigned char data[MAX_BULK_BUF];
};

#endif /* __USB_ADAPTOR_H */
