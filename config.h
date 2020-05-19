/*
    ██████╗ ██╗    ██╗███╗   ███╗
    ██╔══██╗██║    ██║████╗ ████║
    ██║  ██║██║ █╗ ██║██╔████╔██║
    ██║  ██║██║███╗██║██║╚██╔╝██║
    ██████╔╝╚███╔███╔╝██║ ╚═╝ ██║
    ╚═════╝  ╚══╝╚══╝ ╚═╝     ╚═╝
*/
/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 4;        /* border pixel of windows */
static const unsigned int snap           = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;        /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 5;        /* systray spacing */
static const int systraypinningfailfirst = 1;        /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;        /* 0 means no systray */
static const int showbar                 = 1;        /* 0 means no bar */
static const int topbar                  = 1;        /* 0 means bottom bar */
static const int barpadding              = 20;       /* 0 means bottom bar */
static const char *fonts[]               = {
        "monospace:size=14",
        "Font Awesome 5 Free:size=14:antialias=true:autohint=true",
        "JoyPixels:size=14:antialias=true:autohint=true",
};
static char color0[]     = "#090a0d";
static char color1[]     = "#265957";
static char color2[]     = "#367f6d";
static char color3[]     = "#92443e";
static char color4[]     = "#46a557";
static char color5[]     = "#99ac4a";
static char color6[]     = "#4fb3a3";
static char color7[]     = "#c5c9c3";
static char color8[]     = "#898c88";
static char color9[]     = "#265957";
static char color10[]    = "#367f6d";
static char color11[]    = "#92443e";
static char color12[]    = "#46a557";
static char color13[]    = "#99ac4a";
static char color14[]    = "#4fb3a3";
static char color15[]    = "#c5c9c3";
static char *colors[][3] = {
    /*                fg           bg           border   */
    [SchemeNorm]  = { color7,      color0,      color1  },
    [SchemeSel]   = { color0,      color1,      color2  },
    [SchemeOff]   = { color8,      color0,      color8  },
    [SchemeWar]   = { color0,      color3,      color7  },
};

