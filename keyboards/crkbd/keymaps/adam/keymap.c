/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#include QMK_KEYBOARD_H
#include "version.h"
#include <stdio.h>

enum layers {
    _WIN_BASE,  // default layer
    _MAC_BASE,  // default layer but with Mac keys
    _SYMB,      // symbols
    _NUM,       // numbers
    _FUN,       // fn keys
    _NAV,       // navigation keys
    _MDIA,      // media keys
};

enum custom_keycodes {
    // Ctrl on Mac, GUI on Win
    MAC_CTRL_WIN_GUI = SAFE_RANGE,
    // GUI on Mac, ctrl on Win
    MAC_GUI_WIN_CTRL,
    // (, {, and [ based on which modifier is held
    KC_LEFT_ENCLOSE,
    // ), }, and ] based on which modifier is held
    KC_RIGHT_ENCLOSE,
};

// Left-hand home row mods on Windows: GACS (Gui → Alt → Ctrl → Shift)
// ("W_HM" = "Windows home")
#define W_HM_A LGUI_T(KC_A)
#define W_HM_S LALT_T(KC_S)
#define W_HM_D LCTL_T(KC_D)
#define W_HM_F LSFT_T(KC_F)

// Right-hand home row mods on Windows: SCAG
// All of these use the left-hand modifier to make some of the custom code
// easier to write (since there's only a need to check, unset, or set a single
// modifier rather than both).
#define W_HM_J LSFT_T(KC_J)
#define W_HM_K LCTL_T(KC_K)
#define W_HM_L LALT_T(KC_L)
#define W_HM_QUOT LGUI_T(KC_QUOT)

// Left-hand home row mods on Mac: CAGS
#define M_HM_A LCTL_T(KC_A)
#define M_HM_S LALT_T(KC_S)
#define M_HM_D LGUI_T(KC_D)
#define M_HM_F LSFT_T(KC_F)

// Right-hand home row mods on Mac: SGAC
#define M_HM_J LSFT_T(KC_J)
#define M_HM_K LGUI_T(KC_K)
#define M_HM_L LALT_T(KC_L)
#define M_HM_QUOT LCTL_T(KC_QUOT)

// The number of per-key LEDs on each side of a 5-column Corne.
#define NUM_LEDS_PER_SIDE 24

// keyboards/crkbd/rev1/rev1.c has a hard-coded g_led_config with 27 LEDs, so we
// have to work around this.
#define NUM_LEDS_PER_SIDE_ON_NORMAL_CORNE 27

// The LEDs are so bright on the Corne, so we set the intensity pretty low.
#define LED_INTENSITY 0x16

// Define the usual colors using the desired LED_INTENSITY defined above.
#define RGB_DARK_BLUE 0x00, 0x00, LED_INTENSITY
#define RGB_DARK_CYAN 0x00, LED_INTENSITY, LED_INTENSITY
#define RGB_DARK_GREEN 0x00, LED_INTENSITY, 0x00
#define RGB_DARK_MAGENTA LED_INTENSITY, 0x00, LED_INTENSITY
#define RGB_DARK_RED LED_INTENSITY, 0x00, 0x00
#define RGB_DARK_WHITE LED_INTENSITY, LED_INTENSITY, LED_INTENSITY
#define RGB_DARK_YELLOW LED_INTENSITY, LED_INTENSITY, 0x00

