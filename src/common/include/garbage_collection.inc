# Set Logging
%post --log=/root/anvil-garbage_collection.log

# Cleanup /root
rm -rf /root/*.log
rm -rf /root/*.syslog
rm -rf /root/template*
rm -rf /root/*.cfg

# Cleanup /tmp
rm -rf /tmp/ks-script*
rm -rf /tmp/*.log
rm -rf /tmp/yum*

# Cleanup System Logs
cp -f /dev/null /var/log/lastlog
cp -f /dev/null /var/log/messages
cp -f /dev/null /var/log/boot.log
cp -f /dev/null /var/log/wtmp
cp -f /dev/null /root/.bash_history
rm -f /var/mail/root

# Cleanup Generic Repos
rm -rf /et/yum.repos.d/CentOS*

# Switch over to Public repos
YUM=$(cat /etc/hosts | grep -i "anvil" | awk '{print $1}')
for file in /etc/yum.repos.d/ANVIL-*; do sed -i 's/10.9.8.1/'%{YUM}'/' $file; done

# Cleanup Staged files
rm -rf /var/security

%end