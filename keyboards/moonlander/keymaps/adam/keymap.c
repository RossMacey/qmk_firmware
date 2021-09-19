/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
    _WIN_BASE,  // default layer
    _MAC_BASE,  // default layer but with Mac keys
    _SYMB,      // symbols
    _NAV,       // navigation keys
    _MDIA,      // media keys
};

enum custom_keycodes {
    MAC_SWP = ML_SAFE_RANGE,
};

// Left-hand home row mods on Windows: GACS
// ("W_HM" = "Windows home")
#define W_HM_A LGUI_T(KC_A)
#define W_HM_S LALT_T(KC_S)
#define W_HM_D LCTL_T(KC_D)
#define W_HM_F LSFT_T(KC_F)

// Right-hand home row mods on Windows: SCAG
#define W_HM_J RSFT_T(KC_J)
#define W_HM_K RCTL_T(KC_K)
#define W_HM_L LALT_T(KC_L)
#define W_HM_SCLN RGUI_T(KC_SCLN)

// Left-hand home row mods on Mac: CAGS
#define M_HM_A LCTL_T(KC_A)
#define M_HM_S LALT_T(KC_S)
#define M_HM_D LGUI_T(KC_D)
#define M_HM_F LSFT_T(KC_F)

// Right-hand home row mods on Mac: SGAC
#define M_HM_J RSFT_T(KC_J)
#define M_HM_K RGUI_T(KC_K)
#define M_HM_L LALT_T(KC_L)
#define M_HM_SCLN RCTL_T(KC_SCLN)

#define RGB_ACTUAL_AZURE 0x00, 0x7F, 0xFF

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_WIN_BASE] = LAYOUT_moonlander(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,              KC_EQL, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    A(KC_LSFT),    A(KC_LSFT), KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_LGUI,W_HM_A, W_HM_S,  W_HM_D,  W_HM_F,    KC_G,    KC_HYPR,           KC_MEH,  KC_H, W_HM_J,  W_HM_K,  W_HM_L, W_HM_SCLN, LT(_MDIA, KC_QUOT),
        KC_LSFT, LCTL_T(KC_Z),KC_X,KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,    KC_COMM, KC_DOT,  LCTL_T(KC_SLSH), KC_RSFT,
        KC_LCTL,KC_LGUI,KC_LALT,KC_LEFT,TT(_SYMB),  KC_LALT,                      LCTL_T(KC_ESC),   KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, TT(_SYMB),
                                            KC_SPC,  KC_LCTL, KC_LGUI,           KC_ENT,  KC_BSPC, MO(_NAV)
    ),
    [_MAC_BASE] = LAYOUT_moonlander(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,              KC_EQL, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    A(KC_LSFT),    A(KC_LSFT), KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_HYPR, M_HM_A,M_HM_S,  M_HM_D,  M_HM_F,    KC_G,    KC_HYPR,           KC_MEH, KC_H,  M_HM_J,  M_HM_K,  M_HM_L,  M_HM_SCLN, LT(_MDIA, KC_QUOT),
        KC_LSFT, LGUI_T(KC_Z),KC_X,KC_C,    KC_V,    KC_B,                       KC_N,    KC_M,    KC_COMM, KC_DOT,  LGUI_T(KC_SLSH), KC_RSFT,
        KC_LCTL,KC_LGUI,KC_LALT,KC_LEFT,TT(_SYMB),  KC_LALT,                      LGUI_T(KC_ESC),   KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, TT(_SYMB),
                                            KC_SPC,  KC_LGUI, KC_LALT,           KC_ENT,  KC_BSPC, MO(_NAV)
    ),

    [_SYMB] = LAYOUT_moonlander(
        KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,         _______, KC_F6,   KC_F7,    KC_F8,    KC_F9,    KC_F10,  KC_F11,
        _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, _______,           _______,KC_NLCK,KC_P7,    KC_P8,    KC_P9,    KC_PAST, KC_F12,
        _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,  _______,           _______, KC_PMNS, KC_P4,    KC_P5,    KC_P6,    KC_PPLS, _______,
        _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                             KC_AMPR, KC_P1,    KC_P2,    KC_P3,    KC_BSLS, _______,
        _______, _______, _______, _______, TG(_SYMB),          _______,           _______,          KC_P0,    KC_P0,   KC_PDOT,   KC_PEQL, TG(_SYMB),
                                            _______, _______, _______,           _______,_______, _______
    ),

    [_NAV] = LAYOUT_moonlander(
        _______,_______,_______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, TG(_SYMB),
        _______, _______, _______, _______, _______, _______, _______,           _______,KC_PGUP,KC_HOME, KC_UP,   KC_END,  KC_TAB, _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______,                             KC_ESC,  KC_BSPC, KC_ENT,  KC_DEL,  _______, _______,
        _______, _______, _______, _______, _______,         _______,            _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),

    // For some reason, if _NAV is above _MDIA, then the mouse movement from _MDIA starts affecting _NAV.
    [_MDIA] = LAYOUT_moonlander(
        _______,_______,_______, _______, _______, _______, DF(_WIN_BASE),       DF(_MAC_BASE), _______, _______, KC_MS_BTN3, _______, _______, RESET,
        _______, _______, _______, KC_MS_U, _______, _______, _______,           _______, _______, _______, KC_MS_U, _______, KC_PSCR, _______,
        _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,           _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_MPLY, _______,
        _______, _______, _______, _______, _______, _______,                             _______, _______, KC_MPRV, KC_MNXT, KC_BTN2, _______,
        _______, _______, _______, KC_BTN1, KC_BTN2,         _______,            _______,          KC_VOLU, KC_VOLD, KC_MUTE, _______, _______,
                                            _______, _______, _______,           _______, _______, KC_BTN1
    ),
};
// clang-format on

