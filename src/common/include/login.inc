# Set Logging
%post --log=/root/anvil-login.log

sed -i "s/PASS_MIN_DAYS 1 /PASS_MIN_DAYS 7/" /etc/login.defs