/* tagging */
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                        instance   title   tags mask   truefs   iscentered     isfloating   monitor */
	{ "Gimp",                       NULL,      NULL,   0,          0,             0,       1,           -1 },
	{ "Firefox",                    NULL,      NULL,   1 << 8,     0,             0,       0,           -1 },
	{ "ncpamixer",                  NULL,      NULL,   0,          0,             1,       1,           -1 },
	{ "transmission-remote-cli",    NULL,      NULL,   0,          0,             1,       1,           -1 },
	{ "jetbrains-idea", "jetbrains-idea",    "win0",   0,          0,             1,       1,           -1 },
	{ "jetbrains-idea", "jetbrains-idea",    "win0",   0,          0,             1,       1,           -1 },
        { "Microsoft Teams - Preview", "microsoft teams - preview", "Microsoft Teams Notification", 0, 0, 0, 1 ,-1},
	{ "mpv",                        NULL,      NULL,   0,          1,             0,       0,           -1 },
	{ NULL,                     "sptodo",      NULL,   SPTAG(0),   1,             1,       1,           -1 },
	{ NULL,                     "spcalc",      NULL,   SPTAG(1),   1,             1,       1,           -1 },
	{ NULL,                  "spncmpcpp",      NULL,   SPTAG(2),   1,             1,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

/* #include "fibonacci.c" */
/* #include "gaplessgrid.c" */
enum { TILE, BSTACK, CMASTER, MONOCLE, BSTACKH, DECK, CFMASTER, FLOAT, END };
static const Layout layouts[] = {
	/*               symbol      arrange function */
	[TILE]       = { "[]=",      tile }, /* default */
        [BSTACK]     = { "TTT",      bstack },
        [CMASTER]    = { "|M|",      centeredmaster },
 	/* [SPIRAL]     = { "[@]",      spiral }, */
        /* [GRID]       = { "###",      gaplessgrid }, */
	[MONOCLE]    = { "[M]",      monocle },
	[BSTACKH]    = { "===",      bstackhoriz },
        [DECK]       = { "[D]",      deck },
 	/* [DWINDLE]    = { "[\\]",     dwindle }, */
	[CFMASTER]   = { ">M>",      centeredfloatingmaster },
	[FLOAT]      = { "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL }
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

typedef struct {
	const char *name;
	const void *cmd;
} Scratchpad;

/* static const void* autostart[] = { */
/*         {"xcompmgr", "&", NULL}, */
/*         {"nm-applet", "&", NULL}, */
/*         /1* "pidof -s dwmblocks >/dev/null || dwmblocks &", *1/ */
/*         /1* "pkill -RTMIN+0 dwmblocks", *1/ */
/* }; */

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-h", "50", NULL };
static const char *termcmd[]  = { "st", NULL };

const char *spcmd1[] = {"st", "-n", "sptodo",    "-g", "70x30",  "-e", "ctodo", "/home/aiden/Documents/todo.txt", NULL };
const char *spcmd2[] = {"st", "-n", "spcalc",    "-g", "50x20",  "-e", "bc", "-lq", NULL };
const char *spcmd3[] = {"st", "-n", "spncmpcpp", "-g", "100x30", "-e", "ncmpcpp", NULL };
static Scratchpad scratchpads[] = {
	/* name       cmd  */
	{"sptodo",    spcmd1},
	{"spcalc",    spcmd2},
	{"spncmpcpp", spcmd3},
};

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key              function        argument */
	{ MODKEY,                       XK_p,            spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,       spawn,          {.v = termcmd } },
        { MODKEY,			XK_grave,	 togglescratch,	 {.ui = 0} },
	{ MODKEY|ShiftMask,		XK_grave,	 togglescratch,	 {.ui = 1} },
	{ MODKEY,	           	XK_n,	         togglescratch,	 {.ui = 2} },
	{ MODKEY,                       XK_b,            togglebar,      {0} },
	{ MODKEY,                       XK_j,            focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,            focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,            incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,            incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,            setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,            setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_o,            setmfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_h,            setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_l,            setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_j,            movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,            movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Return,       zoom,           {0} },
        { MODKEY|ControlMask,           XK_j,            moveresize,     {.v = (int []){ 0, 50, 0, 0 }}},
        { MODKEY|ControlMask,           XK_k,            moveresize,     {.v = (int []){ 0, -50, 0, 0 }}},
        { MODKEY|ControlMask,           XK_l,            moveresize,     {.v = (int []){ 50, 0, 0, 0 }}},
        { MODKEY|ControlMask,           XK_h,            moveresize,     {.v = (int []){ -50, 0, 0, 0 }}},
        { MODKEY|ControlMask|ShiftMask, XK_j,            moveresize,     {.v = (int []){ 0, 0, 0, 50 }}},
        { MODKEY|ControlMask|ShiftMask, XK_k,            moveresize,     {.v = (int []){ 0, 0, 0, -50 }}},
        { MODKEY|ControlMask|ShiftMask, XK_l,            moveresize,     {.v = (int []){ 0, 0, 50, 0 }}},
        { MODKEY|ControlMask|ShiftMask, XK_h,            moveresize,     {.v = (int []){ 0, 0, -50, 0 }}},
        /* { MODKEY,                       XK_minus,        setgaps,        {.i = -5 } }, */
	/* { MODKEY,                       XK_equal,        setgaps,        {.i = +5 } }, */
	/* { MODKEY|ShiftMask,             XK_equal,        setgaps,        {.i = 0  } }, */
	{ MODKEY,                       XK_Tab,          view,           {0} },
	{ MODKEY,                       XK_s,            swapfocus,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_c,            killclient,     {0} },
	{ MODKEY,                       XK_t,            setlayout,      {.v = &layouts[TILE]} },
	{ MODKEY,                       XK_v,            setlayout,      {.v = &layouts[BSTACK]} },
	{ MODKEY,                       XK_m,            setlayout,      {.v = &layouts[MONOCLE]} },
	{ MODKEY|ControlMask,		XK_comma,        cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period,       cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,        setlayout,      {0} },
	{ MODKEY,                       XK_f,            togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_space,        unfloatvisible, {0} },
	{ MODKEY|ShiftMask,             XK_t,            unfloatvisible, {.v = &layouts[0]} },
	{ MODKEY,                       XK_0,            view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,            tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,        focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,       focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,        tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,       tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_F5,           xrdb,           {.v = NULL } },
	{ MODKEY,                       XK_bracketleft,  viewtoleft,     {0} },
	{ MODKEY,                       XK_bracketright, viewtoright,    {0} },
	{ MODKEY|ShiftMask,             XK_bracketleft,  tagtoleft,      {0} },
	{ MODKEY|ShiftMask,             XK_bracketright, tagtoright,     {0} },
	{ MODKEY|ShiftMask,             XK_q,            quit,           {0} },
	TAGKEYS(                        XK_1,                            0)
	TAGKEYS(                        XK_2,                            1)
	TAGKEYS(                        XK_3,                            2)
	TAGKEYS(                        XK_4,                            3)
	TAGKEYS(                        XK_5,                            4)
	TAGKEYS(                        XK_6,                            5)
	TAGKEYS(                        XK_7,                            6)
	TAGKEYS(                        XK_8,                            7)
	TAGKEYS(                        XK_9,                            8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	/* { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } }, */
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
