#pragma once

#define TAPPING_TERM 160
#define PERMISSIVE_HOLD

// Turn off RGB when computer goes to sleep
#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT_SLEEP
#    undef RGBLIGHT_ANIMATIONS

#    define RGBLIGHT_LAYERS
#    undef RGBLED_NUM
#    define RGBLED_NUM 16  // Number of LEDs
#    define RGBLIGHT_LIMIT_VAL 225
#endif // RGBLIGHT_ENABLE

#undef PRODUCT
#define PRODUCT Keyboard van Marina

#undef DEBOUNCE
#define DEBOUNCE 20
