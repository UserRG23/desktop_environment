//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/

	{"", "dwmwifi",					1,		0},
	{"", "dwmbr",					0,		2},
	{"", "dwmvol",					0,		1},
	{"", "dwmkeyboard",				0,		10},
	{"", "dwmpow",			    	30,		0},
	{"", "dwmpowon",          		1,		0},
	{"", "dwmclock",		    	30,		0},

};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " ";
static unsigned int delimLen = 5;

