#include QMK_KEYBOARD_H

extern uint8_t  is_master;
static uint32_t oled_timer           = 0;
bool            alt_tab_used         = false;
bool            switched_from_gaming = false;

#ifdef RGB_MATRIX_ENABLE
static uint32_t hypno_timer;
#endif

enum layer_names {
  _COLEMAKDH,
  _GAMING,
  _GAMING_EXT,
  _NUMPAD,
  _SYM,
  _NAV,
  _UTIL
};

enum custom_keycodes {
    BSP_DEL = SAFE_RANGE,
    RGB_RST,  // Reset RGB
    RGB_UND,  // Toggle RGB underglow as layer indicator
    RGB_ATG,  // Toggle active RGB mode
    RGB_PST,  // Toggle simple passive RGB mode
    RGB_PCT,  // Toggle colorful passive RGB mode
    RGB_IDL,  // RGB Idling animations
    TGL_LYR   // Toggle main layer from GAMING to COLEMAKDH and back,
};

typedef union {
    uint32_t raw;
    struct {
        bool     rgb_layer_indicator : 1;
        bool     rgb_matrix_idle_anim : 1;
        uint8_t  rgb_matrix_active_mode : 4;
        uint8_t  rgb_matrix_idle_mode : 4;
        uint8_t  rgb_matrix_active_speed : 8;
        uint8_t  rgb_matrix_idle_speed : 8;
        uint32_t rgb_matrix_idle_timeout : 32;
    };
} user_config_t;

user_config_t user_config;

// Layer toggle and switch
#define T_NAV TT(_NAV)
#define S_NAV MO(_NAV)

#define T_SYM TT(_SYM)
#define S_SYM MO(_SYM)

// Layer keys with functionality on tap
#define NAV_0 LT(_NAV, KC_0)
#define TAB_NUM LT(_NUMPAD, KC_TAB)
#define LCK_NMP TG(_NUMPAD)
#define S_NUM MO(_NUMPAD)

#define EXTALT LT(_GAMING_EXT, KC_LALT)

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
