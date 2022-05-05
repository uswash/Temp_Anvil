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
  echo "zerombr"                                                                   > /tmp/part-include
  echo "clearpart       --all      --initlabel"                                      >> /tmp/part-include
  echo "part /boot      --fstype ext4     --size=512       --ondisk=$DRIVE1"            >> /tmp/part-include
  echo "part pv.0                         --size=1 --grow  --ondisk=$DRIVE1"            >> /tmp/part-include
  echo "volgroup vg.0 pv.0"                                                             >> /tmp/part-include
  echo "logvol /        --fstype ext4  --name=lv_root   --vgname=vg.0   --size=51200"  >> /tmp/part-include
  echo "logvol swap     --fstype swap  --name=lv_swap   --vgname=vg.0   --size=2048" >> /tmp/part-include
  echo "logvol /var     --fstype ext4  --name=lv_var    --vgname=vg.0   --size=8192"
  echo "logvol /home    --fstype ext4  --name=lv_home   --vgname=vg.0   --size=10240" 
  echo "logvol /var/log  --fstype ext4  --name=lv_var_log  --vgname=vg.0 --size=8192"
  echo "logvol /var/log/audit  --fstype ext4  --name=lv_var_log_audit  --vgname=vg.0  --size=8192"
  echo "logvol /tmp      --fstype ext4   -name=lv_tmp  -vgname=vg.0  --size=4096"
  echo "logvol /opt     --fstype ext4   -name=lv_opt   --vgname=vg.0  --size=10240 --grow" 