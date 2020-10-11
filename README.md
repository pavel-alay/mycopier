# mycopier
Handy file copier with macOS plist

plist shall be updated corresponding to your environment and can be added to `$HOME/Library/LaunchAgents/`.

Load and Stop plist: 
```
launchctl load com.alay.copier.plist
launchctl unload com.alay.copier.plist
```

During the first run macOS will ask for permissions and will add program to 'Full Disk Access' and 'Files and Folders' sections of 'Privacy' tab in 'Security & Privacy' settings. It can be updated according to your needs.

Tested on macOS Catalina with copying from `$HOME/Library/*`.

