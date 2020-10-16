/* Copyright 2020
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "process_grave_esc.h"

bool process_bsp_del(uint16_t keycode, keyrecord_t *record) {
    static uint8_t saved_mods   = 0;

    if (keycode == KC_BSDL) {
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
    }
    return true;
}
