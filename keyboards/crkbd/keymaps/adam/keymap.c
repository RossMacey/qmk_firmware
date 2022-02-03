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
#include "transactions.h"
#include "customkeys.h"
#include "oneshot.h"
#include <stdio.h>

enum layers {
    _BASE,   // default layer
    _SYMB,   // symbols
    _NUM,    // numbers
    _FUN,    // fn keys
    _NAV,    // navigation keys
    _NAVLH,  // navigation keys but sort of mirrored so that arrows are on the LH
    _MDIA,   // media keys
};

#define LT_NAV_SPACE LT(_NAV, KC_SPC)
#define LT_MDIA_QUOT LT(_MDIA, KC_QUOT)
#define MO_NAV MO(_NAV)
#define MO_FUN MO(_FUN)
#define MO_NUM MO(_NUM)
#define MO_SYMB MO(_SYMB)

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

enum combos { UI_HYPHEN, UIO_CAPS, MCOMMA_BACKSPACE, COMMADOT_ENTER, MDOT_TAB, NDOT_ESC, COMBO_LENGTH };
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM ui_hyphen[]        = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM uio_caps[]         = {KC_U, KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM mcomma_backspace[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM commadot_enter[]   = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM mdot_tab[]         = {KC_M, KC_DOT, COMBO_END};
const uint16_t PROGMEM ndot_esc[]         = {KC_N, KC_DOT, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [UI_HYPHEN]         = COMBO(ui_hyphen, KC_MINS),
    [UIO_CAPS]          = COMBO(uio_caps, KC_CAPS),
    [MCOMMA_BACKSPACE]  = COMBO(mcomma_backspace, KC_BSPC),
    [COMMADOT_ENTER]    = COMBO(commadot_enter, KC_ENT),
    [MDOT_TAB]          = COMBO(mdot_tab, KC_TAB),
    [NDOT_ESC]          = COMBO(ndot_esc, KC_ESC),
};
// clang-format on

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x5_3(
            KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                    KC_Y,     KC_U,    KC_I,    KC_O,             KC_P,
            KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                    KC_H,     KC_J,    KC_K,    KC_L,     LT_MDIA_QUOT,
    LCTL_T(KC_Z),    KC_X,    KC_C,    KC_V,    KC_B,                    KC_N,     KC_M, KC_COMM,  KC_DOT,  LCTL_T(KC_SLSH),
                          MO_FUN,LT_NAV_SPACE,MO_NUM,                    MO_SYMB,MO_NAV, KC_LSFT
  ),

  [_SYMB] = LAYOUT_split_3x5_3(
    KC_MINS, S(KC_MINS),         KC_EQL,       S(KC_EQL), KC_BSLS,         _______, _______,    _______,   _______,    _______,
    KC_QUOT, S(KC_QUOT),KC_LEFT_ENCLOSE,KC_RIGHT_ENCLOSE,  KC_GRV,         _______, OS_SHFT,    OS_CTRL,   OS_ALT ,    OS_GUI ,
    KC_SCLN, S(KC_SCLN),        KC_LBRC,         KC_RBRC, _______,         _______, S(KC_1), S(KC_COMM), S(KC_DOT), S(KC_SLSH),
                                        _______, _______, _______,         _______, _______, _______
  ),

  [_NUM] = LAYOUT_split_3x5_3(
    _______, KC_LEFT,  KC_DOT, KC_RGHT, _______,               KC_NLCK, KC_7, KC_8, KC_9, S(KC_EQL),
    OS_GUI , OS_ALT , OS_CTRL, OS_SHFT, _______,            S(KC_SCLN), KC_4, KC_5, KC_6,   KC_DOT,
    _______, _______, KC_COMM, _______, _______,               KC_MINS, KC_1, KC_2, KC_3,   _______,
                      _______, _______, _______,                KC_ENT, KC_BSPC, KC_0
  ),

  [_FUN] = LAYOUT_split_3x5_3(
       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            _______, KC_F7, KC_F8, KC_F9, KC_F12,
     OS_GUI,  OS_ALT, OS_CTRL, OS_SHFT, _______,            _______, KC_F4, KC_F5, KC_F6, KC_F11,
       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,            _______, KC_F1, KC_F2, KC_F3, KC_F10,
                      _______, _______, _______,            _______, KC_CAPS, _______
  ),
  [_NAV] = LAYOUT_split_3x5_3(
     SW_WIN, RCS(KC_TAB), CLS_WIN,C(KC_TAB),    SW_APP,            KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DWRD,
     OS_GUI,      OS_ALT, OS_CTRL,  OS_SHFT,TO(_NAVLH),            KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,  KC_SPC,
    _______,     _______, _______,  _______,   _______,            KC_ESC,  KC_BSPC, KC_ENT,  KC_TAB,   KC_DEL,
                          _______,  _______,   _______,            KC_ENT,  KC_BSPC, _______
  ),
  [_NAVLH] = LAYOUT_split_3x5_3(
  TO(_BASE), KC_HOME,   KC_UP,   KC_END, KC_PGUP,            _______, _______, _______, _______, _______,
     KC_SPC, KC_LEFT, KC_DOWN,  KC_RGHT, KC_PGDN,            _______, OS_SHFT, OS_CTRL,  OS_ALT,  OS_GUI,
     KC_DEL,  KC_TAB,  KC_ENT,  KC_BSPC,  KC_ESC,            _______, _______, _______, _______, _______,
                      _______,TO(_BASE), _______,             KC_ENT, KC_BSPC, _______
  ),
  [_MDIA] = LAYOUT_split_3x5_3(
    RESET, _______,   RGB_TOG, _______, CG_TOGG,           KC_WH_U, KC_MPRV, KC_MS_U, KC_MNXT, KC_PSCR,
     OS_GUI,  OS_ALT, OS_CTRL, OS_SHFT, _______,           KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, _______,
    _______, _______, _______, _______, _______,           KC_MUTE, KC_VOLD, KC_MPLY, KC_VOLU, _______,
                      _______, _______, _______,           KC_BTN3, KC_BTN1, KC_BTN2
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
    if (is_mac_the_default()) {
        set_color_for_contiguous_keycodes(0, 5, 0x32, 0x32, 0x32);
        set_color_for_contiguous_keycodes(27, 32, 0x32, 0x32, 0x32);
    } else {
        set_color_for_contiguous_keycodes(0, 5, 0x00, 0x32, 0x00);
        set_color_for_contiguous_keycodes(27, 32, 0x00, 0x32, 0x00);
    }

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            // Common colors between Windows and Mac
            if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) {
                // When caps lock is on, make it REALLY obvious.
                HSV hsv = {rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val()};
                RGB rgb = hsv_to_rgb(hsv);
                set_color_for_contiguous_keycodes(0, 50, rgb.r, rgb.g, rgb.b);
            }

            set_color_split(14, RGB_DARK_WHITE);  // LH thumb key 1
            // set_color_split(13, RGB_DARK_MAGENTA);  // LH thumb key 2
            set_color_split(6, RGB_DARK_GREEN);     // LH thumb key 3
            set_color_split(33, RGB_DARK_BLUE);     // RH thumb key 1
            set_color_split(40, RGB_DARK_MAGENTA);  // RH thumb key 2
            // set_color_split(41, RGB_DARK_WHITE);    // RH thumb key 3

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

            set_color_split(18, RGB_DARK_MAGENTA);  // 'W' key
            set_color_split(17, RGB_DARK_BLUE);     // 'E' key
            set_color_split(10, RGB_DARK_MAGENTA);  // 'R' key
            set_color_split(15, RGB_DARK_BLUE);     // 'C' key

            set_color_split(49, RGB_DARK_BLUE);  // Period key

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
            set_color_split(39, RGB_DARK_RED);     // 'M' key
            set_color_split(42, RGB_DARK_WHITE);   // ',' key
            set_color_split(47, RGB_DARK_WHITE);   // '.' key
            set_color_split(48, RGB_DARK_RED);     // '/' key
            set_color_split(35, RGB_DARK_GREEN);   // 'H' key
            set_color_split(49, RGB_DARK_WHITE);   // ';' key
            set_color_split(36, RGB_DARK_GREEN);   // 'Y' key
            set_color_split(37, RGB_DARK_YELLOW);  // 'U' key
            set_color_split(45, RGB_DARK_YELLOW);  // 'O' key
            set_color_split(50, RGB_DARK_RED);     // 'P' key

            set_color_split(23, RGB_DARK_WHITE);  // 'Q' key
            set_color_split(18, RGB_DARK_GREEN);  // 'W' key
            set_color_split(17, RGB_DARK_RED);    // 'E' key
            set_color_split(10, RGB_DARK_GREEN);  // 'R' key
            set_color_split(9, RGB_DARK_WHITE);   // 'T' key
            set_color_split(8, RGB_DARK_WHITE);   // 'G' key

            const uint8_t keycodes[] = {44 /*I*/, 38 /*J*/, 43 /*K*/, 46 /*L*/};
            set_all_keys_colors(keycodes, sizeof(keycodes) / sizeof(uint8_t), RGB_DARK_MAGENTA);
            break;
        }
        case _NAVLH: {
            light_up_right_mods(RGB_DARK_MAGENTA);

            set_color_split(7, RGB_DARK_WHITE);    // 'B' key
            set_color_split(12, RGB_DARK_RED);     // 'V' key
            set_color_split(15, RGB_DARK_WHITE);   // 'C' key
            set_color_split(20, RGB_DARK_WHITE);   // 'X' key
            set_color_split(21, RGB_DARK_RED);     // 'Z' key
            set_color_split(8, RGB_DARK_GREEN);    // 'G' key
            set_color_split(22, RGB_DARK_WHITE);   // 'A' key
            set_color_split(9, RGB_DARK_GREEN);    // 'T' key
            set_color_split(10, RGB_DARK_YELLOW);  // 'R' key
            set_color_split(18, RGB_DARK_YELLOW);  // 'W' key
            set_color_split(23, RGB_DARK_RED);     // 'Q' key

            const uint8_t keycodes[] = {17 /*E*/, 19 /*S*/, 16 /*D*/, 11 /*F*/};
            set_all_keys_colors(keycodes, sizeof(keycodes) / sizeof(uint8_t), RGB_DARK_MAGENTA);
            break;
        }
        case _MDIA: {
            light_up_left_mods(RGB_DARK_CYAN);

            const uint8_t media_keycodes[] = {37, 45, 39, 42, 47};
            set_all_keys_colors(media_keycodes, sizeof(media_keycodes) / sizeof(uint8_t), RGB_DARK_WHITE);
            set_color_split(34, RGB_DARK_RED);  // 'B' key

            set_color_split(9, RGB_DARK_WHITE);  // CG_TOGG key
            set_color_split(23, RGB_DARK_RED);   // RESET key

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

    // Make it easy to tell when each home-row mod is held for long enough by
    // lighting up the corresponding LEDs on both sides of the keyboard.
    //
    // Keep in mind that this shows over all layers and lights up both halves of
    // the keyboard, so it's good if you care more about your modifier status
    // than you do the regular LED color (i.e. it's good if you know your layout
    // well enough already).
    if (is_shift_held()) {
        set_color_split(11, RGB_DARK_YELLOW);  // 'F' key
        set_color_split(38, RGB_DARK_YELLOW);  // 'J' key
    }
    if (get_mods() & MOD_BIT(KC_LALT)) {
        set_color_split(19, RGB_DARK_YELLOW);  // 'S' key
        set_color_split(46, RGB_DARK_YELLOW);  // 'L' key
    }

    if (is_mac_the_default()) {
        if (is_ctrl_held()) {
            set_color_split(22, RGB_DARK_YELLOW);  // 'A' key
            set_color_split(49, RGB_DARK_YELLOW);  // ';' key
        }
        if (is_gui_held()) {
            set_color_split(16, RGB_DARK_YELLOW);  // 'D' key
            set_color_split(43, RGB_DARK_YELLOW);  // 'K' key
        }
    } else {
        if (is_gui_held()) {
            set_color_split(22, RGB_DARK_YELLOW);  // 'A' key
            set_color_split(49, RGB_DARK_YELLOW);  // ';' key
        }
        if (is_ctrl_held()) {
            set_color_split(16, RGB_DARK_YELLOW);  // 'D' key
            set_color_split(43, RGB_DARK_YELLOW);  // 'K' key
        }
    }
}
#endif

// Lots of this code comes from https://github.com/qmk/qmk_firmware/tree/c4551d7ef1ed2c1069f23cc8499b7c7fc30f3ecf/users/drashna/split
//
// The goal is to sync keymap_config between the two halves since I base several
// lighting decisions on its values.
uint16_t transport_keymap_config = 0;
void     user_keymap_sync(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(transport_keymap_config)) {
        memcpy(&transport_keymap_config, initiator2target_buffer, initiator2target_buffer_size);
    }
}
void user_transport_update(void) {
    if (is_keyboard_master()) {
        transport_keymap_config = keymap_config.raw;
    } else {
        keymap_config.raw = transport_keymap_config;
    }
}

