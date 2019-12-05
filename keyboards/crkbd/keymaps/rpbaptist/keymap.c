#include QMK_KEYBOARD_H

extern uint8_t  is_master;
static uint32_t oled_timer = 0;

enum layer_names {
  _COLEMAKDHM,
  _GAMING,
  _GAMING_EXT,
  _MOUSE,
  _NUM,
  _NAV,
  _META
};

enum custom_keycodes {
    BSP_DEL = SAFE_RANGE,
    RGB_RST,
    RGB_UND,  // Toggle RGB underglow as layer indicator
    RGB_IDL,  // RGB Idling animations
    RGB_MAP,  // RGB_MATRIX_TYPING_HEATMAP
    RGB_SPL,  // RGB_MATRIX_MULTISPLASH
    RGB_SOL,  // RGB_MATRIX_SOLID_COLOR
    RGB_CYC,  // RGB_MATRIX_CYCLE_ALL
    RGB_DUO,  // RGB_MATRIX_RAINBOW_PINWHEELS
    RGB_CHV   // RGB_MATRIX_RAINBOW_MOVING_CHEVRON
};

typedef union {
    uint32_t raw;
    struct {
        bool     rgb_layer_change        : 1;
        bool     rgb_matrix_idle_anim    : 1;
        uint8_t  rgb_matrix_active_mode  : 4;
        uint8_t  rgb_matrix_idle_mode    : 4;
        uint8_t  rgb_matrix_active_speed : 8;
        uint8_t  rgb_matrix_idle_speed   : 8;
        uint16_t rgb_matrix_idle_timeout : 16;
    };
} user_config_t;

user_config_t user_config;

// Base layers
#define COLEMAK DF(_COLEMAKDHM)
#define GAMING  DF(_GAMING)

// Layer toggle and switch
#define T_NAV TT(_NAV)
#define S_NAV MO(_NAV)

#define T_NUM TT(_NUM)
#define S_NUM MO(_NUM)

// Layer keys with functionality on tap
#define NAV_0 LT(_NAV, KC_0)
#define TAB_MS LT(_MOUSE, KC_TAB)

#define EXT_SF LT(_GAMING_EXT, KC_LSHIFT)

// Tap/mod keys
#define RCTL_BR RCTL_T(KC_RBRACKET)
#define LCTL_BR LCTL_T(KC_LBRACKET)

#define SFT_SPC LSFT_T(KC_SPACE)
#define SFT_ENT RSFT_T(KC_ENTER)

// Global tab forward and backward
#define TAB_FWD LCTL(KC_TAB)
#define TAB_BCK LCTL(LSFT(KC_TAB))
#define TAB_CLS LCTL(KC_W)

#define WIN_CLS LALT(KC_F4)

// CTRL become parens keys on NAV and NUM layers
#define LCT_PRN KC_LCPO
#define RCT_PRN KC_RCPC

// €
#define KC_EUR ALGR(KC_5)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAKDHM] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, BSP_DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       TAB_MS,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      LCTL_BR,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, RCTL_BR,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,   T_NUM, SFT_SPC,    SFT_ENT,   T_NAV, KC_RGUI \
                                      //`--------------------------'  `--------------------------'
  ),

  [_GAMING] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, KC_RCTL,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,  EXT_SF,  KC_SPC,    _______, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_GAMING_EXT] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV,    KC_1,    KC_2, _______,    KC_3,    KC_4,                      _______, _______, _______, _______, _______,  KC_DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LBRC, KC_RBRC, _______, _______, _______, KC_BSLS,                      _______, _______, _______, _______, _______, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                      _______, _______, _______, _______, _______, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,     KC_ENT, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_MOUSE] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, XXXXXXX, KC_MPRV, KC_VOLU, KC_MNXT, XXXXXXX,                      KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, XXXXXXX, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, KC_MSTP, KC_VOLD, KC_MPLY, XXXXXXX,                      KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_WH_L, XXXXXXX, KC_WH_R, XXXXXXX, KC_RCTL,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_ACL0, KC_ACL2, _______,    _______, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUM] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_PLUS,    KC_4,    KC_5,    KC_6, KC_MINS, KC_UNDS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      LCT_PRN, KC_CIRC, KC_AMPR, KC_EUR,  KC_PIPE,  KC_EQL,                      KC_ASTR,    KC_1,    KC_2,    KC_3, _______, RCT_PRN,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,   S_NUM, _______,    _______,   NAV_0, KC_DOT \
                                      //`--------------------------'  `--------------------------'
  ),

  [_NAV] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_PGUP, KC_HOME,   KC_UP,  KC_END, XXXXXXX, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, KC_CAPS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      LCT_PRN,  KC_F11,  KC_F12,  KC_INS, KC_PSCR, KC_NLCK,                      WIN_CLS, TAB_BCK, TAB_CLS, TAB_FWD, KC_BSLS, RCT_PRN,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+---------|
                                          _______, _______, _______,    _______, S_NAV, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_META] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, COLEMAK,                      RGB_IDL, RGB_MAP, RGB_SPL, XXXXXXX, RGB_HUD, RGB_HUI,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_RST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  GAMING,                      RGB_UND, RGB_DUO, RGB_CHV, RGB_SPI, RGB_VAD, RGB_VAI,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_SLEP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      RGB_TOG, RGB_SOL, RGB_CYC, RGB_SPD, RGB_SAD, RGB_SAI,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(default_layer_state)) {
        case _COLEMAKDHM:
            state = update_tri_layer_state(state, _NUM, _NAV, _META);
            break;
        case _GAMING:
            state = update_tri_layer_state(state, _GAMING_EXT, _NAV, _META);
            break;
    }
    return state;
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_master) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_180;
    }
}

