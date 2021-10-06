// vim: foldmethod=marker:foldlevel=0

#include QMK_KEYBOARD_H
#include "version.h"
#include "darvelo.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)
#define MOON_LED_LEVEL LED_LEVEL


/* Configurable TAPPING_TERM_PER_KEY */

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
//        case SFT_T(KC_SPC):
//            return TAPPING_TERM + 1250;
//        case LT(1, KC_GRV):
//            return 130;
        /* case TD(CT_LSND): */
        /*     return 100; */
        /* case TD(CT_RSND): */
        /*     return 100; */
        default:
            return TAPPING_TERM;
    }
}
#endif

/* Config Vars */

enum layers {
    MAC,   // default layer
    LINUX, // Linux keys
    NUMS,  // Turns num keys into numbers
    VIM,
    SYMB,  // symbols
    MDIA,  // media keys
    GAME,  // gaming
};

enum custom_keycodes {
    VRSN = ML_SAFE_RANGE,
    RGB_SLD,
    UC_SHRG,                                  // ¯\_(ツ)_/¯
};

/* Configurable layer colors and per-key colors. */

#define BLUE {159,228,255}
#define EGGSHELL {36,228,255}
#define PINK {0,183,238}
#define YELLOW {31,255,255}
#define GREEN {RGB_GREEN}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [VIM] = {
        // LEFT-HAND SPLIT
        // TOP LEFT CORNER ................. BOTTOM LEFT CORNER
        GREEN, GREEN, GREEN, GREEN, GREEN,
        GREEN, GREEN, GREEN, GREEN, GREEN,
        GREEN, GREEN, GREEN, GREEN, GREEN,
        GREEN, GREEN, GREEN, GREEN, GREEN,
        GREEN, GREEN, GREEN, GREEN, GREEN,
        GREEN, GREEN, GREEN, GREEN,
        // TOP RIGHT CORNER ................ BOTTOM RIGHT CORNER
        GREEN, GREEN, GREEN,
        // THUMB CLUSTER: FARTHEST-FROM-ME, MIDDLE, CLOSEST-TO-ME, LAUNCH KEY
        GREEN, GREEN, GREEN, GREEN,

        // RIGHT-HAND SPLIT
        // TOP RIGHT CORNER ................ BOTTOM RIGHT CORNER
        GREEN, GREEN, GREEN, GREEN, GREEN,
        GREEN, GREEN, GREEN, GREEN, GREEN,
        GREEN, GREEN, GREEN, GREEN, GREEN,
        GREEN, GREEN, GREEN, GREEN, GREEN,
        GREEN, GREEN, GREEN, GREEN, GREEN,
        GREEN, GREEN, GREEN, GREEN,
        // TOP LEFT CORNER ................ BOTTOM LEFT CORNER
        GREEN, GREEN, GREEN,
        // THUMB CLUSTER: FARTHEST-FROM-ME, MIDDLE, CLOSEST-TO-ME, LAUNCH KEY
        GREEN, GREEN, GREEN, GREEN
    },

    [SYMB] = {
        // LEFT-HAND SPLIT
        // TOP LEFT CORNER ................. BOTTOM LEFT CORNER
        EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL,
        EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL,
        EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL,
        EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL,
        EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL,
        EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL,
        // TOP RIGHT CORNER ................ BOTTOM RIGHT CORNER
        EGGSHELL, EGGSHELL, EGGSHELL,
        // THUMB CLUSTER: FARTHEST-FROM-ME, MIDDLE, CLOSEST-TO-ME, LAUNCH KEY
        EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL,

        // RIGHT-HAND SPLIT
        // TOP RIGHT CORNER ................ BOTTOM RIGHT CORNER
        EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL,
        EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL,
        EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL,
        EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL,
        EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL,
        EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL,
        // TOP LEFT CORNER ................ BOTTOM LEFT CORNER
        EGGSHELL, EGGSHELL, EGGSHELL,
        // THUMB CLUSTER: FARTHEST-FROM-ME, MIDDLE, CLOSEST-TO-ME, LAUNCH KEY
        EGGSHELL, EGGSHELL, EGGSHELL, EGGSHELL
    },

    [MDIA] = {
        // LEFT-HAND SPLIT
        // TOP LEFT CORNER ................. BOTTOM LEFT CORNER
        BLUE, BLUE, BLUE, BLUE, BLUE,
        BLUE, BLUE, BLUE, BLUE, BLUE,
        BLUE, BLUE, BLUE, BLUE, BLUE,
        BLUE, BLUE, BLUE, BLUE, BLUE,
        BLUE, BLUE, BLUE, BLUE, BLUE,
        BLUE, BLUE, BLUE, BLUE,
        // TOP RIGHT CORNER ................ BOTTOM RIGHT CORNER
        BLUE, BLUE, BLUE,
        // THUMB CLUSTER: FARTHEST-FROM-ME, MIDDLE, CLOSEST-TO-ME, LAUNCH KEY
        BLUE, BLUE, BLUE, BLUE,

        // RIGHT-HAND SPLIT
        // TOP RIGHT CORNER ................ BOTTOM RIGHT CORNER
        BLUE, BLUE, BLUE, BLUE, BLUE,
        BLUE, BLUE, BLUE, BLUE, BLUE,
        BLUE, BLUE, BLUE, BLUE, BLUE,
        BLUE, BLUE, BLUE, BLUE, BLUE,
        BLUE, BLUE, BLUE, BLUE, BLUE,
        BLUE, BLUE, BLUE, BLUE,
        // TOP LEFT CORNER ................ BOTTOM LEFT CORNER
        BLUE, BLUE, BLUE,
        // THUMB CLUSTER: FARTHEST-FROM-ME, MIDDLE, CLOSEST-TO-ME, LAUNCH KEY
        BLUE, BLUE, BLUE, BLUE
    },

    [GAME] = {
        // LEFT-HAND SPLIT
        // TOP LEFT CORNER ................. BOTTOM LEFT CORNER
        PINK, PINK, PINK, PINK, PINK,
        PINK, PINK, PINK, PINK, PINK,
        PINK, PINK, PINK, PINK, PINK,
        PINK, PINK, PINK, PINK, PINK,
        PINK, PINK, PINK, PINK, PINK,
        PINK, PINK, PINK, PINK,
        // TOP RIGHT CORNER ................ BOTTOM RIGHT CORNER
        PINK, PINK, PINK,
        // THUMB CLUSTER: FARTHEST-FROM-ME, MIDDLE, CLOSEST-TO-ME, LAUNCH KEY
        PINK, PINK, PINK, PINK,

        // RIGHT-HAND SPLIT
        // TOP RIGHT CORNER ................ BOTTOM RIGHT CORNER
        PINK, PINK, PINK, PINK, PINK,
        PINK, PINK, PINK, PINK, PINK,
        PINK, PINK, PINK, PINK, PINK,
        PINK, PINK, PINK, PINK, PINK,
        PINK, PINK, PINK, PINK, PINK,
        PINK, PINK, PINK, PINK,
        // TOP LEFT CORNER ................ BOTTOM LEFT CORNER
        PINK, PINK, PINK,
        // THUMB CLUSTER: FARTHEST-FROM-ME, MIDDLE, CLOSEST-TO-ME, LAUNCH KEY
        PINK, PINK, PINK, PINK
    },
};

