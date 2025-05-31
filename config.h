
/* See LICENSE file for copyright and license details. */

/* Includes for media keys */
#include <X11/XF86keysym.h>

/* Appearance */
static const unsigned int borderpx            = 2;        /* border pixel of windows */
static const unsigned int snap                = 32;       /* snap pixel */

/* Manage gaps, gaps by default = 0 */
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 5;        /* 1 means no outer gap when there is only one window */

/* System Tray */
static const unsigned int systraypinning      = 0;
static const unsigned int systrayonleft       = 0;
static const unsigned int systrayspacing      = 2;
static const int systraypinningfailfirst      = 1;
static const int showsystray                  = 1;

/* Bar */
static const int showbar                      = 1;
static const int topbar                       = 0;

/* Fonts and Colors */
static const char *fonts[] = {
    "Overpass:size=10:weight=Bold:antialias=true:autohint=true",
    "Noto Color Emoji:pixelsize=10:antialias=true:autohint=true",
};

static const char col_gray1[] = "#222222";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_cyan[]  = "#005577";

static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* Autostart */
static const char *const autostart[] = {
    "sh", "-c", "~/.fehbg &", NULL,
    "sh", "-c", "pgrep -x \"picom\" >/dev/null || picom &", NULL,
    "sh", "-c", "pgrep -x \"dunst\" >/dev/null || dunst &", NULL,
    "sh", "-c", "xset s off -dpms &", NULL,
    "sh", "-c", "/home/bryant/Documents/github/dotfiles/bin/global/dwmstylebar &", NULL,
    NULL
};

/* Tagging */
static const char *tags[] = {
    "󰎤", "󰎧", "󰎪", "󰎭", "󰎱", "󰎳", "󰎶", "󰎹", "󰎼", "󰽽",
};

static const Rule rules[] = {
    /* class                instance    title       tags mask     iscentered   isfloating   monitor */
    { "jetbrains-datagrip", NULL,       NULL,       1 << 3,       0,           0,           -1 },
    { "Postman",             NULL,       NULL,       1 << 4,       0,           0,           -1 },
    { "bruno",               NULL,       NULL,       1 << 4,       0,           0,           -1 },
    { "calibre",             NULL,       NULL,       1 << 5,       0,           0,           -1 },
    { "qBittorrent",        NULL,       NULL,       1 << 5,       0,           0,           -1 },
    { "mpv",                 NULL,       NULL,       1 << 6,       1,          -1,           -1 },
    { "vesktop",             NULL,       NULL,       1 << 7,       0,           0,           -1 },
    { "St",                  NULL,       "ncmpcpp",  0,            1,          -1,           -1 },
    { "Nsxiv",               NULL,       NULL,       0,            1,           1,           -1 },
};

/* Layouts */
static const float mfact     = 0.50;
static const int nmaster     = 1;
static const int resizehints = 1;
static const int lockfullscreen = 1;

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[\\]",     dwindle },
	{ "[M]",      monocle },
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* Key Definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Commands */
static const char *termcmd[] = { "st", NULL };

