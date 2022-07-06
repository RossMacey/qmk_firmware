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
#include "swapper.h"
#include "customkeys.h"
#include "oneshot.h"

enum layers {
    _BASE,   // default layer
    _SYMB,   // symbols
    _NUM,    // numbers
    _FUN,    // fn keys
    _NAV,    // navigation keys
    _NAVLH,  // navigation keys but sort of mirrored so that arrows are on the LH
    _MDIA,   // media keys
};

// This is just to save space over typing "_______" in layouts.
#define XXX KC_NO

#define LT_NAV_SPACE LT(_NAV, KC_SPC)
#define LT_MDIA_QUOT LT(_MDIA, KC_QUOT)
#define MO_NAV MO(_NAV)
#define MO_FUN MO(_FUN)
#define MO_NUM MO(_NUM)
#define MO_SYMB MO(_SYMB)

#define LED_INTENSITY 0xBB

// Define the usual colors using the desired LED_INTENSITY defined above.
#define RGB_DARK_BLUE 0x00, 0x00, LED_INTENSITY
#define RGB_DARK_CYAN 0x00, LED_INTENSITY, LED_INTENSITY
#define RGB_DARK_GREEN 0x00, LED_INTENSITY, 0x00
#define RGB_DARK_MAGENTA LED_INTENSITY, 0x00, LED_INTENSITY
#define RGB_DARK_RED LED_INTENSITY, 0x00, 0x00
#define RGB_DARK_WHITE LED_INTENSITY, LED_INTENSITY, LED_INTENSITY
#define RGB_DARK_YELLOW LED_INTENSITY, LED_INTENSITY, 0x00

