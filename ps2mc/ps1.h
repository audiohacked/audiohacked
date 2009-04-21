#ifndef __PS1_H
#define __PS1_H

#include <stdint.h>

struct header_frame
{
	unsigned char id[2];
	unsigned char unused[125];
	unsigned char header_xor;
} __attribute__((packed));

struct directory_frame
{
	unsigned char available_blocks;
	unsigned char reserved[3];
	uint32_t use;
	unsigned short link_order;
	char country_code[2];
	char product_code[10];
	char identifier[8];
	unsigned char unused[96];
	unsigned char xor_code;
} __attribute__((packed));

struct header_frame *read_ps1_mc_info(usb_dev_handle *udev);
struct directory_frame *read_ps1_mc_block_info(usb_dev_handle *udev, int block);
int print_ps1_block_info(struct directory_frame data, int info_block_num);
unsigned char *mc1rw_read_frame(usb_dev_handle *udev, int frame);
unsigned char *mc1rw_read_block(usb_dev_handle *udev, int block);
int mc1rw_write_frame(int frame, char *data_f);
int mc1rw_write_block(int block, char *data_b);

#endif /* __PS1_H */
