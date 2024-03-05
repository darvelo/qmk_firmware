// vim: foldmethod=marker:foldlevel=0

#include QMK_KEYBOARD_H
#include "version.h"
#include "darvelo.h"


#define KC_MAC_TABBCK LGUI(LSFT(KC_LBRC))
#define KC_MAC_TABFWD LGUI(LSFT(KC_RBRC))
#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define KC_CAM LCTL(LALT(KC_KP_0))
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)
#define MOON_LED_LEVEL LED_LEVEL


/* Config Vars */

// The order of the layers matters! Read https://docs.qmk.fm/#/keymap?id=layer-precedence-and-transparency
//
// When a layer is activated its keymap DOES NOT get laid on top of the current keymap.
// An item defined later in this enum will take precedence in the keymap over one defined before it when both are activated,
// and so will layer its keys on top even if it was activated before a layer defined earlier in this enum was activated.
//
// In other words, given these layer definitions:
//
// enum layers { A, B, C }
//
// When B and C define a keycode on the same key, and B is activated _after_ C during usage (A -> C -> B), the key from _C_ will take the key because it was defined later in the enum.
//
// In the keymaps I must remember never to allow activating earlier-defined layers after later-defined layers.
// Because of this I've split the layer definitions below into categories visually. Each category's items should be mutually exclusive on the active layer stack, and items in later categories shouldn't have keymaps to earlier categories.
enum layers {
    // Base layers.
    MAC,   // default layer
    LINUX, // Linux keys

    // Workflow layers.
    BLNDR, // Blender
    BLDR2, // Blender 2nd layer
    CODE,  // Used for programming. Slight variation on the MAC layer.

    // Utility layers.
    SYMB,  // symbols
    NUMS,  // Turns num keys into numbers
    MDIA,  // media keys
    MVMT,  // Cursor movement and selection.
    KYBD,  // Keyboard-specific config keys
};

enum custom_keycodes {
    VRSN = ML_SAFE_RANGE,
    RGB_SLD,
    APP_SWCH,
    UC_SHRG,                                  // ¯\_(ツ)_/¯
    ARROW,
    P_ARROW,
    P_BLOCK,
};

