// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// ------------- //
// video_htiming //
// ------------- //

#define video_htiming_wrap_target 1
#define video_htiming_wrap 5

#define video_htiming_offset_entry_point 0u

static const uint16_t video_htiming_program_instructions[] = {
    0x80a0, //  0: pull   block           side 0     
            //     .wrap_target
    0x70f0, //  1: out    exec, 16        side 1     
    0x702d, //  2: out    x, 13           side 1     
    0x6003, //  3: out    pins, 3         side 0     
    0xb042, //  4: nop                    side 1     
    0x0044, //  5: jmp    x--, 4          side 0     
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program video_htiming_program = {
    .instructions = video_htiming_program_instructions,
    .length = 6,
    .origin = -1,
};

static inline pio_sm_config video_htiming_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + video_htiming_wrap_target, offset + video_htiming_wrap);
    sm_config_set_sideset(&c, 1, false, false);
    return c;
}
#endif

// -------------------- //
// video_htiming_states //
// -------------------- //

#define video_htiming_states_wrap_target 0
#define video_htiming_states_wrap 3

static const uint16_t video_htiming_states_program_instructions[] = {
            //     .wrap_target
    0xc000, //  0: irq    nowait 0        side 0     
    0xc001, //  1: irq    nowait 1        side 0     
    0xc004, //  2: irq    nowait 4        side 0     
    0xc044, //  3: irq    clear 4         side 0     
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program video_htiming_states_program = {
    .instructions = video_htiming_states_program_instructions,
    .length = 4,
    .origin = -1,
};

static inline pio_sm_config video_htiming_states_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + video_htiming_states_wrap_target, offset + video_htiming_states_wrap);
    sm_config_set_sideset(&c, 1, false, false);
    return c;
}
#endif

