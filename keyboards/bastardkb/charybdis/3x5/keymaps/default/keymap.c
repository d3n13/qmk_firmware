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
    LAYER_WINDOWS_GUI_CTRL,
    LAYER_SYMBOLS,
    LAYER_NUMERAL,
    LAYER_GAMING,
    LAYER_GAMING_NUMS,
    LAYER_F_KEYS_AND_SETUP,
    LAYER_SETUP
};

#define BSP_SYM LT(LAYER_SYMBOLS, KC_BSPC)
#define TAB_SYM LT(LAYER_SYMBOLS, KC_TAB)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

#define LAYOUT_LAYER_BASE                                                                                           \
    KC_Q, KC_W, KC_E, KC_R, KC_T,                        KC_Y, KC_U, KC_I,    KC_O,   KC_P,                         \
    KC_A, KC_S, KC_D, KC_F, KC_G,                        KC_H, KC_J, KC_K,    KC_L,   KC_SCLN,                      \
    KC_Z, KC_X, KC_C, KC_V, KC_B,                        KC_N, KC_M, KC_COMM, KC_DOT, LT(LAYER_NUMERAL, KC_SLSH),   \
    LT(LAYER_NUMERAL, KC_DEL), BSP_SYM, LGUI_T(KC_SPC),  LT(LAYER_F_KEYS_AND_SETUP, KC_ENTER), TAB_SYM

/** Convenience row shorthands. */
#define ___________TRANSPARENT_HALF_ROW____________ _______, _______, _______, _______, _______

#define LAYOUT_LAYER_NUMERAL \
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,             KC_7,    KC_8,    KC_9,    KC_0,   \
    DRGSCRL, SNIPING, KC_WH_U, _______, _______,        KC_CAPS,          DRGSCRL, DRGSCRL, DRGSCRL, KC_VOLU, \
    KC_ESC,  KC_WH_L, KC_WH_D, KC_WH_R, KC_CAPS,        TG(LAYER_GAMING), KC_BTN1, KC_BTN2, KC_BTN2, KC_VOLD, \
                      _______, _______, _______,        KC_BTN1, KC_BTN2

#define LAYOUT_LAYER_WINDOWS_GUI_CTRL \
    _______, _______,      _______, _______,      _______,                           _______,      _______,      _______,      _______, _______, \
    _______, LGUI_T(KC_S), _______, LCTL_T(KC_F), LCTL_T(KC_G),                      RCTL_T(KC_H), RCTL_T(KC_J), _______, RGUI_T(KC_L), _______, \
    _______, _______,      _______, _______,      _______,                           _______,      _______,      _______,      _______, _______, \
                                    _______,      _______, LCTL_T(KC_SPC),  _______, _______

#define LAYOUT_LAYER_SYMBOLS \
      KC_PLUS, KC_LCBR, KC_RCBR, KC_ASTR, KC_HASH,                     KC_PERC, KC_EQL,  KC_EXLM, KC_UNDS,  KC_KP_MINUS, \
      KC_AT,   KC_LPRN, KC_RPRN, KC_DLR,  KC_TILDE,                    KC_GRV,  KC_QUES, KC_UP,   KC_QUOT,  KC_PIPE, \
      KC_GRV,  KC_LBRC, KC_RBRC, KC_CIRC, KC_COLN,                     KC_AMPR, KC_LEFT, KC_DOWN, KC_RIGHT, KC_BACKSLASH, \
                                 _______, _______, _______,   _______, _______

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

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(HOME_ROW_MOD(LAYOUT_LAYER_BASE)),
  [LAYER_WINDOWS_GUI_CTRL] = LAYOUT_wrapper(LAYOUT_LAYER_WINDOWS_GUI_CTRL),
  [LAYER_NUMERAL] = LAYOUT_wrapper(LAYOUT_LAYER_NUMERAL),
  [LAYER_SYMBOLS] = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
  [LAYER_GAMING] = LAYOUT_wrapper(
      KC_ESC,  KC_Q, KC_W, KC_E,  KC_R,            KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,
      KC_LSFT, KC_A, KC_S, KC_D,  KC_F,            KC_H,   KC_J,    KC_K,    KC_L,    KC_WH_U,
      KC_LCTL, KC_Z, KC_X, KC_C,  KC_V,            KC_N,   KC_BTN1, KC_BTN3, KC_BTN2, KC_WH_D,
      MO(LAYER_GAMING_NUMS), KC_TAB, KC_SPC,       KC_ENTER, TG(LAYER_GAMING)
  ),
  [LAYER_GAMING_NUMS] = LAYOUT_wrapper(
      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,
      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                         _______,  _______, _______, _______, KC_SCLN,
      ___________TRANSPARENT_HALF_ROW____________,                      _______,  KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                                 _______, _______, _______,    _______, _______
   ),
   [LAYER_F_KEYS_AND_SETUP] = LAYOUT_wrapper(
      KC_F1,  KC_F2,  KC_F3,  KC_F4,   KC_F5,             DPI_MOD,                    S_D_MOD, _______, _______, QK_BOOT,
      KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,            TG(LAYER_WINDOWS_GUI_CTRL), _______, _______, _______, _______,
      KC_F11, KC_F12, KC_F13, KC_F14,  KC_F15,            _______,                    _______, _______, _______, _______,
                              _______, _______, _______,  _______,                    _______
   ),
   [LAYER_SETUP] = LAYOUT_wrapper(
      _______, _______, _______, _______,                    QK_BOOT,                    _______, _______, _______, _______, _______,
      _______, _______, _______, DPI_MOD,                    S_D_MOD,                    _______, _______, _______, _______, _______,
      _______, _______, _______, TG(LAYER_WINDOWS_GUI_CTRL), _______,                    _______, _______, _______, _______, _______,
                                 _______,                    _______, _______,  _______, _______
   ),
};

enum combos {
  ZX_SETUP_LAYER
};

const uint16_t PROGMEM zx_combo[] = {KC_Z, KC_X, COMBO_END};

combo_t key_combos[] = {
  [ZX_SETUP_LAYER] = COMBO(zx_combo, MO(LAYER_SETUP)),
};
