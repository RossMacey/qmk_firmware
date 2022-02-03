#pragma once

#include QMK_KEYBOARD_H

enum custom_keycodes {
    // Ctrl on Mac, GUI on Win
    MAC_CTRL_WIN_GUI = SAFE_RANGE,
    // GUI on Mac, ctrl on Win
    MAC_GUI_WIN_CTRL,
    // Cmd+tab on Mac, alt+tab on Win
    SW_APP,
    // Cmd+` (just for Mac since Windows doesn't have something like this)
    SW_WIN,
    // Cmd+w on Mac, ctrl+w on Windows
    CLS_WIN,
    // (, {, and [ based on which modifier is held
    KC_LEFT_ENCLOSE,
    // ), }, and ] based on which modifier is held
    KC_RIGHT_ENCLOSE,

    // Ctrl+backspace on Windows, alt+backspace on Mac
    KC_DWRD,

    // One-shot (Callum) mods
    OS_SHFT,
    OS_CTRL,
    OS_ALT,
    OS_GUI,
};
