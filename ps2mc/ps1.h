#ifndef __PS1_H
#define __PS1_H

#include <stdint.h>

struct header_page
{
	unsigned char id[2];
	unsigned char unused[125];
	unsigned char header_xor;
} __attribute__((packed));

struct directory_page
{
	unsigned char available_blocks;
	unsigned char reserved[3];
	uint32_t use;
	unsigned short link_order;
	char country_code[2];
	char product_code[10];
	char identifier[8];
	unsigned char unused[97];
	unsigned char xor_code;
} __attribute__((packed));

struct header_page *read_ps1_mc_info(usb_dev_handle *udev);
struct directory_page *read_ps1_mc_block_info(usb_dev_handle *udev, int block);
int print_ps1_block_info(struct directory_page data, int info_block_num);

unsigned char *mc1rw_read_page(usb_dev_handle *udev, int page);
unsigned char *mc1rw_read_block(usb_dev_handle *udev, int block);

int mc1rw_write_page(usb_dev_handle *udev, int page, char *data_f);
int mc1rw_write_block(usb_dev_handle *udev, int block, char *data_b);

int mc1rw_write_save2file(usb_dev_handle *udev, int start_block, int save_length, char *filename);
int mc1rw_write_mc2file(usb_dev_handle *udev, char *filename);

#endif /* __PS1_H */
