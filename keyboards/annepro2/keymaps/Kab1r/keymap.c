#include <stdint.h>
#include "annepro2.h"
#include "qmk_ap2_led.h"

enum anne_pro_layers {
    _BASE,
    _MOUSE,
    _FUNCTION,
    _HARDWARE,
};

bool ledEnabled = true;
#define IS_SHIFT_MODIFIED (get_mods() & MOD_MASK_SHIFT)

#define NUM_SPEEDS (4)
#define NUM_INTENSITIES (8)

// This is ROW * MATRIX_COLS + COL
#define CAPS_LOCATION (2 * MATRIX_COLS + 0)

// Keybind Macros
#define ESC_FN (LT(_FUNCTION, KC_ESC))
#define LED_SPD (KC_AP_LED_BIDIR_SPEED)
#define BRIGHTN (KC_AP_LED_BIDIR_INTENSITY)
#define BT_UNPR (KC_AP2_BT_UNPAIR)
#define LED_MOD (KC_AP_LED_BIDIR_PROFILE)
#define LED_TOG (KC_AP_LED_TOGGLE)
#define AP_USB (KC_AP2_USB)
#define AP_BT1 (KC_AP2_BT1)
#define AP_BT2 (KC_AP2_BT2)
#define AP_BT3 (KC_AP2_BT3)
#define AP_BT4 (KC_AP2_BT4)

