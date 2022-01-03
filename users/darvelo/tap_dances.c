#include "tap_dances.h"

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    } else if (state->count == 3) {
        // Handles where one may type for example `www.`.
        if (state->interrupted) return TD_TRIPLE_SINGLE_TAP;
        else if (state->pressed) return TD_TRIPLE_HOLD;
        else return TD_TRIPLE_TAP;
    }

    // Assumes no one is trying to type the same letter four times (at least not quickly).
    if (state->count == 4) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    }

    return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'semicolon_code_punctuation' tap dance.
static td_tap_t semicolon_code_punctuation_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void semicolon_code_punctuation_finished(qk_tap_dance_state_t *state, void *user_data) {
    semicolon_code_punctuation_tap_state.state = cur_dance(state);
    switch (semicolon_code_punctuation_tap_state.state) {
        case TD_SINGLE_TAP:
            // Need to expand both keys for this to work.
            // https://www.reddit.com/r/olkb/comments/73ue11/qmk_need_help_with_compiling_the_hex/dnt9elq/
            register_code16(KC_LSFT);
            register_code16(KC_SCOLON);
            break;
        case TD_SINGLE_HOLD:
            register_code16(KC_LSFT);
            register_code16(KC_SLASH);
            break;
        case TD_DOUBLE_TAP:
            /* register_code16(KC_LSFT); */
            /* register_code16(KC_QUOTE); */
            break;
        case TD_DOUBLE_HOLD:
            /* register_code16(KC_QUOTE); */
            break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP:
            register_code16(KC_LSFT);
            tap_code16(KC_SCOLON);
            tap_code16(KC_SCOLON);
            unregister_code16(KC_LSFT);
            break;
        default:
            break;
    }
}

void semicolon_code_punctuation_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (semicolon_code_punctuation_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_LSFT);
            unregister_code16(KC_SCOLON);
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(KC_LSFT);
            unregister_code16(KC_SLASH);
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(KC_LSFT);
            unregister_code16(KC_QUOTE);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code16(KC_QUOTE);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            break;
        default:
            break;
    }
    semicolon_code_punctuation_tap_state.state = TD_NONE;
}




#define SURROUND_TAP KC_LPRN
#define SURROUND_HOLD KC_RPRN
#define SURROUND_DOUBLE_TAP KC_LCBR
#define SURROUND_DOUBLE_HOLD KC_RCBR
#define SURROUND_TRIPLE_TAP KC_LBRC
#define SURROUND_TRIPLE_HOLD KC_RBRC

// Create an instance of 'td_tap_t' for the 'u_left_surround_punctuation' tap dance.
static td_tap_t surround_punctuation_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void surround_punctuation_finished(qk_tap_dance_state_t *state, void *user_data) {
    surround_punctuation_tap_state.state = cur_dance(state);
    switch (surround_punctuation_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(SURROUND_TAP);
            break;
        case TD_SINGLE_HOLD:
            tap_code16(SURROUND_HOLD);
            break;
        case TD_DOUBLE_TAP:
            tap_code16(SURROUND_DOUBLE_TAP);
            break;
        case TD_DOUBLE_HOLD:
            tap_code16(SURROUND_DOUBLE_HOLD);
            break;
        case TD_TRIPLE_TAP:
            tap_code16(SURROUND_TRIPLE_TAP);
            break;
        case TD_TRIPLE_HOLD:
            tap_code16(SURROUND_TRIPLE_HOLD);
            break;
        default:
            break;
    }
}



#define CT_EPNC_TAP KC_QUOTE
#define CT_EPNC_HOLD KC_DOUBLE_QUOTE
#define CT_EPNC_DOUBLE_TAP KC_PLUS
#define CT_EPNC_DOUBLE_HOLD KC_SLASH

// Create an instance of 'td_tap_t' for the 'quote_extra_code_punctuation' tap dance.
static td_tap_t quote_extra_code_punctuation_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void quote_extra_code_punctuation_finished(qk_tap_dance_state_t *state, void *user_data) {
    quote_extra_code_punctuation_tap_state.state = cur_dance(state);
    switch (quote_extra_code_punctuation_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code16(CT_EPNC_TAP);
            break;
        case TD_SINGLE_HOLD:
            register_code16(CT_EPNC_HOLD);
            break;
        case TD_DOUBLE_TAP:
            register_code16(CT_EPNC_DOUBLE_TAP);
            break;
        case TD_DOUBLE_HOLD:
            register_code16(CT_EPNC_DOUBLE_HOLD);
            break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(KC_I);
            register_code16(KC_I);
            break;
        default:
            break;
    }
}

void quote_extra_code_punctuation_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (quote_extra_code_punctuation_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code16(CT_EPNC_TAP);
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(CT_EPNC_HOLD);
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(CT_EPNC_DOUBLE_TAP);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code16(CT_EPNC_DOUBLE_HOLD);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(CT_EPNC_TAP);
            break;
        default:
            break;
    }
    quote_extra_code_punctuation_tap_state.state = TD_NONE;
}
