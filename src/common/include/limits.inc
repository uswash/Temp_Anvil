# Set Logging
%post --log=/root/anvil-limits.log

# Configure limits
echo ""
echo "# The following lines have been added by Anvil" >> /etc/security/limits.conf
echo "*       soft       nproc         16385"         >> /etc/security/limits.conf
echo "*       hard       nproc         16385"         >> /etc/security/limits.conf
echo "*       -          rtprio          100"         >> /etc/security/limits.conf
echo "*       -          nice            -20"         >> /etc/security/limits.conf
echo "*       -          nofile        32768"         >> /etc/security/limits.conf
echo "*       soft       maxlogins        24"         >> /etc/security/limits.conf
echo "*       hard       maxlogins        24"         >> /etc/security/limits.conf
sed -i 's|3|10|g' /etc/security/limits.d/CS2_limits.conf

# Prevent Fork Bombs
sed -i 's,'"\(.*\)"','"#\1"','  /etc/security/limits.d/*-nproc.conf

# Adjust maxlogins
sed -i "s/maxlogins 3/maxlogins 6/" /etc/security/limits.d/50-cs2limits.conf

%end