enum combos { UI_HYPHEN, UIO_CAPS, JKL_CAPS, MCOMMA_BACKSPACE, COMMADOT_ENTER, MDOT_TAB, NDOT_ESC, COMBO_LENGTH };
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM ui_hyphen[]        = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM uio_caps[]         = {KC_U, KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM jkl_caps[]         = {KC_J, KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM mcomma_backspace[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM commadot_enter[]   = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM mdot_tab[]         = {KC_M, KC_DOT, COMBO_END};
const uint16_t PROGMEM ndot_esc[]         = {KC_N, KC_DOT, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [UI_HYPHEN]         = COMBO(ui_hyphen, KC_MINS),
    [UIO_CAPS]          = COMBO(uio_caps, KC_CAPS),
    [JKL_CAPS]          = COMBO(jkl_caps, KC_CAPS),
    [MCOMMA_BACKSPACE]  = COMBO(mcomma_backspace, KC_BSPC),
    [COMMADOT_ENTER]    = COMBO(commadot_enter, KC_ENT),
    [MDOT_TAB]          = COMBO(mdot_tab, KC_TAB),
    [NDOT_ESC]          = COMBO(ndot_esc, KC_ESC),
};
// clang-format on

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_moonlander(
        XXX,      XXX,     XXX,     XXX,     XXX,     XXX,    XXX,              XXX,  XXX,    XXX,    XXX,    XXX,         XXX,    XXX,
        KC_LSFT,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXX,             XXX, KC_Y,   KC_U,  KC_I,   KC_O,         KC_P,    KC_LSFT,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXX,              XXX, KC_H,   KC_J,  KC_K,   KC_L, LT_MDIA_QUOT,    KC_LCTL,
        KC_LSFT, LCTL_T(KC_Z), KC_X,    KC_C,    KC_V,    KC_B,                                KC_N,     KC_M, KC_COMM,  KC_DOT,  LCTL_T(KC_SLSH),   KC_LSFT,
            XXX,XXX,XXX,XXX,MO_FUN,XXX,                                         XXX,OS_SHFT,XXX,XXX,XXX,XXX,
                LT_NAV_SPACE,MO_NUM, XXX,                                       XXX,  MO_SYMB, MO_NAV
    ),

    [_SYMB] = LAYOUT_moonlander(
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______,   _______,   _______,    _______, _______,
        _______, KC_MINS, S(KC_MINS),         KC_EQL,       S(KC_EQL), KC_BSLS,XXX,       XXX,   MW_COPY,   S(KC_7),    S(KC_8),    KC_DOT ,   MW_PSTE, _______,
        _______, KC_QUOT, S(KC_QUOT),KC_LEFT_ENCLOSE,KC_RIGHT_ENCLOSE,  KC_GRV,XXX,       XXX, REV_COLON,   OS_SHFT,    OS_CTRL,    OS_ALT ,   OS_GUI , _______,
        _______, KC_SCLN, S(KC_SCLN),        KC_LBRC,         KC_RBRC, KC_3GRV,                             KC_MINS,    S(KC_1), S(KC_COMM), S(KC_DOT), S(KC_SLSH), _______,
        _______, _______, _______, _______, _______,        _______,           _______,          _______,   _______,   _______,    _______, _______,
                                            _______, _______, _______,           _______,_______,_______
    ),

    [_NUM] = LAYOUT_moonlander(
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______,    _______, _______,
        _______, _______, KC_LEFT,  KC_DOT, KC_RGHT, _______, _______,           _______, KC_NLCK, KC_7, KC_8, KC_9, S(KC_EQL), _______,
        _______, OS_GUI , OS_ALT , OS_CTRL, OS_SHFT, _______,_______,       _______,    REV_COLON, KC_4, KC_5, KC_6,   KC_DOT, _______,
        _______, _______, _______, KC_COMM, _______, _______,                             KC_MINS, KC_1, KC_2, KC_3,  _______, _______,
        _______, _______, _______, _______, _______,        _______,             _______,          KC_0,  XXX,  XXX,  _______, _______,
                                            _______, _______, _______,           _______,KC_ENT, KC_BSPC
    ),

    [_FUN] = LAYOUT_moonlander(
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______,   _______,  _______,   _______, _______,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5, _______,              _______, _______, KC_F7, KC_F8, KC_F9, KC_F12, _______,
        _______,OS_GUI,  OS_ALT, OS_CTRL, OS_SHFT, _______,_______,              _______, _______, KC_F4, KC_F5, KC_F6, KC_F11, _______,
        _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                                _______, KC_F1, KC_F2, KC_F3, KC_F10, _______,
        _______, _______, _______, _______, _______,        _______,             _______,          _______,   _______,  _______,   _______, _______,
                                            _______, _______, _______,           _______,_______, KC_CAPS
    ),

    [_NAV] = LAYOUT_moonlander(
        _______,_______,_______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, _______,
        _______, SW_WIN, RCS(KC_TAB), CLS_WIN,C(KC_TAB),    SW_APP, _______,     _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DWRD, _______,
        _______, OS_GUI,      OS_ALT, OS_CTRL,  OS_SHFT,TO(_NAVLH), _______,     _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,  KC_SPC, _______,
        _______, MW_UNDO,     MW_CUT, MW_COPY,  MW_PSTE,   MW_REDO,                        KC_ESC, KC_BSPC, KC_ENT,  KC_TAB,   KC_DEL, _______,
        _______, _______, _______, _______, _______,         _______,            _______,          _______,_______, _______, _______, _______,
                                            _______, _______, _______,           _______, KC_ENT, KC_BSPC
    ),

    [_NAVLH] = LAYOUT_moonlander(
        _______,_______,_______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, _______,
        _______,TO(_BASE), KC_HOME,   KC_UP,   KC_END, KC_PGUP, _______,         _______, _______, _______, _______, _______, _______, _______,
        _______,   KC_SPC, KC_LEFT, KC_DOWN,  KC_RGHT, KC_PGDN, _______,         _______, _______, OS_SHFT, OS_CTRL,  OS_ALT,  OS_GUI, _______,
        _______,   KC_DEL,  KC_TAB,  KC_ENT,  KC_BSPC,  KC_ESC,                           _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,         _______,            _______,          _______,_______, _______, _______, _______,
                                            TO(_BASE), _______, _______,           _______, KC_ENT, KC_BSPC
    ),

    [_MDIA] = LAYOUT_moonlander(
        _______,_______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______,  RESET, _______, RGB_TOG, _______, CG_TOGG, _______,           _______, KC_WH_U, KC_MPRV, KC_MS_U, KC_MNXT, KC_PSCR, _______,
        _______, OS_GUI,  OS_ALT, OS_CTRL, OS_SHFT, _______, _______,           _______, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,
        _______, _______, _______, _______, _______, _______,                             KC_MUTE, KC_VOLD, KC_MPLY, KC_VOLU, _______, _______,
        RGB_MOD, _______, _______, _______, _______,         _______,            _______,          KC_BTN2, _______, _______, _______, _______,
                                            _______, _______, _______,           _______, KC_BTN3, KC_BTN1
    ),
};
// clang-format on

// Sets all keycodes specified in the array to the given color. This is good for
// coloring arbitrary keys like WASD or all of the number keys at once.
void set_all_keys_colors(const uint8_t keycodes[], uint8_t len, uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = 0; i < len; ++i) {
        rgb_matrix_set_color(keycodes[i], r, g, b);
    }
}

// Sets keys that fall within a contiguous keycode range to a given color.
// The start and end codes are inclusive.
void set_color_for_contiguous_keycodes(uint8_t start_code, uint8_t end_code, uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = start_code; i <= end_code; ++i) {
        rgb_matrix_set_color(i, r, g, b);
    }
}

