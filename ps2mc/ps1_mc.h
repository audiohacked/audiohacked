#ifndef __PS1_MC_H
#define __PS1_MC_H

char *mc1rw_read_frame(usb_dev_handle *udev, int frame);
char *mc1rw_read_block(usb_dev_handle *udev, int block);
int mc1rw_write_frame(int frame, char *data_f);
int mc1rw_write_block(int block, char *data_b);

#endif /* __PS1_MC_H */
