#!/usr/bin/bash
dd if=/dev/zero of=${imagename} bs=512 count=${size}
losetup /dev/loop9 ${imagename}
parted /dev/loop9 mklabel msdos
parted /dev/loop9 mkpart vfat
parted /dev/loop9 mkpart linux
losetup -d /dev/loop9
losetup -P /dev/loop9 ${imagename}
mkfs.vfat /dev/loop9p1
mkfs.ext4 /dev/loop9p2