void light_up_left_mods(uint8_t r, uint8_t g, uint8_t b) {
    const uint8_t left_mod_keycodes[] = {7, 12, 17, 22};
    set_all_keys_colors(left_mod_keycodes, sizeof(left_mod_keycodes) / sizeof(uint8_t), r, g, b);
}

void light_up_right_mods(uint8_t r, uint8_t g, uint8_t b) {
    const uint8_t right_mod_keycodes[] = {58, 53, 48, 43};
    set_all_keys_colors(right_mod_keycodes, sizeof(right_mod_keycodes) / sizeof(uint8_t), r, g, b);
}

bool is_mac_the_default(void) { return keymap_config.swap_lctl_lgui; }

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

    // Set underglow
    // if (is_mac_the_default()) {
    //     set_color_for_contiguous_keycodes(0, 5, 0x32, 0x32, 0x32);
    //     set_color_for_contiguous_keycodes(27, 32, 0x32, 0x32, 0x32);
    // } else {
    //     set_color_for_contiguous_keycodes(0, 5, 0x00, 0x32, 0x00);
    //     set_color_for_contiguous_keycodes(27, 32, 0x00, 0x32, 0x00);
    // }

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            // Common colors between Windows and Mac
            if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) {
                // When caps lock is on, make it REALLY obvious.
                HSV hsv = {rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val()};
                RGB rgb = hsv_to_rgb(hsv);
                set_color_for_contiguous_keycodes(0, 71, rgb.r, rgb.g, rgb.b);
            }

            rgb_matrix_set_color(24, RGB_DARK_WHITE);  // LH thumb key 1
            // rgb_matrix_set_color(32, RGB_DARK_MAGENTA);  // LH thumb key 2
            rgb_matrix_set_color(33, RGB_DARK_GREEN);    // LH thumb key 3
            rgb_matrix_set_color(69, RGB_DARK_BLUE);     // RH thumb key 1
            rgb_matrix_set_color(68, RGB_DARK_MAGENTA);  // RH thumb key 2
            // rgb_matrix_set_color(69, RGB_DARK_WHITE);    // RH thumb key 3

            break;
        case _SYMB: {
            light_up_right_mods(RGB_DARK_BLUE);
            break;
        }
        case _NUM: {
            light_up_left_mods(RGB_DARK_GREEN);
            rgb_matrix_set_color(62, RGB_DARK_RED);  // 'Y' key
            if (host_keyboard_leds() & (1 << USB_LED_NUM_LOCK)) {
                rgb_matrix_set_color(62, RGB_DARK_YELLOW);  // 'Y' key
            }

            rgb_matrix_set_color(11, RGB_DARK_MAGENTA);  // 'W' key
            rgb_matrix_set_color(16, RGB_DARK_BLUE);     // 'E' key
            rgb_matrix_set_color(21, RGB_DARK_MAGENTA);  // 'R' key
            rgb_matrix_set_color(18, RGB_DARK_BLUE);     // 'C' key

            rgb_matrix_set_color(49, RGB_DARK_BLUE);  // Period key

            const uint8_t numpad_keycodes[] = {57, 52, 47, 58, 53, 48, 59, 54, 49, 60};
            set_all_keys_colors(numpad_keycodes, sizeof(numpad_keycodes) / sizeof(uint8_t), RGB_DARK_GREEN);
            break;
        }
        case _FUN: {
            light_up_left_mods(RGB_DARK_WHITE);

            rgb_matrix_set_color(69, RGB_DARK_RED);  // Caps-lock key
            if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) {
                rgb_matrix_set_color(69, RGB_DARK_MAGENTA);  // Caps-lock key
            }
            const uint8_t numpad_keycodes[] = {57, 52, 47, 42, 58, 53, 48, 43, 59, 54, 49, 44};
            set_all_keys_colors(numpad_keycodes, sizeof(numpad_keycodes) / sizeof(uint8_t), RGB_DARK_WHITE);
            break;
        }
        case _NAV: {
            light_up_left_mods(RGB_DARK_MAGENTA);
            rgb_matrix_set_color(64, RGB_DARK_WHITE);   // 'N' key
            rgb_matrix_set_color(59, RGB_DARK_RED);     // 'M' key
            rgb_matrix_set_color(54, RGB_DARK_WHITE);   // ',' key
            rgb_matrix_set_color(49, RGB_DARK_WHITE);   // '.' key
            rgb_matrix_set_color(44, RGB_DARK_RED);     // '/' key
            rgb_matrix_set_color(63, RGB_DARK_GREEN);   // 'H' key
            rgb_matrix_set_color(43, RGB_DARK_WHITE);   // ';' key
            rgb_matrix_set_color(62, RGB_DARK_GREEN);   // 'Y' key
            rgb_matrix_set_color(57, RGB_DARK_YELLOW);  // 'U' key
            rgb_matrix_set_color(47, RGB_DARK_YELLOW);  // 'O' key
            rgb_matrix_set_color(42, RGB_DARK_RED);     // 'P' key

            rgb_matrix_set_color(6, RGB_DARK_WHITE);   // 'Q' key
            rgb_matrix_set_color(11, RGB_DARK_GREEN);  // 'W' key
            rgb_matrix_set_color(16, RGB_DARK_RED);    // 'E' key
            rgb_matrix_set_color(21, RGB_DARK_GREEN);  // 'R' key
            rgb_matrix_set_color(26, RGB_DARK_WHITE);  // 'T' key
            rgb_matrix_set_color(27, RGB_DARK_WHITE);  // 'G' key

            const uint8_t keycodes[] = {52 /*I*/, 58 /*J*/, 53 /*K*/, 48 /*L*/};
            set_all_keys_colors(keycodes, sizeof(keycodes) / sizeof(uint8_t), RGB_DARK_MAGENTA);
            break;
        }
        case _NAVLH: {
            light_up_right_mods(RGB_DARK_MAGENTA);

            rgb_matrix_set_color(28, RGB_DARK_WHITE);   // 'B' key
            rgb_matrix_set_color(23, RGB_DARK_RED);     // 'V' key
            rgb_matrix_set_color(18, RGB_DARK_WHITE);   // 'C' key
            rgb_matrix_set_color(13, RGB_DARK_WHITE);   // 'X' key
            rgb_matrix_set_color(8, RGB_DARK_RED);      // 'Z' key
            rgb_matrix_set_color(27, RGB_DARK_GREEN);   // 'G' key
            rgb_matrix_set_color(7, RGB_DARK_WHITE);    // 'A' key
            rgb_matrix_set_color(26, RGB_DARK_GREEN);   // 'T' key
            rgb_matrix_set_color(21, RGB_DARK_YELLOW);  // 'R' key
            rgb_matrix_set_color(11, RGB_DARK_YELLOW);  // 'W' key
            rgb_matrix_set_color(6, RGB_DARK_RED);      // 'Q' key

            const uint8_t keycodes[] = {16 /*E*/, 12 /*S*/, 17 /*D*/, 22 /*F*/};
            set_all_keys_colors(keycodes, sizeof(keycodes) / sizeof(uint8_t), RGB_DARK_MAGENTA);
            break;
        }
        case _MDIA: {
            light_up_left_mods(RGB_DARK_CYAN);

            const uint8_t media_keycodes[] = {57, 47, 59, 54, 49};
            set_all_keys_colors(media_keycodes, sizeof(media_keycodes) / sizeof(uint8_t), RGB_DARK_WHITE);
            rgb_matrix_set_color(28, RGB_DARK_RED);  // 'B' key

            rgb_matrix_set_color(26, RGB_DARK_WHITE);  // CG_TOGG key
            rgb_matrix_set_color(6, RGB_DARK_RED);     // RESET key

            rgb_matrix_set_color(42, RGB_DARK_YELLOW);  // 'P' key

            rgb_matrix_set_color(62, RGB_DARK_GREEN);  // 'Y' key
            rgb_matrix_set_color(63, RGB_DARK_GREEN);  // 'H' key

            const uint8_t keycodes[] = {52 /*I*/, 58 /*J*/, 53 /*K*/, 48 /*L*/, 69, 68, 60};
            set_all_keys_colors(keycodes, sizeof(keycodes) / sizeof(uint8_t), RGB_DARK_CYAN);
            break;
        }
        default:
            break;
    }

    // Make it easy to tell when each home-row mod is held for long enough by
    // lighting up the corresponding LEDs on both sides of the keyboard.
    //
    // Keep in mind that this shows over all layers and lights up both halves of
    // the keyboard, so it's good if you care more about your modifier status
    // than you do the regular LED color (i.e. it's good if you know your layout
    // well enough already).
    if (is_shift_held()) {
        rgb_matrix_set_color(22, RGB_DARK_YELLOW);  // 'F' key
        rgb_matrix_set_color(58, RGB_DARK_YELLOW);  // 'J' key
    }
    if (get_mods() & MOD_BIT(KC_LALT)) {
        rgb_matrix_set_color(12, RGB_DARK_YELLOW);  // 'S' key
        rgb_matrix_set_color(48, RGB_DARK_YELLOW);  // 'L' key
    }

    if (is_mac_the_default()) {
        if (is_ctrl_held()) {
            rgb_matrix_set_color(7, RGB_DARK_YELLOW);   // 'A' key
            rgb_matrix_set_color(43, RGB_DARK_YELLOW);  // ';' key
        }
        if (is_gui_held()) {
            rgb_matrix_set_color(17, RGB_DARK_YELLOW);  // 'D' key
            rgb_matrix_set_color(53, RGB_DARK_YELLOW);  // 'K' key
        }
    } else {
        if (is_gui_held()) {
            rgb_matrix_set_color(7, RGB_DARK_YELLOW);   // 'A' key
            rgb_matrix_set_color(43, RGB_DARK_YELLOW);  // ';' key
        }
        if (is_ctrl_held()) {
            rgb_matrix_set_color(17, RGB_DARK_YELLOW);  // 'D' key
            rgb_matrix_set_color(53, RGB_DARK_YELLOW);  // 'K' key
        }
    }
}
#endif

