# ASLSTATUS

---
if you found any issues report it here

for all other questions, feel free to ask in matrix
[#aslstatus:matrix.org](https://matrix.to/#/#aslstatus:matrix.org)

---
![demo](https://i.ibb.co/r5PYRj8/Demo.gif)

---
# instalation
### Gentoo
avaliable in [my overlay](https://notabug.org/dm9pZCAq/dm9pZCAq-overlay):
```sh
eselect repository enable dm9pZCAq
emerge --sync dm9pZCAq
emerge app-admin/aslstatus::dm9pZCAq
```

if you wanna pack `aslstatus` for you distro,
please do so and submit PR to add it here

---
# compile

it is successfully compiling with
* `clang`
* `tcc`
* `gcc`

needs `pkg-config` for `LDLIBS`

you can find out more in [config.mk](config.mk)

## make options
#### X
add support for `X` (needed for `dwm` `WM_NAME`)

you may want to set it to `0` if you use aslstatus in [dvtm](https://www.brain-dump.org/projects/dvtm/)

* default: `1`
* dependencies:
  + `libxcb-dev`

#### XKB
add support for keyboard (needed for `keymap` component)

works only if `X=1`

* default: `1`
* dependencies:
  + `libxcb-xkb-dev`

#### AUDIO
select audio library

* default: `ALSA`
* possible values:
  - `ALSA`
  - `PULSE`
  - `''` (empty) to use `sys/soundcard.h` or `sys/audioio.h` on OpenBSD
* dependencies:
  + `libasound-dev` (if `AUDIO=ALSA`)
  + `libpulse-dev` (if `AUDIO=PULSE`)


---
# config

for more info about configs see [config.h](config.h) and [components_config.h](components_config.h)

also you can change `BUFF_SZ` (see [util.h](util.h))


---
# components/

components were taken from [slstatus](https://tools.suckless.org/slstatus)
and have been modified to work with `pthread`,
some have been completely rewritten

all components are tested in `Linux`

if you are using `OpenBSD` or `FreeBSD`, please tell me if it works correctly,
or if you have any problems


---
### manual updating

just send `USR1` signal to thread which you want to update


---
### how to create you own component

create file with `.c` extension in [components/](components/)

#### basic example

`components/simple_module.c`:
```c
#include "../util.h"  /* you can find some useful functions in `util.c` */

void
function_name(char *out, const char __unused *arg,
		unsigned int __unused interval, void __unused *static_ptr)
{
	bprintf(out, "%s", "Hello, World!");
}
```

`arg`, `interval` and `static_ptr` is optional argument
and if it is unused add `__unused` attribute


then put:
```c
void function_name FUNC_ARGS;
#define function_name {function_name, "thread name", 0}
```

at the end of [aslstatus.h](aslstatus.h)

(`FUNC_ARGS` is already predefined)

#### complex example

`components/my_module.c`:
```c
#include "../util.h"

void
my_module(char *out, const char *arg, unsigned int interval, void *static_ptr)
{
	float *static_data = static_ptr;
	if (!static_data)
		static_data = interval * 20.21;
	
	bprintf(
		out,
		"'%s' module with '%s' arg and '%u' interval, "
		"pointer to static_data is %p with '%f'",
		__FUNCTION__, arg, interval, static_ptr, static_data
	);
}
```

`aslstatus.h`:
```c
/* ... */

void my_module FUNC_ARGS;
#define my_module {my_module, "My Module", sizeof(float)}
```

in `define` third field is size of static data to which point `static_ptr`

also in [os.h](os.h) defined 4 variables which can be used to set
os specific data sizes in branchless way (see: [this lines](https://notabug.org/dm9pZCAq/aslstatus/src/384b798760f5bc333505a5f10cd2ed4b34a91647/aslstatus.h#L40) in [aslstatus.h](aslstatus.h))


---
# TODO
* ~~add pulseaudio support~~
