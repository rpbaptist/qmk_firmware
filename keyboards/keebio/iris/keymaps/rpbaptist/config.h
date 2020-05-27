/*
Copyright 2017 Danny Nguyen <danny@keeb.io>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define USE_I2C

#define MASTER_LEFT

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_LAYERS
#    undef RGBLED_NUM
#    define RGBLED_NUM 18  // Number of LEDs
#    undef RGBLED_SPLIT
#    define RGBLED_SPLIT \
        { 9, 9 }
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8

#    define RGBLIGHT_LIMIT_VAL 225
#endif  // RGBLIGHT_ENABLE

#    define QMK_ESC_OUTPUT F6  // usually COL
#    define QMK_ESC_INPUT D7   // usually ROW
#    define QMK_LED B0

#undef PRODUCT
#define PRODUCT Iris Gamepad
