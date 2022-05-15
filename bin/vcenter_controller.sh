#!/bin/bash

# Get Session Token
curl -k -i -u Administrator@titan.local:Tit@nnet138572 -X POST -c cookie-jar.txt https://192.168.1.238/rest/com/vmware/cis/session

# Set Variables 
now=$(date +"%Y-%m-%d")
sessionId=$(cat cookie-jar.txt  | grep -i "vmware-api-session-id" | awk '{print $7}')


# Get Hosts Names and Instances
offline=$(curl -k -b cookie-jar.txt https://192.168.1.238/rest/vcenter/vm?filter.power_states=POWERED_OFF | jq -r '.value[] | .name')
offlineName=$(curl -k -b cookie-jar.txt https://192.168.1.238/rest/vcenter/vm?filter.power_states=POWERED_OFF | jq -r '.value[] | .vm')
timeStamp=$(date)
# Generate Offline Host Report
if [ -z "$offline" ]; then
  exit 1
else
  echo "--------------------------------------------"                                          > weekly-report_${now}.txt
  echo "- FORGE: Security Scan System Status Check"                                            >> weekly-report_${now}.txt
  echo "- $timeStamp"                                                                          >> weekly-report_${now}.txt
  echo "--------------------------------------------"                                          >> weekly-report_${now}.txt  
  echo ""                                                                                      >> weekly-report_${now}.txt
  echo "*********"                                                                             >> weekly-report_${now}.txt  
  echo "- Offline"                                                                             >> weekly-report_${now}.txt  
  echo "*********"                                                                             >> weekly-report_${now}.txt  
  for i in $offline; do
    echo "$i is offline, marked ffor correction"                                               >> weekly-report_${now}.txt
    offlineCorrection=yes
  done
  echo "**************"                                                                        >> weekly-report_${now}.txt  
  echo "- Corrections:"                                                                        >> weekly-report_${now}.txt  
  echo "**************"                                                                        >> weekly-report_${now}.txt   
  if [ "$offlineCorrection" = "yes" ]; then
    for j in $offlineName; do
      echo "Powering on $j"                                                                    >> weekly-report_${now}.txt
      curl -k -b cookie-jar.txt -X POST https://192.168.1.238/rest/vcenter/vm/$j/power/start
    done
  fi
fi


host_table=$(cat /etc/hosts | grep -v)

for i in $host_table; do
  host_name=$(echo $i | awk '{print $2}')
  host_ip=$(echo $i | awk '{print $1}')
  echo "host_name: $i | awk '{print $2}'"
  echo "host_ip: $i | awk '{print $1}'"
  done

