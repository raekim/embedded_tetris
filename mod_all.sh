#! /bin/sh
ko_name=("fpga_led_driver.ko" "fpga_dot_driver.ko" \
	"fpga_push_switch_driver.ko")
ko_num=(260 262 265)

ko_len=${#ko_name[@]}

for (( i=0; i < ${ko_len}; i++ ));
do
	file_name=${ko_name[$i]%_driver.ko}
	#file_name=$(echo ${ko_name[$i]}| cut -d'_driver.ko' -f 1)
	echo insmod ${ko_name[$i]}
	echo mknod  /dev/${file_name} c ${ko_num[$i]} 0
done
