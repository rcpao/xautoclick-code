/*
 * xAutoClick, Qt 4 GUI
 *
 * Copyright (C) 2010 Ivo van Poorten
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

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

extern "C" {
#include "main.h"
#include "osdep.h"
}

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

class MyWidget : public QWidget {
    public:
        MyWidget(QWidget *parent = 0);
        QPushButton *buttons[3];
        QSpinBox *spins[4];
};

static Display *display;
static QApplication *app;
static MyWidget *mywidget;

void click_mouse_button(void) {
    XTestFakeButtonEvent(display, 1, True, CurrentTime);
    XTestFakeButtonEvent(display, 1, False, CurrentTime);
    XFlush(display);
}

void set_alarm(int ms) {
}

int get_spin_value(spin_t spin) {
    return mywidget->spins[spin]->value();
}

void set_spin_value(spin_t spin, int value) {
    mywidget->spins[spin]->setValue(value);
}

void set_button_sensitive(button_t button, int state) {
    mywidget->buttons[button]->setEnabled(state);
}

MyWidget::MyWidget(QWidget *parent) : QWidget(parent) {

    struct foo {
        QString label;
        int min, max, val;
    } bar[4] = {
        { "Pre-delay",   1, 1<<30, 2000 }, { "Interval",    1, 1<<30, 1000 },
        { "Random +/-",  1, 10240,   64 }, { "# of clicks", 1, 10240,   32 }
    };
    QString butnames[3] = { "Tap", "Stop", "Start" };

    QVBoxLayout *vbox = new QVBoxLayout;

    for (int c=0; c<4; c++) {
        QHBoxLayout *layout = new QHBoxLayout;
        spins[c] = new QSpinBox;
        spins[c]->setMaximum(bar[c].max);
        spins[c]->setMinimum(bar[c].min);
        spins[c]->setValue(bar[c].val);

        layout->addWidget(new QLabel(bar[c].label));
        layout->addWidget(spins[c]);
        vbox->addLayout(layout);
    }

    QHBoxLayout *layout = new QHBoxLayout;

    for (int c=0; c<3; c++)
        layout->addWidget(buttons[c] = new QPushButton(butnames[c]));

    vbox->addLayout(layout);
    setLayout(vbox);
}

int init_gui(int argc, char **argv) {
    if (!(display = XOpenDisplay(NULL))) {
        fprintf(stderr, "Unable to open X display\n");
        return 0;
    }

    app = new QApplication(display);
    mywidget = new MyWidget;

    return 1;
}

void close_gui(void) {
}

void main_loop(void) {
    mywidget->show();
    app->exec();
}