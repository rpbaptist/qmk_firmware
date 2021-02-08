#include QMK_KEYBOARD_H

enum layer_names {
  _QWERTY,
  _FUNCTION
};

#define S_FN MO(_FUNCTION)

const rgblight_segment_t PROGMEM qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 16, HSV_GREEN}
);
const rgblight_segment_t PROGMEM function_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 16, HSV_MAGENTA}
);
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    qwerty_layer, function_layer
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------------------------------------------------------.
   * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \ | Del  |
   * ,-----------------------------------------------------------------------------------------.
   * |-----------------------------------------------------------------------------------------+
   * | Tab    |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  | Bkspc  |
   * |-----------------------------------------------------------------------------------------+
   * |   Fn    |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |     Enter   |
   * |-----------------------------------------------------------------------------------------+
   * | Shift     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | Fn  |  U  | Sft |
   * |-----------------------------------------------------------------------------------------+
   * | Ctrl | Super |  Alt  |              Space                 | Alt | Sup |  L  |  D  |  R  |
   * `-----------------------------------------------------------------------------------------'
   */

  [_QWERTY] = LAYOUT_directional_full_space(
      KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_DEL,
      KC_TAB,    KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,     KC_BSPC,
      S_FN,         KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,        KC_ENT,
      KC_LSFT,        KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, S_FN, KC_UP, KC_RSFT,
      KC_LCTL, KC_LALT, KC_LGUI,         KC_SPC,                   KC_RALT, KC_RGUI, KC_LEFT, KC_DOWN, KC_RIGHT
      ),

  /* Function Layer
   * ,-----------------------------------------------------------------------------------------.
   * |  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |     |PrSc |
   * |-----------------------------------------------------------------------------------------+
   * | Reset  |     |     |     |     |     |     |     |     |     | PsPl | Prv | Nxt | Stop  |
   * |-----------------------------------------------------------------------------------------+
   * |         |     |     |     |     |     |     |     |     |     |     |     |             |
   * |-----------------------------------------------------------------------------------------+
   * |           |     |     |     |     |     |     |     | Vol-| Vol+| Mute|     | PGUP| CAPS|
   * |-----------------------------------------------------------------------------------------+
   * |      |       |       |                                    |     |     | HOME| PGDN| END |
   * `-----------------------------------------------------------------------------------------'
   */

  [_FUNCTION] = LAYOUT_directional_full_space(
       KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, _______, KC_PSCR,
        RESET,      _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_MPRV, KC_MNXT,      KC_MSTP,
      _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______,
      _______,           _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, KC_PGUP, KC_CAPS,
      _______,   _______,   _______,                        _______,                             _______, _______, KC_HOME, KC_PGDN, KC_END
      )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _QWERTY));
    rgblight_set_layer_state(1, layer_state_cmp(state, _FUNCTION));
    return state;
}
