#! /bin/sh

insmod fpga_led_driver.ko
mknod /dev/fpga_led c 260 0

insmod fpga_dot_driver.ko
mknod /dev/fpga_dot c 262 0

insmod fpga_push_switch_driver.ko
mknod /dev/fpga_push_switch c 265 0