// Configurable layer colors and per-key colors. {{{
#define RED {RGB_RED}
#define GOLD {RGB_GOLD}
#define YELLOW {RGB_YELLOW}
#define GREEN {RGB_GREEN}
#define SPRINGGREEN {RGB_SPRINGGREEN}
#define PINK {RGB_PINK}
#define TURQUOISE {RGB_TURQUOISE}
#define PURPLE {RGB_PURPLE}
#define EGGSHELL {36,228,255}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [BLNDR] = {
        // LEFT-HAND SPLIT
        // TOP LEFT CORNER ................. BOTTOM LEFT CORNER
        GOLD, GOLD, GOLD, GOLD, GOLD,
        GOLD, GOLD, GOLD, GOLD, GOLD,
        GOLD, GOLD, GOLD, GOLD, GOLD,
        GOLD, GOLD, GOLD, GOLD, GOLD,
        GOLD, GOLD, GOLD, GOLD, GOLD,
        GOLD, GOLD, GOLD, GOLD,
        // TOP RIGHT CORNER ................ BOTTOM RIGHT CORNER
        GOLD, GOLD, GOLD,
        // THUMB CLUSTER: FARTHEST-FROM-ME, MIDDLE, CLOSEST-TO-ME, LAUNCH KEY
        GOLD, GOLD, GOLD, GOLD,

        // RIGHT-HAND SPLIT
        // TOP RIGHT CORNER ................ BOTTOM RIGHT CORNER
        GOLD, GOLD, GOLD, GOLD, GOLD,
        GOLD, GOLD, GOLD, GOLD, GOLD,
        GOLD, GOLD, GOLD, GOLD, GOLD,
        GOLD, GOLD, GOLD, GOLD, GOLD,
        GOLD, GOLD, GOLD, GOLD, GOLD,
        GOLD, GOLD, GOLD, GOLD,
        // TOP LEFT CORNER ................ BOTTOM LEFT CORNER
        GOLD, GOLD, GOLD,
        // THUMB CLUSTER: FARTHEST-FROM-ME, MIDDLE, CLOSEST-TO-ME, LAUNCH KEY
        GOLD, GOLD, GOLD, GOLD
    },
    [BLDR2] = {
        // LEFT-HAND SPLIT
        // TOP LEFT CORNER ................. BOTTOM LEFT CORNER
        YELLOW, YELLOW, YELLOW, YELLOW, YELLOW,
        YELLOW, YELLOW, YELLOW, YELLOW, YELLOW,
        YELLOW, YELLOW, YELLOW, YELLOW, YELLOW,
        YELLOW, YELLOW, YELLOW, YELLOW, YELLOW,
        YELLOW, YELLOW, YELLOW, YELLOW, YELLOW,
        YELLOW, YELLOW, YELLOW, YELLOW,
        // TOP RIGHT CORNER ................ BOTTOM RIGHT CORNER
        YELLOW, YELLOW, YELLOW,
        // THUMB CLUSTER: FARTHEST-FROM-ME, MIDDLE, CLOSEST-TO-ME, LAUNCH KEY
        YELLOW, YELLOW, YELLOW, YELLOW,

        // RIGHT-HAND SPLIT
        // TOP RIGHT CORNER ................ BOTTOM RIGHT CORNER
        YELLOW, YELLOW, YELLOW, YELLOW, YELLOW,
        YELLOW, YELLOW, YELLOW, YELLOW, YELLOW,
        YELLOW, YELLOW, YELLOW, YELLOW, YELLOW,
        YELLOW, YELLOW, YELLOW, YELLOW, YELLOW,
        YELLOW, YELLOW, YELLOW, YELLOW, YELLOW,
        YELLOW, YELLOW, YELLOW, YELLOW,
        // TOP LEFT CORNER ................ BOTTOM LEFT CORNER
        YELLOW, YELLOW, YELLOW,
        // THUMB CLUSTER: FARTHEST-FROM-ME, MIDDLE, CLOSEST-TO-ME, LAUNCH KEY
        YELLOW, YELLOW, YELLOW, YELLOW
    },

    [CODE] = {
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
        PURPLE, PURPLE, PURPLE, PURPLE, PURPLE,
        PURPLE, PURPLE, PURPLE, PURPLE, PURPLE,
        PURPLE, PURPLE, PURPLE, PURPLE, PURPLE,
        PURPLE, PURPLE, PURPLE, PURPLE, PURPLE,
        PURPLE, PURPLE, PURPLE, PURPLE, PURPLE,
        PURPLE, PURPLE, PURPLE, PURPLE,
        // TOP RIGHT CORNER ................ BOTTOM RIGHT CORNER
        PURPLE, PURPLE, PURPLE,
        // THUMB CLUSTER: FARTHEST-FROM-ME, MIDDLE, CLOSEST-TO-ME, LAUNCH KEY
        PURPLE, PURPLE, PURPLE, PURPLE,

        // RIGHT-HAND SPLIT
        // TOP RIGHT CORNER ................ BOTTOM RIGHT CORNER
        PURPLE, PURPLE, PURPLE, PURPLE, PURPLE,
        PURPLE, PURPLE, PURPLE, PURPLE, PURPLE,
        PURPLE, PURPLE, PURPLE, PURPLE, PURPLE,
        PURPLE, PURPLE, PURPLE, PURPLE, PURPLE,
        PURPLE, PURPLE, PURPLE, PURPLE, PURPLE,
        PURPLE, PURPLE, PURPLE, PURPLE,
        // TOP LEFT CORNER ................ BOTTOM LEFT CORNER
        PURPLE, PURPLE, PURPLE,
        // THUMB CLUSTER: FARTHEST-FROM-ME, MIDDLE, CLOSEST-TO-ME, LAUNCH KEY
        PURPLE, PURPLE, PURPLE, PURPLE
    },

    [MDIA] = {
        // LEFT-HAND SPLIT
        // TOP LEFT CORNER ................. BOTTOM LEFT CORNER
        SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN,
        SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN,
        SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN,
        SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN,
        SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN,
        SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN,
        // TOP RIGHT CORNER ................ BOTTOM RIGHT CORNER
        SPRINGGREEN, SPRINGGREEN, SPRINGGREEN,
        // THUMB CLUSTER: FARTHEST-FROM-ME, MIDDLE, CLOSEST-TO-ME, LAUNCH KEY
        SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN,

        // RIGHT-HAND SPLIT
        // TOP RIGHT CORNER ................ BOTTOM RIGHT CORNER
        SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN,
        SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN,
        SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN,
        SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN,
        SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN,
        SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN,
        // TOP LEFT CORNER ................ BOTTOM LEFT CORNER
        SPRINGGREEN, SPRINGGREEN, SPRINGGREEN,
        // THUMB CLUSTER: FARTHEST-FROM-ME, MIDDLE, CLOSEST-TO-ME, LAUNCH KEY
        SPRINGGREEN, SPRINGGREEN, SPRINGGREEN, SPRINGGREEN
    },

    [NUMS] = {
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
    [MVMT] = {
        // LEFT-HAND SPLIT
        // TOP LEFT CORNER ................. BOTTOM LEFT CORNER
        TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE,
        TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE,
        TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE,
        TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE,
        TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE,
        TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE,
        // TOP RIGHT CORNER ................ BOTTOM RIGHT CORNER
        TURQUOISE, TURQUOISE, TURQUOISE,
        // THUMB CLUSTER: FARTHEST-FROM-ME, MIDDLE, CLOSEST-TO-ME, LAUNCH KEY
        TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE,

        // RIGHT-HAND SPLIT
        // TOP RIGHT CORNER ................ BOTTOM RIGHT CORNER
        TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE,
        TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE,
        TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE,
        TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE,
        TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE,
        TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE,
        // TOP LEFT CORNER ................ BOTTOM LEFT CORNER
        TURQUOISE, TURQUOISE, TURQUOISE,
        // THUMB CLUSTER: FARTHEST-FROM-ME, MIDDLE, CLOSEST-TO-ME, LAUNCH KEY
        TURQUOISE, TURQUOISE, TURQUOISE, TURQUOISE
    },
    [KYBD] = {
        // LEFT-HAND SPLIT
        // TOP LEFT CORNER ................. BOTTOM LEFT CORNER
        RED, RED, RED, RED, RED,
        RED, RED, RED, RED, RED,
        RED, RED, RED, RED, RED,
        RED, RED, RED, RED, RED,
        RED, RED, RED, RED, RED,
        RED, RED, RED, RED,
        // TOP RIGHT CORNER ................ BOTTOM RIGHT CORNER
        RED, RED, RED,
        // THUMB CLUSTER: FARTHEST-FROM-ME, MIDDLE, CLOSEST-TO-ME, LAUNCH KEY
        RED, RED, RED, RED,

        // RIGHT-HAND SPLIT
        // TOP RIGHT CORNER ................ BOTTOM RIGHT CORNER
        RED, RED, RED, RED, RED,
        RED, RED, RED, RED, RED,
        RED, RED, RED, RED, RED,
        RED, RED, RED, RED, RED,
        RED, RED, RED, RED, RED,
        RED, RED, RED, RED,
        // TOP LEFT CORNER ................ BOTTOM LEFT CORNER
        RED, RED, RED,
        // THUMB CLUSTER: FARTHEST-FROM-ME, MIDDLE, CLOSEST-TO-ME, LAUNCH KEY
        RED, RED, RED, RED
    },
};
// }}}

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

