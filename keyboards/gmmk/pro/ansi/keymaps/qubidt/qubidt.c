
/* Copyright 2021 Bao Trinh @qubidt

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
#include "qubidt.h"

#include "print.h"

#ifdef TD_LSFT_CAPSLOCK_ENABLE
// Tap once for shift, twice for Caps Lock but only if Win Key in not disabled
void dance_LSFT_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 || keymap_config.no_gui) {
        register_code16(KC_LSFT);
    } else {
        register_code(KC_CAPS);
    }
}

void dance_LSFT_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 || keymap_config.no_gui) {
        unregister_code16(KC_LSFT);
    } else {
        unregister_code(KC_CAPS);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for shift, twice for Caps Lock
    [TD_LSFT_CAPSLOCK] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_LSFT_CAPS_WIN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_LSFT_finished, dance_LSFT_reset),
};
#endif  // TD_LSFT_CAPSLOCK_ENABLE

// RGB NIGHT MODE
#ifdef RGB_MATRIX_ENABLE
static bool rgb_nightmode = false;

// Turn on/off NUM LOCK if current state is different
void activate_rgb_nightmode(bool turn_on) {
    if (rgb_nightmode != turn_on) {
        rgb_nightmode = !rgb_nightmode;
    }
}

bool get_rgb_nightmode(void) { return rgb_nightmode; }
#endif  // RGB_MATRIX_ENABLE

// TIMEOUTS
#ifdef IDLE_TIMEOUT_ENABLE
static uint16_t timeout_timer     = 0;
static uint16_t timeout_counter   = 0;  // in minute intervals
static uint16_t timeout_threshold = TIMEOUT_THRESHOLD_DEFAULT;

uint16_t get_timeout_threshold(void) { return timeout_threshold; }

void timeout_reset_timer(void) {
    timeout_timer   = timer_read();
    timeout_counter = 0;
};

void timeout_update_threshold(bool increase) {
    if (increase && timeout_threshold < TIMEOUT_THRESHOLD_MAX) timeout_threshold++;
    if (!increase && timeout_threshold > 0) timeout_threshold--;
};

void timeout_tick_timer(void) {
    if (timeout_threshold > 0) {
        if (timer_elapsed(timeout_timer) >= 60000) {  // 1 minute tick
            timeout_counter++;
            timeout_timer = timer_read();
        }
#    ifdef RGB_MATRIX_ENABLE
        if (timeout_threshold > 0 && timeout_counter >= timeout_threshold) {
            rgb_matrix_disable_noeeprom();
        }
#    endif
    }  // timeout_threshold = 0 will disable timeout
}

__attribute__((weak)) void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
    timeout_tick_timer();
    matrix_scan_keymap();
}
#endif  // IDLE_TIMEOUT_ENABLE

#ifdef ENCODER_ENABLE
#    ifndef DYNAMIC_KEYMAP_LAYER_COUNT
#        define DYNAMIC_KEYMAP_LAYER_COUNT 4  // default in case this is not already defined elsewhere
#    endif
#    ifndef ENCODER_DEFAULTACTIONS_INDEX
#        define ENCODER_DEFAULTACTIONS_INDEX 0  // can select encoder index if there are multiple encoders
#    endif

uint8_t selected_layer = 0;

__attribute__((weak)) bool encoder_update_keymap(uint8_t index, bool clockwise) { return true; }

const char *get_layer_name(int layer) {
    // clang-format off
    switch (layer) {
        case _FN1:      return "_FN1";
        case _BASE:     return "_BASE";
        case _LOWER:    return "_LOWER";
        case _RAISE:    return "_RAISE";

        default:        return "UNKNOWN";
    }
    // clang-format on
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    // clang-format off
    if (!encoder_update_keymap(index, clockwise)) { return false; }
    if (index != ENCODER_DEFAULTACTIONS_INDEX) { return true; }  // exit if the index doesn't match
    // clang-format on

    dprintf("[encoder_update_user][%6s] %s\n", get_layer_name(selected_layer), clockwise ? "clockwise" : "counter-clockwise");

    dprint("                               LCTL | LSFT | LALT | LGUI | RCTL | RSFT | RALT | RGUI\n");
    dprint("                              ");
    dprintf(" %4s |", (keyboard_report->mods & MOD_BIT(KC_RCTL)) ? "x" : "_");
    dprintf(" %4s |", (keyboard_report->mods & MOD_BIT(KC_RSFT)) ? "x" : "_");
    dprintf(" %4s |", (keyboard_report->mods & MOD_BIT(KC_RALT)) ? "x" : "_");
    dprintf(" %4s |", (keyboard_report->mods & MOD_BIT(KC_RGUI)) ? "x" : "_");
    dprintf(" %4s |", (keyboard_report->mods & MOD_BIT(KC_LCTL)) ? "x" : "_");
    dprintf(" %4s |", (keyboard_report->mods & MOD_BIT(KC_LSFT)) ? "x" : "_");
    dprintf(" %4s |", (keyboard_report->mods & MOD_BIT(KC_LALT)) ? "x" : "_");
    dprintf(" %4s |", (keyboard_report->mods & MOD_BIT(KC_LGUI)) ? "x" : "_");
    dprint("\n");

    switch (selected_layer) {
        case _FN1:
#    ifdef IDLE_TIMEOUT_ENABLE
            timeout_update_threshold(clockwise);
#    endif
            break;

        case _BASE:
        case _LOWER:
        case _RAISE:
        default:
            if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
                // LSHIFT -> Layer change
                if (clockwise && selected_layer < (DYNAMIC_KEYMAP_LAYER_COUNT - 1)) {
                    selected_layer++;
                } else if (!clockwise && selected_layer > 0) {
                    selected_layer--;
                }
                layer_move(selected_layer);

            } else if (keyboard_report->mods & MOD_BIT(KC_RSFT)) {
                // RSHIFT -> Page down/up
                unregister_mods(MOD_BIT(KC_RSFT));
                wait_ms(1);  // handle race condition
                tap_code(clockwise ? KC_PGDN : KC_PGUP);
                wait_ms(1);
                register_mods(MOD_BIT(KC_RSFT));

            } else if (keyboard_report->mods & MOD_BIT(KC_LCTL)) {
                // LCTRL -> Next/prev word (ctrl right/left)
                // if holding Left Ctrl, navigate next/prev word
                tap_code16(LCTL(clockwise ? KC_RGHT : KC_LEFT));

            } else if (keyboard_report->mods & MOD_BIT(KC_LALT)) {
                // LALT -> Next/Prev track
                unregister_mods(MOD_BIT(KC_LALT));
                wait_ms(1);  // handle race condition
                tap_code(clockwise ? KC_MEDIA_NEXT_TRACK : KC_MEDIA_PREV_TRACK);
                wait_ms(1);
                register_mods(MOD_BIT(KC_LALT));

            } else {
                // Default -> increase/decrease volume
                tap_code(clockwise ? KC_VOLU : KC_VOLD);
            }

            break;
    }

    return true;
}
#endif  // ENCODER_ENABLE

// PROCESS KEY CODES
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

const char *get_key_name(int keycode) {
    // clang-format off
    switch (keycode) {
        case 20737:             return "FN";

        case KC_00:             return "KC_00";
        case ENCFUNC:           return "ENCFUNC";
        case KC_WINLCK:         return "KC_WINLCK";
        case RGB_TOI:           return "RGB_TOI";
        case RGB_TOD:           return "RGB_TOD";
        case RGB_NITE:          return "RGB_NITE";

        case KC_0:              return "KC_0";
        case KC_1:              return "KC_1";
        case KC_2:              return "KC_2";
        case KC_3:              return "KC_3";
        case KC_4:              return "KC_4";
        case KC_5:              return "KC_5";
        case KC_6:              return "KC_6";
        case KC_7:              return "KC_7";
        case KC_8:              return "KC_8";
        case KC_9:              return "KC_9";
        case KC_A:              return "KC_A";
        case KC_AF4:            return "KC_AF4";
        case KC_B:              return "KC_B";
        case KC_BSLS:           return "KC_BSLS";
        case KC_BSPC:           return "KC_BSPC";
        case KC_C:              return "KC_C";
        case KC_CAD:            return "KC_CAD";
        case KC_CALC:           return "KC_CALC";
        case KC_CAPS:           return "KC_CAPS";
        case KC_COMM:           return "KC_COMM";
        case KC_D:              return "KC_D";
        case KC_DEL:            return "KC_DEL";
        case KC_DOT:            return "KC_DOT";
        case KC_DOWN:           return "KC_DOWN";
        case KC_E:              return "KC_E";
        case KC_END:            return "KC_END";
        case KC_ENT:            return "KC_ENT";
        case KC_EQL:            return "KC_EQL";
        case KC_ESC:            return "KC_ESC";
        case KC_F:              return "KC_F";
        case KC_F1:             return "KC_F1";
        case KC_F10:            return "KC_F10";
        case KC_F11:            return "KC_F11";
        case KC_F12:            return "KC_F12";
        case KC_F2:             return "KC_F2";
        case KC_F3:             return "KC_F3";
        case KC_F4:             return "KC_F4";
        case KC_F5:             return "KC_F5";
        case KC_F6:             return "KC_F6";
        case KC_F7:             return "KC_F7";
        case KC_F8:             return "KC_F8";
        case KC_F9:             return "KC_F9";
        case KC_G:              return "KC_G";
        case KC_GRV:            return "KC_GRV";
        case KC_H:              return "KC_H";
        case KC_HOME:           return "KC_HOME";
        case KC_I:              return "KC_I";
        case KC_INS:            return "KC_INS";
        case KC_J:              return "KC_J";
        case KC_K:              return "KC_K";
        case KC_L:              return "KC_L";
        case KC_LALT:           return "KC_LALT";
        case KC_LBRC:           return "KC_LBRC";
        case KC_LCTL:           return "KC_LCTL";
        case KC_LEFT:           return "KC_LEFT";
        case KC_LCMD:           return "KC_LGUI";
        case KC_LSFT:           return "KC_LSFT";
        case KC_LSFTCAPS:       return "KC_LSFTCAPS";
        case KC_LSFTCAPSWIN:    return "KC_LSFTCAPSWIN";
        case KC_M:              return "KC_M";
        case KC_MINS:           return "KC_MINS";
        case KC_MNXT:           return "KC_MNXT";
        case KC_MPLY:           return "KC_MPLY";
        case KC_MPRV:           return "KC_MPRV";
        case KC_MSEL:           return "KC_MSEL";
        case KC_MSTP:           return "KC_MSTP";
        case KC_MUTE:           return "KC_MUTE";
        case KC_MYCM:           return "KC_MYCM";
        case KC_N:              return "KC_N";
        case KC_NLCK:           return "KC_NUMLOCK";
        case KC_NO:             return "KC_NO";
        case KC_O:              return "KC_O";
        case KC_P:              return "KC_P";
        case KC_P0:             return "KC_P0";
        case KC_P1:             return "KC_P1";
        case KC_P2:             return "KC_P2";
        case KC_P3:             return "KC_P3";
        case KC_P4:             return "KC_P4";
        case KC_P5:             return "KC_P5";
        case KC_P6:             return "KC_P6";
        case KC_P7:             return "KC_P7";
        case KC_P8:             return "KC_P8";
        case KC_P9:             return "KC_P9";
        case KC_PAST:           return "KC_PAST";
        case KC_PAUS:           return "KC_PAUS";
        case KC_PDOT:           return "KC_PDOT";
        case KC_PENT:           return "KC_PENT";
        case KC_PGDN:           return "KC_PGDN";
        case KC_PGUP:           return "KC_PGUP";
        case KC_PMNS:           return "KC_PMNS";
        case KC_PPLS:           return "KC_PPLS";
        case KC_PSCR:           return "KC_PSCR";
        case KC_PSLS:           return "KC_PSLS";
        case KC_Q:              return "KC_Q";
        case KC_QUOT:           return "KC_QUOT";
        case KC_R:              return "KC_R";
        case KC_RALT:           return "KC_RALT";
        case KC_RBRC:           return "KC_RBRC";
        case KC_RCTL:           return "KC_RCTL";
        case KC_RGHT:           return "KC_RGHT";
        case KC_RCMD:           return "KC_RGUI";
        case KC_RSFT:           return "KC_RSFT";
        case KC_S:              return "KC_S";
        case KC_SCLN:           return "KC_SCLN";
        case KC_SLCK:           return "KC_SLCK";
        case KC_SLSH:           return "KC_SLSH";
        case KC_SPC:            return "KC_SPC";
        case KC_T:              return "KC_T";
        case KC_TAB:            return "KC_TAB";
        case KC_TASK:           return "KC_TASK";
        case KC_U:              return "KC_U";
        case KC_UP:             return "KC_UP";
        case KC_V:              return "KC_V";
        case KC_VOLD:           return "KC_VOLD";
        case KC_VOLU:           return "KC_VOLU";
        case KC_W:              return "KC_W";
        case KC_WHOM:           return "KC_WHOM";
        case KC_X:              return "KC_X";
        case KC_Y:              return "KC_Y";
        case KC_Z:              return "KC_Z";
        case NK_TOGG:           return "NK_TOGG";
        case RGB_HUI:           return "RGB_HUI";
        case RGB_MOD:           return "RGB_MOD";
        case RGB_RMOD:          return "RGB_RMOD";
        case RGB_SPD:           return "RGB_SPD";
        case RGB_SPI:           return "RGB_SPI";
        case RGB_TOG:           return "RGB_TOG";

        case RGB_VAD:           return "RGB_VAD";
        case RGB_VAI:           return "RGB_VAI";

        default:                return "UNKNOWN";
    }
    // clang-format on
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keymap(keycode, record)) {
        return false;
    }

    dprintf("[process_record_user] key (%3d) %4s %s\n", keycode, record->event.pressed ? "DOWN" : "UP", get_key_name(keycode));

    // key-up handler
    switch (keycode) {
        case KC_00:
            // toggle no_gui (disable winlock)
            if (record->event.pressed) {
                SEND_STRING("00");
            } else {
                dprintf("[process_record_user] unregistering (%d): %s\n", keycode, get_key_name(keycode));
                unregister_code16(keycode);
            }
            break;

        case KC_WINLCK:
            // toggle no_gui (disable winlock)
            if (record->event.pressed) {
                keymap_config.no_gui = !keymap_config.no_gui;
            } else {
                dprintf("[process_record_user] unregistering (%d): %s\n", keycode, get_key_name(keycode));
                unregister_code16(keycode);
            }
            break;

#ifdef RGB_MATRIX_ENABLE
        case RGB_NITE:
            if (record->event.pressed) {
                rgb_nightmode ^= 1;
            } else {
                dprintf("[process_record_user] unregistering (%d): %s\n", keycode, get_key_name(keycode));
                unregister_code16(keycode);
            }
            break;

        case RGB_TOG:
            if (record->event.pressed) {
                rgb_matrix_toggle();
                return false;
            } else {
                dprintf("[process_record_user] unregistering (%d): %s\n", keycode, get_key_name(keycode));
                unregister_code16(keycode);
            }
            break;
#endif  // RGB_MATRIX_ENABLE

#ifdef IDLE_TIMEOUT_ENABLE
        case RGB_TOI:
        case RGB_TOD:
            // increase/decrease timeout
            if (record->event.pressed) {
                timeout_update_threshold(keycode == RGB_TOI);
            } else {
                dprintf("[process_record_user] unregistering (%d): %s\n", keycode, get_key_name(keycode));
                unregister_code16(keycode);
            }
            break;
#endif  // IDLE_TIMEOUT_ENABLE

        default:
#ifdef RGB_MATRIX_ENABLE
            rgb_matrix_enable();
#endif
#ifdef IDLE_TIMEOUT_ENABLE
            timeout_reset_timer();
#endif
            break;
    }

    return true;
};

// Turn on/off NUM LOCK if current state is different
void activate_numlock(bool turn_on) {
    if (IS_HOST_LED_ON(USB_LED_NUM_LOCK) != turn_on) {
        tap_code(KC_NUMLOCK);
    }
}

// INITIAL STARTUP

__attribute__((weak)) void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) {
    dprint("[keyboard_post_init_user] begin");

    keyboard_post_init_keymap();

#ifdef STARTUP_NUMLOCK_ON
    // turn on Num lock by default so that the numpad layer always has predictable results
    activate_numlock(true);
#endif  // STARTUP_NUMLOC_ON

#ifdef IDLE_TIMEOUT_ENABLE
    // set inital time for ide timeout
    timeout_timer = timer_read();
#endif  // IDLE_TIMEOUT_ENABLE

    dprint("[keyboard_post_init_user] end");
}