/* Keys */
static const Key keys[] = {
    /* modifier             key                 function        argument */

    /* --- WM Control & Session --- */
    { MODKEY,               XK_q,               killclient,     {0} },
    { MODKEY|Mod1Mask,      XK_e,               quit,           {0} },

    /* --- Application Launchers --- */
    { MODKEY,               XK_d,               spawn,          SHCMD("rofi -show run") },
    { MODKEY,               XK_t,               spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,     XK_t,               spawn,          SHCMD("alacritty") },
    { MODKEY,               XK_Return,          spawn,          SHCMD("thorium-browser") },
    { MODKEY|ShiftMask,     XK_Return,          spawn,          SHCMD("thorium-browser --user-data-dir=/home/bryant/.config/thorium-work") },
    { MODKEY,               XK_e,               spawn,          SHCMD("pcmanfm") },
    { MODKEY,               XK_a,               spawn,          SHCMD("~/bin/wm/passmenu") },
    { MODKEY,               XK_o,               spawn,          SHCMD("~/bin/wm/passmenu --otp") },
    { MODKEY,               XK_minus,           spawn,          SHCMD("st -e yazi") },
    { MODKEY,               XK_m,               spawn,          SHCMD("st -t ncmpcpp -e ncmpcpp") },
    { MODKEY,               XK_i,               spawn,          SHCMD("~/bin/wm/bg") },
    { MODKEY,               XK_b,               spawn,          SHCMD("~/bin/wm/set-brightness") },
    { MODKEY,               XK_s,               spawn,          SHCMD("~/bin/wm/screenkey") },
    { MODKEY,               XK_r,               spawn,          SHCMD("~/bin/wm/read") },
    { MODKEY|ShiftMask,     XK_r,               spawn,          SHCMD("~/bin/global/recording") },
    { MODKEY|ShiftMask,     XK_c,               spawn,          SHCMD("mpv --volume=100 ~/Documents/github/media/videos/biy/cristiano.mp4") },
    { MODKEY,               XK_space,           spawn,          SHCMD("~/bin/wm/switch-keyboard") },

    /* --- Window Management --- */
    { MODKEY,               XK_l,               focusstack,     {.i = +1 } },
    { MODKEY,               XK_h,               focusstack,     {.i = -1 } },
    { MODKEY,               XK_n,               viewnext,       {0} },
    { MODKEY,               XK_p,               viewprev,       {0} },
    { MODKEY,               XK_f,               togglefullscr,  {0} },
    { MODKEY,               XK_w,               togglefloating, {0} },
    { MODKEY|ShiftMask,     XK_w,               togglebar,      {0} },
    { MODKEY|Mod1Mask,      XK_l,               setmfact,       {.f = +0.05} },
    { MODKEY|Mod1Mask,      XK_h,               setmfact,       {.f = -0.05} },
    { MODKEY,               XK_Tab,             zoom,           {0} },
    { MODKEY,               XK_Escape,          view,           {0} },

    /* --- Tags --- */
    TAGKEYS(XK_bracketleft, 0)
    TAGKEYS(XK_braceleft,   1)
    TAGKEYS(XK_parenleft,   2)
    TAGKEYS(XK_percent,     3)
    TAGKEYS(XK_equal,       4)
    TAGKEYS(XK_ampersand,   5)
    TAGKEYS(XK_parenright,  6)
    TAGKEYS(XK_braceright,  7)
    TAGKEYS(XK_bracketright,8)
    TAGKEYS(XK_exclam,      9)
    TAGKEYS(XK_1,           0)
    TAGKEYS(XK_2,           1)
    TAGKEYS(XK_3,           2)
    TAGKEYS(XK_4,           3)
    TAGKEYS(XK_5,           4)
    TAGKEYS(XK_6,           5)
    TAGKEYS(XK_7,           6)
    TAGKEYS(XK_8,           7)
    TAGKEYS(XK_9,           8)
    TAGKEYS(XK_0,           9)

    /* --- Screenshots --- */
    { 0,          XK_Print,   spawn, SHCMD("~/bin/wm/take-screenshots -m select -s clip && notify-send 'Saved in clipboard'") },
    { Mod1Mask,   XK_Print,   spawn, SHCMD("~/bin/wm/take-screenshots -m select -s save && notify-send 'Saved in disk'") },
    { MODKEY,     XK_Print,   spawn, SHCMD("~/bin/wm/take-screenshots -m full -s clip && notify-send 'Saved in clipboard'") },
    { ControlMask,XK_Print,   spawn, SHCMD("~/bin/wm/take-screenshots -m full -s save && notify-send 'Saved in disk'") },

    /* --- Hardware Keys --- */
    { 0, XF86XK_AudioLowerVolume, spawn, SHCMD("~/bin/wm/volume-dunst down") },
    { 0, XF86XK_AudioRaiseVolume, spawn, SHCMD("~/bin/wm/volume-dunst up") },
    { 0, XF86XK_AudioMute,        spawn, SHCMD("~/bin/wm/volume-dunst mute") },
};

/* Mouse buttons */
static const Button buttons[] = {
    { ClkLtSymbol,     0, Button1, setlayout,  {0} },
    { ClkClientWin, MODKEY, Button1, movemouse,  {0} },
    { ClkClientWin, MODKEY, Button3, resizemouse,{0} },
    { ClkTagBar,    0, Button1, view,        {0} },
};
