/* See LICENSE file for copyright and license details. */

#define SESSION_FILE "/tmp/dwm-session"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char buttonbar[]       = "󰣇";
static const int user_bh            = 28;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
#define ICONSIZE (bh - 8)   /* icon size */
#define ICONSPACING 10 /* space between icon and title */
static const char *fonts[]          = { "Ubuntu Nerd Font:size=14" };
static const char dmenufont[]       = "Ubuntu Nerd Font:size=14";

#include "termcolors.h"

static char black[]           = "#000000";
static char gray1[]       = "#111111";
static char gray2[]           = "#666666";
static char gray3[]            = "#bbbbbb";
static char gray4[]        = "#eeeeee";
static char yellow[]        = "#d19a66";
static char blue[]            = "#61afef";
static char accent[]		= "#005577";
static char *colors[][3] = {
       /*					fg			bg			border   */
       [SchemeNorm]		= { gray3,		gray1,		gray2 },
       [SchemeSel]		= { gray4,		accent,		blue  },
       [SchemeStButton]	= { blue,		gray1,		black },
       [SchemeTagsNorm]	= { gray2,		gray1,		black },
       [SchemeTagsOcc]	= { gray3,		gray1,		black },
       [SchemeTagsSel]	= { gray4,		accent,		black },
       [SchemeLtSymbol]	= { yellow,		gray1,		black },
       [SchemeTitle]	= { gray4,		gray1,		black },
};


static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;

static const unsigned int alphas[][3]      = {
    /*               fg      bg        border*/
    [SchemeNorm]		= { OPAQUE, baralpha, borderalpha },
	[SchemeSel]			= { OPAQUE, baralpha, borderalpha },
    [SchemeStButton]	= { OPAQUE, baralpha, borderalpha },
    [SchemeTagsNorm]	= { OPAQUE, baralpha, borderalpha },
    [SchemeTagsOcc]		= { OPAQUE, baralpha, borderalpha },
    [SchemeTagsSel]		= { OPAQUE, baralpha, borderalpha },
    [SchemeLtSymbol]	= { OPAQUE, baralpha, borderalpha },
    [SchemeTitle]		= { OPAQUE, baralpha, borderalpha },
};

/* autostart */
static const char *const autostart[] = {
	"/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1", NULL,
	"nitrogen", "--restore", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	{ .class = "Lxappearance", .isfloating = 1 },
	{ .class = "Pavucontrol", .isfloating = 1 },
	{ .class = "firefox", .tags = 1 << 1 },
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
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "HHH",      gaplessgrid },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", gray1, "-nf", gray3, "-sb", accent, "-sf", gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *firefoxcmd[]	= { "firefox", NULL };


static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = firefoxcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_b,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscreen, {0} },
	{ MODKEY,                       XK_slash,  togglegaps,     {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
	{ MODKEY,                       XK_Right,  viewnext,       {0} },
	{ MODKEY,                       XK_Left,   viewprev,       {0} },
	{ MODKEY|ShiftMask,             XK_Right,  tagtonext,      {0} },
	{ MODKEY|ShiftMask,             XK_Left,   tagtoprev,      {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkButton,		0,		Button1,	spawn,		{.v = dmenucmd } },
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

