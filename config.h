
/* Constants */
#define TERMINAL "kitty"
#define TERMCLASS "St"
#define BROWSER "google-chrome"

/* appearance */
// static unsigned int borderpx  = 3;        /* border pixel of windows */
// static unsigned int snap      = 32;       /* snap pixel */
// static unsigned int gappih    = 20;       /* horiz inner gap between windows */
// static unsigned int gappiv    = 10;       /* vert inner gap between windows */
// static unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
// static unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */

const static unsigned int gapmodifier = 5;
static unsigned int borderpx  = 3;                      /* border pixel of windows */
static unsigned int snap      = 5 * gapmodifier;       /* snap pixel */
static unsigned int gappih    = 6 * gapmodifier;       /* horiz inner gap between windows */
static unsigned int gappiv    = 3 * gapmodifier;       /* vert inner gap between windows */
static unsigned int gappoh    = 6 * gapmodifier;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 4 * gapmodifier;       /* vert outer gap between windows and screen edge */


static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static int showbar            = 0;        /* 0 means no bar */
static int topbar             = 0;        /* 0 means bottom bar */
//static char *fonts[]          = { "monospace:size=10", "NotoColorEmoji:pixelsize=10:antialias=true:autohint=true"  };
static char *fonts[]          = { "monospace:size=12", "System San Francisco Display:pixelsize=12:antialias=true:autohint=true", "-misc-kochi gothic-medium-r-normal-*-12-0-0-0-p-0-jisx0201.1976-0"  };
static char normbgcolor[]           = "#1a1b26";  // Darker background
//static char normbordercolor[]       = "#0f172a";  // Dark Marine Border
static char normbordercolor[]       = "#24283b";  // from Chrome
                                                  //
static char normfgcolor[]           = "#c0caf5";  // Foreground text
static char selfgcolor[]            = "#a9b1d6";  // Selected text
//static char selbordercolor[]        = "#7aa2f7";  // Light Selected border
//static char selbordercolor[]       = "#12131a";  // Dark Selected Border
static char selbordercolor[]       = "#1a1b26";  // Selected Border
//static char selbordercolor[]       = "#414868";  // Selected Border
//This color was messing up the bar so I just put the normal bg color                                                   // 
//static char selbgcolor[]            = "#2ac3de";  // Selected background
static char selbgcolor[]            = "#1a1b26";  // Selected background
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spcalc",      spcmd2},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
//static const char *tags[] = { "!", "{", "[", "(", "=", "&", ")", "]", "}" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class                instance        title       	 tags mask    isfloating   isterminal  noswallow  monitor */
	{ "Gimp",               NULL,           NULL,            1 << 8,      0,           0,          0,         -1 },
	{ TERMCLASS,            NULL,           NULL,       	 0,           0,           1,          0,         -1 },
	{ NULL,                 NULL,           "Event Tester",  0,           0,           0,          1,         -1 },
	{ TERMCLASS,            "floatterm",    NULL,       	 0,           1,           1,          0,         -1 },
	{ TERMCLASS,            "bg",           NULL,       	 1 << 7,      0,           1,          0,         -1 },
	{ TERMCLASS,            "spterm",       NULL,       	 SPTAG(0),    1,           1,          0,         -1 },
	{ TERMCLASS,            "spcalc",       NULL,       	 SPTAG(1),    1,           1,          0,         -1 },
	{ "discord",            NULL,           NULL,       	 1 << 7,      0,           0,          0,         -1 },
	{ "telegram-desktop",   NULL,           NULL,       	 1 << 7,      0,           0,          0,         -1 },
    { "google-chrome",      NULL,           NULL,            0,           0,          -1,          0,         -1 },
    //{ "GtkFileChooserDialog", NULL, NULL, 0, 1, -1 }


};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
    { "[M]",	monocle },              /* All windows on top of eachother */
	{ "[D]",	deck },	                /* Master on left, slaves in monocle-like mode on right */

	{ "[]=",	tile },	                /* Default: Master on left, slaves on right */
	{ "TTT",	bstack },               /* Master on top, slaves on bottom */

	{ "[@]",	spiral },               /* Fibonacci spiral */
	{ "[\\]",	dwindle },              /* Decreasing in size right and leftward */

	{ "|M|",	centeredmaster },               /* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster },       /* Same but master floats */

	{ "><>",	NULL },	                /* no layout function means floating behavior */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_n,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_p,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "color0",		STRING,	&normbordercolor },
		{ "color8",		STRING,	&selbordercolor },
		{ "color0",		STRING,	&normbgcolor },
		{ "color4",		STRING,	&normfgcolor },
		{ "color0",		STRING,	&selfgcolor },
		{ "color4",		STRING,	&selbgcolor },
		{ "borderpx",		INTEGER, &borderpx },
		{ "snap",		INTEGER, &snap },
		{ "showbar",		INTEGER, &showbar },
		{ "topbar",		INTEGER, &topbar },
		{ "nmaster",		INTEGER, &nmaster },
		{ "resizehints",	INTEGER, &resizehints },
		{ "mfact",		FLOAT,	&mfact },
		{ "gappih",		INTEGER, &gappih },
		{ "gappiv",		INTEGER, &gappiv },
		{ "gappoh",		INTEGER, &gappoh },
		{ "gappov",		INTEGER, &gappov },
		{ "swallowfloating",	INTEGER, &swallowfloating },
		{ "smartgaps",		INTEGER, &smartgaps },
};