enum combos { UI_HYPHEN, UIO_CAPS, COMBO_LENGTH };
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM ui_hyphen[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM uio_caps[]  = {KC_U, KC_I, KC_O, COMBO_END};

combo_t key_combos[] = {
    [UI_HYPHEN] = COMBO(ui_hyphen, KC_MINS),
    [UIO_CAPS]  = COMBO(uio_caps, KC_CAPS),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_WIN_BASE] = LAYOUT_split_3x5_3(
         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,     KC_U,    KC_I,    KC_O,               KC_P,
       W_HM_A,  W_HM_S,  W_HM_D,  W_HM_F,    KC_G,                         KC_H,   W_HM_J,  W_HM_K,  W_HM_L,          W_HM_QUOT,
 LCTL_T(KC_Z),    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,     KC_M, KC_COMM,  KC_DOT, LT(_MDIA, KC_SLSH),
    LT(_FUN, KC_ESC),  LT(_NAV, KC_SPC), LT(_NUM, KC_TAB),               KC_ENT, LT(_SYMB, KC_BSPC), MO(_NAV)
  ),

  [_MAC_BASE] = LAYOUT_split_3x5_3(
         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,     KC_U,    KC_I,    KC_O,               KC_P,
       M_HM_A,  M_HM_S,  M_HM_D,  M_HM_F,    KC_G,                         KC_H,   M_HM_J,  M_HM_K,  M_HM_L,          M_HM_QUOT,
 LGUI_T(KC_Z),    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,     KC_M, KC_COMM,  KC_DOT, LT(_MDIA, KC_SLSH),
    LT(_FUN, KC_ESC),  LT(_NAV, KC_SPC), LT(_NUM, KC_TAB),               KC_ENT, LT(_SYMB, KC_BSPC), MO(_NAV)
  ),

  [_SYMB] = LAYOUT_split_3x5_3(
    KC_MINS,    S(KC_MINS),         KC_EQL,       S(KC_EQL), KC_BSLS,         _______, _______,          _______, _______,         _______,
    KC_QUOT,    S(KC_QUOT),KC_LEFT_ENCLOSE,KC_RIGHT_ENCLOSE,  KC_GRV,         _______, KC_LSFT, MAC_GUI_WIN_CTRL, KC_LALT,MAC_CTRL_WIN_GUI,
    KC_SCLN,    S(KC_SCLN),        KC_LBRC,         KC_RBRC, _______,         _______, _______,          _______, _______,         _______,
                                           _______, _______, _______,         _______, _______, _______
  ),

  [_NUM] = LAYOUT_split_3x5_3(
             _______, _______,         _______, _______, _______,            KC_NLCK,      KC_7, KC_8, KC_9, S(KC_EQL),
    MAC_CTRL_WIN_GUI, KC_LALT,MAC_GUI_WIN_CTRL, KC_LSFT, _______,            S(KC_SCLN),   KC_4, KC_5, KC_6, KC_MINS,
             _______, _______,         _______, _______, _______,            KC_COMM,      KC_1, KC_2, KC_3, _______,
                                       _______, _______, _______,            KC_DOT,    _______, KC_0
  ),

  [_FUN] = LAYOUT_split_3x5_3(
                KC_1,    KC_2,            KC_3,    KC_4,    KC_5,            _______, KC_F7,     KC_F8, KC_F9, KC_F12,
    MAC_CTRL_WIN_GUI, KC_LALT,MAC_GUI_WIN_CTRL, KC_LSFT, _______,            _______, KC_F4,     KC_F5, KC_F6, KC_F11,
                KC_6,    KC_7,            KC_8,    KC_9,    KC_0,            _______, KC_F1,     KC_F2, KC_F3, KC_F10,
                                       _______, _______, _______,            _______, KC_CAPS, _______
  ),
  [_NAV] = LAYOUT_split_3x5_3(
             _______, RCS(KC_TAB),         _______,C(KC_TAB), _______,            KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_TAB,
    MAC_CTRL_WIN_GUI,     KC_LALT,MAC_GUI_WIN_CTRL, KC_LSFT, _______,            KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC,
             _______,     _______,         _______, _______, _______,            KC_ESC,  KC_BSPC, KC_ENT,  KC_DEL, _______,
                                           _______, _______, _______,            _______, KC_BSPC, _______
  ),
  [_MDIA] = LAYOUT_split_3x5_3(
               RESET, _______,          RGB_TOG, DF(_MAC_BASE), DF(_WIN_BASE),     KC_WH_U, KC_MPRV, KC_MS_U, KC_MNXT, KC_PSCR,
    MAC_CTRL_WIN_GUI, KC_LALT, MAC_GUI_WIN_CTRL,       KC_LSFT, _______,           KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, _______,
             _______, _______,          _______,       _______, _______,           KC_MUTE, KC_VOLD, KC_MPLY, KC_VOLU, _______,
                                        _______,       _______, _______,           KC_BTN3, KC_BTN1, KC_BTN2
  )
};
// clang-format on

