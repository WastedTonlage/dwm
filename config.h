/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int gappx              = 15;       /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Source Code Pro:size=12", "Noto Color Emoji"};
static const char dmenufont[]       = "Source Code Pro:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_red[]         = "#c47d12";
static const char gruvbox_bg3[]          = "#665c54";
static const char gruvbox_bg1[]          = "#3c3836";
static const char gruvbox_fg4[]          = "#a89984";
static const char gruvbox_fg2[]          = "#d5c4a1";
static const char gruvbox_orange_dark[]  = "#d65d03";
static const char gruvbox_gray[]         = "#928374";
static const char gruvbox_fg0[]          = "#fbf1c7";
static const char gruvbox_bg4[]          = "#7c6f63";
static const char gruvbox_fg1[]          = "#ebdbb2";
static const char gruvbox_bg2[]          = "#504945";
static const char gruvbox_orange_light[] = "#fe8019";
static const char gruvbox_yellow_light[] = "#fabd2f";
static const char col_black[]            = "#000000";
static const char col_white[]            = "#ffffff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { gruvbox_fg1, gruvbox_bg1, gruvbox_orange_dark  },
	[SchemeSel]  = { gruvbox_yellow_light, gruvbox_bg2, gruvbox_yellow_light  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",       NULL,       NULL,       0,            1,           -1 },
	{ "Ghidra",     NULL,       NULL,       0,            1,           -1 },
	// { "Tor Browser",NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "[@]",      spiral },   /* first entry is default */
 	{ "[\\]",     dwindle },
	{ "[]=",      tile },    
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_red, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *musicdcmd_tag[] = {"musicd", "playtag", NULL};
static const char *musicdcmd_song[] = {"musicd", "play", NULL};
static const char *pausecmd[] = {"musicd", "pause", NULL};
static const char *nextcmd[] = {"musicd", "next", NULL};
static const char *browsercmd[] = {"firefox", NULL};
static const char *privatecmd[] = {"firefox", "-private", NULL};
static const char *torbrowsercmd[] = {"tor-browser", NULL};
static const char *mixercmd[] = {"pavucontrol-qt", NULL};
static const char *reloadcmd[] = {"reload-dwm", NULL};
static const char *pomstartcmd[] = {"start_pomodoro", NULL};
static const char *pombreakcmd[] = {"start_break", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,						XK_aring,  spawn,          {.v = musicdcmd_tag}},
	{ MODKEY,						XK_dead_diaeresis,  spawn, {.v = musicdcmd_song}},
	{ MODKEY,						XK_space,  spawn,          {.v = pausecmd}},
	{ MODKEY,						XK_Right,  spawn,          {.v = nextcmd}},
	{ MODKEY,						XK_b,      spawn,          {.v = browsercmd}},
	// { MODKEY,						XK_p,      spawn,          {.v = privatecmd}},
	{ MODKEY,						XK_t,      spawn,          {.v = torbrowsercmd}},
	{ MODKEY,						XK_a,      spawn,          {.v = mixercmd}},
	{ MODKEY|ShiftMask,			   	XK_p,      spawn,          {.v = pombreakcmd}},
	{ MODKEY,             		   	XK_p,      spawn,          {.v = pomstartcmd}},
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,						XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_f,      togglefullscreen,{0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_exclam,                      0)
	TAGKEYS(                        XK_at,                      1)
	TAGKEYS(                        XK_numbersign,                      2)
	TAGKEYS(                        XK_dollar,                      3)
	TAGKEYS(                        XK_percent,                      4)
	TAGKEYS(                        XK_ampersand,                      5)
	TAGKEYS(                        XK_slash,                      6)
	TAGKEYS(                        XK_parenleft,                      7)
	TAGKEYS(                        XK_parenright,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button2,        killclient,    {0} },
	{ ClkClientWin,         MODKEY,         Button3,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

