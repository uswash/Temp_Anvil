# Set Logging
%post --log=/root/anvil-audit.log

# Update logrotate
sed -i 's/weekly/daily/' /etc/logrotate.conf
sed -i 's/weeks/days/'  /etc/logrotate.conf

# Set 10 audit logs at 100MB each
sed -i "s/.*num_logs.*/num_logs = 10/"          /etc/audit/auditd.conf
sed -i "s/.*max_log_file.*/max_log_file = 100/" /etc/audit/auditd.conf

# Comment out, noise in server is IPA'd
sed -i '/adjtimex/s/^/###/' /etc/audit/rules.d/CS2_audit.rules

# Prevents system lockups while installing packages with YUM
sed -i 's/-w \/var\/log\/audit\/ -p wa/###-w \/var\/log\/audit\/ -p wa/g' /etc/audit/audit.rules
sed -i 's/-w \/var\/log\/audit\/audit.log -p wa/###-w \/var\/log\/audit\/audit.log -p wa/g' /etc/audit/audit.rules
sed -i 's/-w \/var\/log\/audit\/audit.log.1 -p wa/###-w \/var\/log\/audit\/audit.log.1 -p wa/g' /etc/audit/CS2_audit.rules

# Set Failure mode to panic to f1
sed -i "s/^-f 2/-F 1/"  /etc/audit/rules.d/CS2_audit.rules
sed -i "s/^-f 2/-F 1/"  /etc/audit/audit.rules

# Set the audit.rules to immutable
sed -i "s/^-e 1/-e 2/" /etc/audit/rules.d/CS2_audit.rules
sed -i "s/^-e 1/-e 2/" /etc/audit/audit.rules

# Match buffer size to the max_log_file param
sed -i 's/freq = 50/freq = 100/g' /etc/audit/audit.rules
sed -i 's/freq = 20/freq = 100/g' /etc/audit/audit.rules
sed -i "s/^-b 9000/-b 102400000/" /etc/audit/rules.d/CS2_audit.rules

%end