#ifndef __PS2_MC_H
#define __PS2_MC_H

struct timeofday
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t day;
	uint8_t month;
	uint32_t year;
} __attribute__((packed));

struct superblock 
{
	char magic[28];
	char version[12];
	uint16_t page_len;
	uint16_t pages_per_cluster;
	uint16_t pages_per_block;
	uint16_t unused;
	uint32_t clusters_per_card;
	uint32_t alloc_offset;
	uint32_t alloc_end;
	uint32_t rootdir_cluster;
	uint32_t backup_block1;
	uint32_t backup_block2;
	uint32_t ifc_list[32];
	uint32_t bad_block_list[32];
	uint8_t card_type;
	uint8_t card_flags;
} __attribute__((packed));

struct direntry
{
	uint16_t mode;
	uint32_t length;
	struct timeofday created;
	uint32_t cluster;
	uint32_t dir_entry;
	struct timeofday modified;
	uint32_t attr;
	char name[32];
} __attribute__((packed));

enum card_flags
{
	CF_USE_ECC = 0x01,
	CF_BAD_BLOCK = 0x08,
	CF_ERASE_ZEROES = 0x10,
};

enum direntry_mode_flags
{
	DF_READ = 0x0001,
	DF_WRITE = 0x0002,
	DF_EXECUTE = 0x0004,
	DF_PROTECTED = 0x0008,
	DF_FILE = 0x0010,
	DF_DIRECTORY = 0x0020,
	CREAT = 0x0040,
	COPIED = 0x0080,
	O_CREAT = 0x0200,
	DF_0400 = 0x0400,
	DF_POCKETSTN = 0x0800,
	DF_PSX = 0x1000,
	DF_HIDDEN = 0x2000,
	DF_EXISTS = 0x8000,
};

unsigned char *mc2rw_read_page(usb_dev_handle *udev, int page);
int mc2rw_xor_addr(unsigned char *array, int index, int data);
int mc2rw_xor_data(unsigned char *array, int index, unsigned char *data, int size);
int mc2rw_write(void);
int mc2rw_erase(void);

#endif /* __PS2_MC_H */

