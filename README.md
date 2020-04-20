# mycopier
Handy file copier with macOS plist

plist shall be updated corresponding to your environment and can be added to `$HOME/Library/LaunchAgents/`.

Load and Stop plist: 
```
launchctl load com.alay.copier.plist
launchctl unload com.alay.copier.plist
```

During the first run macOS will ask for permissions and will add program to Full Disk Access. You may grant full disk access, check the box.

Tested on macOS Catalina with `$HOME/Library` folders.
