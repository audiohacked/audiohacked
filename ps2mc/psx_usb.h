#ifndef __PSX_USB_H
#define __PSX_USB_H
//extern struct usb_bulk_buf mcrw_cmd[];
//extern uint8_t mc2rw_response[];

int print_bulk_buffer(struct usb_bulk_buf *buf, int returned_byte_count);
int setup_mcrw(usb_dev_handle *udev);
int cleanup_mcrw(usb_dev_handle *udev);
int mcrw_send(usb_dev_handle *udev, int usb_cmd);
struct usb_bulk_buf mcrw_receive(usb_dev_handle *udev);

#endif /* __PSX_USB_H */
