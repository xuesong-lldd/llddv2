#!/bin/bash

while [ 0 ] ; do
    mount /dev/sda10 /mnt/10 &
    mount /dev/sda11 /mnt/11 &
    mount /dev/sda12 /mnt/12 &
    mount /dev/sda13 /mnt/13 &

    umount /mnt/10 &
    umount /mnt/11 &
    umount /mnt/12 &
    umount /mnt/13 &
    sleep 1
done