void set_all_keys_colors(const uint8_t keycodes[], uint8_t len, uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = 0; i < len; ++i) {
        rgb_matrix_set_color(keycodes[i], r, g, b);
    }
}

// RGB_MATRIX_INDICATOR_SET_COLOR is just a reference to rgb_matrix_set_color
#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch (get_highest_layer(layer_state)) {
        case _WIN_BASE:
            // Common colors between Windows and Mac
            rgb_matrix_set_color(7, 0x00, 0x16, 0x16);   // 'A' key
            rgb_matrix_set_color(12, 0x00, 0x64, 0x64);  // 'S' key
            rgb_matrix_set_color(17, 0x00, 0xC8, 0xC8);  // 'D' key
            rgb_matrix_set_color(22, 0x00, 0xF8, 0xF8);  // 'F' key

            rgb_matrix_set_color(58, 0x00, 0xF8, 0xF8);  // 'J' key
            rgb_matrix_set_color(53, 0x00, 0xC8, 0xC8);  // 'K' key
            rgb_matrix_set_color(48, 0x00, 0x64, 0x64);  // 'L' key
            rgb_matrix_set_color(43, 0x00, 0x16, 0x16);  // ';' key

            // MAC (this is here because default layers just work strangely I guess; when the Mac layer is default, the Windows layer is still the highest layer)
            if (layer_state_cmp(default_layer_state, _MAC_BASE)) {
                rgb_matrix_set_color(65, RGB_WHITE);  // Mac key
            } else {
                // WINDOWS
                rgb_matrix_set_color(29, RGB_GREEN);  // Win key
            }

            rgb_matrix_set_color(68, 0x64, 0x00, 0x64);  // Rightmost RH piano key
            break;
        case _MAC_BASE:
            rgb_matrix_set_color(22, 0x64, 0x64, 0x64);  // 'F' key
            rgb_matrix_set_color(58, 0x64, 0x64, 0x64);  // 'J' key
            break;
        case _SYMB: {
            rgb_matrix_set_color(62, 0x64, 0x00, 0x00);  // 'Y' key
            if (host_keyboard_leds() & (1 << USB_LED_NUM_LOCK)) {
                rgb_matrix_set_color(62, RGB_YELLOW);  // 'Y' key
            }

            const uint8_t fn_keys_keycodes[] = {5, 10, 15, 20, 25, 61, 56, 51, 46, 41, 36, 37};
            set_all_keys_colors(fn_keys_keycodes, sizeof(fn_keys_keycodes) / sizeof(uint8_t), RGB_WHITE);

            const uint8_t numpad_keycodes[] = {57, 58, 59, 60, 52, 53, 54, 55, 47, 48, 49};
            set_all_keys_colors(numpad_keycodes, sizeof(numpad_keycodes) / sizeof(uint8_t), RGB_GREEN);
            break;
        }
        case _MDIA: {
            const uint8_t mouse_keycodes[] = {58, 51, 52, 53, 48, 44, 68};
            set_all_keys_colors(mouse_keycodes, sizeof(mouse_keycodes) / sizeof(uint8_t), RGB_CYAN);

            const uint8_t media_keycodes[] = {60, 54, 55, 49, 50, 43};
            set_all_keys_colors(media_keycodes, sizeof(media_keycodes) / sizeof(uint8_t), RGB_WHITE);

            rgb_matrix_set_color(42, RGB_GREEN);  // 'P' key
            rgb_matrix_set_color(36, RGB_RED);    // RESET key

            rgb_matrix_set_color(29, RGB_GREEN);  // Win key
            rgb_matrix_set_color(65, RGB_WHITE);  // Mac key
            break;
        }
        case _NAV: {
            rgb_matrix_set_color(64, 0x64, 0x64, 0x64);  // 'N' key
            rgb_matrix_set_color(42, 0x64, 0x64, 0x64);  // 'P' key
            rgb_matrix_set_color(59, 0x64, 0x00, 0x00);  // 'M' key
            rgb_matrix_set_color(54, 0x64, 0x64, 0x64);  // ',' key
            rgb_matrix_set_color(49, 0x64, 0x00, 0x00);  // '.' key
            rgb_matrix_set_color(62, 0x00, 0x64, 0x00);  // 'Y' key
            rgb_matrix_set_color(63, 0x00, 0x64, 0x00);  // 'H' key
            rgb_matrix_set_color(57, 0x64, 0x64, 0x00);  // 'U' key
            rgb_matrix_set_color(47, 0x64, 0x64, 0x00);  // 'O' key

            const uint8_t keycodes[] = {52 /*I*/, 58 /*J*/, 53 /*K*/, 48 /*L*/};
            set_all_keys_colors(keycodes, sizeof(keycodes) / sizeof(uint8_t), 0x64, 0x00, 0x64);
            break;
        }
        default:  //  for any other layers, or the default layer
            break;
    }
}
#endif