bool isCodeLayer = false;
const bool use_rgb_matrix_animation_from_eeprom = true;

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case CODE:
        if (!isCodeLayer) {
            isCodeLayer = true;
            // RGB_MATRIX_DIGITAL_RAIN is the keyboard animation from the Matrix movie.
            rgb_matrix_mode_noeeprom(RGB_MATRIX_DIGITAL_RAIN);
        }
        break;
    default: // for any other layers, or the default layer
        if (isCodeLayer) {
            if (use_rgb_matrix_animation_from_eeprom) {
                rgb_matrix_reload_from_eeprom();
            } else {
                // I can replace RGB_MATRIX_TYPING_HEATMAP below with the definition of my favorite named animation.
                rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
            }
            isCodeLayer = false;
        }
        break;
    }
    return state;
}

void rgb_matrix_indicators_user(void) {
    // Remove `g_suspend_state` which stopped being a visible symbol after a rebase.
    // if (g_suspend_state || keyboard_config.disable_layer_led) { return; }
    if (keyboard_config.disable_layer_led) { return; }
    switch (biton32(layer_state)) {
        case BLNDR:
            set_layer_color_rgb(BLNDR);
            break;
        case BLDR2:
            set_layer_color_rgb(BLDR2);
            break;
        case CODE:
            // Put nothing here because we're setting a
            // custom RGB animation in the `layer_state_set_user()` function definition above.
            break;
        case SYMB:
            set_layer_color_rgb(SYMB);
            break;
        case MDIA:
            set_layer_color_rgb(MDIA);
            break;
        case NUMS:
            set_layer_color_rgb(NUMS);
            break;
        case MVMT:
            set_layer_color_rgb(MVMT);
            break;
        case KYBD:
            set_layer_color_rgb(KYBD);
            break;
        default:
            if (rgb_matrix_get_flags() == LED_FLAG_NONE)
                rgb_matrix_set_color_all(0, 0, 0);
            break;
    }
}

