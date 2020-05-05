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
* a rule for true fullscreen (ignore fakefullscreen patch)
* colored emoji support using libxft-bgra

TODO
====
* [ ] [config][shortcuts] sxhkd -> config.h
* [ ] [config][colors] default tag color scheme (colored blocks)
* [ ] [feature][scratchpad] multiple scratchpads
* [ ] [feature][shortcut] force kill client
* [ ] [improvement][fakefs] merge isfullscreen, ignorefakefs
* [ ] [improvement][focusadjacenttag] dont use gcc builtins: ```__builtin_popcount(int x)```
* [ ] [issue][Steam] borderpx != 1 causes weird window movement
* [x] [issue][fakefs] window wont fill the screen
* [x] [issue][fakefs] cant shift focus using j,k
* [x] [issue][statuscmd] strip status2d tags from stext
* [x] [issue][systray] icon artifacting
* [x] [improvement][fakefullscreen] no border with 1 client