void user_transport_sync(void) {
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to secondary
        static uint16_t last_keymap = 0;
        static uint32_t last_sync;
        bool            needs_sync = false;

        // Check if the state values are different
        if (memcmp(&transport_keymap_config, &last_keymap, sizeof(transport_keymap_config))) {
            needs_sync = true;
            memcpy(&last_keymap, &transport_keymap_config, sizeof(transport_keymap_config));
        }

        // Send to secondary every so often regardless of state change
        //
        // [Adam] Note: I toned this way down since I only really care about one
        // magic keycode, and that keycode represents a change in operating
        // systems (i.e. it's infrequent), and the result of a desync is just
        // having incorrect LEDs lit up. This code is mostly just if a sync
        // fails for whatever reason, which is actually pretty common (~10% of
        // the time?).
        if (timer_elapsed32(last_sync) > 1000) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_USER_KEYMAP_SYNC, sizeof(transport_keymap_config), &transport_keymap_config)) {
                last_sync = timer_read32();
            }
            needs_sync = false;
        }
    }
}

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

void housekeeping_task_user(void) {
    // Update kb_state so we can send to secondary
    user_transport_update();

    // Data sync from master to secondary
    user_transport_sync();

    change_matrix_color();
}

void keyboard_post_init_user(void) {
    rgblight_sethsv_noeeprom(HSV_MAGENTA);

    transaction_register_rpc(RPC_ID_USER_KEYMAP_SYNC, user_keymap_sync);

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
        case KC_DWRD: {
            uint16_t code = is_mac_the_default() ? A(KC_BSPC) : C(KC_BSPC);
            if (isPressed) {
                register_code16(code);
            } else {
                unregister_code16(code);
            }
            return false;
        }
        case CLS_WIN: {
            uint16_t code = is_mac_the_default() ? G(KC_W) : C(KC_W);
            if (isPressed) {
                register_code16(code);
            } else {
                unregister_code16(code);
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