// Color-setting functions -- DO NOT MODIFY {{{
extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

void set_layer_color_rgb(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    RGB rgb = {
      .r = pgm_read_byte(&ledmap[layer][i][0]),
      .g = pgm_read_byte(&ledmap[layer][i][1]),
      .b = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!rgb.r && !rgb.g && !rgb.b) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
    }
  }
}

void set_layer_color_hsv(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}
// }}}


/* Songs */

float campanella[][2] = SONG(CAMPANELLA);
float nocturne[][2] = SONG(NOCTURNE_OP_9_NO_1);
float fantasie[][2] = SONG(FANTASIE_IMPROMPTU);
float zelda_treasure[][2] = SONG(ZELDA_TREASURE);
float zelda_puzzle[][2] = SONG(ZELDA_PUZZLE);
float doom[][2] = SONG(E1M1_DOOM);
float terra[][2] = SONG(TERRAS_THEME);
float disco[][2] = SONG(PLATINUM_DISCO);
float oneup[][2] = SONG(ONE_UP_SOUND);

/* Configurable Layer color settings (configure only the `case` values). */

void rgb_matrix_indicators_user(void) {
    if (g_suspend_state || keyboard_config.disable_layer_led) { return; }
    switch (biton32(layer_state)) {
        case VIM:
            set_layer_color_rgb(VIM);
            break;
        case SYMB:
            set_layer_color_hsv(SYMB);
            break;
        case MDIA:
            set_layer_color_hsv(MDIA);
            break;
        case GAME:
            set_layer_color_hsv(GAME);
            break;
        default:
            if (rgb_matrix_get_flags() == LED_FLAG_NONE)
                rgb_matrix_set_color_all(0, 0, 0);
            break;
    }
}


