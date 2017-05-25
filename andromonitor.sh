#!/bin/bash
echo "start custom system.img flashing ..."
#./simg2img system.img system.img.raw
sudo mount -t ext4 -o loop,rw andromonitor/system.img.raw andromonitor/sys/
sudo cp out/target/product/hammerhead/system/lib/libdvm.so andromonitor/sys/lib/libdvm.so
sudo chmod 644 andromonitor/sys/lib/libdvm.so
sudo chown root:root andromonitor/sys/lib/libdvm.so
sudo ./andromonitor/make_ext4fs -s -l 1024M -a system andromonitor/new/system.img andromonitor/sys/
sudo umount andromonitor/sys
adb reboot bootloader
fastboot flash system andromonitor/new/system.img
fastboot reboot