void render_crkbd_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

#    ifdef RGB_MATRIX_ENABLE
const char *rgb_matrix_anim_oled_text(uint8_t mode) {
    switch (mode) {
        case RGB_MATRIX_TYPING_HEATMAP:
            return PSTR("Heat ");
        case RGB_MATRIX_MULTISPLASH:
            return PSTR("Splsh");
        case RGB_MATRIX_SOLID_COLOR:
            return PSTR("Solid");
        case RGB_MATRIX_CYCLE_ALL:
            return PSTR("Cycle");
        case RGB_MATRIX_RAINBOW_PINWHEELS:
            return PSTR("Wheel");
        case RGB_MATRIX_RAINBOW_MOVING_CHEVRON:
            return PSTR("Wave ");
        default:
            return PSTR("");
    }
}
#    endif

void render_status(void) {
    // oled_write_P(PSTR("Layout: "), false);
    switch (get_highest_layer(default_layer_state)) {
        case _COLEMAKDHM:
            oled_write_P(PSTR("TYPE "), false);
            break;
        case _GAMING:
            oled_write_P(PSTR("GAME "), false);
            break;
    }

    oled_write_P(PSTR("\n"), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("     "), false);
            break;
        case _NUM:
            oled_write_P(PSTR("Comm "), false);
            break;
        case _NAV:
            oled_write_P(PSTR("Fuel "), false);
            break;
        case _GAMING_EXT:
            oled_write_P(PSTR("Ext  "), false);
            break;
        case _MOUSE:
            oled_write_P(PSTR("Mouse"), false);
            break;
        case _META:
            oled_write_P(PSTR("Meta "), false);
            break;
        default:
            oled_write_P(PSTR("Unkn "), false);
            break;
    }
    oled_write_P(PSTR("\n"), false);

    uint8_t modifiers = get_mods();

    oled_write_P((modifiers & MOD_MASK_SHIFT) ? PSTR("SHIFT") : PSTR("\n"), false);
    oled_write_P((modifiers & MOD_MASK_CTRL) ? PSTR("CTRL ") : PSTR("\n"), false);
    oled_write_P((modifiers & MOD_MASK_ALT) ? PSTR("ALT  ") : PSTR("\n"), false);
    oled_write_P((modifiers & MOD_MASK_GUI) ? PSTR("SUPER") : PSTR("\n"), false);

    oled_write_P(PSTR("\n"), false);

    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(PSTR("Mode:"), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR(" NUM ") : PSTR("\n"), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR(" CAPS") : PSTR("\n"), false);

#    ifdef RGB_MATRIX_ENABLE
    oled_write_P(PSTR("\n"), false);
    oled_write_P(PSTR("\n"), false);

    if (rgb_matrix_config.enable) {
        if (user_config.rgb_matrix_idle_anim) {
            oled_write_P(rgb_matrix_anim_oled_text(user_config.rgb_matrix_active_mode), false);
            oled_write_P(rgb_matrix_anim_oled_text(user_config.rgb_matrix_idle_mode), false);
        } else {
            oled_write_P(PSTR("\n"), false);
            oled_write_P(rgb_matrix_anim_oled_text(rgb_matrix_get_mode()), false);
        }
      } else {
        oled_write_P(PSTR("\n"), false);
        oled_write_P(PSTR("\n"), false);
      }
#    endif
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > OLED_TIMEOUT) {
        oled_off();
        return;
    } else {
        oled_on();
    }

    if (is_master) {
        render_status();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_crkbd_logo();
        // oled_scroll_left();  // Turns on scrolling
    }
}
#endif

#ifdef RGB_MATRIX_ENABLE

static uint32_t hypno_timer;

