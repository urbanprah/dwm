dwm 
===
dwm is an extremely fast, small, and dynamic window manager for X and this is my custom build.

INSTALLATION
------------
You probably know what you are doing.

PATCHES
-------
Base patches can be found in patches/
* statuscmd + dwmblocks + status2d work together
* fakefullscren modified with ignorefakefs rule
* colored emoji support using libxft-bgra

TODO
====
* [ ] [config][shortcuts] sxhkd -> config.h
* [ ] [feature][shortcut] force kill client
* [ ] [improvement][fakefs] merge isfullscreen, ignorefakefs
* [ ] [issue][fakefs] window wont fill the screen
* [ ] [issue][fakefs] cant shift focus using j,k
* [ ] [issue][Steam] borderpx != 1 causes weird window movement
* [x] [issue][statuscmd] strip status2d tags from stext
* [x] [improvement][fakefullscreen] no border with 1 client
* [x] [issue][systray] icon artifacting
