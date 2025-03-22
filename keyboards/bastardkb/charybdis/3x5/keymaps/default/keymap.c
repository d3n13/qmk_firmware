/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum custom_keycodes {
    JS_ARROW_FN = SAFE_RANGE,
    JS_FN,
    JS_PROMISE,
    JSX_USE_EFFECT,
    JSX_USE_STATE,
    JSX_USE_REF
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case JS_ARROW_FN:
        if (record->event.pressed) {
            SEND_STRING("()=>{}" SS_TAP(X_LEFT));
        }
        break;
    case JS_FN:
        if (record->event.pressed) {
            SEND_STRING("function (){}" SS_TAP(X_LEFT));
        }
        break;
    case JS_PROMISE:
        if (record->event.pressed) {
            SEND_STRING("new Promise((res,rej)=>{res()})" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
        }
        break;
    case JSX_USE_EFFECT:
        if (record->event.pressed) {
            SEND_STRING("useEffect(()=>{},[])" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
        }
        break;
    case JSX_USE_STATE:
        if (record->event.pressed) {
            SEND_STRING("const [state,setState]=useState()" SS_TAP(X_LEFT));
        }
        break;
    case JSX_USE_REF:
        if (record->event.pressed) {
            SEND_STRING("const ref=useRef(null)");
        }
        break;
    }
    return true;
};

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_SYMBOLS,
    LAYER_NUMERAL,
    LAYER_GAMING,
    LAYER_GAMING_NUMS,
    LAYER_POINTER,
    LAYER_MACROS_AND_SETUP,
    LAYER_SETUP
};

// Automatically enable sniping-mode on the pointer layer.
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define BSP_SYM LT(LAYER_SYMBOLS, KC_BSPC)
#define TAB_SYM LT(LAYER_SYMBOLS, KC_TAB)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
/** \brief QWERTY layout (3 rows, 10 columns). */
#define LAYOUT_LAYER_BASE                                                                          \
    KC_Q, KC_W, KC_E, KC_R, KC_T,       KC_Y, KC_U, KC_I,    KC_O,   KC_P,                         \
    KC_A, KC_S, KC_D, KC_F, KC_G,       KC_H, KC_J, KC_K,    KC_L,   KC_SCLN,                      \
    KC_Z, KC_X, KC_C, KC_V, KC_B,       KC_N, KC_M, KC_COMM, KC_DOT, LT(LAYER_NUMERAL, KC_SLSH),   \
    LT(LAYER_NUMERAL, KC_DEL), BSP_SYM, LGUI_T(KC_SPC),  LT(LAYER_MACROS_AND_SETUP, KC_ENTER), TAB_SYM

/** Convenience row shorthands. */
#define ___________TRANSPARENT_HALF_ROW____________ _______, _______, _______, _______, _______

/*
 * Layers used on the Charybdis Nano.
 *
 * These layers started off heavily inspired by the Miryoku layout, but trimmed
 * down and tailored for a stock experience that is meant to be fundation for
 * further personalization.
 *
 * See https://github.com/manna-harbour/miryoku for the original layout.
 */

/**
 * \brief Numeral layout.
 *
 * Primary left-hand layer (right home thumb) is numerals and symbols. Numerals
 * are in the standard numpad locations with symbols in the remaining positions.
 * `KC_DOT` is duplicated from the base layer.
 */
#define LAYOUT_LAYER_NUMERAL \
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,             KC_7,    KC_8,    KC_9,    KC_0,   \
    DRGSCRL, SNIPING, KC_WH_U, _______, _______,        KC_CAPS,          DRGSCRL, DRGSCRL, DRGSCRL, KC_VOLU, \
    KC_ESC,  KC_WH_L, KC_WH_D, KC_WH_R, KC_CAPS,        TG(LAYER_GAMING), KC_BTN1, KC_BTN2, KC_BTN2, KC_VOLD, \
                      _______, _______, _______,        KC_BTN1, KC_BTN2

/**
 * \brief Symbols layer.
 *
 * Secondary left-hand layer has shifted symbols in the same locations to reduce
 * chording when using mods with shifted symbols. `KC_LPRN` is duplicated next to
 * `KC_RPRN`.
 */
