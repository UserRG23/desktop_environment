//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/

	{"", "~/dwmblocks/script/dwmwifi",					1,		0},
	{"", "~/dwmblocks/script/dwmvol",					1,		0},
	{"", "~/dwmblocks/script/dwmkeyboard",				1,		0},
	{"", "~/dwmblocks/script/dwmpow",				30,		0},
	{"", "~/dwmblocks/script/dwmpowon",          			1,		0},
	{"", "~/dwmblocks/script/dwmclock",				30,		0},

};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " ";
static unsigned int delimLen = 5;