// Cycle the matrix color in a limited range of red/pinks/purples.
// https://docs.qmk.fm/#/feature_rgblight?id=color-selection
void change_matrix_color(void) {
    static uint16_t last_update;
    static bool     increase = true;

    if (timer_elapsed(last_update) > 1500) {
        last_update = timer_read();

        // I know about rgblight_increase_hue_noeeprom, but for some reason, I
        // can't #define a different step and I don't know why.
        rgblight_sethsv_noeeprom(rgblight_get_hue() + (increase ? 1 : -1), rgblight_get_sat(), rgblight_get_val());

        uint8_t hue = rgblight_get_hue();
        // 11 is definitely yellow despite the color wheel, so we stop in
        // orange.
        if ((increase && hue >= 2 && hue < 100) || (!increase && hue > 50 && hue < 180)) {
            increase = !increase;
        }
    }
}

void housekeeping_task_user(void) { /*change_matrix_color();*/
}

void keyboard_post_init_user(void) {
    rgblight_sethsv_noeeprom(HSV_MAGENTA);

    // This is good in case I screw anything up with bad code; it's REALLY hard
    // to fix it when mods get messed up since it can mess up the whole OS.
    //
    // Ctrl+alt+del can help on Windows, as can osk.exe sometimes.
    clear_mods();
}

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case MO_NAV:
        case MO_FUN:
        case MO_NUM:
        case MO_SYMB:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case MO_NAV:
        case MO_FUN:
        case MO_NUM:
        case MO_SYMB:
        case KC_LSFT:
        case OS_SHFT:
        case OS_CTRL:
        case OS_ALT:
        case OS_GUI:
            return true;
        default:
            return false;
    }
}