/* Configurable TAPPING_TERM_PER_KEY */

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        /* case LT(SYMB, KC_SPC): */
        /* case LT(NUMS, KC_BSPC): */
        /*     return 10000; */
//        case SFT_T(KC_SPC):
//            return TAPPING_TERM + 1250;
//        case LT(1, KC_GRV):
//            return 130;
        /* case TD(CT_LSND): */
        /*     return 100; */
        default:
            return TAPPING_TERM;
    }
}
#endif

/* Configurable TAPPING_FORCE_HOLD_PER_KEY */
#ifdef TAPPING_FORCE_HOLD_PER_KEY
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Allow me to:
        //    * press shift after pressing esc so I can get into normal mode and use Shift+a right away
        //    * press space right after pressing space to start entering symbol characters
        case LSFT_T(KC_ESC):
        case LT(SYMB, KC_SPC):
        /* case LT(NUMS, KC_BSPC): */
            return true;
        default:
            return false;
    }
}
#endif

#ifdef PERMISSIVE_HOLD_PER_KEY
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(SYMB, KC_SPC):
        case LT(NUMS, KC_BSPC):
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}
#endif

#ifdef HOLD_ON_OTHER_KEY_PRESS_PER_KEY
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        /* case LT(SYMB, KC_SPC): */
        /* case LT(NUMS, KC_BSPC): */
            // Immediately select the hold action when another key is pressed.
            /* return true; */
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}
#endif