// This is a thin wrapper around rgb_matrix_set_color which allows you to put
// the same firmware on both halves of the keyboard (other than a #define for
// `MASTER_LEFT` or `MASTER_RIGHT`) and still have the correct LEDs light up
// regardless of which half has the USB cable in it.
//
// This complexity behind this logic is explained in the comments within the
// function itself.
void set_color_split(uint8_t key_code, uint8_t r, uint8_t g, uint8_t b) {
    // When using defines for MASTER_LEFT and MASTER_RIGHT, is_keyboard_left()
    // will be inaccurate. For example, (is_keyboard_left() &&
    // !is_keyboard_master()) can NEVER be true.
#ifdef MASTER_LEFT
    bool is_left = true;
#endif
#ifdef MASTER_RIGHT
    bool is_left = false;
#endif

    bool left_is_master = (is_keyboard_master() && is_left) || (!is_keyboard_master() && !is_left);

    // Note on constants: 23 is the number of LEDs on each side (24) minus 1.
    // 27 is the number of LEDs that the Corne normally has with six columns.

    // Rule #1: you must set the LED based on what the master's range is. So if
    // the USB cable is in the left half, then the range is 0-23, otherwise it's
    // 27-50.

    // Rule #2: each half of the keyboard can only set its own LEDs, it's just
    // that the codes change according to Rule #1.

    // Rule #2
    if ((is_left && key_code >= NUM_LEDS_PER_SIDE) || (!is_left && key_code < NUM_LEDS_PER_SIDE)) {
        return;
    }

    // Rule #1
    if (left_is_master && key_code >= NUM_LEDS_PER_SIDE)
        key_code -= NUM_LEDS_PER_SIDE_ON_NORMAL_CORNE;
    else if (!left_is_master && key_code < NUM_LEDS_PER_SIDE)
        key_code += NUM_LEDS_PER_SIDE_ON_NORMAL_CORNE;
    rgb_matrix_set_color(key_code, r, g, b);
}

// Sets all keycodes specified in the array to the given color. This is good for
// coloring arbitrary keys like WASD or all of the number keys at once.
void set_all_keys_colors(const uint8_t keycodes[], uint8_t len, uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = 0; i < len; ++i) {
        set_color_split(keycodes[i], r, g, b);
    }
}

// Sets keys that fall within a contiguous keycode range to a given color.
// The start and end codes are inclusive.
void set_color_for_contiguous_keycodes(uint8_t start_code, uint8_t end_code, uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = start_code; i <= end_code; ++i) {
        set_color_split(i, r, g, b);
    }
}

void light_up_left_mods(uint8_t r, uint8_t g, uint8_t b) {
    const uint8_t left_mod_keycodes[] = {22, 19, 16, 11};
    set_all_keys_colors(left_mod_keycodes, sizeof(left_mod_keycodes) / sizeof(uint8_t), r, g, b);
}

void light_up_right_mods(uint8_t r, uint8_t g, uint8_t b) {
    const uint8_t right_mod_keycodes[] = {38, 43, 46, 49};
    set_all_keys_colors(right_mod_keycodes, sizeof(right_mod_keycodes) / sizeof(uint8_t), r, g, b);
}

bool is_mac_the_default(void) { return layer_state_cmp(default_layer_state, _MAC_BASE); }