#define LAYOUT_LAYER_SYMBOLS \
      KC_PLUS, KC_LCBR, KC_RCBR, KC_ASTR, KC_HASH,                     KC_PERC, KC_EQL,  KC_EXLM, KC_UNDS,  KC_KP_MINUS, \
      KC_AT,   KC_LPRN, KC_RPRN, KC_DLR,  KC_TILDE,                    KC_GRV,  KC_QUES, KC_UP,   KC_QUOT,  KC_PIPE, \
      KC_GRV,  KC_LBRC, KC_RBRC, KC_CIRC, KC_COLN,                     KC_AMPR, KC_LEFT, KC_DOWN, KC_RIGHT, KC_BACKSLASH, \
                                 _______, _______, _______,   _______, _______

/**
 * \brief Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for GACS (Gui, Alt, Ctl, Shift)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     HOME_ROW_MOD_GACS(LAYER_ALPHAS_QWERTY)
 */
#define _HOME_ROW_MOD(                                            \
    L00, L01, L02, L03, L04,   R05, R06, R07, R08, R09, \
    L10, L11, L12, L13, L14,   R15, R16, R17, R18, R19,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
             LSFT_T(L10), LCTL_T(L11), LALT_T(L12), LGUI_T(L13), LGUI_T(L14), \
             RGUI_T(R15), RGUI_T(R16), RALT_T(R17), RCTL_T(R18), RSFT_T(R19), \
      __VA_ARGS__
#define HOME_ROW_MOD(...) _HOME_ROW_MOD(__VA_ARGS__)

/** \brief Mouse emulation and pointer functions. */
#define LAYOUT_LAYER_POINTER                                                                  \
    QK_BOOT,  EE_CLR, XXXXXXX, DPI_MOD, S_D_MOD, S_D_MOD, DPI_MOD, XXXXXXX,  EE_CLR, QK_BOOT, \
    ___________TRANSPARENT_HALF_ROW____________, ___________TRANSPARENT_HALF_ROW____________, \
    _______, DRGSCRL, SNIPING, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, SNIPING, DRGSCRL, _______, \
                      KC_BTN2, KC_BTN1, KC_BTN3, KC_BTN3, KC_BTN1



#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(HOME_ROW_MOD(LAYOUT_LAYER_BASE)),
  [LAYER_NUMERAL] = LAYOUT_wrapper(LAYOUT_LAYER_NUMERAL),
  [LAYER_SYMBOLS] = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
  [LAYER_POINTER] = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
  [LAYER_GAMING] = LAYOUT_wrapper(
      KC_ESC,  KC_Q, KC_W, KC_E,  KC_R,            KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,
      KC_LSFT, KC_A, KC_S, KC_D,  KC_F,            KC_H,   KC_J,    KC_K,    KC_L,    KC_WH_U,
      KC_LCTL, KC_Z, KC_X, KC_C,  KC_V,            KC_N,   KC_BTN1, KC_BTN3, KC_BTN2, KC_WH_D,
      MO(LAYER_GAMING_NUMS), KC_TAB, KC_SPC,       KC_ENTER, TG(LAYER_GAMING)
  ),
  [LAYER_GAMING_NUMS] = LAYOUT_wrapper(
      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         ___________TRANSPARENT_HALF_ROW____________,
      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                         _______,  _______, _______, _______, KC_SCLN,
      ___________TRANSPARENT_HALF_ROW____________,                      _______,  KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                                 _______, _______, _______,    _______, _______
   ),
   [LAYER_MACROS_AND_SETUP] = LAYOUT_wrapper(
      JS_ARROW_FN,    JS_FN,         JS_PROMISE,  _______, _______,                      DPI_MOD, S_D_MOD, _______, _______, QK_BOOT,
      JSX_USE_EFFECT, JSX_USE_STATE, JSX_USE_REF, _______, _______,                      CG_TOGG, _______, _______, _______, _______,
      _______,        _______,       _______,     _______, _______,                      _______, _______, _______, _______, _______,
                                     _______,     _______, _______,    _______, _______
   ),
   [LAYER_SETUP] = LAYOUT_wrapper(
      _______, _______, _______, _______, QK_BOOT,                      _______, _______, _______, _______, _______,
      _______, _______, _______, DPI_MOD, S_D_MOD,                      _______, _______, _______, _______, _______,
      _______, _______, _______, CG_TOGG, _______,                      _______, _______, _______, _______, _______,
                                 _______, _______, _______,    _______, _______
   ),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in
// rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

enum combos {
  ZX_SETUP_LAYER
};

const uint16_t PROGMEM zx_combo[] = {KC_Z, KC_X, COMBO_END};

combo_t key_combos[] = {
  [ZX_SETUP_LAYER] = COMBO(zx_combo, MO(LAYER_SETUP)),
};
