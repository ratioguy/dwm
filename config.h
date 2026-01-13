/* My dwm config */

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Literation Mono Nerd Font:size=10" };
static const char dmenufont[]       = "Literation Mono Nerd Font:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "imv",      NULL,     NULL,         		 0,            1,           -1 },
	{ "nsxiv-rifle",    NULL,     NULL,         		 0,            1,           -1 },
	{ "MuPDF",    NULL,     NULL,        		 0,            1,           -1 },
	{ "dialog",   NULL,     NULL,			 0,            1,           -1 },
	{ "gimp-file-open",     NULL,			 0,            0,            1 },
	{ "Thunar",   NULL,     NULL,			 0,            1,           -1 },
	{ "st",       NULL,     "youtube-launcher",      0,            1,           -1 },
	{ "st",       NULL,     "youtube-downloader",    0,            1,           -1 },
	{ "st",       NULL,     "pulsemixer",  		 0,            1,           -1 },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-i", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
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
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

	/* My Bindings*/
	{ MODKEY|ShiftMask,	        XK_b, 	   spawn,          SHCMD("firefox") },
	{ MODKEY,	                XK_v,      spawn,          SHCMD("clipmenu -p clipboard -i") },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          SHCMD("clipdel -d .") },
	{ MODKEY,			XK_e,	   spawn,     	   SHCMD("st -e lf") },
	{ MODKEY|ShiftMask,		XK_m,	   spawn,     	   SHCMD("st -e ncmpcpp") },
	{ MODKEY,			XK_n,	   spawn,     	   SHCMD("st -e newsboat") },
	{ MODKEY|ShiftMask,			XK_t,	   spawn,     	   SHCMD("st -e htop") },
	{ MODKEY,			XK_u,	   spawn,     	   SHCMD("st -T pulsemixer -e pulsemixer ") },
	{ MODKEY,			XK_y,	   spawn,     	   SHCMD("st -T youtube-launcher -e ~/.local/bin/yt-launcher.sh") },
	{ MODKEY,			XK_y,	   spawn,     	   SHCMD("st -T youtube-downloader -e ~/.local/bin/yt-downloader.sh") },
	{0,          0x1008FF13, 	spawn,    	   SHCMD("bash ~/.local/bin/volume.sh up") },
	{0,          0x1008FF11, 	spawn,    	   SHCMD("bash ~/.local/bin/volume.sh down") },
	{0,          0x1008FF12,	spawn,    	   SHCMD("bash ~/.local/bin/volume.sh mute") },
	{ MODKEY,			XK_w,	   spawn,     	   SHCMD("bash ~/.local/bin/volume.sh up") },
	{ MODKEY,			XK_s,	   spawn,     	   SHCMD("bash ~/.local/bin/volume.sh down") },
	{ MODKEY|ShiftMask,		XK_s,	   spawn,     	   SHCMD("bash ~/.local/bin/volume.sh mute") },
	{ MODKEY,			XK_o,	   spawn,     	   SHCMD("pactl set-default-sink alsa_output.usb-HP_HP_Speaker_Bar-00.analog-stereo ; notify-send -t 8000 Output: Speaker") },
	{ MODKEY|ShiftMask,		XK_o,	   spawn,     	   SHCMD("pactl set-default-sink alsa_output.pci-0000_00_1f.3.analog-stereo ; notify-send -t 8000 Output: Headphones") },
	{0,          0x1008FF02, 	   spawn,    	   SHCMD("brightnessctl -d intel_backlight set 5%+ ; notify-send Brightness $(brightnessctl  | grep % | awk '{print $4}' | sed 's/[()]//g')") },
	{0,          0x1008FF03, 	   spawn,    	   SHCMD("brightnessctl -d intel_backlight set 5%- ; notify-send Brightness $(brightnessctl  | grep % | awk '{print $4}' | sed 's/[()]//g')") },
	{ MODKEY,			XK_x,	   spawn,     	   SHCMD("xnap | pnmtopng | tee ~/Pictures/Screenshots/Screenshot-$(date +%Y-%m-%d-%S_%N).png ; notify-send -t 2000 'Screenshot Taken.'") },
	
	{ MODKEY|ShiftMask,		XK_x,	   spawn,     	   SHCMD("xnap -w | pnmtopng | tee ~/Pictures/Screenshots/Screenshot-$(date +%Y-%m-%d-%S_%N).png ; notify-send -t 2000 'Screenshot Taken.'") },
	{ MODKEY,			XK_backslash,	   spawn,  SHCMD("playerctl play-pause") },
	{ MODKEY,			XK_bracketright,   spawn,  SHCMD("playerctl next") },
	{ MODKEY,			XK_bracketleft,	   spawn,  SHCMD("playerctl previous") },
	


};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