bool is_shift_held(void) { return (get_mods() & MOD_BIT(KC_LSFT)) || (get_mods() & MOD_BIT(KC_RSFT)); }
bool is_ctrl_held(void) { return get_mods() & MOD_BIT(KC_LCTL); }
bool is_gui_held(void) { return get_mods() & MOD_BIT(KC_LGUI); }

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Diagram of underglow LEDs on the LH side when viewed from above:
    // 2   1   0
    // 3   4   5
    // (i.e. LED 0 is underneath the "R" key on a QWERTY keyboard)
    //
    // Diagram of per-key LEDs on the LH side when viewed from above:
    //  23  18  17  10  9
    //  22  19  16  11  8
    //  21  20  15  12  7
    //           14  13  6
    //
    // LEDs 24, 25, and 26 don't exist.
    //
    // Diagram of underglow LEDs on the RH side when viewed from above:
    // 27  28  29
    // 32  31  30
    // (i.e. LED 29 is underneath the "P" key on a QWERTY keyboard)
    //
    // Diagram of per-key LEDs on the RH side when viewed from above:
    //   36  37  44  45  50
    //   35  38  43  46  49
    //   34  39  42  47  48
    //  33  40  41

    switch (get_highest_layer(layer_state)) {
        case _WIN_BASE:
            // Common colors between Windows and Mac
            if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) {
                // When caps lock is on, make it REALLY obvious.
                set_color_for_contiguous_keycodes(0, 50, RGB_DARK_MAGENTA);
            }

            // Make it easy to tell when each home-row mod is held for long
            // enough by lighting up the corresponding LEDs on both sides of the
            // keyboard.
            if (is_shift_held()) {
                set_color_split(11, RGB_DARK_GREEN);  // 'F' key
                set_color_split(38, RGB_DARK_GREEN);  // 'J' key
            }
            if (get_mods() & MOD_BIT(KC_LALT)) {
                set_color_split(19, RGB_DARK_GREEN);  // 'S' key
                set_color_split(46, RGB_DARK_GREEN);  // 'L' key
            }

            set_color_split(14, RGB_DARK_WHITE);    // LH thumb key 1
            set_color_split(13, RGB_DARK_MAGENTA);  // LH thumb key 2
            set_color_split(6, RGB_DARK_GREEN);     // LH thumb key 3
            set_color_split(40, RGB_DARK_BLUE);     // RH thumb key 2

            // MAC (this is here because default layers just work strangely I
            // guess; when the Mac layer is default, the Windows layer is still
            // the highest layer)
            if (is_mac_the_default()) {
                if (is_ctrl_held()) {
                    set_color_split(22, RGB_DARK_GREEN);  // 'A' key
                    set_color_split(49, RGB_DARK_GREEN);  // ';' key
                }
                if (is_gui_held()) {
                    set_color_split(16, RGB_DARK_GREEN);  // 'D' key
                    set_color_split(43, RGB_DARK_GREEN);  // 'K' key
                }
                // Set underglow
                set_color_for_contiguous_keycodes(0, 5, 0x32, 0x32, 0x32);
                set_color_for_contiguous_keycodes(27, 32, 0x32, 0x32, 0x32);
            } else {
                // WINDOWS
                if (is_gui_held()) {
                    set_color_split(22, RGB_DARK_GREEN);  // 'A' key
                    set_color_split(49, RGB_DARK_GREEN);  // ';' key
                }
                if (is_ctrl_held()) {
                    set_color_split(16, RGB_DARK_GREEN);  // 'D' key
                    set_color_split(43, RGB_DARK_GREEN);  // 'K' key
                }
                // Set underglow
                set_color_for_contiguous_keycodes(0, 5, 0x00, 0x32, 0x00);
                set_color_for_contiguous_keycodes(27, 32, 0x00, 0x32, 0x00);
            }

            break;
        case _SYMB: {
            light_up_right_mods(RGB_DARK_BLUE);
            set_color_for_contiguous_keycodes(8, 23, RGB_DARK_BLUE);
            break;
        }
        case _NUM: {
            light_up_left_mods(RGB_DARK_GREEN);
            set_color_split(36, RGB_DARK_RED);  // 'Y' key
            if (host_keyboard_leds() & (1 << USB_LED_NUM_LOCK)) {
                set_color_split(36, RGB_DARK_YELLOW);  // 'Y' key
            }

            set_color_split(33, RGB_DARK_BLUE);  // Period key

            const uint8_t numpad_keycodes[] = {41, 37, 44, 45, 38, 43, 46, 39, 42, 47};
            set_all_keys_colors(numpad_keycodes, sizeof(numpad_keycodes) / sizeof(uint8_t), RGB_DARK_GREEN);
            break;
        }
        case _FUN: {
            light_up_left_mods(RGB_DARK_WHITE);

            set_color_split(40, RGB_DARK_RED);  // Caps-lock key
            if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) {
                set_color_split(40, RGB_DARK_MAGENTA);  // Caps-lock key
            }
            const uint8_t numpad_keycodes[] = {37, 44, 45, 38, 43, 46, 39, 42, 47, 50, 49, 48};
            set_all_keys_colors(numpad_keycodes, sizeof(numpad_keycodes) / sizeof(uint8_t), RGB_DARK_WHITE);
            break;
        }
        case _NAV: {
            light_up_left_mods(RGB_DARK_MAGENTA);
            set_color_split(34, RGB_DARK_WHITE);   // 'N' key
            set_color_split(50, RGB_DARK_WHITE);   // 'P' key
            set_color_split(49, RGB_DARK_WHITE);   // ';' key
            set_color_split(39, RGB_DARK_RED);     // 'M' key
            set_color_split(42, RGB_DARK_WHITE);   // ',' key
            set_color_split(47, RGB_DARK_RED);     // '.' key
            set_color_split(36, RGB_DARK_GREEN);   // 'Y' key
            set_color_split(35, RGB_DARK_GREEN);   // 'H' key
            set_color_split(37, RGB_DARK_YELLOW);  // 'U' key
            set_color_split(45, RGB_DARK_YELLOW);  // 'O' key

            const uint8_t keycodes[] = {44 /*I*/, 38 /*J*/, 43 /*K*/, 46 /*L*/};
            set_all_keys_colors(keycodes, sizeof(keycodes) / sizeof(uint8_t), RGB_DARK_MAGENTA);
            break;
        }
        case _MDIA: {
            light_up_left_mods(RGB_DARK_CYAN);

            const uint8_t media_keycodes[] = {37, 45, 39, 42, 47};
            set_all_keys_colors(media_keycodes, sizeof(media_keycodes) / sizeof(uint8_t), RGB_DARK_WHITE);
            set_color_split(34, RGB_DARK_RED);  // 'B' key

            set_color_split(9, RGB_DARK_GREEN);   // Win key
            set_color_split(10, RGB_DARK_WHITE);  // Mac key
            set_color_split(23, RGB_DARK_RED);    // RESET key

            set_color_split(50, RGB_DARK_YELLOW);  // 'P' key

            set_color_split(36, RGB_DARK_GREEN);  // 'Y' key
            set_color_split(35, RGB_DARK_GREEN);  // 'H' key

            const uint8_t keycodes[] = {44 /*I*/, 38 /*J*/, 43 /*K*/, 46 /*L*/, 33, 40, 41};
            set_all_keys_colors(keycodes, sizeof(keycodes) / sizeof(uint8_t), RGB_DARK_CYAN);
            break;
        }
        default:
            break;
    }
}
#endif

