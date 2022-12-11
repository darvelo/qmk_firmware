#pragma once
#include "darvelo.h"

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps.
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD,
    TD_TRIPLE_SINGLE_TAP, // Send three single taps.
    TD_QUADRUPLE_TAP,
    TD_QUADRUPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums.
enum tap_dance_codes {
    CT_CPNC,
    CT_LSND,
    CT_RSND
};


td_state_t cur_dance(qk_tap_dance_state_t *state);

// For the `code_punctuation` tap dance. Put it here so it can be used in any keymap.
void code_punctuation_finished(qk_tap_dance_state_t *state, void *user_data);
void code_punctuation_reset(qk_tap_dance_state_t *state, void *user_data);
// For the `surround_punctuation` tap dance. Put it here so it can be used in any keymap.
void add_left_surround_punctuation(qk_tap_dance_state_t *state, void *user_data);
void add_right_surround_punctuation(qk_tap_dance_state_t *state, void *user_data);
