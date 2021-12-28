// Taken from here: https://github.com/callum-oakley/qmk_firmware/tree/d63988caaf86217cfddf903c2c32dc042a8ef4da/users/callum
#include "swapper.h"

// The arrow keys and shift don't count since they're typically used to help
// navigate in a typical window-switching scenario.
bool is_swapper_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case KC_LSFT:
        case KC_UP:
        case KC_LEFT:
        case KC_DOWN:
        case KC_RGHT:
            return true;
        default:
            return false;
    }
}

void update_swapper(bool *active, uint16_t cmdish, uint16_t tabish, uint16_t trigger, uint16_t keycode, keyrecord_t *record) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(cmdish);
            }
            register_code(tabish);
        } else {
            // Don't unregister cmdish until some other key is hit or released.
            unregister_code(tabish);
        }
    } else if (*active && !is_swapper_ignored_key(keycode)) {
        unregister_code(cmdish);
        *active = false;
    }
}
