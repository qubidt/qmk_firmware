/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
   Copyright 2021 Qubidt

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

#include "rgb_matrix_map.h"
#include "qubidt.h"

#include "print.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.

    //  ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
    //  ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
    //  Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
    //  Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
    //  Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
    //  Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right

    [_BASE] = LAYOUT(
        KC_CAPS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LALT, KC_LCMD,                            KC_SPC,                             KC_RALT, MO(_FN1),KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN1] = LAYOUT(
        XXXXXXX, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, KC_SLCK,          XXXXXXX,
        XXXXXXX, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEBUG,            XXXXXXX,
        XXXXXXX, XXXXXXX, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,            XXXXXXX,
        KC_CAPS, XXXXXXX, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          NK_TOGG,          XXXXXXX,
        XXXXXXX,          RGB_NITE,RGB_HUI, XXXXXXX, XXXXXXX, XXXXXXX, KC_NLCK, XXXXXXX, RGB_TOD, RGB_TOI, XXXXXXX,          XXXXXXX, RGB_MOD, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, RGB_SPD, RGB_RMOD,RGB_SPI
    ),

    [_LOWER] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_PMNS, KC_PPLS, _______,          _______,
        _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______, KC_TAB,  KC_P4,   KC_P5,   KC_P6,   KC_PDOT, _______, _______, _______,          KC_HOME,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_NO,   KC_PAST,          KC_PENT,          KC_END,
        _______,          KC_NO,   KC_DEL,  KC_INS,  KC_NO,   KC_NO,   KC_NO,   KC_P0,   KC_00,   KC_PDOT, KC_PSLS,          _______, RCTL(KC_PGUP), _______,
        _______, _______, _______,                            KC_BSPC,                            _______, _______, _______, RCTL(KC_LEFT), RCTL(KC_PGDN), RCTL(KC_RIGHT)
    ),

    [_RAISE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

};
// clang-format on

#ifdef RGB_MATRIX_ENABLE

// RGB_AZURE
// RGB_BLACK
// RGB_BLUE
// RGB_CHARTREUSE
// RGB_CORAL
// RGB_CYAN
// RGB_GOLD
// RGB_GOLDENROD
// RGB_GREEN
// RGB_MAGENTA
// RGB_ORANGE
// RGB_PINK
// RGB_PURPLE
// RGB_RED
// RGB_SPRINGGREEN
// RGB_TEAL
// RGB_TURQUOISE
// RGB_WHITE
// RGB_YELLOW

// Capslock, Scroll lock and Numlock  indicator on Left side lights.
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (get_rgb_nightmode()) rgb_matrix_set_color_all(RGB_BLUE);

    if (IS_HOST_LED_ON(USB_LED_SCROLL_LOCK)) {
        rgb_matrix_set_color(LED_L1, RGB_GREEN);
        rgb_matrix_set_color(LED_L2, RGB_GREEN);
    }
    if (!IS_HOST_LED_ON(USB_LED_NUM_LOCK)) {  // on if NUM lock is OFF
        rgb_matrix_set_color(LED_L3, RGB_MAGENTA);
        rgb_matrix_set_color(LED_L4, RGB_MAGENTA);
    }
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(LED_L5, RGB_RED);
        rgb_matrix_set_color(LED_L6, RGB_RED);
        rgb_matrix_set_color(LED_L7, RGB_RED);
    }
    if (keymap_config.no_gui) {
        rgb_matrix_set_color(LED_LWIN, RGB_RED);  // light up Win key when disabled
    }

    switch (get_highest_layer(layer_state)) {  // special handling per layer
        case _FN1:                             // on Fn layer select what the encoder does when pressed
            // rgb_matrix_set_color(LED_R2, RGB_RED);
            // rgb_matrix_set_color(LED_R3, RGB_RED);
            // rgb_matrix_set_color(LED_R4, RGB_RED);

            rgb_matrix_set_color(LED_DEL, RGB_TEAL);
            rgb_matrix_set_color(LED_PGUP, RGB_BLUE);
            rgb_matrix_set_color(LED_PGDN, RGB_CHARTREUSE);
            rgb_matrix_set_color(LED_END, RGB_GOLD);

            rgb_matrix_set_color(LED_FN, RGB_PINK);  // FN key

            // Add RGB Timeout Indicator -- shows 0 to 139 using F row and num row;  larger numbers using 16bit code
            uint16_t timeout_threshold = get_timeout_threshold();
            if (timeout_threshold <= 10)
                rgb_matrix_set_color(LED_LIST_FUNCROW[timeout_threshold], RGB_RED);
            else if (timeout_threshold < 140) {
                rgb_matrix_set_color(LED_LIST_FUNCROW[(timeout_threshold / 10)], RGB_RED);
                rgb_matrix_set_color(LED_LIST_NUMROW[(timeout_threshold % 10)], RGB_RED);
            } else {  // >= 140 minutes, just show these 3 lights
                rgb_matrix_set_color(LED_LIST_NUMROW[10], RGB_RED);
                rgb_matrix_set_color(LED_LIST_NUMROW[11], RGB_RED);
                rgb_matrix_set_color(LED_LIST_NUMROW[12], RGB_RED);
            }
            break;
        case _LOWER:
            for (uint8_t i = 0; i < ARRAYSIZE(LED_LIST_NUMPAD); i++) {
                rgb_matrix_set_color(LED_LIST_NUMPAD[i], RGB_MAGENTA);
            }
            rgb_matrix_set_color(LED_R4, RGB_MAGENTA);
            rgb_matrix_set_color(LED_R5, RGB_MAGENTA);
            rgb_matrix_set_color(LED_R6, RGB_MAGENTA);
            break;
        case _RAISE:
            rgb_matrix_set_color(LED_R6, RGB_GREEN);
            rgb_matrix_set_color(LED_R7, RGB_GREEN);
            rgb_matrix_set_color(LED_R8, RGB_GREEN);
            break;
        default:
            break;
    }
}

void suspend_power_down_user(void) { rgb_matrix_set_suspend_state(true); }

void suspend_wakeup_init_user(void) { rgb_matrix_set_suspend_state(false); }
#endif

void keyboard_post_init_keymap(void) {
    print("[keyboard_post_init_keymap] begin");

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_set_color_all(RGB_NAUTILUS);  // Default startup colour
    activate_rgb_nightmode(false);           // Set to true if you want to startup in nightmode, otherwise use Fn + Z to toggle
#endif                                       // RGB_MATRIX_ENABLE

    debug_enable   = true;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;

    print("[keyboard_post_init_keymap] end");
}
