/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx		= 3;
static const unsigned int snap			= 32;
static int floatposgrid_x				= 5;
static int floatposgrid_y				= 5;
static const int attachmode         	= 2; 
static const char *toggle_float_pos		= "50% 50% 80% 80%";

static const unsigned int gappih		= 10;
static const unsigned int gappiv		= 10;
static const unsigned int gappoh		= 20;
static const unsigned int gappov		= 20;
static int smartgaps					= 0;

static const int showbar				= 1;
static const int topbar					= 1;
static const int hidevacanttags			= 0;
#define ICONSIZE (bh - 16) 
#define ICONSPACING 10 

static const char *fonts[]				= { "Iosevka Nerd Font Props:size=12",
											"JetBrainsMono Nerd Font:style=ExtraBold:size=10" };
static const char dmenufont[]			= "Iosevka Nerd Font Propo:size=12";

#include "termcolors.h"

static char normfgcolor[]				= "#bbbbbb";
static char normbgcolor[]				= "#222222";
static char normbordercolor[]			= "#444444";
static char normfloatcolor[]			= "#444444";

static char selfgcolor[]				= "#eeeeee";
static char selbgcolor[]				= "#005577";
static char selbordercolor[]			= "#005577";
static char selfloatcolor[]				= "#005577";

static char scratchnormbordercolor[]	= "#555555";
static char scratchnormfloatcolor[]		= "#555555";
static char scratchselbordercolor[]		= "#c678dd";
static char scratchselfloatcolor[]		= "#c678dd";

static char tagsemptyfgcolor[]			= "#444444";
static char tagsemptybgcolor[]			= "#222222";
static char tagsoccfgcolor[]			= "#bbbbbb";
static char tagsoccbgcolor[]			= "#222222";
static char tagsselfgcolor[]			= "#eeeeee";
static char tagsselbgcolor[]			= "#005577";

static char ltsymbolfgcolor[]			= "#dddd00";
static char ltsymbolbgcolor[]			= "#222222";

static char *colors[][4] = {
       /*						fg					bg					border					float */
       [SchemeNorm]			= { normfgcolor,		normbgcolor,		normbordercolor,		normfloatcolor },
       [SchemeSel]			= { selfgcolor,			selbgcolor,			selbordercolor,			selfloatcolor },
       [SchemeScratchNorm]	= { NULL,				NULL,				scratchnormbordercolor,	scratchnormfloatcolor },
       [SchemeScratchSel]	= { NULL,				NULL,				scratchselbordercolor,	scratchselfloatcolor },
       [SchemeTagsEmpty]	= { tagsemptyfgcolor,	tagsemptybgcolor,	NULL,					NULL },
       [SchemeTagsOcc]		= { tagsoccfgcolor,		tagsoccbgcolor,		NULL,					NULL },
       [SchemeTagsSel]		= { tagsselfgcolor,		tagsselbgcolor,		NULL,					NULL },
       [SchemeLtSymbol]		= { ltsymbolfgcolor,	ltsymbolbgcolor,	NULL,					NULL },
};

static const unsigned int baralpha		= 0xd0;
static const unsigned int borderalpha	= OPAQUE;
static const unsigned int alphas[][4]	= {
    /*               		fg      bg        border       float */
    [SchemeNorm]		= { OPAQUE, baralpha, borderalpha, borderalpha },
	[SchemeSel]  		= { OPAQUE, baralpha, borderalpha, borderalpha },
    [SchemeScratchNorm]	= { OPAQUE, baralpha, borderalpha, borderalpha },
    [SchemeScratchSel]	= { OPAQUE, baralpha, borderalpha, borderalpha },
    [SchemeTagsEmpty]	= { OPAQUE, baralpha, borderalpha, borderalpha },
    [SchemeTagsOcc]		= { OPAQUE, baralpha, borderalpha, borderalpha },
    [SchemeTagsSel]		= { OPAQUE, baralpha, borderalpha, borderalpha },
    [SchemeLtSymbol]	= { OPAQUE, baralpha, borderalpha, borderalpha },
};

