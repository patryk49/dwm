/* See LICENSE file for copyright and license details. */

/* home path */
#define HOME_PATH "/home/patryk"


/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
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
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           0,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol    arrange function */
	{ "[ ]",     tile },    /* first entry is default */
	{ "[/]",     dwindle },
//	{ "><",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,              KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
//	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static const char *cmd_options[] =    { HOME_PATH"/.options_run", NULL };
static const char *cmd_vol_mute[] =   { "amixer", "set", "Master", "toggle", NULL };
static const char *cmd_vol_down[] =   { "amixer", "set", "Master", "2dB-", NULL };
static const char *cmd_vol_up[] =     { "amixer", "set", "Master", "2dB+", NULL };
static const char *cmd_mic_mute[] =   { "amixer", "set", "Mic", "toggle", NULL };
static const char *cmd_br_down[] =    { "setbr", "-200", NULL };
static const char *cmd_br_up[] =      { "setbr", "+200", NULL };
static const char *cmd_scr_full[] =   { "scrot", HOME_PATH"/screens/%Y-%m-%d.png", NULL };
static const char *cmd_scr_select[] = { "scrot", "-s", HOME_PATH"/screens/%Y-%m-%d.png", NULL };
static const char *cmd_browser[] =    { "brave", NULL };
static const char *cmd_calculator[] = { "st", "-ig", "40x8", "-f", "monospace:size=14", "-e", "kalk", "-d", NULL };

static Key keys[] = {
	/* modifier                     key           function        argument */
	{ MODKEY,                       XK_b,         togglebar,      {0} },
	{ MODKEY,                       XK_j,         focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,         focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,         setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,         setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,    zoom,           {0} },
//	{ MODKEY,                       XK_Tab,       view,           {0} },
	{ MODKEY,                       XK_x,         killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,         quit,           {0} },
	{ MODKEY,                       XK_t,         setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_space,     setlayout,      {0} },
	{ MODKEY,                       XK_space,     togglefloating, {0} },
	{ MODKEY,                       XK_0,         view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,         tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,     incnmaster,      {.i = -1 } },
	{ MODKEY,                       XK_period,    incnmaster,      {.i = +1 } },
//	{ MODKEY,                       XK_comma,     focusmon,       {.i = -1 } },
//	{ MODKEY,                       XK_period,    focusmon,       {.i = +1 } },
//	{ MODKEY|ShiftMask,             XK_comma,     tagmon,         {.i = -1 } },
//	{ MODKEY|ShiftMask,             XK_period,    tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                         0)
	TAGKEYS(                        XK_2,                         1)
	TAGKEYS(                        XK_3,                         2)
	TAGKEYS(                        XK_4,                         3)
	TAGKEYS(                        XK_5,                         4)
	TAGKEYS(                        XK_6,                         5)
	TAGKEYS(                        XK_7,                         6)
	TAGKEYS(                        XK_8,                         7)
	TAGKEYS(                        XK_9,                         8)
	{ MODKEY,                       XK_p,         spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,    spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_t,         spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,         spawn,          {.v = cmd_browser } },
	{ MODKEY|ShiftMask,             XK_c,         spawn,          {.v = cmd_calculator } },
	{ MODKEY,                       XK_o,         spawn,          {.v = cmd_options } },
	{ MODKEY|ShiftMask,             XK_m,         spawn,          {.v = cmd_vol_mute } },
	{ MODKEY|ShiftMask,             XK_f,         spawn,          {.v = cmd_scr_full } },
	{ MODKEY|ShiftMask,             XK_s,         spawn,          {.v = cmd_scr_select } },
	{ 0,                            0x1008ff12,   spawn,          {.v = cmd_vol_mute } },
	{ 0,                            0x1008ff11,   spawn,          {.v = cmd_vol_down } },
	{ 0,                            0x1008ff13,   spawn,          {.v = cmd_vol_up } },
	{ 0,                            0x1008ffb2,   spawn,          {.v = cmd_mic_mute } },
	{ 0,                            0x1008ff03,   spawn,          {.v = cmd_br_down } },
	{ 0,                            0x1008ff02,   spawn,          {.v = cmd_br_up } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
//	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
//	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
//	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
//	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

