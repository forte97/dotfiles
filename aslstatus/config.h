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
        { uptime,   "^B8^^C15^Up: %s ",	 NULL, 1 _MIN, END},
        { netspeed_rx, "^B15^^C8^  %sB/s ", "eth0", 2 _SEC, END}, 
        { run_command, "^B8^^C15^ 墳: %s%% ", "pamixer --get-volume", 2 _SEC, END},
        { cpu_perc, "^B15^^C8^  CPU: %s%% ",   NULL, 2 _SEC, END},
        { ram_used, "^B8^^C15^  RAM: %sB ",    NULL, 2 _SEC, END},
        { datetime, "^B15^^C8^  %s ", "%b %d %a", 1 _MIN, END},
        { datetime, "^B8^^C15^  %s  ", "%I:%M %p", 1 _SEC, END},

#if USE_X && USE_XKB
/* { keymap,		"-[ %s] ",	NULL,		 0,	END }, */
#endif

};
/* clang-format on */
