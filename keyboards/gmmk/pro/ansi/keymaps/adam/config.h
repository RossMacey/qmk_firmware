// See https://docs.qmk.fm/#/feature_rgb_matrix

#define RGB_MATRIX_KEYPRESSES   // reacts to keypresses
#define RGB_MATRIX_KEYRELEASES  // reacts to keyreleases (instead of keypresses)

// Disable a whole bunch of effects I don't ever plan on using so that there are
// fewer to cycle through
#define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN           // Static gradient top to bottom, speed controls how much gradient changes
#define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT        // Static gradient left to right, speed controls how much gradient changes
#define DISABLE_RGB_MATRIX_BREATHING                  // Single hue brightness cycling animation
#define DISABLE_RGB_MATRIX_BAND_SAT                   // Single hue band fading saturation scrolling left to right
#define DISABLE_RGB_MATRIX_BAND_VAL                   // Single hue band fading brightness scrolling left to right
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT          // Single hue 3 blade spinning pinwheel fades saturation
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL          // Single hue 3 blade spinning pinwheel fades brightness
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT            // Single hue spinning spiral fades saturation
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL            // Single hue spinning spiral fades brightness
#define DISABLE_RGB_MATRIX_CYCLE_ALL                  // Full keyboard solid hue cycling through full gradient
#define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT           // Full gradient scrolling left to right
#define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN              // Full gradient scrolling top to bottom
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN               // Full gradient scrolling out to in
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL          // Full dual gradients scrolling out to in
#define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON     // Full gradent Chevron shapped scrolling left to right
#define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL             // Full gradient spinning pinwheel around center of keyboard
#define DISABLE_RGB_MATRIX_CYCLE_SPIRAL               // Full gradient spinning spiral around center of keyboard
#define DISABLE_RGB_MATRIX_DUAL_BEACON                // Full gradient spinning around center of keyboard
#define DISABLE_RGB_MATRIX_RAINBOW_BEACON             // Full tighter gradient spinning around center of keyboard
#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS          // Full dual gradients spinning two halfs of keyboard
#define DISABLE_RGB_MATRIX_RAINDROPS                  // Randomly changes a single key's hue
#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS        // Randomly changes a single key's hue and saturation
#define DISABLE_RGB_MATRIX_HUE_BREATHING              // Hue shifts up a slight ammount at the same time, then shifts back
#define DISABLE_RGB_MATRIX_HUE_PENDULUM               // Hue shifts up a slight ammount in a wave to the right, then back to the left
#define DISABLE_RGB_MATRIX_HUE_WAVE                   // Hue shifts up a slight ammount and then back down in a wave to the right
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE        // Hue & value pulse near a single key hit then fades value out
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE   // Hue & value pulse near multiple key hits then fades value out
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS       // Hue & value pulse the same column and row of a single key hit then fades value out
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS  // Hue & value pulse the same column and row of multiple key hits then fades value out
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS       // Hue & value pulse away on the same column and row of a single key hit then fades value out
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS  // Hue & value pulse away on the same column and row of multiple key hits then fades value out
#define DISABLE_RGB_MATRIX_SPLASH                     // Full gradient & value pulse away from a single key hit then fades value out
#define DISABLE_RGB_MATRIX_MULTISPLASH                // Full gradient & value pulse away from multiple key hits then fades value out
#define DISABLE_RGB_MATRIX_SOLID_SPLASH               // Hue & value pulse away from a single key hit then fades value out
#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH          // Hue & value pulse away from multiple key hits then fades value out

// Set default RGB mode
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_REACTIVE_SIMPLE
// Set default hue
// #define RGB_MATRIX_STARTUP_HUE 50
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
