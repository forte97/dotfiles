/*
 * for components info see: wiki/COMPONENTS.md
 *
 * extra configs in can be found in `components_config.h`
 */

/* for usleep */
#define _SEC *1000
#define _MIN *(60 _SEC)
#define _HR  *(60 _MIN)

/* interval to run only once */
#define ONCE ((unsigned int)-1)

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 256
/*
 * if you want to change buffer size for each segment,
 * then change `BUFF_SZ` in lib/util.h
 */

#define IFC "wlan0" /* wifi interface */

/* clang-format off */
static struct arg_t args[] = {

/* function		format		argument	interval (in ms) */

#if USE_X
/* { bspwm_ws,		" [ %s ]%%{r}",	NULL,		0,	END }, */
#endif
        { username, "^B0^^C6^%s@",     		 NULL,	ONCE,	END},
        { hostname, "%s ",      		 NULL,	ONCE,	END},
        { uptime,   "^B6^^C0^ Uptime: %s ",	 NULL,	1 _MIN,	END},
        { run_command, "^B0^^C6^  : %s ",	 "nmcli con show --active | awk 'NR==2{print $1}'",	2 _SEC,	END},
        { run_command, "^B6^^C0^ 墳 : %s%% ",	 "pamixer --get-volume",	2 _SEC,		END},
        { cpu_perc, "^B0^^C6^ CPU: %s%% ",     	 NULL,	2 _SEC,	END},
        { ram_used, "^B6^^C0^ MEM: %sB ",        NULL,	2 _SEC, END},
        { datetime, "^B0^^C6^  %s ",          	 "%b %d  %a",	2 _SEC,	END},
        { datetime, "^B6^^C0^   %s   ",		 "%I:%M %p"	,2 _SEC,	END},

#if USE_X && USE_XKB
/* { keymap,		"-[ %s] ",	NULL,		 0,	END }, */
#endif

};
/* clang-format on */
