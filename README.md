# brightness-manager
Program that controls screen brightness, by modyfing monitor device file. Mainly intended to be used as a keybinded action, in windows managers that not supporting this feature by default like suckless DWM

#### usage:
1. Build and install brightness-manager 
* edit config.h if you need
* build and install
  ```
  $ make
  $ sudo make install  
  ```
* modyfing monitor device file needs sudo permissions, disable asking about password. Add this entry to /etc/sudoers
  ```
  YourUserName ALL = (root) NOPASSWD: /usr/bin/brightness-manager
  ```
* done, to increase or decrease your screen brightness type in terminal
  ```
  increase
  $ brightness-manager -i
  decrease
  $ brightness-manager -d
  ```

2. Configure keybinds in dwm's config.h and rebuild dwm
* Include this header at a top of file, needed for brightness keys definitons
  ```
  #include <X11/XF86keysym.h>
  ```
* Add this command definition
  ```
  static const char *brupcmd[] = { "sudo", "brightness-manager", "-i", NULL };
  static const char *brdowncmd[] = { "sudo", "brightness-manager", "-d", NULL };
  ```
* Add keybind to keys array
  ```
  { 0, XF86XK_MonBrightnessUp, spawn, {.v = brupcmd} },
  { 0, XF86XK_MonBrightnessDown, spawn, {.v = brdowncmd} },
  ```
* Reboot or restart display-manager
  ```
  systemctl restart display-manager
  ```
  
 Have fun, after this few easy steps you will be able set fucking brightness on your linux pc.
 Or not
