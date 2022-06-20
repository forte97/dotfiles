#- aslstatus - async suckless status monitor -#

include config.mk


COMPONENTS  := $(wildcard components/*.c)
OBJ          = ${COMPONENTS:.c=.o}

NEED_VOLUME := aslstatus.o

X         ?= 1
XKB       ?= 1
AUDIO     ?= ALSA
A_ALSA_O  := components/volume/alsa.o
A_DEF_O   := components/volume/default.o
A_PULSE_O := components/volume/pulse.o


.PHONY: all
all: aslstatus




ifeq (${X},1)
LDLIBS   += ${LDXCB}
CPPFLAGS += -DUSE_X=1

ifeq (${XKB},1)
LDLIBS   += ${LDXCB_XKB}
CPPFLAGS += -DUSE_XKB=1
else
CPPFLAGS += -DUSE_XKB=0
endif  # XKB

else
CPPFLAGS += -DUSE_X=0
CPPFLAGS += -DUSE_XKB=0
endif  # X


ifeq (${AUDIO},ALSA)
LDLIBS     += ${LDALSA}
COMPONENTS += ${A_ALSA_O:.o=.c}

${NEED_VOLUME}: CPPFLAGS += -DUSE_ALSA
endif  # ALSA


ifeq (${AUDIO},PULSE)
LDLIBS     += ${LDPULSE}
COMPONENTS += ${A_PULSE_O:.o=.c}

${NEED_VOLUME}: CPPFLAGS += -DUSE_PULSE
endif  # PULSE


ifneq (${AUDIO},ALSA)
ifneq (${AUDIO},PULSE)
COMPONENTS += ${A_DEF_O:.o=.c}
endif  # PULSE
endif  # ALSA

${NEED_VOLUME}: components/volume/volume.h


${OBJ}: util.h components_config.h
aslstatus.o: aslstatus.c aslstatus.h config.h util.h os.h

${OBJ} util.o: %.o: %.c
	$(CC) -o $@ -c $< ${CFLAGS} ${CPPFLAGS}

aslstatus: aslstatus.o util.o ${OBJ}
	$(CC) -o $@ ${LDFLAGS} ${LDLIBS} ${CFLAGS} ${CPPFLAGS} $^

aslstatus.1: aslstatus.1.md
	pandoc --standalone --from=markdown $< --to=man -o $@

.PHONY: man
man: aslstatus.1

.PHONY: install
install: all
	mkdir -p "${DESTDIR}${PREFIX}/bin"
	cp -f aslstatus "${DESTDIR}${PREFIX}/bin"
	chmod 755 "${DESTDIR}${PREFIX}/bin/aslstatus"
	mkdir -p "${DESTDIR}${MANPREFIX}/man1"
	cp -f aslstatus.1 "${DESTDIR}${MANPREFIX}/man1"
	chmod 644 "${DESTDIR}${MANPREFIX}/man1/aslstatus.1"

.PHONY: clean
clean:
	rm -f aslstatus aslstatus.o util.o ${OBJ} ${A_ALSA_O} ${A_PULSE_O} ${A_DEF_O}

.PHONY: uninstall
uninstall:
	rm -f "${DESTDIR}${PREFIX}/bin/aslstatus"
	rm -f "${DESTDIR}${MANPREFIX}/man1/aslstatus.1"
