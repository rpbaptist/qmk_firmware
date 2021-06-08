#include "rpbaptist.h"

static uint32_t oled_timer           = 0;
bool            alt_tab_used         = false;
bool            switched_from_gaming = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAKDH] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, BSP_DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TAB_NUM,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      LCTL_BR,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, RCTL_BR,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,   T_SYM, SFT_SPC,    SFT_ENT,   T_NAV, KC_RGUI \
                                      //`--------------------------'  `--------------------------'
  ),

  [_GAMING] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,    KC_T,    KC_Q,    KC_W,    KC_E,    KC_R,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_G,    KC_A,    KC_S,    KC_D,    KC_F,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_B,    KC_Z,    KC_X,    KC_C,    KC_V,                         KC_N,    KC_M, _______, _______, _______, KC_RCTL,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          EXTALT, KC_LSFT,  KC_SPC,    _______, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_GAMING_EXT] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV,    KC_Y,    KC_I,    KC_J,    KC_M,    KC_N,                      _______, _______, _______, _______, _______,  KC_DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_CAPS,    KC_6,    KC_7, KC_LBRC, KC_RBRC, KC_BSLS,                      _______, _______, _______, _______, _______, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, KC_LALT, KC_ENT,     KC_ENT, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUMPAD] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_EUR,   KC_P7,   KC_P8,   KC_P9, _______, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        S_NUM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS,   KC_P4,   KC_P5,   KC_P6, KC_PMNS, KC_PPLS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_NLCK,                       KC_EQL,   KC_P1,   KC_P2,   KC_P3, KC_PSLS, KC_PAST,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,   KC_P0,  KC_DOT \
                                      //`--------------------------'  `--------------------------'
  ),

  [_SYM] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, KC_MINS, KC_PLUS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      LCT_PRN, XXXXXXX, XXXXXXX, XXXXXXX,  KC_EUR, XXXXXXX,                       KC_EQL, KC_PIPE,   KC_LT,   KC_GT, KC_BSLS, RCT_PRN,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,   S_SYM, _______,    _______, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_NAV] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_PGUP, KC_HOME,   KC_UP,  KC_END,  KC_INS, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TILD,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      LCT_PRN,  KC_F11,  KC_F12,  KC_F13, KC_PSCR, KC_CAPS,                      WIN_CLS, TAB_BCK, TAB_CLS, TAB_FWD, XXXXXXX, RCT_PRN,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+---------|
                                          _______, _______, _______,    _______,   S_NAV, _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [_UTIL] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET, RGB_RST, KC_MPRV, KC_VOLU, KC_MNXT, TGL_LYR,                      RGB_ATG, XXXXXXX, XXXXXXX, RGB_IDL, RGB_UND, RGB_TOG,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      LCK_NMP, XXXXXXX, KC_MSTP, KC_VOLD, KC_MPLY, XXXXXXX,                      RGB_PST, XXXXXXX, RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      EEP_RST, KC_SLEP, XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX,                      RGB_PCT, XXXXXXX, RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______ \
                                      //`--------------------------'  `--------------------------'
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(default_layer_state)) {
        case _COLEMAKDH:
            state = update_tri_layer_state(state, _SYM, _NAV, _UTIL);
            break;
        case _GAMING:
            state = update_tri_layer_state(state, _GAMING_EXT, _NAV, _UTIL);
            break;
    }
    return state;
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
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