static const char *const autostart[] = {
	"/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1", NULL,
	"dunst", NULL,
	"nitrogen", "--restore", NULL,
	"picom", "-b", NULL,
	"dwmblocks", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	{ .class = "Nwg-look", .isfloating = 1 },
	{ .class = "firefox", .tags = 1 << 1 },
	{ .instance = "floaterm", .isfloating = 1, .floatpos = "50% 50% 80% 80%" },
	{ .instance = "spterm", .scratchkey = 't', .isfloating = 1, .floatpos = "50% 50% 80% 80%" },
};

/* layout(s) */
static const float mfact		= 0.50;
static const int nmaster		= 1;
static const int resizehints	= 0;
static const int lockfullscreen	= 1;

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol	arrange function */
	{ "[]=",	tile },    /* first entry is default */
	{ "><>",	NULL },    /* no layout function means floating behavior */
	{ "[M]",	monocle },
	{ "TTT",	bstack },
	{ "HHH",	gaplessgrid },
	{ NULL,		NULL },
};

/* key definitions */
#define Mod Mod4Mask
#define Shift ShiftMask
#define Ctrl ControlMask
#define Alt Mod1Mask

#define TAGKEYS(KEY,TAG) \
	{ Mod,				KEY,	view,			{.ui = 1 << TAG} }, \
	{ Mod|Ctrl,			KEY,	toggleview,		{.ui = 1 << TAG} }, \
	{ Mod|Shift,		KEY,	tag,			{.ui = 1 << TAG} }, \
	{ Mod|Ctrl|Shift,	KEY,	toggletag,		{.ui = 1 << TAG} },

