SRC += $(USER_PATH)/darvelo.c

CUSTOM_TAP_DANCE ?= yes
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    ifeq ($(strip $(CUSTOM_TAP_DANCE)), yes)
        SRC += $(USER_PATH)/tap_dances.c
    endif
endif

