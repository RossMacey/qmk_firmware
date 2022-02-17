#pragma once

#include QMK_KEYBOARD_H

enum custom_keycodes {
    // Switch app: cmd+tab on Mac, alt+tab on Win
    SW_APP = SAFE_RANGE,
    // Switch window: cmd+` (just for Mac since Windows doesn't have something like this)
    SW_WIN,
    // Close window: cmd+w on Mac, ctrl+w on Windows
    CLS_WIN,
    // (, {, and [ based on which modifier is held
    KC_LEFT_ENCLOSE,
    // ), }, and ] based on which modifier is held
    KC_RIGHT_ENCLOSE,

    // Ctrl+backspace on Windows, alt+backspace on Mac
    KC_DWRD,

    // Mac/Windows variants for common commands
    MW_UNDO,
    MW_CUT,
    MW_COPY,
    MW_PSTE,
    MW_REDO,

    // One-shot (Callum) mods
    OS_SHFT,
    OS_CTRL,
    OS_ALT,
    OS_GUI,
};