void keyboard_post_init_user(void) {
    rgblight_sethsv(HSV_MAGENTA);

    // This is good in case I screw anything up with bad code; it's REALLY hard to
    // fix it when mods get messed up since it can mess up the whole OS.
    clear_mods();
}

// https://github.com/qmk/qmk_firmware/issues/4611#issuecomment-446713700
// https://www.reddit.com/r/olkb/comments/oflwv6/how_do_i_change_qmk_layer_tap_behavior/h4l7u8n/?utm_source=reddit&utm_medium=web2x&context=3
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool isPressed   = record->event.pressed;
    bool isCtrlHeld  = get_mods() & MOD_BIT(KC_LCTL);
    bool isShiftHeld = get_mods() & MOD_BIT(KC_LSFT);

    switch (keycode) {
        // case MAC_SWP:
        //     if (isPressed) {
        //         if (layer_state_cmp(default_layer_state, _WIN_BASE)) {
        //             // set_single_persistent_default_layer(_MAC_BASE);
        //             default_layer_set(_MAC_BASE);
        //         } else {
        //             default_layer_set(_WIN_BASE);
        //         }
        //     }
        //     break;
        case KC_9:
            // When in the nav layer:
            // 9 → (
            // Ctrl+9 → [
            // Shift+9 → {
            if (isPressed && IS_LAYER_ON(_NAV)) {
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
        case KC_0:
            // When in the nav layer:
            // 0 → )
            // Ctrl+0 → ]
            // Shift+0 → }
            if (isPressed && IS_LAYER_ON(_NAV)) {
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

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Windows
        case W_HM_S:
        case W_HM_D:
        case W_HM_F:
        case W_HM_J:
        case W_HM_K:
        case W_HM_L:
        // Mac
        // case M_HM_S: // ← these keys are the same between Windows and Mac
        // case M_HM_F: // ← these keys are the same between Windows and Mac
        // case M_HM_J: // ← these keys are the same between Windows and Mac
        // case M_HM_L: // ← these keys are the same between Windows and Mac
        case M_HM_D:
        case M_HM_K:
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}