#include <X11/XF86keysym.h>
#include "shiftview.c"

static const Key keys[] = {
	/* modifier                     key            function                argument */
	STACKKEYS(MODKEY,                              focus)
	STACKKEYS(MODKEY|ShiftMask,                    push)
	{ MODKEY,			XK_grave,      spawn,	               {.v = (const char*[]){ "dmenuunicode", NULL } } },
    
//	TAGKEYS(			XK_1,          0)
//	TAGKEYS(			XK_2,          1)
//	TAGKEYS(			XK_3,          2)
//	TAGKEYS(			XK_4,          3)
//	TAGKEYS(			XK_5,          4)
//	TAGKEYS(			XK_6,          5)
//	TAGKEYS(			XK_7,          6)
//	TAGKEYS(			XK_8,          7)
//	TAGKEYS(			XK_9,          8)

	TAGKEYS(			XK_exclam,          0)
	TAGKEYS(			XK_braceleft,          1)
	TAGKEYS(			XK_bracketleft,          2)
	TAGKEYS(			XK_parenleft,          3)
	TAGKEYS(			XK_equal,          4)
	TAGKEYS(			XK_ampersand,          5)
	TAGKEYS(			XK_parenright,          6)
	TAGKEYS(			XK_bracketright,          7)
	TAGKEYS(			XK_braceright,          8)

	//{ MODKEY,			XK_0,	       view,                   {.ui = ~0 } },
	//{ MODKEY,			XK_asterisk,	       view,                   {.ui = ~0 } },
	//{ MODKEY|ShiftMask, XK_asterisk,	       tag,                    {.ui = ~0 } },
	//{ MODKEY,			XK_minus,      spawn,                  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof dwmblocks)") },
	//{ MODKEY|ShiftMask, XK_minus,      spawn,                  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%-; kill -44 $(pidof dwmblocks)") },
	//{ MODKEY,			XK_equal,      spawn,                  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof dwmblocks)") },
	//{ MODKEY|ShiftMask, XK_equal,      spawn,                  SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%+; kill -44 $(pidof dwmblocks)") },
	//{ MODKEY,			XK_BackSpace,  spawn,                  {.v = (const char*[]){ "sysact", NULL } } },
	//{ MODKEY|ShiftMask,		XK_BackSpace,  spawn,                  {.v = (const char*[]){ "sysact", NULL } } },

    // 1 - First Row
	{ MODKEY,			XK_Tab,        view,                   {0} },
	//{ MODKEY|ShiftMask,		XK_Tab,	       spawn,                  SHCMD("") }, 
	{ MODKEY|ShiftMask,			XK_q,          killclient,             {0} },
	{ MODKEY,			XK_w,          spawn,                  {.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY|ShiftMask,		XK_w,          spawn,              SHCMD("~/dotfiles/.scripts/set_wallpaper.sh") },
	//{ MODKEY,			XK_e,          spawn,                  SHCMD() },
	//{ MODKEY|ShiftMask,		XK_e,          spawn,          SHCMD() },
	//{ MODKEY,			XK_r,          spawn,                  SHCMD() },
	//{ MODKEY|ShiftMask,		XK_r,          spawn,          SHCMD() },
    { MODKEY,			XK_u,          setlayout,              {.v = &layouts[0]} }, /* monocle */
    { MODKEY|ShiftMask,		XK_u,          setlayout,          {.v = &layouts[1]} }, /* deck */
    { MODKEY,			XK_t,          setlayout,              {.v = &layouts[2]} }, /* tile */
    { MODKEY|ShiftMask,		XK_t,          setlayout,          {.v = &layouts[3]} }, /* bstack */
    { MODKEY,			XK_y,          setlayout,              {.v = &layouts[4]} }, /* spiral */
    { MODKEY|ShiftMask,		XK_y,          setlayout,          {.v = &layouts[5]} }, /* dwindle */
	{ MODKEY,			XK_i,          setlayout,              {.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,		XK_i,          setlayout,          {.v = &layouts[7]} }, /* centeredfloatingmaster */
	{ MODKEY,			XK_o,          incnmaster,             {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,          incnmaster,         {.i = -1 } },

    // Screen Layouts
	{ MODKEY|ControlMask,			XK_p,          spawn,              SHCMD("~/.screenlayout/stacked.sh") },
	{ MODKEY|ShiftMask,		        XK_p,          spawn,              SHCMD("~/dotfiles/.scripts/cycle_displays.sh") },
	{ MODKEY|ShiftMask|ControlMask, XK_p,          spawn,              SHCMD("~/.screenlayout/notebook.sh") },
	//{ MODKEY,			            XK_backslash,  view,                   {0} },
	//{ MODKEY|ShiftMask,		XK_backslash,  spawn,          SHCMD() }, 

    // 2-Second Row
	{ MODKEY,			            XK_a,          togglegaps,             {0} },
	{ MODKEY|ShiftMask,		        XK_a,          defaultgaps,            {0} },
	{ MODKEY,			            XK_s,          togglesticky,           {0} },
	{ MODKEY|ShiftMask,		        XK_s,          spawn,                  SHCMD("~/dotfiles/.scripts/ssh-list.sh") },
	{ MODKEY,			            XK_d,          spawn,                  SHCMD("rofi -modi drun,run -show drun" ) },
	{ MODKEY,			            XK_c,          spawn,                  {.v = (const char*[]){ "mate-calc", NULL } } },
	//{ MODKEY|ShiftMask,		XK_d,          spawn,                  {.v = (const char*[]){ "passmenu", NULL } } },
	{ MODKEY,			            XK_f,          togglefullscr,          {0} },
	{ MODKEY|ShiftMask,		        XK_f,          setlayout,              {.v = &layouts[8]} },
	{ MODKEY,			            XK_g,          shiftview,              { .i = -1 } },
	{ MODKEY|ShiftMask,		        XK_g,          shifttag,               { .i = -1 } },
	{ MODKEY,			            XK_h,          setmfact,               {.f = -0.05} },
	/* J and K are automatically bound above in STACKEYS */
	{ MODKEY,			            XK_l,          setmfact,               {.f = +0.05} },
	{ MODKEY,			            XK_semicolon,  shiftview,              { .i = 1 } },
	{ MODKEY|ShiftMask,		        XK_semicolon,  shifttag,               { .i = 1 } },
	{ MODKEY,			            XK_apostrophe, togglescratch,          {.ui = 1} },
	/* { MODKEY|ShiftMask,		XK_apostrophe, spawn,                  SHCMD("") }, */
	{ MODKEY|ShiftMask,		        XK_apostrophe, togglesmartgaps,        {0} },
	{ MODKEY,			            XK_Return,     spawn,                  {.v = termcmd } },
	{ MODKEY|ShiftMask,		        XK_Return,     togglescratch,          {.ui = 0} },

    // 3 - Third Row

	{ MODKEY,			            XK_z,          incrgaps,               {.i = +3 } },
	/* { MODKEY|ShiftMask,		XK_z,          spawn,                  SHCMD("") }, */
	{ MODKEY,			            XK_x,          incrgaps,               {.i = -3 } },
	{ MODKEY|ShiftMask,		        XK_x,          spawn,                  SHCMD("i3lock -f -c 1A1B26 -i ~/.wallpapers/.not-using/tokyo.png && systemctl suspend") }, 
	//{ MODKEY,			XK_c,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "profanity", NULL } } },
	{ MODKEY,			            XK_c,          spawn,                  {.v = (const char*[]){ "mate-calc", NULL } } },
    { MODKEY|ShiftMask,		        XK_c,          spawn,              SHCMD("~/dotfiles/.scripts/select-quotes.sh") }, 
    { MODKEY|ShiftMask|ControlMask,	XK_c,          spawn,  SHCMD("~/dotfiles/.scripts/youtube-cross-fade-start.sh") }, 
	/* V is automatically bound above in STACKKEYS */
	{ MODKEY,			            XK_b,          togglebar,              {0} },
    { MODKEY|ShiftMask,		        XK_b,          spawn,              SHCMD("~/dotfiles/.scripts/bt_menu.sh") }, 
	{ MODKEY,			            XK_c,          spawn,                  SHCMD("dunstctl close-all")},
	{ MODKEY|ShiftMask,	            XK_n,          spawn,                  SHCMD("python3 ~/dotfiles/.scripts/showtime.py") },
	//{ MODKEY,			            XK_m,          spawn,                  SHCMD() },
	{ MODKEY|ShiftMask,		        XK_m,          spawn,              SHCMD("/home/andre/dotfiles/.scripts/macros/venv/bin/python ~/dotfiles/.scripts/macros/fightcade_macro.py") },
	{ MODKEY,		                XK_m,          spawn,              SHCMD("/home/andre/dotfiles/.scripts/macros/venv/bin/python ~/dotfiles/.scripts/macros/fightcade_macro_notebook.py") },
    { MODKEY,			            XK_comma,      spawn,                  SHCMD("/home/andre/dotfiles/.scripts/macros/venv/bin/python ~/dotfiles/.scripts/macros/getCursorPosition.py") },
    { MODKEY|ShiftMask,			    XK_comma,      spawn,          SHCMD("/home/andre/dotfiles/.scripts/macros/venv/bin/python ~/dotfiles/.scripts/macros/shorys.sh") },
    { MODKEY,			            XK_period,     spawn,                  SHCMD("~/dotfiles/.scripts/youtube-download.sh") },
    //{ MODKEY|ShiftMask,		XK_period,     spawn,          SHCMD() },
 
	{ MODKEY,			            XK_j,       focusmon,               {.i = -1 } },
	{ MODKEY|ShiftMask,		        XK_j,       tagmon,                 {.i = -1 } },
	{ MODKEY,			            XK_k,      focusmon,               {.i = +1 } },
	{ MODKEY|ShiftMask,		        XK_k,      tagmon,                 {.i = +1 } },

	{ MODKEY,			            XK_Page_Up,    shiftview,              { .i = -1 } },
	{ MODKEY|ShiftMask,		        XK_Page_Up,    shifttag,               { .i = -1 } },
	{ MODKEY,			            XK_Page_Down,  shiftview,              { .i = +1 } },
	{ MODKEY|ShiftMask,		        XK_Page_Down,  shifttag,               { .i = +1 } },
	//{ MODKEY,			XK_Insert,     spawn,                  SHCMD("xdotool type $(grep -v '^#' ~/.local/share/larbs/snippets | dmenu -i -l 50 | cut -d' ' -f1)") },

	{ MODKEY,		            	XK_F1,         spawn,                  SHCMD("python3 ~/dotfiles/.scripts/showtime.py open_music") },
	{ MODKEY,		                XK_F2,         spawn,                  SHCMD("python3 ~/dotfiles/.scripts/showtime.py open_notes_obsidian") },
	{ MODKEY,		                XK_F3,         spawn,                  SHCMD("python3 ~/dotfiles/.scripts/showtime.py open_dev_setup") },
	{ MODKEY,		                XK_F4,         spawn,                  SHCMD("python3 ~/dotfiles/.scripts/showtime.py ascii_image_converter") },
	{ MODKEY,		                XK_F5,         spawn,                   SHCMD("python3 ~/dotfiles/.scripts/showtime.py spiral") },
	{ MODKEY,		                XK_F6,         spawn,                  SHCMD("python3 ~/dotfiles/.scripts/showtime.py curtains") },
	{ MODKEY,		                XK_F7,         spawn,                  SHCMD("python3 ~/dotfiles/.scripts/showtime.py open_music_thematic") },
	{ MODKEY,		                XK_F8,         spawn,                  SHCMD("python3 ~/dotfiles/.scripts/showtime.py open_music") },
	{ MODKEY,		                XK_F9,         spawn,                  SHCMD("python3 ~/dotfiles/.scripts/showtime.py open_music") },
	{ MODKEY,		                XK_F10,        spawn,                  {.v = (const char*[]){ "unmounter", NULL } } },
	{ MODKEY,		                XK_F11,        spawn,                  SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
	{ MODKEY,		                XK_F12,        spawn,                  SHCMD("remaps") },
	{ MODKEY,		                XK_space,      zoom,                   {0} },
	{ MODKEY|ShiftMask,             XK_space,      togglefloating,         {0} },

	//{ 0,				XK_Print,      spawn,                  SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ 0,				            XK_Print,      spawn,                  SHCMD("~/dotfiles/.scripts/screenshot.sh") },
	//{ ShiftMask,			XK_Print,      spawn,                  {.v = (const char*[]){ "maimpick", NULL } } },
	//{ MODKEY,			XK_Print,      spawn,		       {.v = (const char*[]){ "~/dotfiles/.scripts/screenshot.sh" } } },
	//{ MODKEY|ShiftMask,		XK_Print,      spawn,                  {.v = (const char*[]){ "dmenurecord", "kill", NULL } } },
	//{ MODKEY,			XK_Delete,     spawn,                  {.v = (const char*[]){ "dmenurecord", "kill", NULL } } },
	//{ MODKEY,			XK_Scroll_Lock, spawn,                 SHCMD("killall screenkey || screenkey &") },

	{ 0, XF86XK_AudioMute,                         spawn,                  SHCMD("~/dotfiles/.scripts/volume-notify.sh mute") },
	{ MODKEY, XF86XK_AudioMute,                    spawn,                  SHCMD("~/dotfiles/.scripts/toggle-audio-profile.sh") },
	{ MODKEY, XK_F9,                               spawn,                  SHCMD("~/dotfiles/.scripts/cycle-audio.sh") },
	{ 0, XF86XK_AudioRaiseVolume,                  spawn,                  SHCMD("~/dotfiles/.scripts/volume-notify.sh up") },
	{ ShiftMask, XF86XK_AudioRaiseVolume,          spawn,                  SHCMD("~/dotfiles/.scripts/volume-notify.sh up20") },
	{ 0, XF86XK_AudioLowerVolume,                  spawn,                  SHCMD("~/dotfiles/.scripts/volume-notify.sh down") },
    { ShiftMask, XF86XK_AudioLowerVolume,          spawn,                  SHCMD("~/dotfiles/.scripts/volume-notify.sh down20") },
	//{ 0, XF86XK_AudioPrev,                         spawn,                  {.v = (const char*[]){ "mpc", "prev", NULL } } },
	//{ 0, XF86XK_AudioNext,                         spawn,                  {.v = (const char*[]){ "mpc",  "next", NULL } } },
	//{ 0, XF86XK_AudioPause,                        spawn,                  {.v = (const char*[]){ "mpc", "pause", NULL } } },
	//{ 0, XF86XK_AudioPlay,                         spawn,                  {.v = (const char*[]){ "mpc", "play", NULL } } },
	//{ 0, XF86XK_AudioStop,                         spawn,                  {.v = (const char*[]){ "mpc", "stop", NULL } } },
	//{ 0, XF86XK_AudioRewind,                       spawn,                  {.v = (const char*[]){ "mpc", "seek", "-10", NULL } } },
	//{ 0, XF86XK_AudioForward,                      spawn,                  {.v = (const char*[]){ "mpc", "seek", "+10", NULL } } },
	//{ 0, XF86XK_AudioMedia,                        spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "ncmpcpp", NULL } } },
	//{ 0, XF86XK_AudioMicMute,                      spawn,                  SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	//{ 0, XF86RFKill,                      spawn,                  SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	/* { 0, XF86XK_PowerOff,                       spawn,                  {.v = (const char*[]){ "sysact", NULL } } }, */
	{ 0, XF86XK_Calculator,                        spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "bc", "-l", NULL } } },
	{ 0, XF86XK_Sleep,                             spawn,                  {.v = (const char*[]){ "sudo", "-A", "zzz", NULL } } },
	{ 0, XF86XK_WWW,                               spawn,                  {.v = (const char*[]){ BROWSER, NULL } } },
	{ 0, XF86XK_DOS,                               spawn,                  {.v = termcmd } },
	{ 0, XF86XK_ScreenSaver,                       spawn,                  SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0, XF86XK_TaskPane,                          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "htop", NULL } } },
	{ 0, XF86XK_Mail,                              spawn,                  SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_MyComputer,                        spawn,                  {.v = (const char*[]){ TERMINAL, "-e",  "lfub",  "/", NULL } } },
	/* { 0, XF86XK_Battery,                        spawn,                  SHCMD("") }, */
	{ 0, XF86XK_Launch1,                           spawn,                  {.v = (const char*[]){ "xset", "dpms", "force", "off", NULL } } },
	{ 0, XF86XK_TouchpadToggle,                    spawn,                  SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,                       spawn,                  {.v = (const char*[]){ "synclient", "TouchpadOff=1", NULL } } },
	{ 0, XF86XK_TouchpadOn,                        spawn,                  {.v = (const char*[]){ "synclient", "TouchpadOff=0", NULL } } },
	{ 0, XF86XK_MonBrightnessUp,                   spawn,                  {.v = (const char*[]){ "xbacklight", "-inc", "15", NULL } } },
	{ 0, XF86XK_MonBrightnessDown,                 spawn,                  {.v = (const char*[]){ "xbacklight", "-dec", "15", NULL } } },

	/* { MODKEY|Mod4Mask,           XK_h,          incrgaps,               {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,           XK_l,          incrgaps,               {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask, XK_h,          incrogaps,              {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask, XK_l,          incrogaps,              {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask, XK_h,        incrigaps,              {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask, XK_l,        incrigaps,              {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask, XK_0,          defaultgaps,            {0} }, */
	/* { MODKEY,                    XK_y,          incrihgaps,             {.i = +1 } }, */
	/* { MODKEY,                    XK_o,          incrihgaps,             {.i = -1 } }, */
	/* { MODKEY|ControlMask,        XK_y,          incrivgaps,             {.i = +1 } }, */
	/* { MODKEY|ControlMask,        XK_o,          incrivgaps,             {.i = -1 } }, */
	/* { MODKEY|Mod4Mask,           XK_y,          incrohgaps,             {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,           XK_o,          incrohgaps,             {.i = -1 } }, */
	/* { MODKEY|ShiftMask,          XK_y,          incrovgaps,             {.i = +1 } }, */
	/* { MODKEY|ShiftMask,          XK_o,          incrovgaps,             {.i = -1 } }, */

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask           button          function        argument */
#ifndef __OpenBSD__
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,                   Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,                   Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,                   Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,                   Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,           Button1,        sigdwmblocks,   {.i = 6} },
#endif
	{ ClkStatusText,        ShiftMask,           Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/personal/projects/dwmblocks/config.h") },
	{ ClkClientWin,         MODKEY,              Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,              Button2,        defaultgaps,    {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkClientWin,		MODKEY,		     Button4,	     incrgaps,       {.i = +1} },
	{ ClkClientWin,		MODKEY,		     Button5,	     incrgaps,       {.i = -1} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
	{ ClkTagBar,		0,		     Button4,	     shiftview,      {.i = -1} },
	{ ClkTagBar,		0,		     Button5,	     shiftview,      {.i = 1} },
	{ ClkRootWin,		0,		     Button2,	     togglebar,      {0} },
};
