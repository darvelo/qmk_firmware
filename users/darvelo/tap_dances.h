#pragma once
#include "darvelo.h"

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, TD_NONE}), }

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

// Tap Dance tap-hold configuration.
typedef struct {
    uint16_t tap_keycode;
    uint16_t hold_keycode;
    td_state_t state;
} tap_dance_tap_hold_t;

// Tap dance enums.
enum tap_dance_codes {
    CT_CPNC,
    CT_EPNC,
    CT_SRND,
    TD_PSHP_ERSR, // photoshop layer eraser key with tap vs. hold
};

// We're on an older version of QMK where this macro isn't available.
// See https://github.com/qmk/qmk_firmware/blob/7620c64b99dc5bec480bfaa2708cb3fae709e2b3/quantum/quantum_keycodes.h#L195
#ifndef QK_TAP_DANCE_GET_INDEX
#define QK_TAP_DANCE_GET_INDEX(kc) ((kc)&0xFF)
#endif

td_state_t cur_dance(qk_tap_dance_state_t *state);

// For the `code_punctuation` tap dance. Put it here so it can be used in any keymap.
void semicolon_code_punctuation_finished(qk_tap_dance_state_t *state, void *user_data);
void semicolon_code_punctuation_reset(qk_tap_dance_state_t *state, void *user_data);
// For the `extra_code_punctuation` tap dance. Put it here so it can be used in any keymap.
void quote_extra_code_punctuation_finished(qk_tap_dance_state_t *state, void *user_data);
void quote_extra_code_punctuation_reset(qk_tap_dance_state_t *state, void *user_data);
// For the `surround_punctuation` tap dance. Put it here so it can be used in any keymap.
void surround_punctuation_finished(qk_tap_dance_state_t *state, void *user_data);
