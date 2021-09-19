/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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

void set_side_light_color(uint8_t hue, uint8_t sat, uint8_t val);

enum custom_layers {
    _MAIN,  // regular typing
    _NUMP,  // mostly just for the numpad
    _NAV,   // arrows, home/end, pgup/pgdn, etc.
    _FUNC,  // mostly RGB stuff and RESET
};

enum custom_keycodes {
    MO_SCLN = SAFE_RANGE,
};

// https://www.reddit.com/r/glorious/comments/okrbjg/peeps_qmk_and_via_rgb_guide_only_for_ansi/h5i4jbu?utm_source=share&utm_medium=web2x&context=3
// RGB_MATRIX_INDICATOR_SET_COLOR is just a reference to rgb_matrix_set_color
#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // In all layers, I want this key highlighted red.
    // Note: 69 = print screen
    // rgb_matrix_set_color(75, 0x64, 0x00, 0x00); // Second key from the top in the right-side cluster

    switch (get_highest_layer(layer_state)) {
        case _MAIN:
            set_side_light_color(RGB_OFF);
            rgb_matrix_set_color(26, 0x00, 0x00, 0x64);  // 'F' key
            rgb_matrix_set_color(42, 0x00, 0x00, 0x64);  // 'J' key
            rgb_matrix_set_color(59, 0x00, 0x00, 0x64);  // ';' key
            break;
        case _NUMP: {
            set_side_light_color(RGB_GREEN);

            rgb_matrix_set_color(35, 0x64, 0x00, 0xFF);  // '6' key
            if (host_keyboard_leds() & (1 << USB_LED_NUM_LOCK)) {
                rgb_matrix_set_color(35, RGB_YELLOW);  // '6' key
            }

            const uint8_t keycodes[] = {40, 45, 51, 41, 46, 52, 42, 47, 53, 43, 48, 54};
            for (uint8_t i = 0; i < sizeof(keycodes) / sizeof(uint8_t); ++i) {
                rgb_matrix_set_color(keycodes[i], RGB_GREEN);
            }
            break;
        }
        case _NAV:
            // set_side_light_color(RGB_BLUE);
            // rgb_matrix_set_color(26, 0x64, 0x00, 0x64); // 'F' key
            // rgb_matrix_set_color(42, 0x64, 0x00, 0x64); // 'J' key
            rgb_matrix_set_color(38, 0x64, 0x64, 0x64);  // 'N' key
            rgb_matrix_set_color(58, 0x64, 0x64, 0x64);  // 'P' key
            rgb_matrix_set_color(43, 0x64, 0x00, 0x00);  // 'M' key
            rgb_matrix_set_color(48, 0x64, 0x64, 0x64);  // ',' key
            rgb_matrix_set_color(54, 0x64, 0x00, 0x00);  // '.' key
            rgb_matrix_set_color(36, 0x00, 0x64, 0x00);  // 'Y' key
            rgb_matrix_set_color(37, 0x00, 0x64, 0x00);  // 'H' key
            rgb_matrix_set_color(41, 0x64, 0x64, 0x00);  // 'U' key
            rgb_matrix_set_color(52, 0x64, 0x64, 0x00);  // 'O' key

            const uint8_t keycodes[] = {46 /*I*/, 42 /*J*/, 47 /*K*/, 53 /*L*/};
            for (uint8_t i = 0; i < sizeof(keycodes) / sizeof(uint8_t); ++i) {
                rgb_matrix_set_color(keycodes[i], 0x64, 0x00, 0x64);
            }
            break;
        case _FUNC: {
            set_side_light_color(RGB_YELLOW);

            const uint8_t keycodes[] = {14 /*W*/, 15 /*S*/, 16 /*X*/, 79 /*→*/, 94 /*↑*/, 95 /*←*/, 97 /*↓*/, 93 /*\*/};
            for (uint8_t i = 0; i < sizeof(keycodes) / sizeof(uint8_t); ++i) {
                rgb_matrix_set_color(keycodes[i], RGB_YELLOW);
            }
            break;
        }
        default:  //  for any other layers, or the default layer
            break;
    }
}
#endif

