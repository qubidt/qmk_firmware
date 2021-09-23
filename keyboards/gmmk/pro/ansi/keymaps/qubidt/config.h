/* Copyright 2021 Bao Trinh @qubidt
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

#pragma once

#define TAPPING_TOGGLE 2  // TT () set to two taps

/*  Handle GRAVESC combo keys */
#define GRAVE_ESC_ALT_OVERRIDE   // Always send Escape if Alt is pressed
#define GRAVE_ESC_CTRL_OVERRIDE  // Always send Escape if Control is pressed

#define TAPPING_TERM 180

#ifdef RGB_MATRIX_ENABLE
// clang-format off

#   define RGB_MATRIX_KEYPRESSES           // reacts to keypresses
//  define RGB_MATRIX_KEYRELEASES          // reacts to keyreleases (instead of keypresses)
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS  // enable framebuffer effects
#   define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended

#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_ALL          // Sets the default mode, if none has been set
#    define RGB_MATRIX_STARTUP_HUE 32                             // Sets the default hue value, if none has been set
//   define RGB_MATRIX_STARTUP_SAT 255                            // Sets the default saturation value, if none has been set
//   define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS  // Sets the default brightness value, if none has been set
//   define RGB_MATRIX_STARTUP_SPD 127                            // Sets the default animation speed, if none has been set
//   define RGB_MATRIX_DISABLE_KEYCODES                           // disables control of rgb matrix by keycodes (must use code functions to control the feature)

//   define RGB_DISABLE_TIMEOUT 0                                    // number of milliseconds to wait until rgb automatically turns off
//   define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5  // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
//   define RGB_MATRIX_LED_FLUSH_LIMIT 16                            // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
//   define RGB_MATRIX_MAXIMUM_BRIGHTNESS UINT8_MAX                  // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255

//   define RGB_MATRIX_HUE_STEP 8
//   define RGB_MATRIX_SAT_STEP 16
//   define RGB_MATRIX_VAL_STEP 16
//   define RGB_MATRIX_SPD_STEP 16

/* BEGIN: Disable RGB Effects */
// This list in in the correct mode order. Next mode is the following line, previous mode is previous line. Loops around.

//   define DISABLE_RGB_MATRIX_ALPHAS_MODS                  // Static dual hue, speed is hue for secondary hue
//   define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN             // Static gradient top to bottom, speed controls how much gradient changes
//   define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT          // Static gradient left to right, speed controls how much gradient changes
//   define DISABLE_RGB_MATRIX_BREATHING                    // Single hue brightness cycling animation
//   define DISABLE_RGB_MATRIX_BAND_SAT                     // Single hue band fading saturation scrolling left to right
//   define DISABLE_RGB_MATRIX_BAND_VAL                     // Single hue band fading brightness scrolling left to right
//   define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT            // Single hue 3 blade spinning pinwheel fades saturation
//   define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL            // Single hue 3 blade spinning pinwheel fades brightness
//   define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT              // Single hue spinning spiral fades saturation
//   define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL              // Single hue spinning spiral fades brightness
//   define DISABLE_RGB_MATRIX_CYCLE_ALL                    // Full keyboard solid hue cycling through full gradient
//   define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT             // Full gradient scrolling left to right
//   define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN                // Full gradient scrolling top to bottom
//   define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON       // Full gradent Chevron shapped scrolling left to right
//   define DISABLE_RGB_MATRIX_CYCLE_OUT_IN                 // Full gradient scrolling out to in
//   define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL            // Full dual gradients scrolling out to in
//   define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL               // Full gradient spinning pinwheel around center of keyboard
//   define DISABLE_RGB_MATRIX_CYCLE_SPIRAL                 // Full gradient spinning spiral around center of keyboard
//   define DISABLE_RGB_MATRIX_DUAL_BEACON                  // Full gradient spinning around center of keyboard
//   define DISABLE_RGB_MATRIX_RAINBOW_BEACON               // Full tighter gradient spinning around center of keyboard
//   define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS            // Full dual gradients spinning two halfs of keyboard
//   define DISABLE_RGB_MATRIX_RAINDROPS                    // Randomly changes a single key's hue
//   define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS          // Randomly changes a single key's hue and saturation
//   define DISABLE_RGB_MATRIX_HUE_BREATHING                // Hue shifts up a slight ammount at the same time, then shifts back
//   define DISABLE_RGB_MATRIX_HUE_PENDULUM                 // Hue shifts up a slight ammount in a wave to the right, then back to the left
//   define DISABLE_RGB_MATRIX_HUE_WAVE                     // Hue shifts up a slight ammount and then back down in a wave to the right

/* BEGIN: RGB_MATRIX_FRAMEBUFFER_EFFECTS */
//   define DISABLE_RGB_MATRIX_TYPING_HEATMAP               // How hot is your WPM!
//   define DISABLE_RGB_MATRIX_DIGITAL_RAIN                 // That famous computer simulation
/* END: RGB_MATRIX_FRAMEBUFFER_EFFECTS */

/* BEGIN: RGB_MATRIX_KEYPRESSES|RGB_MATRIX_KEYRELEASES */
//   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE        // Pulses keys hit to hue & value then fades value out
//   define DISABLE_RGB_MATRIX_SOLID_REACTIVE               // Static single hue, pulses keys hit to shifted hue then fades to current hue
//   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE          // Hue & value pulse near a single key hit then fades value out
//   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE     // Hue & value pulse near multiple key hits then fades value out
//   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS         // Hue & value pulse the same column and row of a single key hit then fades value out
//   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS    // Hue & value pulse the same column and row of multiple key hits then fades value out
//   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS         // Hue & value pulse away on the same column and row of a single key hit then fades value out
//   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS    // Hue & value pulse away on the same column and row of multiple key hits then fades value out
//   define DISABLE_RGB_MATRIX_SPLASH                       // Full gradient & value pulse away from a single key hit then fades value out
//   define DISABLE_RGB_MATRIX_MULTISPLASH                  // Full gradient & value pulse away from multiple key hits then fades value out
//   define DISABLE_RGB_MATRIX_SOLID_SPLASH                 // Hue & value pulse away from a single key hit then fades value out
//   define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH            // Hue & value pulse away from multiple key hits then fades value out
/* END: RGB_MATRIX_KEYPRESSES|RGB_MATRIX_KEYRELEASES */
// clang-format on

/* END: Disable RGB Effects */
#endif