extern led_config_t g_led_config;
void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t led_type) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_config.hsv.v) {
        hsv.v = rgb_matrix_config.hsv.v;
    }

    RGB rgb = hsv_to_rgb(hsv);
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

void check_default_layer(uint8_t type) {
    switch (get_highest_layer(default_layer_state)) {
        case _COLEMAKDHM:
            rgb_matrix_layer_helper(HSV_TEAL, type);
            break;
        case _GAMING:
            rgb_matrix_layer_helper(HSV_RED, type);
            break;
    }
}

void rgb_matrix_indicators_user(void) {
  if (
    user_config.rgb_layer_change && !g_suspend_state && rgb_matrix_config.enable &&
      (!user_config.rgb_matrix_idle_anim || rgb_matrix_get_mode() != user_config.rgb_matrix_idle_mode)
  )
    {
        switch (get_highest_layer(layer_state)) {
            case _GAMING_EXT:
                rgb_matrix_layer_helper(HSV_PURPLE, LED_FLAG_UNDERGLOW);
                break;
            case _NUM:
                rgb_matrix_layer_helper(HSV_GOLDENROD, LED_FLAG_UNDERGLOW);
                break;
            case _NAV:
                rgb_matrix_layer_helper(HSV_SPRINGGREEN, LED_FLAG_UNDERGLOW);
                break;
            case _META:
                rgb_matrix_layer_helper(HSV_PINK, LED_FLAG_UNDERGLOW);
                break;
            case _MOUSE:
                rgb_matrix_layer_helper(HSV_CORAL, LED_FLAG_UNDERGLOW);
                break;
            default: {
                check_default_layer(LED_FLAG_UNDERGLOW);
                break;
            }
        }
    }
}

void rgb_matrix_update_current_mode(uint8_t mode, uint8_t speed) {
    rgb_matrix_config.speed = speed;
    rgb_matrix_mode_noeeprom(mode);
    eeconfig_update_user(user_config.raw);
}

void rgb_matrix_update_dynamic_mode(uint8_t mode, uint8_t speed, bool active) {
    if (active) {
        user_config.rgb_matrix_active_speed = speed;
        user_config.rgb_matrix_active_mode  = mode;
    } else {
        user_config.rgb_matrix_idle_speed = speed;
        user_config.rgb_matrix_idle_mode  = mode;
    }
}

void rgb_matrix_update_mode(uint8_t mode, uint8_t speed, bool active) {
    if (user_config.rgb_matrix_idle_anim) {
        rgb_matrix_update_dynamic_mode(mode, speed, active);
    }
    if (active || !user_config.rgb_matrix_idle_anim) {
        rgb_matrix_update_current_mode(mode, speed);
    }
}

void rgb_matrix_set_defaults(void) {
    rgb_matrix_config.enable = 1;
    rgb_matrix_config.hsv    = (HSV){128, 255, 128};  // TEAL

    user_config.rgb_layer_change        = true;
    user_config.rgb_matrix_idle_anim    = true;
    user_config.rgb_matrix_idle_timeout = 60000;

    rgb_matrix_update_dynamic_mode(RGB_MATRIX_CYCLE_ALL, RGB_MATRIX_ANIMATION_SPEED_SLOWER, false);
    rgb_matrix_update_dynamic_mode(RGB_MATRIX_TYPING_HEATMAP, RGB_MATRIX_ANIMATION_SPEED_DEFAULT, true);

    eeprom_update_block(&rgb_matrix_config, EECONFIG_RGB_MATRIX, sizeof(rgb_matrix_config));
}

void matrix_scan_rgb(void) {
    if (user_config.rgb_matrix_idle_anim && rgb_matrix_get_mode() == user_config.rgb_matrix_active_mode && timer_elapsed32(hypno_timer) > user_config.rgb_matrix_idle_timeout) {
        if (user_config.rgb_layer_change) {
            rgb_matrix_layer_helper(0, 0, 0, LED_FLAG_UNDERGLOW);
        }
        rgb_matrix_update_current_mode(user_config.rgb_matrix_idle_mode, user_config.rgb_matrix_idle_speed);
    }
}

void matrix_scan_user(void) {
    static bool has_ran_yet;
    if (!has_ran_yet) {
        has_ran_yet = true;
        startup_user();
    }
    matrix_scan_rgb();
}

void suspend_power_down_keymap(void) {
    oled_off();
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    oled_on();
    rgb_matrix_set_suspend_state(false);
}

void eeconfig_init_user(void) {
    user_config.raw = 0;
    rgb_matrix_mode_noeeprom(user_config.rgb_matrix_active_mode);
    keyboard_init();
}

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
    rgb_matrix_set_defaults();
    rgb_matrix_enable_noeeprom();
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t saved_mods   = 0;
    uint16_t       temp_keycode = keycode;

    oled_timer = timer_read32();

