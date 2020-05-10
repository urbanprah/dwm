# dwm
dwm is an extremely fast, small, and dynamic window manager for X and this is my custom build.

CHANGES
-------
* base **patches** can be found in patches/
* statuscmd + dwmblocks + status2d compatibility fixes
* multiple scratchpads
* ignore fakefullscreen patch rule
* colored emoji support using [libxft-bgra](https://aur.archlinux.org/packages/libxft-bgra/)
* [tcc](https://www.archlinux.org/packages/community/x86_64/tcc/) as default compiler (it's soo faaast!)

##### TODO
* [ ] 20+ clients crash (client goes off screen)
* [ ] m->gappx too small crash (client goes below where it should)
* [ ] autostart: list of applications in config.h
* [ ] shortcuts
* [ ] forcekill client shortcut
* [ ] merge isfullscreen, truefs
* [ ] multihead functionality
    * [ ] scratchpads shared across monitors
    * [ ] focusadjecenttag patch jump monitors (9->1, 1->9)
    * [ ] swaptags (MODKEY+XK_Tab)
    * [ ] swapfocus patch (MODKEY+XK_s)
* [ ] usage, manpage
* [ ] requirements
* [ ] layouts.h
* [ ] adhere to [suckless coding style](https://suckless.org/coding_style/)
