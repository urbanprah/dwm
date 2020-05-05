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
* multiple scratchpads
* a rule for true fullscreen (ignore fakefullscreen patch)
* colored emoji support using libxft-bgra

TODO
====
* [ ] [config][shortcuts] sxhkd -> config.h
* [ ] [config][colors] default tag color scheme (colored blocks)
* [ ] [feature][shortcut] force kill client
* [ ] [improvement][fakefs] merge isfullscreen, ignorefakefs
* [ ] [improvement][focusadjacenttag] dont use gcc builtins: ```__builtin_popcount(int x)```
* [ ] [improvement][scratchpad] same scratchpad on all monitors