// https://docs.qmk.fm/#/feature_combo
// enum combo_events {
//   QUOT_SCLN_SWITCH_LAYERS,
//   QUOT_SCLN_SWITCH_LAYERS2,
//   QUOT_SWITCH_TO_MAIN,
//   COMBO_CUSTOM_END,
//   COMBO_CUSTOM_HOME,
//   COMBO_CUSTOM_PGUP,
//   COMBO_CUSTOM_PGDOWN,
//   COMBO_CUSTOM_LEFT,
//   COMBO_CUSTOM_RIGHT,
//   COMBO_CUSTOM_UP,
//   COMBO_CUSTOM_DOWN,
//   COMBO_CUSTOM_BACKSPACE,
//   COMBO_CUSTOM_DELETE,
// };
// const uint16_t PROGMEM test_combo[] = {KC_J, KC_SCLN, COMBO_END};
// const uint16_t PROGMEM test_combo2[] = {KC_LEFT, KC_RGHT, COMBO_END};
// const uint16_t PROGMEM test_combo3[] = {KC_S, KC_F, COMBO_END};
// const uint16_t PROGMEM test_combo4[] = {KC_J, KC_O, COMBO_END};
// const uint16_t PROGMEM test_combo5[] = {KC_L, KC_U, COMBO_END};
// const uint16_t PROGMEM test_combo6[] = {KC_L, KC_Y, COMBO_END};
// const uint16_t PROGMEM test_combo7[] = {KC_L, KC_H, COMBO_END};
// const uint16_t PROGMEM test_combo8[] = {KC_K, KC_J, COMBO_END};
// const uint16_t PROGMEM test_combo9[] = {KC_K, KC_L, COMBO_END};
// const uint16_t PROGMEM test_combo10[] = {KC_J, KC_I, COMBO_END};
// const uint16_t PROGMEM test_combo11[] = {KC_J, KC_COMM, COMBO_END};
// const uint16_t PROGMEM test_combo12[] = {KC_U, KC_I, COMBO_END};
// const uint16_t PROGMEM test_combo13[] = {KC_I, KC_O, COMBO_END};
// combo_t key_combos[COMBO_COUNT] = {
//   [QUOT_SCLN_SWITCH_LAYERS] = COMBO_ACTION(test_combo),
//   [QUOT_SCLN_SWITCH_LAYERS2] = COMBO_ACTION(test_combo2),
//   [QUOT_SWITCH_TO_MAIN] = COMBO_ACTION(test_combo3),
//   [COMBO_CUSTOM_END] = COMBO(test_combo4, KC_END),
//   [COMBO_CUSTOM_HOME] = COMBO(test_combo5, KC_HOME),
//   [COMBO_CUSTOM_PGUP] = COMBO(test_combo6, KC_PGUP),
//   [COMBO_CUSTOM_PGDOWN] = COMBO(test_combo7, KC_PGDN),
//   [COMBO_CUSTOM_LEFT] = COMBO(test_combo8, KC_LEFT),
//   [COMBO_CUSTOM_RIGHT] = COMBO(test_combo9, KC_RGHT),
//   [COMBO_CUSTOM_UP] = COMBO(test_combo10, KC_UP),
//   [COMBO_CUSTOM_DOWN] = COMBO(test_combo11, KC_DOWN),
//   [COMBO_CUSTOM_BACKSPACE] = COMBO(test_combo12, KC_BSPC),
//   [COMBO_CUSTOM_DELETE] = COMBO(test_combo13, KC_DEL),
// };

// void process_combo_event(uint16_t combo_index, bool pressed) {
//   if (!pressed) {
//     return;
//   }

//   switch(combo_index) {
//     case QUOT_SCLN_SWITCH_LAYERS:
//       if (IS_LAYER_ON(_MAIN)) {
//         layer_on(_SOME_LAYER);
//       }
//       break;
//     case QUOT_SCLN_SWITCH_LAYERS2:
//       if (IS_LAYER_ON(_SOME_LAYER)) {
//         layer_off(_SOME_LAYER);
//       }
//       break;
//     case QUOT_SWITCH_TO_MAIN:
//       layer_move(_MAIN);
//       break;
//   }
// }

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    [_MAIN] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MPLY,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          TO(_NUMP),
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_DEL,
        // KC_CAPS, SFT_T(KC_A),   CTL_T(KC_S), WIN_T(KC_D),    ALT_T(KC_F),    KC_G,    KC_H,    SFT_T(KC_J),    SFT_T(KC_K),    SFT_T(KC_L),    MO_SCLN, LT(_NAV, KC_QUOT),          KC_ENT,           KC_HOME,
        KC_CAPS, (KC_A),   (KC_S), (KC_D),    (KC_F),    KC_G,    KC_H,    (KC_J),    (KC_K),    (KC_L),    MO_SCLN, KC_QUOT,          KC_ENT,           KC_HOME,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RCTL, MO(_FUNC), KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_NUMP] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, KC_NLCK, KC_P7  , KC_P8  , KC_P9  , _______, _______, _______, _______,          TO(_MAIN),
        _______, _______, _______, _______, _______, _______, _______, KC_P4  , KC_P5  , KC_P6  , _______, _______, _______, RESET  ,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P1  , KC_P2  , KC_P3  , MO_SCLN,TO(_MAIN),         _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, KC_P0  , KC_P0  , KC_PDOT, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, MO(_FUNC), _______, _______, _______
    ),

    [_NAV] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, KC_PGUP, KC_HOME, KC_UP  , KC_END , KC_TAB , _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, KC_ESC , KC_BSPC, KC_ENT , KC_DEL , _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    [_FUNC] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            _______,
        _______, _______, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, RGB_HUI, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RGB_MOD, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),


};
// clang-format on

