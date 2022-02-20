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

    // Colon on its own, semicolon when shift is press. In this sense, it's
    // reversed from the regular colon key. I did this for my number layer where
    // I type colons much, much more frequently than semicolons.
    REV_COLON,

    // One-shot (Callum) mods
    OS_SHFT,
    OS_CTRL,
    OS_ALT,
    OS_GUI,
};
