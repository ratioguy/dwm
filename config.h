/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 5;       /* snap pixel */
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "LiterationMono Nerd Font:size=10" };
static const char col_gray1[]       = "#1e1c1b";
static const char col_gray2[]       = "#504945";
static const char col_gray3[]       = "#ebdbb2";
static const char col_gray4[]       = "#dddddd";
static const char col_yellow[]        = "#d79920";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_yellow,  col_yellow  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "imv",      NULL,     NULL,         0,            1,           -1 },
	{ "MuPDF",    NULL,     NULL,         0,            1,           -1 },
	{ "dialog",   NULL,     NULL,         0,            1,           -1 },
	{ "gimp-file-open",     NULL,         0,       0,            1,           -1 },
	{ "Pcmanfm",  NULL,     NULL,         0,            1,           -1 },
	{ "st",       NULL,     "youtube-launcher",       0,            1,           -1 },
	{ "st",       NULL,     "pulsemixer",  0,            1,            -1 },

};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "HHH",      grid },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
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

/* commands */
#include <X11/XF86keysym.h>
#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,	                XK_b, 	   spawn,          SHCMD("firefox") },
	{ MODKEY,	                XK_Return, spawn,          SHCMD("st") },
	{ MODKEY,                       XK_d,      spawn,          SHCMD("python ~/.local/bin/dmenu_drun") },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          SHCMD("bash ~/.local/bin/dmenu-power-menu.sh") },
	{ MODKEY,	                XK_v,      spawn,          SHCMD("clipmenu -p clipboard -i") },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          SHCMD("clipdel -d .") },
	{ MODKEY,			XK_e,	   spawn,     	   SHCMD("st -e lf") },
	{ MODKEY,			XK_m,	   spawn,     	   SHCMD("st -e ncmpcpp") },
	{ MODKEY,			XK_n,	   spawn,     	   SHCMD("st -e newsboat") },
	{ MODKEY,			XK_t,	   spawn,     	   SHCMD("st -e htop") },
	{ MODKEY,			XK_u,	   spawn,     	   SHCMD("st -T pulsemixer -e pulsemixer ") },
	{ MODKEY,			XK_y,	   spawn,     	   SHCMD("st -T youtube-launcher -e ~/.local/bin/youtube-launcher.sh") },
	{0,          XF86XK_AudioRaiseVolume, 	   spawn,    	   SHCMD("bash ~/.local/bin/volume.sh up") },
	{0,          XF86XK_AudioLowerVolume, 	   spawn,    	   SHCMD("bash ~/.local/bin/volume.sh down") },
	{0,           		  0x1008ff12,	   spawn,    	   SHCMD("bash ~/.local/bin/volume.sh mute") },
	{ MODKEY,			XK_w,	   spawn,     	   SHCMD("bash ~/.local/bin/volume.sh up") },
	{ MODKEY,			XK_s,	   spawn,     	   SHCMD("bash ~/.local/bin/volume.sh down") },
	{ MODKEY|ShiftMask,		XK_s,	   spawn,     	   SHCMD("bash ~/.local/bin/volume.sh mute") },
	{ MODKEY,			XK_o,	   spawn,     	   SHCMD("pactl set-default-sink alsa_output.usb-HP_HP_Speaker_Bar-00.analog-stereo ; notify-send -t 8000 Output: Speaker") },
	{ MODKEY|ShiftMask,		XK_o,	   spawn,     	   SHCMD("pactl set-default-sink alsa_output.pci-0000_00_1f.3.analog-stereo ; notify-send -t 8000 Output: Headphones") },
	{0,          XF86XK_MonBrightnessUp, 	   spawn,    	   SHCMD("brightnessctl -d intel_backlight set 5%+ ; notify-send Brightness $(brightnessctl  | grep % | awk '{print $4}' | sed 's/[()]//g')") },
	{0,          XF86XK_MonBrightnessDown, 	   spawn,    	   SHCMD("brightnessctl -d intel_backlight set 5%- ; notify-send Brightness $(brightnessctl  | grep % | awk '{print $4}' | sed 's/[()]//g')") },
	{ MODKEY,			XK_p,	   spawn,     	   SHCMD("scrot --select --line mode=edge --freeze ~/Pictures/Screenshots/Screenshot-%Y-%m-%d.png ; notify-send -t 2000 'Screenshot Taken.'") },
	
	{ MODKEY|Mod1Mask,		XK_p,	   spawn,     	   SHCMD("scrot --focussed --freeze ~/Pictures/Screenshots/Screenshot-%Y-%m-%d.png ; notify-send -t 2000 'Screenshot Taken.'") },
	{ MODKEY|ShiftMask,		XK_p,	   spawn,     	   SHCMD("scrot --freeze ~/Pictures/Screenshots/Screenshot-%Y-%m-%d.png ; notify-send -t 2000 'Screenshot Taken.'") },
	{ MODKEY,			XK_backslash,	   spawn,  SHCMD("playerctl play-pause") },
	{ MODKEY,			XK_bracketright,   spawn,  SHCMD("playerctl next") },
	{ MODKEY,			XK_bracketleft,	   spawn,  SHCMD("playerctl previous") },


	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_c,      incnmaster,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|Mod1Mask,              XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_k,      setcfact,       {.f = +0.25} },
	{ MODKEY|Mod1Mask,              XK_j,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	/*{ MODKEY,                     XK_Return, zoom,           {0} },*/
	{ MODKEY,	                XK_g,      togglegaps,     {0} },
	{ MODKEY,                       XK_grave,  view,           {0} },
	{ MODKEY,	                XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_z,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_x,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_f,      togglefullscr,   {0} },
	/*{ MODKEY,                     XK_f,      setlayout,      {.v = &layouts[1]} },*/
	/*{ MODKEY,                     XK_space,  setlayout,      {0} },*/
	{ MODKEY,	                XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0}  },
	{ MODKEY,                       XK_equal,  scratchpad_show, {0} },
	{ MODKEY,	                XK_minus,  scratchpad_hide, {0} },
	{ MODKEY|ShiftMask,             XK_equal, scratchpad_remove,{0} },
        { MODKEY,                       XK_i,      togglecanfocusfloating,   {0} },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          SHCMD("st") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

