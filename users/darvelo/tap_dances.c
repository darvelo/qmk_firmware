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

// Create an instance of 'td_tap_t' for the 'code_punctuation' tap dance.
static td_tap_t code_punctuation_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void code_punctuation_finished(qk_tap_dance_state_t *state, void *user_data) {
    code_punctuation_tap_state.state = cur_dance(state);
    switch (code_punctuation_tap_state.state) {
        case TD_SINGLE_TAP:
            // Need to expand both keys for this to work.
            // https://www.reddit.com/r/olkb/comments/73ue11/qmk_need_help_with_compiling_the_hex/dnt9elq/
            register_code16(KC_LSFT);
            register_code16(KC_SCOLON);
            break;
        case TD_SINGLE_HOLD:
            register_code16(KC_LSFT);
            register_code16(KC_QUOTE);
            break;
        case TD_DOUBLE_TAP:
            register_code16(KC_LSFT);
            register_code16(KC_SLASH);
            break;
        case TD_DOUBLE_HOLD:
            register_code16(KC_QUOTE);
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

void code_punctuation_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (code_punctuation_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_LSFT);
            unregister_code16(KC_SCOLON);
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(KC_LSFT);
            unregister_code16(KC_QUOTE);
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(KC_LSFT);
            unregister_code16(KC_SLASH);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code16(KC_QUOTE);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            break;
        default:
            break;
    }
    code_punctuation_tap_state.state = TD_NONE;
}




// Create an instance of 'td_tap_t' for the 'left_surround_punctuation' tap dance.
static td_tap_t left_surround_punctuation_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void left_surround_punctuation_finished(qk_tap_dance_state_t *state, void *user_data) {
    left_surround_punctuation_tap_state.state = cur_dance(state);
    switch (left_surround_punctuation_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code16(KC_U);
            break;
        case TD_SINGLE_HOLD:
            register_code16(KC_LPRN);
            break;
        case TD_DOUBLE_TAP:
            register_code16(KC_LCBR);
            break;
        case TD_DOUBLE_HOLD:
            register_code16(KC_LBRC);
            break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(KC_U);
            register_code16(KC_U);
            break;
        default:
            break;
    }
}

void left_surround_punctuation_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (left_surround_punctuation_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_U);
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(KC_LPRN);
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(KC_LCBR);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code16(KC_LBRC);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_U);
            break;
        default:
            break;
    }
    left_surround_punctuation_tap_state.state = TD_NONE;
}




// Create an instance of 'td_tap_t' for the 'right_surround_punctuation' tap dance.
static td_tap_t right_surround_punctuation_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void right_surround_punctuation_finished(qk_tap_dance_state_t *state, void *user_data) {
    right_surround_punctuation_tap_state.state = cur_dance(state);
    switch (right_surround_punctuation_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code16(KC_I);
            break;
        case TD_SINGLE_HOLD:
            register_code16(KC_RPRN);
            break;
        case TD_DOUBLE_TAP:
            register_code16(KC_RCBR);
            break;
        case TD_DOUBLE_HOLD:
            register_code16(KC_RBRC);
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

void right_surround_punctuation_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (right_surround_punctuation_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_I);
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(KC_RPRN);
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(KC_RCBR);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code16(KC_RBRC);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_I);
            break;
        default:
            break;
    }
    right_surround_punctuation_tap_state.state = TD_NONE;
}