#define SCRATCHKEYS(KEY,CMD) \
	{ Mod,			KEY,		togglescratch,		{.v = CMD} }, \
	{ Mod|Shift,	KEY,		removescratch,		{.v = CMD} }, \
	{ Mod|Ctrl,		KEY,		setscratch,			{.v = CMD} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static const char *dmenucmd[]	= { "dmenu_run", "-p", "Run: ", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *roficmd[]	= { "rofi", "-show", "drun", NULL };
static const char *termcmd[]	= { "ghostty", NULL };
static const char *firefoxcmd[]	= { "firefox", NULL };

static const char *volmutecmd[]	= { "volume", "--toggle", NULL };
static const char *voldowncmd[]	= { "volume", "--dec", NULL };
static const char *volupcmd[]	= { "volume", "--inc", NULL };
static const char *micmutecmd[]	= { "volume", "--toggle-mic", NULL };
static const char *bldowncmd[]	= { "brightness", "--dec", NULL };
static const char *blupcmd[]	= { "brightness", "--inc", NULL };


static const char *sptermcmd[]	= { "t", "ghostty", "--x11-instance-name=spterm", "--title=Scratchpad", NULL };

static const Key keys[] = {
	/* modifier			key				function				argument */
	{ Mod,				XK_p,			spawn,					{.v = dmenucmd } },
	{ Mod,				XK_space,		spawn,					{.v = roficmd } },
	{ Mod,				XK_Return,		spawn,					{.v = termcmd } },
	{ Mod,				XK_w,			spawn,					{.v = firefoxcmd } },

	{ 0,				XK_F1,			spawn,					{.v = volmutecmd } },
	{ 0,				XK_F2,			spawn,					{.v = voldowncmd } },
	{ 0,				XK_F3,			spawn,					{.v = volupcmd } },
	{ 0,				XK_F4,			spawn,					{.v = micmutecmd } },
	{ 0,				XK_F5,			spawn,					{.v	 = bldowncmd } },
	{ 0,				XK_F6,			spawn,					{.v= blupcmd } },

	{ Mod,				XK_j,			focusstack,				{.i = +1 } },
	{ Mod,				XK_k,			focusstack,				{.i = -1 } },
	{ Mod|Shift,		XK_j,			rotatestack,			{.i = +1 } },
	{ Mod|Shift,		XK_k,			rotatestack,			{.i = -1 } },
	{ Mod,				XK_i,			incnmaster,				{.i = +1 } },
	{ Mod,				XK_d,			incnmaster,				{.i = -1 } },
	{ Mod,				XK_h,			setmfact,				{.f = -0.05} },
	{ Mod,				XK_l,			setmfact,				{.f = +0.05} },
	{ Mod|Shift,		XK_h,			setcfact,				{.f = +0.25} },
	{ Mod|Shift,		XK_l,			setcfact,				{.f = -0.25} },
	{ Mod|Shift,		XK_o,			setcfact,				{.f =	0.00} },

	{ Mod,				XK_q,			killclient,				{0} },
	{ Mod|Shift,		XK_q,			quit,					{0} },
	{ Mod|Shift,		XK_r,			quit,					{1} }, 

	{ Mod,				XK_t,			setlayout,				{.v = &layouts[0]} },
	{ Mod,				XK_f,			setlayout,				{.v = &layouts[1]} },
	{ Mod,				XK_m,			setlayout,				{.v = &layouts[2]} },
	{ Mod,				XK_b,			setlayout,				{.v = &layouts[3]} },
	{ Mod,				XK_g,			setlayout,				{.v = &layouts[4]} },

	{ Mod|Shift,		XK_b,			togglebar,				{0} },
	{ Mod|Shift,		XK_space,		togglefloating, 		{0} },
	{ Mod|Shift,		XK_f,			togglefullscr,			{0} },
	{ Mod|Shift,		XK_g,			togglegaps,				{0} },
	{ Mod|Shift,		XK_x,			xrdb,					{.v = NULL } },

	{ Mod,				XK_0,			view,					{.ui = ~0 } },
	{ Mod|Shift,		XK_0,			tag,					{.ui = ~0 } },
	{ Mod,				XK_Right,		viewnext,				{0} },
	{ Mod,				XK_Left,		viewprev,				{0} },
	{ Mod|Shift,		XK_Right,		tagtonext,				{0} },
	{ Mod|Shift,		XK_Left,		tagtoprev,				{0} },

	SCRATCHKEYS(		XK_grave,								sptermcmd)

	TAGKEYS(			XK_1,									0)
	TAGKEYS(			XK_2,									1)
	TAGKEYS(			XK_3,									2)
	TAGKEYS(			XK_4,									3)
	TAGKEYS(			XK_5,									4)
	TAGKEYS(			XK_6,									5)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click			event mask	button		function			argument */
	{ ClkLtSymbol,		0,			Button1,	setlayout,			{0} },
	{ ClkLtSymbol,		0,			Button3,	setlayout,			{.v = &layouts[2]} },

	{ ClkWinTitle,		0,			Button2,	zoom,				{0} },

	{ ClkStatusText,	0,			Button1,	sigstatusbar,		{.i = 1} },
	{ ClkStatusText,	0,			Button2,	sigstatusbar,		{.i = 2} },
	{ ClkStatusText,	0,			Button3,	sigstatusbar,		{.i = 3} },
	{ ClkStatusText,	0,			Button4,	sigstatusbar,		{.i = 4} },
	{ ClkStatusText,	0,			Button5,	sigstatusbar,		{.i = 5} },

	{ ClkClientWin,		Mod,		Button1,	movemouse,			{0} },
	{ ClkClientWin,		Mod,		Button2,	togglefloating,		{0} },
	{ ClkClientWin,		Mod,		Button3,	resizemouse,		{0} },

	{ ClkTagBar,		0,			Button1,	view,				{0} },
	{ ClkTagBar,		0,			Button3,	toggleview,			{0} },
	{ ClkTagBar,		Mod,		Button1,	tag,				{0} },
	{ ClkTagBar,		Mod,		Button3,	toggletag,			{0} },
};

