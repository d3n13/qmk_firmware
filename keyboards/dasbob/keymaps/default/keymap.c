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

enum dasbob_layers {
  _QWERTY_MAC = 0,
  _GUI_CTRL_WIN,
  _LOWER, // nums_mouse_misc_layer
  _RAISE, // symbols_arrows_layer
  _R_MOUSE, // one_handed_mouse_layer
  _GAMING, 
  _GAMING_2,
  _F_KEYS_AND_SETUP,
  _SETUP
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY_MAC] = LAYOUT_split_3x5_3(
      KC_Q,         KC_W,         KC_E,         KC_R,               KC_T,                                                                        KC_Y,               KC_U,              KC_I,         KC_O,         KC_P,
      LSFT_T(KC_A), LCTL_T(KC_S), LALT_T(KC_D), LGUI_T(KC_F),       LGUI_T(KC_G),                                                                RGUI_T(KC_H),       RGUI_T(KC_J),      RALT_T(KC_K), RCTL_T(KC_L), RSFT_T(KC_SCLN),
      KC_Z,         KC_X,         KC_C,         KC_V,               KC_B,                                                                        KC_N,               KC_M,              KC_COMM,      KC_DOT,       LT(_LOWER, KC_SLSH),
                                                LT(_LOWER, KC_DEL), LT(_RAISE, KC_BACKSPACE), LGUI_T(KC_SPC),   LT(_F_KEYS_AND_SETUP, KC_ENTER), LT(_RAISE, KC_TAB), LT(_RAISE, KC_ESC)
    ),
    [_GUI_CTRL_WIN] = LAYOUT_split_3x5_3(
      _______, _______,      _______, _______,      _______,                                _______,      _______,      _______, _______,      _______,
      _______, LGUI_T(KC_S), _______, LCTL_T(KC_F), LCTL_T(KC_G),                           RCTL_T(KC_H), RCTL_T(KC_J), _______, RGUI_T(KC_L), _______,
      _______, _______,      _______, _______,      _______,                                _______,      _______,      _______, _______,      _______,
                                      _______,      _______,      LCTL_T(KC_SPC),  _______, _______,      _______
    ),
    [_LOWER] = LAYOUT_split_3x5_3(
      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,         KC_7,    KC_8,    KC_9,    KC_0,
      _______, _______, KC_WH_U, _______, _______,                     _______,      KC_BTN1, KC_MS_U, KC_BTN2, KC_VOLU,
      KC_ESC,  KC_WH_L, KC_WH_D, KC_WH_R, _______,                     MO(_R_MOUSE), KC_MS_L, KC_MS_D, KC_MS_R, KC_VOLD,
                                 _______, _______, _______,   KC_BTN1, KC_BTN2,      TG(_GAMING)
    ),
    [_R_MOUSE] = LAYOUT_split_3x5_3(
        _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                     _______, _______, MS_WHLU, _______, _______,
        _______, _______, _______, _______, _______,                     _______, MS_WHLL, MS_WHLD, MS_WHLR, _______,
                                   _______, _______, _______,   _______, _______, _______
    ),
    [_RAISE] = LAYOUT_split_3x5_3(
      KC_PLUS, KC_LCBR, KC_RCBR, KC_ASTR, KC_HASH,                    KC_PERC, KC_EQL,  KC_EXLM, KC_UNDS,  KC_KP_MINUS,
      KC_AT,   KC_LPRN, KC_RPRN, KC_DLR,  KC_TILDE,                   KC_GRV,  KC_QUES, KC_UP,   KC_QUOT,  KC_PIPE,
      KC_GRV,  KC_LBRC, KC_RBRC, KC_CIRC, KC_COLN,                    KC_AMPR, KC_LEFT, KC_DOWN, KC_RIGHT, KC_BACKSLASH,
                                 _______, _______,  _______,   _______, _______, _______
    ),
    [_GAMING] = LAYOUT_split_3x5_3(
      KC_ESC,  KC_Q, KC_W, KC_E,          KC_R,                       KC_Y,   KC_U,       KC_I,    KC_O,   KC_P,
      KC_LSFT, KC_A, KC_S, KC_D,          KC_F,                       KC_H,   KC_J,       KC_K,    KC_L,   KC_SCLN,
      KC_LCTL, KC_Z, KC_X, KC_C,          KC_V,                       KC_N,   KC_M,       KC_COMM, KC_DOT, KC_SLSH,
                           MO(_GAMING_2), KC_TAB, KC_SPC,   KC_ENTER, KC_TAB, TG(_GAMING)
    ),
    [_GAMING_2] = LAYOUT_split_3x5_3(
      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                         _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______,
                                 _______, _______, _______,    _______, _______, _______
    ),
    [_F_KEYS_AND_SETUP] = LAYOUT_split_3x5_3(
      KC_F1 , KC_F2 , KC_F3 , KC_F4 ,  KC_F5 ,                       _______,           _______, _______, _______, QK_BOOT,
      KC_F6 , KC_F7 , KC_F8 , KC_F9 ,  KC_F10,                       TG(_GUI_CTRL_WIN), _______, _______, _______, _______,
      KC_F11, KC_F12, KC_F13, KC_F14,  KC_F15,                       _______,           _______, _______, _______, _______,
                              _______, _______, _______,    _______, _______, _______
    ),
    [_SETUP] = LAYOUT_split_3x5_3(
        _______, _______, _______, _______,           QK_BOOT,             _______, _______, _______, _______, _______,
        _______, _______, _______, _______,           _______,             _______, _______, _______, _______, KC_BRIU,
        _______, _______, _______, TG(_GUI_CTRL_WIN), _______,             _______, _______, _______, _______, KC_BRID,
                                   _______, _______,  _______,    _______, _______, _______
      )
};

enum combos {
    ZX_SETUP_LAYER
};

const uint16_t PROGMEM zx_combo[] = {KC_Z, KC_X, COMBO_END};

combo_t key_combos[] = {
    [ZX_SETUP_LAYER] = COMBO(zx_combo, MO(_SETUP)),
};
