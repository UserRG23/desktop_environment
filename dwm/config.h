/* See LICENSE file for copyright and license details. */
#define SESSION_FILE "/tmp/dwm-session"

#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMonoNL NFP:size=15:style=bold",
"Font Awesome 6 Free Solid:size=8"};
static const char dmenufont[]       = "JetBrainsMonoNL NFP:size=15:style=Bold" ;
static const char col_gray1[]       = "#282828";        /* цвет col_gray1 */
static const char col_gray2[]       = "#d4be98";        /* цвет col_gray2 */
static const char col_gray3[]       = "#d4be98";        /* цвет col_gray3 */
static const char col_gray4[]       = "#282828";        /* цвет col_gray4 */
static const char col_cyan[]        = "#e78a4e";        /* цвет col_cyan */
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
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *firefox[]  = { "firefox", NULL };
static const char *htop[]  = { "st", "-e", "btop", NULL };
static const char *vifm[]  = { "st", "-e", "vifm", NULL };
static const char *increasevolume[]  = { "amixer", "set", "Master", "5%+", NULL };
static const char *decreasevolume[]  = { "amixer", "set", "Master", "5%-", NULL };
static const char *switchvolume[]  = { "amixer", "set", "Master", "toggle", NULL };


static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Escape, spawn,          {.v = htop } },
	{ MODKEY,                       XK_b,      spawn,          {.v = firefox} },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          SHCMD("sudo logout")},
	{ MODKEY,                       XK_e,      spawn,          {.v = vifm }},
	{ MODKEY,                       XK_t,      spawn,          SHCMD("telegram-desktop")},
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_z,      setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ 0,                            XK_Print,  spawn,          SHCMD("flameshot gui --raw | xclip -sel clip -t image/png") },
	{ ShiftMask,                            XK_Print,  spawn,          SHCMD("flameshot gui") },

	{ 0, 			            	XF86XK_AudioRaiseVolume,   spawn,   {.v = increasevolume } }, 
	{ 0, 				            XF86XK_AudioLowerVolume,   spawn,   {.v = decreasevolume } }, 
	{ 0, 				            XF86XK_AudioMute,          spawn,   {.v = switchvolume } }, 
	{ 0, 			            	XF86XK_AudioRaiseVolume,   spawn,   SHCMD("pkill -RTMIN+1 dwmblocks") }, 
	{ 0, 				            XF86XK_AudioLowerVolume,   spawn,   SHCMD("pkill -RTMIN+1 dwmblocks") }, 
	{ 0, 				            XF86XK_AudioMute,          spawn,   SHCMD("pkill -RTMIN+1 dwmblocks") }, 
    { 0,                            XF86XK_MonBrightnessUp,    spawn,   SHCMD("brghp") },
                                                                            // copy /home/riza/.environment/scripts/brghp to /bin/bash
    { 0,                            XF86XK_MonBrightnessDown,  spawn,   SHCMD("brghm") },
                                                                            // copy /home/riza/.environment/scripts/brghm to /bin/bash
    { 0,                            XF86XK_MonBrightnessUp,    spawn,   SHCMD("pkill -RTMIN+2 dwmblocks") },
    { 0,                            XF86XK_MonBrightnessDown,  spawn,   SHCMD("pkill -RTMIN+2 dwmblocks") },

	{ MODKEY,                       XK_space,                  spawn,   SHCMD("pkill -RTMIN+10 dwmblocks") },
	{ 0,                            0x1008ffa9,                spawn,   SHCMD("pkill -RTMIN+11 dwmblocks") },
	{ 0,                            0x1008ffa9,                spawn,   SHCMD("touchpad_toggle") },
                                                                            // copy ~/.environment/dwm/scripts/touchpad_toggle to /bin/bash

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
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