void render_status(void) {
    // oled_write_P(PSTR("Layout: "), false);
    switch (get_highest_layer(default_layer_state)) {
        case _COLEMAKDH:
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
        case _SYM:
            oled_write_P(PSTR("Sym  "), false);
            break;
        case _NAV:
            oled_write_P(PSTR("Nav  "), false);
            break;
        case _GAMING_EXT:
            oled_write_P(PSTR("Ext  "), false);
            break;
        case _NUMPAD:
            oled_write_P(PSTR("Num  "), false);
            break;
        case _UTIL:
            oled_write_P(PSTR("Util "), false);
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
    if (is_keyboard_master()) {
        if (sync_timer_elapsed32(oled_timer) > OLED_TIMEOUT) {
            oled_off();
            return;
        } else {
            oled_on();
        }
        render_status();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
        } else {
            render_crkbd_logo();
#    ifdef RGB_MATRIX_ENABLE
            if (user_config.rgb_matrix_idle_anim && rgb_matrix_get_mode() == user_config.rgb_matrix_idle_mode) {
                oled_scroll_left();  // Turns on scrolling
            } else {
                oled_scroll_off();
            }
#    endif
    }
}
#endif

void suspend_power_down_keymap(void) {
#ifdef OLED_DRIVER_ENABLE
    oled_off();
#endif
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(true);
#endif
}

void suspend_wakeup_init_keymap(void) {
#ifdef OLED_DRIVER_ENABLE
    oled_on();
#endif
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_suspend_state(false);
#endif
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_ENT:
            return TAPPING_TERM - 20;
        default:
            return TAPPING_TERM;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t saved_mods   = 0;
    uint16_t       temp_keycode = keycode;

    oled_timer = sync_timer_read32();

#ifdef RGB_MATRIX_ENABLE
    if (user_config.rgb_matrix_idle_anim) {
        hypno_timer = sync_timer_read32();
        if (rgb_matrix_get_mode() == user_config.rgb_matrix_idle_mode) {
            rgb_matrix_update_current_mode(user_config.rgb_matrix_active_mode);
            if (!user_config.rgb_layer_indicator) {
                rgb_matrix_turn_off_underglow();
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
        case KC_TAB:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_ALT) {  // ALT is pressed
                    alt_tab_used = true;          // Set a reminder that ALT+TAB has been used
                }
            }
            return true;
        case KC_LALT:
        case KC_RALT:
            if (!record->event.pressed && alt_tab_used) {  // Only run this upon release and if ALT+TAB was used
                switch (get_highest_layer(default_layer_state)) {
                    case _GAMING:
                        switched_from_gaming = true;  // remember if we switched from ALT+TAB
                        default_layer_set(1U << _COLEMAKDH);
                        break;
                    case _COLEMAKDH:
                        if (switched_from_gaming) {
                            switched_from_gaming = false;  // return to default state
                            default_layer_set(1U << _GAMING);
                        }
                        break;
                }
                alt_tab_used = false;  // return to default state
            }
            return true;
        case TGL_LYR:
            if (record->event.pressed) {
                switch (get_highest_layer(default_layer_state)) {
                    case _GAMING:
#ifdef RGB_MATRIX_ENABLE
                        rgb_matrix_set_typing_defaults();
#endif
                        switched_from_gaming = false;  // When manually switching, disable ALT+TAB behavior
                        default_layer_set(1U << _COLEMAKDH);
                        break;
                    case _COLEMAKDH:
#ifdef RGB_MATRIX_ENABLE
                        rgb_matrix_set_gaming_defaults();
#endif
                        default_layer_set(1U << _GAMING);
                        break;
                }
            }
            return true;
#ifdef RGB_MATRIX_ENABLE
        case RGB_RST:
            if (record->event.pressed) {
                rgb_matrix_set_defaults();
                rgb_matrix_enable();
            }
            break;
        case RGB_UND:  // Toggle separate underglow status
            if (record->event.pressed) {
                rgb_matrix_toggle_underglow_layer_indicator();
            }
            break;
        case RGB_IDL:  // Toggle idle/active vs constant animation
            if (record->event.pressed) {
                rgb_matrix_toggle_idle_animation_change();
            }
            break;
        case RGB_ATG:
            if (record->event.pressed) {
                rgb_matrix_toggle_active_mode();
            }
            break;
        case RGB_PST:
            if (record->event.pressed) {
                rgb_matrix_toggle_simple_passive_mode();
            }
            break;
        case RGB_PCT:
            if (record->event.pressed) {
                rgb_matrix_toggle_color_passive_mode();
            }
            break;
#endif
    }
    return true;
}
