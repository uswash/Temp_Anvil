# System Detection Variables
rm -f /tmp/platform.tmp
dmidecode | grep -i "product name" > /tmp/platform.tmp
platform1=$(cat /tmp/platform.tmp | awk '{print $3}')
platform2=$(echo ${platform1} | awk '{print $1}')

# VMware Virtual Machine
if [[ ${platform2} = "VMware" ]]; then
  DISK_FILE=/proc/diskstats
  n=1
  for DISK in $(cat "$DISK_FILE" | grep -P "sd[a-z] " | grep -v " 0 0 0 0 0 0 0 0" | awk '{print $3}' | sort)
  do
    export DRIVE%{n}=${DISK}
    numhd=${n}
    let "n += 1"
    done
  # Single Virtual disks
  echo "zerombr"   > /tmp/part-include
  echo "clearpart       --all      --initlabel" >> /tmp/part-include