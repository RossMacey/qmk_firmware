// See https://docs.qmk.fm/#/feature_rgb_matrix

#define RGB_MATRIX_KEYPRESSES   // reacts to keypresses
#define RGB_MATRIX_KEYRELEASES  // reacts to keyreleases (instead of keypresses)

#define RGB_MATRIX_KEYPRESSES  // reacts to keypresses
// Light up keys when pressed, then fade to unlit.
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
// Set default RGB mode
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_REACTIVE_SIMPLE
// Set default hue
#define RGB_MATRIX_STARTUP_HUE 200
// Set default saturation
#define RGB_MATRIX_STARTUP_SAT 255
// Set default brightness
#define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
// Set default animation speed
#define RGB_MATRIX_STARTUP_SPD 35
// Turn off RGB when USB is suspended
#define RGB_DISABLE_WHEN_USB_SUSPENDED

// https://docs.qmk.fm/#/feature_combo
// #define COMBO_COUNT 13
// #define COMBO_TERM 20

// Default is 10ms apparently, but I want FAST POLLS
// #define USB_POLLING_INTERVAL_MS 1

// Allow sending more keys at a time
// #define QMK_KEYS_PER_SCAN 4

#define TAPPING_TERM 500

// Allow activating a dual-function "hold" action right after tapping it rather
// than repeating the "tap" action.
#define TAPPING_FORCE_HOLD

// To activate the hold function of a Mod-Tap key, this requires you to press
// AND release another key.
#define IGNORE_MOD_TAP_INTERRUPT

#define PERMISSIVE_HOLD