/* Keyboard layers. */

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC] = LAYOUT_moonlander(
        TG(VIM),          KC_EXLM,      KC_AT,            KC_HASH,            KC_DLR,             KC_PERC, UC_MOD,                  LT(MDIA, KC_SCLN), KC_CIRC, KC_AMPR,            KC_ASTR,     KC_LPRN, KC_RPRN,     _______,
        _______,          KC_Q,         KC_W,             KC_E,               KC_R,               KC_T,    _______,                 TG(GAME),          KC_Y,    TD(CT_LSND),        TD(CT_RSND), KC_O,    KC_P,        KC_BSLS,
        KC_LSFT,          KC_A,         KC_S,             KC_D,               KC_F,               KC_G,    KC_HYPR,                 KC_MEH,            KC_H,    KC_J,               KC_K,        KC_L,    TD(CT_CPNC), KC_EQL,
        LT(SYMB, KC_GRV), KC_Z,         KC_X,             KC_C,               KC_V,               KC_B,                                                KC_N,    KC_M,               KC_COMM,     KC_DOT,  KC_SLSH,     KC_MINS,
        _______,          _______,      _______,          LM(NUMS, MOD_LALT), LM(NUMS, MOD_LGUI),          KC_APP,                  KC_LCTRL,                   LM(NUMS, MOD_LGUI), _______,     KC_LBRC, KC_RBRC,     MO(SYMB),
                                                                              KC_SPC,             KC_BSPC, LCTL_T(KC_DEL),          LALT_T(KC_TAB),    KC_ESC,  KC_ENT
    ),

    [LINUX] = LAYOUT_moonlander(
        _______, _______,      _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______,      _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______,      _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, LCTL_T(KC_QUOT),
        _______, LGUI_T(KC_Z), _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______,
        _______, _______,      _______, _______, _______,          _______,           _______,          _______, _______, _______, _______, _______,
                                                 _______, _______, KC_LCTRL,          _______, _______, _______
    ),

    [NUMS] = LAYOUT_moonlander(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,           _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______,           _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),

    [VIM] = LAYOUT_moonlander(
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
        _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______,          _______,           _______,          _______, _______, _______,  _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),

    [SYMB] = LAYOUT_moonlander(
        VRSN,    KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,                     _______, KC_F6,   KC_F7,  KC_F8, KC_F9,  KC_F10,  KC_F11,
        _______, KC_EXLM,  KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, _______,                     _______, KC_UP,   KC_1,   KC_2,  KC_3,   KC_ASTR, KC_F12,
        _______, KC_HASH,  KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,  _______,                     _______, KC_DOWN, KC_4,   KC_5,  KC_6,   KC_PLUS, KC_BRIU,
        _______, KC_PERC,  KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                                       KC_AMPR, KC_7,   KC_8,  KC_9,   KC_BSLS, KC_BRID,
        _______, KC_COMMA, _______, _______, _______,          RGB_MOD,                     RGB_TOG,          KC_DOT, KC_0,  KC_EQL, _______, _______,
                                             RGB_VAD, RGB_VAI, TOGGLE_LAYER_COLOR,          RGB_SLD, RGB_HUD, RGB_HUI
    ),

    [MDIA] = LAYOUT_moonlander(
        LED_LEVEL,_______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, RESET,
        AU_TOG,  _______,  _______, KC_MS_U, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
        MU_TOG,  _______,  KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,          _______, _______, _______, _______, _______, _______, KC_MPLY,
        MU_MOD,  _______,  _______, _______, _______, _______,                            _______, _______, KC_MPRV, KC_MNXT, _______, _______,
        _______, _______,  _______, KC_BTN1, KC_BTN2,          _______,          _______,          KC_VOLU, KC_VOLD, KC_MUTE, _______, _______,
                                             _______, _______, _______,          _______, _______, _______
    ),

    [GAME] = LAYOUT_moonlander(
        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LEFT,           KC_RGHT, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_DEL,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    TG(SYMB),          TG(GAME), KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HYPR,           KC_MEH,  KC_H,    KC_J,    KC_K,    KC_L,    LT(MDIA, KC_SCLN), LGUI_T(KC_QUOT),
        KC_LSFT, LCTL_T(KC_Z),KC_X,KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,    KC_COMM, KC_DOT,  RCTL_T(KC_SLSH), KC_RSFT,
    LT(SYMB,KC_GRV),WEBUSB_PAIR,A(KC_LSFT),KC_LEFT, KC_RGHT,  LALT_T(KC_APP),    RCTL_T(KC_ESC),   KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, MO(SYMB),
                                            KC_SPC,  KC_BSPC, KC_LGUI,           KC_LALT,  KC_TAB,  KC_ENT
    ),

};


/* Configurable responses to keypresses by keycode (including custom keycodes defined above). */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VRSN:
            if (record->event.pressed) {
                SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            }
            return false;
        case RGB_SLD:
            if (record->event.pressed) {
                rgblight_mode(1);
            }
            return false;
#ifdef UNICODE_ENABLE
        case UC_MOD: {
                if (record->event.pressed) {
                    uint8_t unicode_input_mode = get_unicode_input_mode();
                    if (unicode_input_mode == UC_MAC) {
                        // These layers are reversed since the key takes effect after this function returns.
                        set_single_persistent_default_layer(LINUX);
                    } else if (unicode_input_mode == UC_LNX) {
                        // These layers are reversed since the key takes effect after this function returns.
                        set_single_persistent_default_layer(MAC);
                    }
                }
            }
            break;
        case UC_SHRG:  // ¯\_(ツ)_/¯
            if (record->event.pressed) {
                send_unicode_string("¯\\_(ツ)_/¯");
            }
            break;
#endif
    }
    return true;
}

/* Tap Dance Configuration */

qk_tap_dance_action_t tap_dance_actions[] = {
    [CT_CPNC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, code_punctuation_finished, code_punctuation_reset),
    [CT_LSND] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, left_surround_punctuation_finished, left_surround_punctuation_reset),
    [CT_RSND] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, right_surround_punctuation_finished, right_surround_punctuation_reset)
};