void keyboard_post_init_user(void) {
    rgblight_sethsv(HSV_MAGENTA);

    // This is good in case I screw anything up with bad code; it's REALLY hard
    // to fix it when mods get messed up since it can mess up the whole OS.
    clear_mods();
}

// https://github.com/qmk/qmk_firmware/issues/4611#issuecomment-446713700
// https://www.reddit.com/r/olkb/comments/oflwv6/how_do_i_change_qmk_layer_tap_behavior/h4l7u8n/?utm_source=reddit&utm_medium=web2x&context=3
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool isPressed   = record->event.pressed;
    bool isCtrlHeld  = is_ctrl_held();
    bool isShiftHeld = is_shift_held();

    switch (keycode) {
        case MAC_CTRL_WIN_GUI: {
            // When in Mac, send ctrl. When on Windows, send GUI.
            uint16_t mod = is_mac_the_default() ? KC_LCTL : KC_LGUI;
            if (isPressed) {
                register_mods(MOD_BIT(mod));
            } else {
                unregister_mods(MOD_BIT(mod));
            }
            return false;
        }
        case MAC_GUI_WIN_CTRL: {
            // When in Mac, send GUI. When on Windows, send ctrl.
            uint16_t mod = is_mac_the_default() ? KC_LGUI : KC_LCTL;
            if (isPressed) {
                register_mods(MOD_BIT(mod));
            } else {
                unregister_mods(MOD_BIT(mod));
            }
            return false;
        }
        case KC_LEFT_ENCLOSE:
            // No mod → (
            // Ctrl → [
            // Shift → {
            if (isPressed && (IS_LAYER_ON(_NAV) || IS_LAYER_ON(_SYMB))) {
                if (isCtrlHeld && !isShiftHeld) {
                    unregister_mods(MOD_BIT(KC_LCTL));
                    tap_code_delay(KC_LBRC, 0);
                    register_mods(MOD_BIT(KC_LCTL));
                } else if (isShiftHeld) {
                    tap_code_delay(KC_LBRC, 0);
                } else {
                    tap_code16(S(KC_9));
                }
                return false;
            }
            break;
        case KC_RIGHT_ENCLOSE:
            // No mod → )
            // Ctrl → ]
            // Shift → }
            if (isPressed && (IS_LAYER_ON(_NAV) || IS_LAYER_ON(_SYMB))) {
                if (isCtrlHeld && !isShiftHeld) {
                    unregister_mods(MOD_BIT(KC_LCTL));
                    tap_code_delay(KC_RBRC, 0);
                    register_mods(MOD_BIT(KC_LCTL));
                } else if (isShiftHeld) {
                    tap_code_delay(KC_RBRC, 0);
                } else {
                    tap_code16(S(KC_0));
                }
                return false;
            }
            break;
    }

    return true;
}