bool          sw_app_active = false;
bool          sw_win_active = false;
oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state  = os_up_unqueued;
oneshot_state os_gui_state  = os_up_unqueued;

// Sends `mac_code` on macOS, `win_code` on Windows.
//
// Credit to Rhymu
void send_mac_or_win(uint16_t mac_code, uint16_t win_code, bool is_pressed) {
    uint16_t code = is_mac_the_default() ? mac_code : win_code;
    if (is_pressed) {
        register_code16(code);
    } else {
        unregister_code16(code);
    }
}

// https://github.com/qmk/qmk_firmware/issues/4611#issuecomment-446713700
// https://www.reddit.com/r/olkb/comments/oflwv6/how_do_i_change_qmk_layer_tap_behavior/h4l7u8n/?utm_source=reddit&utm_medium=web2x&context=3
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool isPressed   = record->event.pressed;
    bool isCtrlHeld  = is_ctrl_held();
    bool isShiftHeld = is_shift_held();

    bool sent_keycode = false;

    {
        uint16_t mod = is_mac_the_default() ? KC_LGUI : KC_LALT;
        update_swapper(&sw_app_active, mod, KC_TAB, SW_APP, keycode, record);
    }
    update_swapper(&sw_win_active, KC_LGUI, KC_GRV, SW_WIN, keycode, record);

    // Handle these before one-shot modifiers so that the modifiers are still
    // pressed. Also, consider pressing these to have sent a keycode for
    // one-shot modifiers since the register_code() call in oneshot.c can't
    // understand these custom keycodes.
    switch (keycode) {
        case REV_COLON:
            // No mod → :
            // Shift → ;
            if (isPressed) {
                if (isShiftHeld) {
                    unregister_mods(MOD_BIT(KC_LSFT));
                    tap_code_delay(KC_SCLN, 0);
                    register_mods(MOD_BIT(KC_LSFT));
                } else {
                    tap_code16(S(KC_SCLN));
                }
                sent_keycode = true;
            }
            break;
        case MW_PSTE:
            // No mod → paste
            // Shift → shift+paste
            //
            // (I frequently want to send shift+paste to paste unformatted text,
            // e.g. in documents or emails)
            if (isShiftHeld) {
                send_mac_or_win(G(S(KC_V)), C(S(KC_V)), isPressed);
            } else {
                send_mac_or_win(G(KC_V), C(KC_V), isPressed);
            }
            sent_keycode = true;
            break;
        case KC_LEFT_ENCLOSE:
            // No mod → (
            // Ctrl → [
            // Shift → {
            if (isPressed && IS_LAYER_ON(_SYMB)) {
                if (isCtrlHeld && !isShiftHeld) {
                    unregister_mods(MOD_BIT(KC_LCTL));
                    tap_code_delay(KC_LBRC, 0);
                    register_mods(MOD_BIT(KC_LCTL));
                } else if (isShiftHeld) {
                    tap_code_delay(KC_LBRC, 0);
                } else {
                    tap_code16(S(KC_9));
                }
                sent_keycode = true;
            }
            break;
        case KC_RIGHT_ENCLOSE:
            // No mod → )
            // Ctrl → ]
            // Shift → }
            if (isPressed && IS_LAYER_ON(_SYMB)) {
                if (isCtrlHeld && !isShiftHeld) {
                    unregister_mods(MOD_BIT(KC_LCTL));
                    tap_code_delay(KC_RBRC, 0);
                    register_mods(MOD_BIT(KC_LCTL));
                } else if (isShiftHeld) {
                    tap_code_delay(KC_RBRC, 0);
                } else {
                    tap_code16(S(KC_0));
                }
                sent_keycode = true;
            }
            break;
    }

    update_oneshot(&os_shft_state, &sent_keycode, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot(&os_ctrl_state, &sent_keycode, is_mac_the_default() ? KC_LGUI : KC_LCTL, OS_CTRL, keycode, record);
    update_oneshot(&os_alt_state, &sent_keycode, KC_LALT, OS_ALT, keycode, record);
    update_oneshot(&os_gui_state, &sent_keycode, is_mac_the_default() ? KC_LCTL : KC_LGUI, OS_GUI, keycode, record);
    if (sent_keycode) return false;

    switch (keycode) {
        case MW_UNDO:
            send_mac_or_win(G(KC_Z), C(KC_Z), isPressed);
            return false;
        case MW_CUT:
            send_mac_or_win(G(KC_X), C(KC_X), isPressed);
            return false;
        case MW_COPY:
            send_mac_or_win(G(KC_C), C(KC_C), isPressed);
            return false;
        case CLS_WIN:
            send_mac_or_win(G(KC_W), C(KC_W), isPressed);
            return false;
        case MW_REDO: {
            uint16_t code = is_mac_the_default() ? G(S(KC_Z)) : C(KC_Y);
            if (isPressed) {
                register_code16(code);
            } else {
                unregister_code16(code);
            }
            return false;
        }
        case KC_DWRD: {
            uint16_t CODE = is_mac_the_default() ? A(KC_BSPC) : C(KC_BSPC);
            if (isPressed) {
                register_code16(CODE);
            } else {
                unregister_code16(CODE);
            }
            return false;
        }
        case KC_3GRV: {
            if (isPressed) {
                for (uint8_t i = 0; i < 3; i++) tap_code16(KC_GRV);
            }

            return false;
        }
    }

    return true;
}

#ifdef TAPPING_TERM_PER_KEY
// Increasing the tapping term means that dual-function keys have to be held for
// longer before they're treated as their "hold" action.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // I was making a bunch of typos presumably due to this shortcut, so I'm
        // trying a much longer TAPPING_TERM so that I hopefully only hit this
        // intentionally.
        case LT_NAV_SPACE:
            return TAPPING_TERM + 125;
        default:
            return TAPPING_TERM;
    }
}
#endif

// Note: by default, COMBO_TERM is 50ms (https://docs.qmk.fm/#/feature_combo?id=combo-term)
#ifdef COMBO_TERM_PER_COMBO
uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        // "UI" is a common enough bigram in software engineering ("UI",
        // "build", "requirements") that the combo time needs to be pretty low
        // so that natural typing doesn't trigger it.
        case UI_HYPHEN:
            return 20;
        // "UIO" transpositions *do* appear in some words, e.g. "curious". All I
        // know is that 50 has been too low for me to consistently activate caps
        // lock with "UIO".
        case UIO_CAPS:
        case JKL_CAPS:
            return 70;
    }

    return COMBO_TERM;
}
#endif
