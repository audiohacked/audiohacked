#!/bin/bash

declare -x device=${1:-"/dev/sdb"}
declare -x mbr="/usr/lib/syslinux/bios/gptmbr.bin"
declare -x iso="target.iso"

#### Create the Partition Table
parted ${device} 'mklabel gpt'
parted ${device} 'mkpart ESP fat32 1MiB 551MiB name 1 ESP'
parted ${device} 'set 1 boot on'

parted ${device} 'mkpart BIOS ext2 551MiB 553MiB name 2 BIOS'
parted ${device} 'set 2 bios_grub on'

parted ${device} 'mkpart ISO ext4 553MiB 9769MiB name 3 ISO'
parted ${device} 'set 3 legacy_boot on'

parted ${device} 'mkpart OEMDRV ext4 9769MiB 100% name 4 OEMDRV'

#### Format the Partitions
mkfs.vfat -F 32 ${device}1
mkfs.ext4 -L ISO ${device}3
mkfs.ext4 -L OEMDRV ${device}4

#### Install Grub2
mount ${device}1 /mnt
mkdir /mnt/boot
grub-install --target=i386-pc --recheck --boot-directory=/mnt/boot ${device}
grub-install --target=x86_64-efi --removable --boot-directory=/mnt/boot --efi-directory=/mnt
umount /mnt

#dd conv=notrunc bs=440 count=1 if=${mbr} of=${device}
