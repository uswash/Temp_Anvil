# Set Logging
%post --log=/root/audit.log

# Update logrotate
sed -i 's/weekly/daily/' /etc/logrotate.conf
sed -i 's/weeks/days/'  /etc/logrotate.conf

# Set 10 audit logs at 100MB each
sed -i "s/.*num_logs.*/num_logs = 10/"          /etc/audit/auditd.conf
sed -i "s/.*max_log_file.*/max_log_file = 100/" /etc/audit/auditd.conf