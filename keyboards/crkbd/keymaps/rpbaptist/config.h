/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

/* Select hand configuration */
#define EE_HANDS

#define USB_POLLING_INTERVAL_MS 1

#undef USE_I2C
#define USE_SERIAL_PD2

#define NO_ACTION_ONESHOT

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5  // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#    define IDLE_TIMEOUT 60000 * 5
#    define GAMING_IDLE_TIMEOUT 10000
#    define RGB_MATRIX_TYPING_ACTIVE RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#    define RGB_MATRIX_TYPING_PASSIVE RGB_MATRIX_CYCLE_ALL
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true  // turn off effects when suspended
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 135

#    define RGB_MATRIX_HUE_STEP 6
#    define RGB_MATRIX_SAT_STEP 8
#    define RGB_MATRIX_VAL_STEP 10
#    define RGB_MATRIX_SPD_STEP 10

#    define DISABLE_RGB_MATRIX_ALPHAS_MODS
#    define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#    define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
// #    define DISABLE_RGB_MATRIX_BREATHING
#    define DISABLE_RGB_MATRIX_BAND_SAT
#    define DISABLE_RGB_MATRIX_BAND_VAL
#    define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#    define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#    define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#    define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL

#    define DISABLE_RGB_MATRIX_HUE_BREATHING
#    define DISABLE_RGB_MATRIX_HUE_PENDULUM
#    define DISABLE_RGB_MATRIX_HUE_WAVE

// #define DISABLE_RGB_MATRIX_CYCLE_ALL
// #    define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
#    define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
#    define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#    define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#    define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
#    define DISABLE_RGB_MATRIX_CYCLE_SPIRAL
#    define DISABLE_RGB_MATRIX_DUAL_BEACON
#    define DISABLE_RGB_MATRIX_RAINBOW_BEACON
// #define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#    define DISABLE_RGB_MATRIX_RAINDROPS
#    define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS

#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #define DISABLE_RGB_MATRIX_TYPING_HEATMAP
#    define DISABLE_RGB_MATRIX_DIGITAL_RAIN

#    define RGB_MATRIX_KEYPRESSES  // reacts to keypresses

// #    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
// #    define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS

#    define DISABLE_RGB_MATRIX_SPLASH
#    define DISABLE_RGB_MATRIX_MULTISPLASH
#    define DISABLE_RGB_MATRIX_SOLID_SPLASH
#    define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH

#    define RGB_MATRIX_ANIMATION_SPEED_FAST UINT8_MAX / 2
#    define RGB_MATRIX_ANIMATION_SPEED_MEDIUM UINT8_MAX / 4
#    define RGB_MATRIX_ANIMATION_SPEED_SLOW UINT8_MAX / 8
#    define RGB_MATRIX_ANIMATION_SPEED_SLOWER UINT8_MAX / 24

#    if defined(THEME_GODSPEED)
#        define THEME_HSV 132, 255, 125
#    elif defined(THEME_GODSPEED_ARES)
#        define THEME_HSV HSV_ORANGE
#    elif defined(THEME_LASER)
#        undef RGB_MATRIX_TYPING_ACTIVE
#        undef RGB_MATRIX_TYPING_PASSIVE
#        define THEME_HSV HSV_PURPLE
#        define RGB_MATRIX_TYPING_ACTIVE RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#        define RGB_MATRIX_TYPING_PASSIVE RGB_MATRIX_CYCLE_LEFT_RIGHT
#    elif defined(THEME_MILKSHAKE)
#        undef RGB_MATRIX_TYPING_ACTIVE
#        undef RGB_MATRIX_TYPING_PASSIVE
#        define THEME_HSV 30, 255, 218
#        define RGB_MATRIX_TYPING_ACTIVE RGB_MATRIX_TYPING_HEATMAP
#        define RGB_MATRIX_TYPING_PASSIVE RGB_MATRIX_CYCLE_LEFT_RIGHT
#    else
#        define THEME_HSV 123, 255, 125  // default to PULSE
#    endif
#endif

#define TAPPING_TERM 140
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TERM_PER_KEY

#define TAPPING_TOGGLE 2

#ifdef MOUSEKEY_ENABLE
#    define MOUSEKEY_DELAY 0
#    define MOUSEKEY_INTERVAL 16
#    define MOUSEKEY_MAX_SPEED 6
#    define MOUSEKEY_TIME_TO_MAX 36
#    define MOUSEKEY_WHEEL_MAX_SPEED 4
#    define MOUSEKEY_WHEEL_TIME_TO_MAX 100
#endif

#ifdef OLED_DRIVER_ENABLE
#    undef SSD1306OLED
#    define OLED_TIMEOUT 600000
#    define OLED_FONT_H "glcdfont_multi.c"
#endif

#undef PRODUCT
#define PRODUCT Corne Keyboard

#define LCPC_KEYS KC_LCTL, KC_LSFT, KC_9
#define RCPC_KEYS KC_RCTL, KC_RSFT, KC_0
