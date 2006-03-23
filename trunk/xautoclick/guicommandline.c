/* ------------------------------------------------------------------------- */

/*
 * $Id$
 * 
 * xAutoClick
 *
 * Copyright (C) 2006 Ivo van Poorten
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

/* ------------------------------------------------------------------------- */

#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

#include "main.h"
#include "osdep.h"

/* ------------------------------------------------------------------------- */

static Display *display;

static int predelay, interval, random, numberofclicks;

static int sleeptime;

/* ------------------------------------------------------------------------- */

void click_mouse_button(void) {

    XTestFakeButtonEvent(display, 1, True, CurrentTime);
    XTestFakeButtonEvent(display, 1, False, CurrentTime);
    XFlush(display);
}

/* ------------------------------------------------------------------------- */

void set_alarm(int ms) {
    sleeptime = ms;
}

/* ------------------------------------------------------------------------- */

int get_spin_value(spin_t spin) {

    switch(spin) {
    case SPIN_PREDELAY:
        return predelay;
        break;
    case SPIN_INTERVAL:
        return interval;
        break;
    case SPIN_RANDOM:
        return random;
        break;
    case SPIN_NUMBER:
        return numberofclicks;
        break;
    }

    return 0;
}

/* ------------------------------------------------------------------------- */

void set_spin_value(spin_t spin, int value) {

    switch(spin) {
    case SPIN_PREDELAY:
        predelay = value;
        break;
    case SPIN_INTERVAL:
        interval = value;
        break;
    case SPIN_RANDOM:
        random = value;
        break;
    case SPIN_NUMBER:
        numberofclicks = value;
        break;
    }
}

/* ------------------------------------------------------------------------- */

void set_button_sensitive(button_t button, int state) {

    switch(button) {
    case BUTTON_TAP:
        break;
    case BUTTON_STOP:
        break;
    case BUTTON_START:
        break;
    }
}

/* ------------------------------------------------------------------------- */

int init_gui(int argc, char **argv) {

    display = XOpenDisplay(NULL);

    if (!display) {
        fprintf(stderr, "Unable to open X display\n");
        return 0;
    }

    predelay = 2000;
    interval = 1024;
    random = 0;
    numberofclicks = 32;

    /* parse command line */

    return 1;
}

/* ------------------------------------------------------------------------- */

void close_gui(void) {

    XCloseDisplay(display);
}

/* ------------------------------------------------------------------------- */

void main_loop(void) {

    common_start_button();

    while (sleeptime) {
        usleep(sleeptime * 1000);
        sleeptime = 0;
        common_alarm_callback();
    }

    return;
}

/* ------------------------------------------------------------------------- */

