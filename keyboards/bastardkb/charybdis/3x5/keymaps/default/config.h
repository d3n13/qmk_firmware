// Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#ifndef __arm__
/* Disable unused features. */
#    define NO_ACTION_ONESHOT
#endif // __arm__

/*
 * Settings previously in v2/splinky_3/config.h and 3x5/config.h, which upstream
 * removed in #25488. The Splinky is now built as elitec + CONVERT_TO=rp2040_ce,
 * which already provides the SPI0/PMW3360 pins and double-tap reset.
 */

/* Handedness: the right half (trackball) is the one plugged into USB. */
#define MASTER_RIGHT

/* Reset: keep the original 1s double-tap window. */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

/* Mouse keys. */
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_TIME_TO_MAX 50
#define MOUSEKEY_DELAY 5
#define MOUSEKEY_MOVE_DELTA 4

#define MOUSEKEY_WHEEL_DELAY 100
#define MOUSEKEY_WHEEL_INTERVAL 50
#define MOUSEKEY_WHEEL_TIME_TO_MAX 100

/* Caps word. */
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_INVERT_ON_SHIFT