/* Keyboard layers. */

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    [TEMPLATE] = LAYOUT_moonlander(
//        _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
//        _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
//        _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
//        _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
//        _______, _______, _______, _______, _______,          _______,          _______,          _______, _______, _______, _______, _______,
//                                            _______, _______, _______,          _______, _______, _______
//    ),
//    [TEMPLATE] = LAYOUT_moonlander(
//        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//                                            XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX
//    ),
    // MEH  = ctrl + shift + alt
    // HYPR = ctrl + shift + alt + gui
    [MAC] = LAYOUT_moonlander(
        _______,        KC_1,     KC_2,      KC_3,      KC_4,              KC_5,              KC_MAC_TABBCK,           KC_MAC_TABFWD, KC_6,             KC_7,          KC_8,    KC_9,    KC_0,    KC_MINS,
        _______,        KC_Q,     KC_W,      KC_E,      KC_R,              KC_T,              _______,                 _______,       KC_Y,             KC_U,          KC_I,    KC_O,    KC_P,    KC_EQL,
        LCTL_T(KC_TAB), KC_A,     KC_S,      KC_D,      KC_F,              KC_G,              _______,                 _______,       KC_H,             KC_J,          KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        _______,        KC_Z,     KC_X,      KC_C,      KC_V,              KC_B,                                                      KC_N,             KC_M,          KC_COMM, KC_DOT,  KC_SLSH, KC_DQT,
        _______,        TT(MDIA), TO(BLNDR), KC_LALT,   KC_LGUI,                              _______,                 TO(CODE),                        _______,       _______, _______, RGB_MOD, KC_APP,
                                                        LT(SYMB, KC_SPC),  LT(NUMS, KC_BSPC), LALT_T(KC_DEL),          KC_LEAD,       LT(MVMT, KC_ENT), LSFT_T(KC_ESC)
    ),
    // I don't explicitly switch to this layer. I use the UC_MOD to programmatically swap the base layer between the MAC and LINUX layers.
    [LINUX] = LAYOUT_moonlander(
        _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______,          _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,          _______, _______, _______
    ),
    // needed: period/dot (median/origin point), p for parenting, n key to open/close tool menu, i for insert keyframe, m to add marker in timeline and join vertices (alt+m), h for hide, j to join
    [BLNDR] = LAYOUT_moonlander(
        TG(BLNDR),         _______, _______, _______,  _______, _______,        KC_I,                     _______, _______, _______, _______, _______, _______, _______,
        KC_M,              _______, _______, _______,  _______, _______,        KC_L,                     _______, _______, _______, _______, _______, _______, _______,
        LT(BLDR2, KC_TAB), _______, _______, _______,  _______, _______,        KC_N,                     _______, _______, _______, _______, _______, _______, _______,
        KC_Y,              _______, _______, _______,  _______, _______,                                           _______, _______, _______, _______, _______, _______,
        KC_P,              KC_DOT,  KC_H,    TT(SYMB), _______,                 _______,                  _______,          _______, _______, _______, _______, _______,
                                                       KC_LSFT, LCTL_T(KC_SPC), LALT_T(KC_ENT),           _______, _______, _______
    ),
    [BLDR2] = LAYOUT_moonlander(
        TG(BLDR2), _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
        _______,   KC_CAM,  KC_KP_5, KC_KP_7, KC_KP_0, KC_PSLS, _______,          _______, _______, _______, _______, _______, _______, _______,
        _______,   KC_O,    KC_KP_1, KC_KP_9, KC_KP_3, KC_PDOT, _______,          _______, _______, _______, _______, _______, _______, _______,
        _______,   _______, _______, _______, KC_J,    _______,                            _______, _______, _______, _______, _______, _______,
        _______,   _______, _______, _______, _______,          _______,          _______,          _______, _______, _______, _______, _______,
                                              _______, _______, _______,          _______, _______, _______
    ),
    [CODE] = LAYOUT_moonlander(
        TG(CODE), _______, _______, _______, _______, _______, _______,          _______, _______, _______,      _______, _______, _______, _______,
        KC_QUES,  _______, _______, _______, _______, _______, _______,          _______, _______, _______,      _______, _______, _______, KC_QUOT,
        _______,  _______, _______, _______, _______, _______, KC_PIPE,          KC_AMPR, _______, _______,      _______, _______, KC_COLN, KC_EQL,
        KC_EXLM,  _______, _______, _______, _______, _______,                            _______, _______,      _______, _______, _______, KC_DQT,
        _______,  _______, _______, _______, _______,          _______,          LSFT(KC_ESC),     LALT(KC_ENT), _______, _______, _______, _______,
                                             _______, _______, _______,          _______, _______, _______
    ),
    [SYMB] = LAYOUT_moonlander(
        TG(SYMB),   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_GRV,     XXXXXXX, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, XXXXXXX,          XXXXXXX, KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS, KC_BSLS, XXXXXXX,
        LGUI(KC_S), KC_LT,   KC_LCBR, KC_LBRC, KC_LPRN, P_ARROW, KC_PIPE,          XXXXXXX, ARROW,   KC_RPRN, KC_RBRC, KC_RCBR, KC_GT,   KC_COLN,
        KC_TILD,    XXXXXXX, XXXXXXX, XXXXXXX, P_BLOCK, KC_EXLM,                            KC_SCLN, KC_QUES, KC_COMM, KC_DQT,  KC_QUOT, XXXXXXX,
        XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                               _______, _______, _______,          XXXXXXX, _______, XXXXXXX
    ),
    [NUMS] = LAYOUT_moonlander(
        TG(NUMS), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX,          XXXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        XXXXXXX,  XXXXXXX, KC_UNDS, KC_LPRN, KC_RPRN, KC_PERC, XXXXXXX,          XXXXXXX, XXXXXXX, KC_KP_7, KC_KP_8, KC_KP_9, XXXXXXX, KC_F12,
        XXXXXXX,  KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS, KC_PEQL, KC_PENT,          XXXXXXX, XXXXXXX, KC_KP_4, KC_KP_5, KC_KP_6, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, KC_DLR,  KC_CIRC, XXXXXXX,                            XXXXXXX, KC_KP_1, KC_KP_2, KC_KP_3, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______,          XXXXXXX,          XXXXXXX, KC_KP_0, KC_PDOT, XXXXXXX, XXXXXXX,
                                             _______, _______, _______,          XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [MVMT] = LAYOUT_moonlander(
        TG(MVMT), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, KC_LALT, KC_LGUI, XXXXXXX, XXXXXXX,          XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                             KC_LSFT, XXXXXXX, XXXXXXX,          _______, XXXXXXX, XXXXXXX
    ),
    [MDIA] = LAYOUT_moonlander(
        TG(MDIA), HYPR(KC_1), HYPR(KC_2), HYPR(KC_3),  HYPR(KC_4), HYPR(KC_5), XXXXXXX,         XXXXXXX, HYPR(KC_6), HYPR(KC_7), HYPR(KC_8), HYPR(KC_9), HYPR(KC_0), TO(KYBD),
        XXXXXXX,  XXXXXXX,    KC_LEFT,    KC_MPLY,     KC_RIGHT,   XXXXXXX,    XXXXXXX,         KC_BTN2, KC_MS_L,    KC_MS_D,    KC_MS_U,    KC_MS_R,    KC_VOLU,    KC_BRIU,
        XXXXXXX,  KC_MPRV,    HYPR(KC_W), HYPR(KC_UP), HYPR(KC_E), KC_MNXT,    XXXXXXX,         KC_BTN1, KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    KC_VOLD,    KC_BRID,
        XXXXXXX,  XXXXXXX,    KC_MUTE,    KC_VOLD,     KC_VOLU,    XXXXXXX,                              XXXXXXX,    KC_MPLY,    KC_MPRV,    KC_MNXT,    KC_MUTE,    XXXXXXX,
        XXXXXXX,  XXXXXXX,    XXXXXXX,    KC_BRID,     KC_BRIU,                XXXXXXX,         XXXXXXX,             XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
                                                       HYPR(KC_W), KC_VOLD,    KC_BRID,         KC_BRIU, KC_VOLU,    HYPR(KC_E)
    ),
    // TOGGLE_LAYER_COLOR means the preset solid RGB color for all layers can be disabled, showing only the base layer color/animation.
    // RGB_SLD resets the animation to the first one. You can then tap RGB_MOD repeatedly to cycle through animations again.
    // RGB_HUI/RGB_HUD cycles the RGB hue. RGB_VAI/RGB_VAD changes RGB brightness.
    // LED_LEVEL enables/disables the 3 bright LEDs on both sides of the keyboard that indicate which layer you're on.
    [KYBD] = LAYOUT_moonlander(
        TG(KYBD),  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD,         RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, UC_MOD,
        LED_LEVEL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_HUI,         RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        VRSN,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_HUD,         RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, AU_TOG,
        XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TOGGLE_LAYER_COLOR,                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MU_TOG,
        XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          RESET,           RGB_SLD,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MU_MOD,
                                              XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX
    ),
};


/* Configurable responses to keypresses by keycode (including custom keycodes defined above). */

uint16_t key_timer_app_switch = 0;

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
        case APP_SWCH: {
                if (record->event.pressed) {
                    uint8_t unicode_input_mode = get_unicode_input_mode();
                    uint16_t keycode_super;
                    if (unicode_input_mode == UC_MAC) {
                        keycode_super = KC_LGUI;
                    } else {
                        keycode_super = KC_LALT;
                    }
                    if (timer_elapsed(key_timer_app_switch) > 3000) {
                        register_code16(keycode_super);
                        tap_code16(KC_TAB);
                    } else if (timer_elapsed(key_timer_app_switch) > 500) {
                        unregister_code16(keycode_super);
                    } else {
                        tap_code16(KC_TAB);
                    }
                    key_timer_app_switch = timer_read();
                }
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
        case ARROW:
            if (record->event.pressed) {
                send_string("-> ");
            }
            break;
        case P_ARROW:
            if (record->event.pressed) {
                send_string(") -> ");
            }
            break;
        case P_BLOCK:
            if (record->event.pressed) {
                send_string(") {\n");
            }
            break;
#endif
    }
    return true;
}

