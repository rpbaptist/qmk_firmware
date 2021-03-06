#This enables Link Time Optimization.This can save a good chunk of space(several KB for me), but the macro and function... functions cause it to error out.
LTO_ENABLE = yes

#Build Options
#change to "no" to disable the options, or define them in the Makefile in
#the appropriate keymap folder that will get included automatically
#
EXTRAKEY_ENABLE    = yes  # Audio control and System control(+450)
NKRO_ENABLE        = yes  # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE    = yes   # Enable WS2812 RGB underlight.

DYNAMIC_MACRO_ENABLE = no
MOUSEKEY_ENABLE    = no   # Mouse keys(+4700)
BOOTMAGIC_ENABLE   = no   # Virtual DIP switch configuration(+1000)
CONSOLE_ENABLE     = no   # Console for debug(+400)
COMMAND_ENABLE     = no   # Commands for debug and configuration
BACKLIGHT_ENABLE   = no   # Enable keyboard backlight functionality
MIDI_ENABLE        = no   # MIDI controls
AUDIO_ENABLE       = no   # Audio output on port C6
UNICODE_ENABLE     = no   # Unicode
BLUETOOTH_ENABLE   = no   # Enable Bluetooth with the Adafruit EZ-Key HID
SWAP_HANDS_ENABLE  = no   # Enable one-hand typing
SPACE_CADET_ENABLE = no

INDICATOR_LIGHTS  = no
RGBLIGHT_TWINKLE  = no
RGBLIGHT_STARTUP_ANIMATION = no

BOOTLOADER       = qmk-dfu
