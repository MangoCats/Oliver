# Oliver
HTTP accessible script launcher

# you will need to copy Oliver.ini to /home/user/.config/MangoCats/

# to autolaunch: (change Exec path to wherever you keep your Oliver executable)
mkdir ~/.config/autostart
nano ~/.config/autostart/Oliver.desktop
```
[Desktop Entry]
Type=Application
Name=Oliver
Exec=/home/user/Dev/Oliver/Oliver
StartupNotify=false
Terminal=true
```

# to enable VNC to operate when no monitor is connected
# (to a Raspberry Pi) uncomment and edit the following lines in config.txt
sudo nano /boot/config.txt
```
hdmi_force_hotplug=1
hdmi_group=2
hdmi_mode=82
```