/* Tap Dance Configuration */

#ifdef TAP_DANCE_ENABLE
qk_tap_dance_action_t tap_dance_actions[] = {
    [CT_CPNC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, semicolon_code_punctuation_finished, semicolon_code_punctuation_reset),
    [CT_EPNC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quote_extra_code_punctuation_finished, quote_extra_code_punctuation_reset),
    [CT_SRND] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, surround_punctuation_finished, NULL), //surround_punctuation_reset),
};
#endif


/* Leader Key Configuration */

bool did_leader_succeed;
#ifdef AUDIO_ENABLE
float leader_start_sound[][2] = SONG(ZELDA_TREASURE);
float leader_succeed[][2] = SONG(COIN_SOUND);
float leader_fail[][2] = SONG(MARIO_GAMEOVER);
#endif

void leader_start(void) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_start_sound);
#endif
}

void leader_end(void) {
  if (did_leader_succeed) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_succeed);
#endif
  } else {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_fail);
#endif
  }
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    did_leader_succeed = leading = false;

    // SEQ_ONE_KEY(KC_E) {
    //   // Anything you can do in a macro.
    //   SEND_STRING(SS_LSFT("t"));
    //   did_leader_succeed = true;
    // } else

    // SEQ_TWO_KEYS(KC_E, KC_D) {
    //   SEND_STRING(SS_LGUI("r") "cmd\n" SS_LCTL("c"));
    //   did_leader_succeed = true;
    // }

    // SEQ_THREE_KEYS(KC_D, KC_D, KC_S) {
    //   SEND_STRING("https://start.duckduckgo.com\n");
    //   did_leader_succeed = true;
    // }

    // SEQ_TWO_KEYS(KC_A, KC_S) {
    //   register_code(KC_LGUI);
    //   register_code(KC_S);
    //   unregister_code(KC_S);
    //   unregister_code(KC_LGUI);
    //   did_leader_succeed = true;
    // }

    // Mission Control.
    SEQ_ONE_KEY(KC_A) {
      register_code(KC_LGUI);
      register_code(KC_SPC);
      unregister_code(KC_SPC);
      unregister_code(KC_LGUI);
      did_leader_succeed = true;
    }

    // Emoji panel.
    SEQ_ONE_KEY(KC_E) {
      register_code(KC_LCTL);
      register_code(KC_LGUI);
      register_code(KC_SPC);
      unregister_code(KC_SPC);
      unregister_code(KC_LGUI);
      unregister_code(KC_LCTL);
      did_leader_succeed = true;
    }

    // Change input source language.
    SEQ_ONE_KEY(KC_T) {
      register_code(KC_LCTL);
      register_code(KC_LALT);
      register_code(KC_SPC);
      unregister_code(KC_SPC);
      unregister_code(KC_LALT);
      unregister_code(KC_LCTL);
      did_leader_succeed = true;
    }

    // Open a new Finder window.
    SEQ_ONE_KEY(KC_F) {
      register_code(KC_LGUI);
      register_code(KC_LALT);
      register_code(KC_SPC);
      unregister_code(KC_SPC);
      unregister_code(KC_LALT);
      unregister_code(KC_LGUI);
      did_leader_succeed = true;
    }

    leader_end();
  }
}
