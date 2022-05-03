# Set Logging
%post --log=/root/anvil-ssh.log

# Enable VNC via ssh
sed -i "s/#AllowTcpForwarding/AllowTcpForwarding/"  /etc/ssh/sshd_config