#ifdef RGB_MATRIX_ENABLE
    if (user_config.rgb_matrix_idle_anim) {
        hypno_timer = timer_read32();
        if (rgb_matrix_get_mode() == user_config.rgb_matrix_idle_mode) {
            rgb_matrix_update_current_mode(user_config.rgb_matrix_active_mode, user_config.rgb_matrix_active_speed);
            if (!user_config.rgb_layer_change) {
                rgb_matrix_layer_helper(0, 0, 0, LED_FLAG_UNDERGLOW);
            }
        }
    }
#endif

    // Filter out the actual keycode from MT and LT keys.
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        temp_keycode &= 0xFF;
    }

    switch (temp_keycode) {
        case BSP_DEL:
            if (record->event.pressed) {
                saved_mods = get_mods() & MOD_MASK_SHIFT;

                if (saved_mods == MOD_MASK_SHIFT) {  // Both shifts pressed
                    register_code(KC_DEL);
                } else if (saved_mods) {   // One shift pressed
                    del_mods(saved_mods);  // Remove any Shifts present
                    register_code(KC_DEL);
                    add_mods(saved_mods);  // Add shifts again
                } else {
                    register_code(KC_BSPC);
                }
            } else {
                unregister_code(KC_DEL);
                unregister_code(KC_BSPC);
            }
            return false;
#ifdef RGB_MATRIX_ENABLE
        case COLEMAK:
            if (record->event.pressed) {
                user_config.rgb_matrix_idle_timeout = 60000;
                rgb_matrix_update_mode(RGB_MATRIX_CYCLE_ALL, RGB_MATRIX_ANIMATION_SPEED_SLOWER, false);
            }
            return true;
        case GAMING:
            if (record->event.pressed) {
                if (!user_config.rgb_layer_change) {
                    user_config.rgb_layer_change = true;
                }
                user_config.rgb_matrix_idle_timeout = 5000;
                rgb_matrix_update_mode(RGB_MATRIX_RAINBOW_PINWHEELS, RGB_MATRIX_ANIMATION_SPEED_SLOW, false);
            }
            return true;
        case RGB_RST:
            if (record->event.pressed) {
                rgb_matrix_set_defaults();
                rgb_matrix_enable();
            }
            break;
        case RGB_UND:  // Toggle separate underglow status
            if (record->event.pressed) {
                user_config.rgb_layer_change ^= 1;
                eeconfig_update_user(user_config.raw);
                if (user_config.rgb_layer_change) {
                    layer_state_set(layer_state);  // This is needed to immediately set the layer color (looks better)
                } else {
                    rgb_matrix_layer_helper(0, 0, 0, LED_FLAG_UNDERGLOW);
                }
            }
            break;
        case RGB_IDL:  // Toggle idle/heatmap animation
            if (record->event.pressed) {
                user_config.rgb_matrix_idle_anim ^= 1;
                if (user_config.rgb_matrix_idle_anim) {
                    rgb_matrix_update_mode(user_config.rgb_matrix_active_mode, user_config.rgb_matrix_active_speed, true);
                } else {
                    rgb_matrix_update_current_mode(user_config.rgb_matrix_idle_mode, user_config.rgb_matrix_idle_speed);
                }
            }
            break;
        case RGB_MAP:
            if (record->event.pressed) {
                rgb_matrix_update_mode(RGB_MATRIX_TYPING_HEATMAP, rgb_matrix_config.speed, true);
            }
            break;
        case RGB_SPL:
            if (record->event.pressed) {
                rgb_matrix_update_mode(RGB_MATRIX_MULTISPLASH, RGB_MATRIX_ANIMATION_SPEED_DEFAULT, true);
            }
            break;
        case RGB_SOL:
            if (record->event.pressed) {
                rgb_matrix_update_mode(RGB_MATRIX_SOLID_COLOR, rgb_matrix_config.speed, false);
            }
            break;
        case RGB_CYC:
            if (record->event.pressed) {
                rgb_matrix_update_mode(RGB_MATRIX_CYCLE_ALL, RGB_MATRIX_ANIMATION_SPEED_SLOWER, false);
            }
            break;
        case RGB_DUO:
            if (record->event.pressed) {
                rgb_matrix_update_mode(RGB_MATRIX_RAINBOW_PINWHEELS, RGB_MATRIX_ANIMATION_SPEED_SLOW, false);
            }
            break;
        case RGB_CHV:
            if (record->event.pressed) {
                rgb_matrix_update_mode(RGB_MATRIX_RAINBOW_MOVING_CHEVRON, RGB_MATRIX_ANIMATION_SPEED_SLOW, false);
            }
            break;
#endif
    }
    return true;
}