// clang-format off
enum custom_keycodes {
    KC_AP_LED_TOGGLE = AP2_SAFE_RANGE,
    KC_AP_LED_BIDIR_PROFILE,
    KC_AP_LED_BIDIR_SPEED,
    KC_AP_LED_BIDIR_INTENSITY
};
const uint16_t keymaps[/* LAYERS */][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Base Layer
     *  ,-----------------------------------------------------------------------------------------.
     *  |  `  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   | (14)
     *  |-----------------------------------------------------------------------------------------+
     *  | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    | (14)
     *  |-----------------------------------------------------------------------------------------+
     *  | esc FN  |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Enter    | (13)
     *  |-----------------------------------------------------------------------------------------+
     *  | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift       | (12)
     *  |-----------------------------------------------------------------------------------------+
     *  | Ctrl  | L_GUI |  Alt  |               space             |  Alt  | Lock  | HW    | Ctrl  | (8)
     *  \-----------------------------------------------------------------------------------------/
     */
    [_BASE] = KEYMAP(                                                                                                                   /* Base Layer */
        KC_GRAVE,KC_1 , KC_2 , KC_3 , KC_4 , KC_5 , KC_6 , KC_7 , KC_8 , KC_9 , KC_0 , KC_MINS , KC_EQL ,    KC_BSPC,                   //
        KC_TAB    , KC_Q , KC_W , KC_E , KC_R , KC_T , KC_Y , KC_U , KC_I , KC_O , KC_P  , KC_LBRC, KC_RBRC, KC_BSLS,                   //
        ESC_FN ,      KC_A,  KC_S, KC_D,  KC_F , KC_G , KC_H , KC_J , KC_K, KC_L, KC_SCLN, KC_QUOT  ,    KC_ENT     ,                   //
        KC_LSFT        , KC_Z , KC_X , KC_C , KC_V , KC_B , KC_N , KC_M ,KC_COMM,KC_DOT,KC_SLSH  ,     KC_RSFT      ,                   //
        KC_LCTL  , KC_LGUI , KC_LALT,              KC_SPACE,          KC_RALT, KC_LOCK      , MO(_HARDWARE), KC_RCTL                    //
        ),                                                                                                                              /* Base Layer */
    /* Function Layer
     *  ,-----------------------------------------------------------------------------------------.
     *  |     | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 | Del       |
     *  |-----------------------------------------------------------------------------------------+
     *  |        | F13 | F14 | F15 | F16 | F17 | F18 | F19 | F20 | F21 |PrtSc| Home| End |        |
     *  |-----------------------------------------------------------------------------------------+
     *  |         |     |     |     |     |     | <-  |  V  |  ^  | ->  | PGU | PGD |             |
     *  |-----------------------------------------------------------------------------------------+
     *  |            |     |     |     |     |     |ScrlL|Pause|     | Ins | Del |                |
     *  |-----------------------------------------------------------------------------------------+
     *  |       |       |       |        toggle mouse mode        |       |       |       |       |
     *  \-----------------------------------------------------------------------------------------/
     */
    [_FUNCTION] = KEYMAP(                                                                                                               /* Function Layer */
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12, KC_DEL,    //
        _______, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_PSCR , KC_HOME, KC_END,  _______,  //
        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_PGUP, KC_PGDN, _______,             //
        _______           , _______ , _______ , _______ , _______ , _______ ,KC_SLCK,KC_BRK,_______   ,KC_INS,KC_DEL,         _______,  //
        _______     , _______    , _______   ,           TG(_MOUSE)  ,              _______   , _______        ,    _______,  _______   //
        ),                                                                                                                              /* Function Layer */
    /* Hardware Layer
     *  ,-----------------------------------------------------------------------------------------.
     *  | USB | BT1 | BT2 | BT3 | BT4 |     |     |     |     |MODE |TOGGL|SPEED|BRIGH| BT_UNPAIR |
     *  |-----------------------------------------------------------------------------------------+
     *  |        |     |     |     |     |     |     |     |     |     |     |     |     |        |
     *  |-----------------------------------------------------------------------------------------+
     *  |         |     |     |     |     |     |     |     |     |     |     |     |             |
     *  |-----------------------------------------------------------------------------------------+
     *  |            |     |     |     |     |     |     |     |     |     |     |                |
     *  |-----------------------------------------------------------------------------------------+
     *  |       |       |       |                                 |       |       |       |       |
     *  \-----------------------------------------------------------------------------------------/
     */
    [_HARDWARE] = KEYMAP(                                                                                                               /* Hardware Layer */
        AP_USB,  AP_BT1,  AP_BT2,  AP_BT3,  AP_BT4,  _______, _______, _______, _______, LED_MOD, LED_TOG, LED_SPD, BRIGHTN, BT_UNPR,   //
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   //
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,   //
        _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         _______,   //
        _______,     _______,     _______,                  _______,                  _______,     _______,     _______,     _______    //
        ),                                                                                                                              /* Hardware Layer */
    /* Mouse Layer
     *  ,-----------------------------------------------------------------------------------------.
     *  |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
     *  |-----------------------------------------------------------------------------------------+
     *  |        |     |     |     |     |     |     |     |     |     |     |     |     |        |
     *  |-----------------------------------------------------------------------------------------+
     *  |         |     |     |     |     |     | <-  |  V  |  ^  |  -> |     |     |             |
     *  |-----------------------------------------------------------------------------------------+
     *  |            |     |     |     |     |     |     |     |     |     |     |                |
     *  |-----------------------------------------------------------------------------------------+
     *  |SecClic|       |       |          Primary Click          |       |       |       |       |
     *  \-----------------------------------------------------------------------------------------/
     */
    [_MOUSE] = KEYMAP(                                                                                                                  /* Mouse Layer */
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   //
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   //
        _______,     _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,      _______,   //
        _______,           _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,         _______,   //
        KC_BTN2,     _______,     _______,                  KC_BTN1,                  _______,     _______,     _______,     _______    //
        ),                                                                                                                              /* Mouse Layer */
};
// clang-format on

const uint16_t keymaps_size = sizeof(keymaps);

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

layer_state_t layer_state_set_user(layer_state_t layer) { return layer; }

void annepro2LedPrevAnimationSpeed(void) {
    for (int i = 0; i < NUM_SPEEDS - 1; i++) {
        annepro2LedNextAnimationSpeed();
    }
}
void annepro2LedPrevIntensity(void) {
    for (int i = 0; i < NUM_INTENSITIES - 1; i++) {
        annepro2LedNextIntensity();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }
    switch (keycode) {
        case KC_AP_LED_TOGGLE:
            (ledEnabled = !ledEnabled) ? annepro2LedEnable() : annepro2LedDisable();
            return false;
        case KC_AP_LED_BIDIR_PROFILE:
            (IS_SHIFT_MODIFIED) ? annepro2LedPrevProfile() : annepro2LedNextProfile();
            return false;
        case KC_AP_LED_BIDIR_SPEED:
            (IS_SHIFT_MODIFIED) ? annepro2LedPrevAnimationSpeed() : annepro2LedNextAnimationSpeed();
            return false;
        case KC_AP_LED_BIDIR_INTENSITY:
            (IS_SHIFT_MODIFIED) ? annepro2LedPrevIntensity() : annepro2LedNextIntensity();
            return false;
        default:
            return true;  // Process normally
    }
}

void keyboard_post_init_user(void) {
    annepro2LedEnable();
    // annepro2LedSetProfile(0);
}

bool led_update_user(led_t leds) {
    if (leds.caps_lock) {
        annepro2LedSetMask(CAPS_LOCATION);
    } else {
        annepro2LedClearMask(CAPS_LOCATION);
    }
    return true;
}
