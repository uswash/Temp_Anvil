# Set Logging
%post --log=/root/anvil-mods.log

# Set YUM Variables
yum_install=(eval "yum install -y")
yum_remove=(eval "yum remove -y --disablerepo=*")

# Install Admin Tools
"${yum_install[@]}" filezilla fping ansible htop git iftop

# Install RDP
"${yum_install[@]}" fltk tigervnc tigervnc-icons tigervnc-server tigervnc-server-applet tigervnc-server-module xrdp
systemctl enable xrdp
systemctl start xrdp

# Package Removals 
"${yum_remove[@]}" gnome-initial-setup gnome-boxes initial-setup initial-setup-gui
systemctl stop chronyd
systemctl disable chronyd

%end