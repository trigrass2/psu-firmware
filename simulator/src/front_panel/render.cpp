/*
 * EEZ PSU Firmware
 * Copyright (C) 2015-present, Envox d.o.o.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "psu.h"
#include "front_panel/render.h"
#include "imgui/window.h"

namespace eez {

using namespace imgui;

namespace psu {
namespace simulator {
namespace front_panel {

#if EEZ_PSU_SELECTED_REVISION == EEZ_PSU_REVISION_R1B9
static WindowDefinition window_definition_small = {
	"EEZ Software Simulator",
	1475, 531,
	10,
	"eez.png"
};

static WindowDefinition window_definition_large = window_definition_small;
#elif EEZ_PSU_SELECTED_REVISION == EEZ_PSU_REVISION_R2B6
static WindowDefinition window_definition_small = {
	"EEZ Software Simulator",
	1081, 366,
	10,
	"eez.png"
};

static WindowDefinition window_definition_large = {
	"EEZ Software Simulator",
	2 * 1081, 2 * 366,
	10,
	"eez.png"
};
#endif

static int F = 1;

#define D(x) (F * x)
#define RECT(x, y, w, h) D(x), D(y), D(w), D(h)

#define R1B9_IMAGE(IMAGE) "r1b9/" IMAGE ".png"
#define R2B6_IMAGE(IMAGE) (F == 1 ? "r2b6/small/" IMAGE ".png" : "r2b6/large/" IMAGE ".png")

imgui::WindowDefinition *getWindowDefinition(int w, int h) {
	if (w >= SIM_FRONT_PANEL_LARGE_MODE_MIN_WIDTH) {
		F = 2;
		return &window_definition_large;
	} else {
		F = 1;
		return &window_definition_small;
	}
}

void render(Window *window, Data *data) {
#if EEZ_PSU_SELECTED_REVISION == EEZ_PSU_REVISION_R1B9
    window->addImage(0, 0, 1475, 531, R1B9_IMAGE("front-panel"));

    window->addOnOffImage(878, 34, 17, 16, data->standby, R1B9_IMAGE("led-blue"), R1B9_IMAGE("led-off"));

    window->addOnOffImage(878, 126, 17, 16, data->ch1.cv, R1B9_IMAGE("led-yellow"), R1B9_IMAGE("led-off"));
    window->addOnOffImage(878, 172, 17, 16, data->ch1.cc, R1B9_IMAGE("led-red"), R1B9_IMAGE("led-off"));
    window->addOnOffImage(983, 80, 17, 16, data->ch1.out_plus, R1B9_IMAGE("led-green"), R1B9_IMAGE("led-off"));
    window->addOnOffImage(1071, 80, 17, 16, data->ch1.sense_plus, R1B9_IMAGE("led-yellow"), R1B9_IMAGE("led-off"));
    window->addOnOffImage(1159, 80, 17, 16, data->ch1.sense_minus, R1B9_IMAGE("led-yellow"), R1B9_IMAGE("led-off"));
    window->addOnOffImage(1247, 80, 17, 16, data->ch1.out_minus, R1B9_IMAGE("led-green"), R1B9_IMAGE("led-off"));
    if (data->ch1.load_text) {
        window->addImage(992, 184, 266, 71, R1B9_IMAGE("load"));
        window->addText(1047, 217, 156, 32, data->ch1.load_text);
    }

    window->addOnOffImage(878, 366, 17, 16, data->ch2.cv, R1B9_IMAGE("led-yellow"), R1B9_IMAGE("led-off"));
    window->addOnOffImage(878, 412, 17, 16, data->ch2.cc, R1B9_IMAGE("led-red"), R1B9_IMAGE("led-off"));
    window->addOnOffImage(983, 324, 17, 16, data->ch2.out_plus, R1B9_IMAGE("led-green"), R1B9_IMAGE("led-off"));
    window->addOnOffImage(1071, 324, 17, 16, data->ch2.sense_plus, R1B9_IMAGE("led-yellow"), R1B9_IMAGE("led-off"));
    window->addOnOffImage(1159, 324, 17, 16, data->ch2.sense_minus, R1B9_IMAGE("led-yellow"), R1B9_IMAGE("led-off"));
    window->addOnOffImage(1247, 324, 17, 16, data->ch2.out_minus, R1B9_IMAGE("led-green"), R1B9_IMAGE("led-off"));
    if (data->ch2.load_text) {
        window->addImage(992, 428, 266, 71, R1B9_IMAGE("load"));
        window->addText(1047, 461, 156, 32, data->ch2.load_text);
    }

    data->reset = window->addButton(509, 398, 18, 18, R1B9_IMAGE("reset-normal"), R1B9_IMAGE("reset-pressed"));

    data->local_control_widget.x = 594;
    data->local_control_widget.y = 94;
    data->local_control_widget.w = 240;
    data->local_control_widget.h = 320;

    window->addUserWidget(&data->local_control_widget);
#elif EEZ_PSU_SELECTED_REVISION == EEZ_PSU_REVISION_R2B6
    window->addImage(RECT(0, 0, 1081, 366), R2B6_IMAGE("front-panel"));

    window->addOnOffImage(RECT(131, 243, 17, 17), data->standby, R2B6_IMAGE("led-blue"), R2B6_IMAGE("led-off"));

    window->addOnOffImage(RECT(689, 61, 17, 17), data->ch1.cv, R2B6_IMAGE("led-yellow"), R2B6_IMAGE("led-off"));
    window->addOnOffImage(RECT(689, 95, 17, 17), data->ch1.cc, R2B6_IMAGE("led-red"), R2B6_IMAGE("led-off"));
    window->addOnOffImage(RECT(713, 267, 17, 17), data->ch1.out, R2B6_IMAGE("led-green"), R2B6_IMAGE("led-off"));
    window->addOnOffImage(RECT(689, 128, 17, 17), data->ch1.sense, R2B6_IMAGE("led-yellow"), R2B6_IMAGE("led-off"));
    window->addOnOffImage(RECT(650, 128, 17, 17), data->ch1.prog, R2B6_IMAGE("led-red"), R2B6_IMAGE("led-off"));
    if (data->ch1.load_text) {
        window->addImage(RECT(652, 294, 138, 66), R2B6_IMAGE("load"));
        window->addText(RECT(677, 326, 88, 29), data->ch1.load_text);
    }

    window->addOnOffImage(RECT(918, 61, 17, 17), data->ch2.cv, R2B6_IMAGE("led-yellow"), R2B6_IMAGE("led-off"));
    window->addOnOffImage(RECT(918, 95, 17, 17), data->ch2.cc, R2B6_IMAGE("led-red"), R2B6_IMAGE("led-off"));
    window->addOnOffImage(RECT(894, 267, 17, 17), data->ch2.out, R2B6_IMAGE("led-green"), R2B6_IMAGE("led-off"));
    window->addOnOffImage(RECT(918, 128, 17, 17), data->ch2.sense, R2B6_IMAGE("led-yellow"), R2B6_IMAGE("led-off"));
    window->addOnOffImage(RECT(879, 128, 17, 17), data->ch2.prog, R2B6_IMAGE("led-red"), R2B6_IMAGE("led-off"));
    if (data->ch2.load_text) {
        window->addImage(RECT(834, 294, 138, 66), R2B6_IMAGE("load"));
        window->addText(RECT(859, 326, 88, 29), data->ch2.load_text);
    }

	data->reset = window->addButton(RECT(129, 165, 20, 20), R2B6_IMAGE("reset-normal"), R2B6_IMAGE("reset-pressed"));

    data->local_control_widget.x = D(211);
    data->local_control_widget.y = D(57);
    data->local_control_widget.w = D(320);
    data->local_control_widget.h = D(240);

    window->addUserWidget(&data->local_control_widget);
#endif
}

}
}
}
} // namespace eez::psu::simulator::front_panel;