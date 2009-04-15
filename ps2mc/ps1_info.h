#ifndef __PS1_INFO_H
#define __PS1_INFO_H

struct header_frame
{
	unsigned char id[2];
	unsigned char unused[125];
	unsigned char header_xor;
};

struct directory_frame
{
	unsigned char available_blocks;
	unsigned char reserved[3];
	unsigned char use[3];
	unsigned char link_order[2];
	unsigned char country_code[2];
	unsigned char product_code[10];
	unsigned char identifier[8];
	unsigned char unused[98];
	unsigned char xor_code;
};

struct header_frame read_ps1_mc_info(usb_dev_handle *udev);
struct directory_frame read_ps1_mc_block_info(usb_dev_handle *udev, int block);
int print_ps1_block_info(struct directory_frame data);

#endif /* __PS1_INFO_H */