// Taken from https://github.com/qmk/qmk_firmware/blob/d90897052243808863bcab3b07e16d5b6a0b08f0/keyboards/gmmk/pro/ansi/keymaps/jonavin/keymap.c#L124-L149
// Shift: pgup/pgdown
// Ctrl: navigate by word
// Alt: change media track
// No mod: volume
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        if (get_mods() & MOD_BIT(KC_LSFT)) {
            unregister_mods(MOD_BIT(KC_LSFT));
            tap_code(KC_PGDN);
            register_mods(MOD_BIT(KC_LSFT));
        } else if (get_mods() & MOD_BIT(KC_LCTL)) {
            tap_code16(LCTL(KC_RGHT));
        } else if (get_mods() & MOD_BIT(KC_LALT)) {
            tap_code(KC_MEDIA_NEXT_TRACK);
        } else {
            tap_code(KC_VOLU);
        }
    } else {
        if (get_mods() & MOD_BIT(KC_LSFT)) {
            unregister_mods(MOD_BIT(KC_LSFT));
            tap_code(KC_PGUP);
            register_mods(MOD_BIT(KC_LSFT));
        } else if (get_mods() & MOD_BIT(KC_LCTL)) {
            tap_code16(LCTL(KC_LEFT));
        } else if (get_mods() & MOD_BIT(KC_LALT)) {
            tap_code(KC_MEDIA_PREV_TRACK);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}

void set_side_light_color(uint8_t hue, uint8_t sat, uint8_t val) {
    const uint8_t keycodes[] = {
        // Left side LEDs 1-8
        67,
        70,
        73,
        76,
        80,
        83,
        87,
        91,
        // Right side LEDs 1-8
        68,
        71,
        74,
        77,
        81,
        84,
        88,
        92,
    };
    for (uint8_t i = 0; i < sizeof(keycodes) / sizeof(uint8_t); ++i) {
        rgb_matrix_set_color(keycodes[i], hue, sat, val);
    }
}

void keyboard_post_init_user(void) {
    rgblight_sethsv(HSV_MAGENTA);

    // This is good in case I screw anything up with bad code; it's REALLY hard to
    // fix it when mods get messed up since it can mess up the whole OS.
    clear_mods();
}

// Sat 08/14/2021 - 11:17 PM - commenting all of this out because there's a
// ~75-ms lag writing to EEPROM. To sort of work around this, we could keep
// track of the last color we set so that we don't end up writing to EEPROM if
// it wouldn't have an effect. Alternatively, we could bind some keys in a weird
// layer to EEPROM-based stuff.
// layer_state_t layer_state_set_user(layer_state_t state) {
//   switch (get_highest_layer(state)) {
//     case _MAIN:
//         // Sets the lighting-effect color (sort of like how fn+X does for the Pro out of the box)
//         // rgblight_sethsv(HSV_MAGENTA);
//         break;
//     case _NAV:
//         // rgblight_sethsv(HSV_BLUE);
//         break;
//     default: //  for any other layers, or the default layer
//         rgblight_sethsv(HSV_ORANGE);
//         break;
//     }
//   return state;
// }

// https://github.com/qmk/qmk_firmware/issues/4611#issuecomment-446713700
// https://www.reddit.com/r/olkb/comments/oflwv6/how_do_i_change_qmk_layer_tap_behavior/h4l7u8n/?utm_source=reddit&utm_medium=web2x&context=3
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool            isPressed         = record->event.pressed;
    static bool     other_key_pressed = false;
    static uint16_t layer_timer;

    if (keycode != MO_SCLN && isPressed) {
        other_key_pressed = true;
    }

    bool isCtrlHeld  = get_mods() & MOD_BIT(KC_LCTL);
    bool isShiftHeld = get_mods() & MOD_BIT(KC_LSFT);

    switch (keycode) {
        case KC_MPLY:
            if (isPressed && isCtrlHeld) {
                tap_code(KC_MUTE);
                return false;
            }
            break;
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
        case MO_SCLN:
            if (isPressed) {
                other_key_pressed = false;
                layer_timer       = timer_read();
                layer_on(_NAV);
            } else {
                if (!other_key_pressed && timer_elapsed(layer_timer) < 300) {
                    register_code(KC_SCLN);
                    unregister_code(KC_SCLN);
                }
                layer_off(_NAV);
            }
            return false;
    }

    return true;
}
