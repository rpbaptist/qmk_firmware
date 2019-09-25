#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
  // Following line allows macro to read current RGB settings
  extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

enum layer_names {
  _COLEMAKDHM,
  _GAMING,
  _GAMING_EXT,
  _NUM,
  _SYM,
  _NAV,
  _UTIL
};

int RGB_current_mode;

enum custom_keycodes {
  RGBRST = SAFE_RANGE
};

#define KC_CLMK DF(_COLEMAKDHM)
#define KC_GAME DF(_GAMING)

#define KC_T_NAV TT(_NAV)
#define KC_S_NAV MO(_NAV)

#define KC_T_NUM TT(_NUM)
#define KC_S_NUM MO(_NUM)

#define KC_SYMTB LT(_SYM, KC_TAB)
#define KC_0_NAV LT(_NAV, KC_0)

#define KC_GMSFT LT(_GAMING_EXT, KC_LSHIFT)

#define KC_TBFWD LCTL(KC_TAB)
#define KC_TBBCK LCTL(LSFT(KC_TAB))

#define KC_CTENT RCTL_T(KC_ENTER)

#define KC_RCTBR RCTL_T(KC_RBRACKET)
#define KC_LCTBR LCTL_T(KC_LBRACKET)

#define KC_SFSPC LSFT_T(KC_SPACE)
#define KC_SFENT LSFT_T(KC_ENTER)
#define KC_SFBSP RSFT_T(KC_BSPACE)

#define KC_EUR ALGR(KC_5)

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_RST   RESET
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LRST  RGBRST

#define KC_LFMOD  RGB_MODE_FORWARD
#define KC_LRMOD  RGB_MODE_REVERSE

#define KC_RGBST RGB_MODE_PLAIN
#define KC_RGBBR RGB_MODE_BREATHE
#define KC_RGBRB RGB_MODE_RAINBOW
#define KC_RGBSW RGB_MODE_SWIRL

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAKDHM] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     Q,     W,     F,     P,     B,                      J,     L,    U,     Y,   SCLN,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      SYMTB,     A,     R,     S,     T,     G,                      M,     N,     E,     I,     O,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      LCTBR,     Z,     X,     C,     D,     V,                      K,     H,  COMM,   DOT,  SLSH, RCTBR,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LALT, T_NUM, SFSPC,    SFENT, T_NAV,  RGUI \
                              //`--------------------'  `--------------------'
  ),

  [_GAMING] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____, _____, _____, _____, _____, _____,                  _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        TAB, _____, _____, _____, _____, _____,                  _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL, _____, _____, _____, _____, _____,                  _____, _____, _____, _____, _____,  RCTL,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, GMSFT, _____,    _____, _____, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_GAMING_EXT] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        GRV,     1,     2, _____,     3,     4,                     F1,    F2,    F3,    F4,    F5,   DEL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LBRC,  RBRC, _____, _____, _____,  BSLS,                     F6,    F7,    F8,    F9,   F10, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
          5,     6,     7,     8,     9,     0,                    F11,   F12,  MINS,   EQL, _____, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,      ENT, _____, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_SYM] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        GRV,  EXLM,    AT,  HASH,   DLR,  PERC,                   EXLM,    AT,  HASH,   DLR,  PERC,  BSLS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX,   EUR, XXXXX,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN,  PIPE,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX,   EUR, XXXXX,                  XXXXX,  MINS,  UNDS, PLUS,    EQL, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, S_NUM, _____,    _____, _____, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_NAV] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,  WH_U, TBBCK,  MS_U, TBFWD,  BTN2,                   PGUP,  HOME,    UP,   END, XXXXX,   DEL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        TAB,  WH_D,  MS_L,  MS_D,  MS_R,  BTN1,                   PGDN,  LEFT,  DOWN,  RGHT, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX,  WH_L, XXXXX,  WH_R, XXXXX,                  XXXXX,  ACL0,  ACL1,  ACL2, XXXXX, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+-----+-------|
                                  _____, _____, SPACE,    _____, S_NAV, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_NUM] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        GRV,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,  SLSH,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       TILD,    F1,    F2,    F3,    F4,    F5,                    F11,     4,     5,     6,  MINS,  PLUS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,    F6,    F7,    F8,    F9,   F10,                    F12,     1,     2,     3,  ASTR, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, S_NUM, _____,    _____, 0_NAV,   DOT \
                              //`--------------------'  `--------------------'
  ),

  [_UTIL] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST, XXXXX,  MSTP,  VOLU,  MNXT, XXXXX,                   CLMK,  GAME, XXXXX, XXXXX,  LHUD,  LHUI,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LRST, XXXXX,  MPRV,  VOLD,  MPLY, XXXXX,                  RGBST, RGBBR, RGBRB, RGBSW,  LSAD,  LSAI,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      XXXXX,  SLEP, XXXXX,  MUTE, XXXXX, XXXXX,                   LTOG, XXXXX, XXXXX, XXXXX,  LVAD,  LVAI,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____, _____ \
                              //`--------------------'  `--------------------'
  )

/*
  [_TEMPLATE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____, _____, _____, _____, _____, _____,                 _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____,                  _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____,                  _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____, _____ \
                              //`--------------------'  `--------------------'
  )
*/
};

uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(default_layer_state)) {
    case _COLEMAKDHM:
      state = update_tri_layer_state(state, _NUM, _NAV, _UTIL);
      break;
    case _GAMING:
      state = update_tri_layer_state(state, _GAMING_EXT, _NAV, _UTIL);
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

void render_status(void) {
  // oled_write_P(PSTR("Layout: "), false);
  switch (biton32(default_layer_state)) {
    case _COLEMAKDHM:
      oled_write_P(PSTR("CLMK "), false);
      break;
    case _GAMING:
      oled_write_P(PSTR("GAME "), false);
      break;
  }

  oled_write_P(PSTR("\n"), false);

  switch (biton32(layer_state)) {
    case 0:
      oled_write_P(PSTR("     "), false);
      break;
    case _NUM:
      oled_write_P(PSTR("Stage"), false);
      break;
    case _SYM:
      oled_write_P(PSTR("Comm "), false);
      break;
    case _NAV:
      oled_write_P(PSTR("Gyro "), false);
      break;
    case _GAMING_EXT:
      oled_write_P(PSTR("Ext  "), false);
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

  oled_write_P( (modifiers & MOD_MASK_CTRL)  ? PSTR("PROG ") : PSTR("     "), false);
  oled_write_P( (modifiers & MOD_MASK_SHIFT) ? PSTR("FUEL ") : PSTR("     "), false);
  oled_write_P( (modifiers & MOD_MASK_ALT)   ? PSTR("AUX  ") : PSTR("     "), false);
  oled_write_P( (modifiers & MOD_MASK_GUI)   ? PSTR("DOCK ") : PSTR("     "), false);

  oled_write_P(PSTR("\n"), false);

  uint8_t led_usb_state = host_keyboard_leds();
  oled_write_P(PSTR("Mode:\n"), false);
  oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK)    ? PSTR(" NUM ") : PSTR("     "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK)   ? PSTR(" CAPS") : PSTR("     "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR(" SCRL") : PSTR("     "), false);
}

void oled_task_user(void) {
  if (is_master) {
    render_status();     // Renders the current keyboard state (layer, lock, caps, scroll, etc)
  } else {
    render_crkbd_logo();
    // oled_scroll_left();  // Turns on scrolling
  }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}
