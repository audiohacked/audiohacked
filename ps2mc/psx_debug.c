#include <stdio.h>

int mcrw_debug(unsigned char *data, int length)
{
#ifdef __MCRW_DEBUG__
	int i=0;
	printf("DEBUG: ");
	for (i=0; i<length; i++)
	{
		printf("%02x ", data[i]);
	}
	printf("\n");
#endif
	return 0;
}

int mcrw_addr_debug(int page)
{
#ifdef __MCRW_DEBUG__
 	printf("Page Address: %02x %02x\n", (page >> 8) & 0xff, page & 0xff);
#endif
	return 0;
}