#ifdef TAPPING_TERM_PER_KEY
// Increasing the tapping term means that dual-function keys have to be held for
// longer before they're treated as their "hold" action.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // The shift keys are much more common and typically more deliberate as
        // a result.
        case W_HM_F:
        case W_HM_J:
            return TAPPING_TERM - 30;
        // "A" and "S" are the source of a lot of rolls, so activating their
        // hold functions too soon can be a cause of frustration.
        //
        // I just tend to hold "L" for longer, and since it's bound to alt and
        // all of my numbers are also on my right hand, I may as well increase
        // it.
        //
        // Note that it seems like an absolute value of about 185 is good.
        case W_HM_A:
        case M_HM_A:
        case W_HM_S:
        case W_HM_L:
            // case M_HM_L: // ← this is the same between Windows and Mac
            // case M_HM_S: // ← this is the same between Windows and Mac
            return TAPPING_TERM + 25;
        default:
            return TAPPING_TERM;
    }
}
#endif

#ifdef PERMISSIVE_HOLD_PER_KEY
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Make DF JK be permissive-hold keys. I don't want pinkies to be
        // permissive hold due to rolling those more frequently. I learned the
        // same thing happens with my ring fingers too (especially with the word
        // "said").
        // Windows
        case W_HM_D:
        case W_HM_F:
        case W_HM_J:
        case W_HM_K:
        // Mac
        // case M_HM_F: // ← this is the same between Windows and Mac
        // case M_HM_J: // ← this is the same between Windows and Mac
        case M_HM_D:
        case M_HM_K:
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}
#endif

#ifdef COMBO_TERM_PER_COMBO
uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        // "UI" is a common enough bigram in software engineering ("UI",
        // "build", "requirements") that the combo time needs to be pretty low
        // so that natural typing doesn't trigger it.
        case UI_HYPHEN:
            return 20;
    }

    return COMBO_TERM;
}
#endif
