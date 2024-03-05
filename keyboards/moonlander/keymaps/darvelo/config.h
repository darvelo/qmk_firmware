/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR
#define USB_SUSPEND_WAKEUP_DELAY 0
#define FIRMWARE_VERSION u8"bn6vg/nzAq0"
#define RGB_MATRIX_STARTUP_SPD 60

#ifdef AUDIO_ENABLE
#define STARTUP_SONG SONG(FF_PRELUDE)
#define DEFAULT_LAYER_SONGS { \
        SONG(SONIC_RING),   \
        SONG(ONE_UP_SOUND),  \
        SONG(MARIO_THEME), \
        SONG(ZELDA_PUZZLE), \
        }
#endif

#define UNICODE_SELECTED_MODES UC_MAC, UC_LNX
/* #define UNICODE_SONG_MAC  SONG(SONIC_RING) */
/* #define UNICODE_SONG_LNX  SONG(ONE_UP_SOUND) */

#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 250
#define LEADER_NO_TIMEOUT

/* #ifdef TAP_DANCE_ENABLE */
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
/* #endif */

#define TAPPING_FORCE_HOLD
#define TAPPING_FORCE_HOLD_PER_KEY

#define PERMISSIVE_HOLD
#define PERMISSIVE_HOLD_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
