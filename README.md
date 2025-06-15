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

Scripts added to the folder will automatically be shown on next page reload.

If you add a line:
```
#OliverName=Display Name
```
to the script, that's what will show on the webpage.

If you add a .png file with the same name as the .sh script file, that image
will be embedded in the webpage.  Recommend resizing images down to 180 pixels
in width for quicker page rendering and loading.


