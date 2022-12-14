#ifndef FIRMWARE_H
#define FIRMWARE_H

#define SYS_FREQ 16000000
#define TCA_FREQ 4000000
#define BOOST_FREQ 10000

enum waveform {
    OFF,
    PULSE,
    DIFFERENTIAL,
    ASCENDING,
    ASCENDING_DIFFERENTIAL
};

void waveform_param_set(uint32_t frequency, float duty, float amplitude, enum waveform type);

/* Turn on the high side to either output line
   direction:
        0 - line 1
        >= 1 - line 2
*/
static inline void set_pulse_line_on(uint8_t direction);

static inline void set_pulse_line_off(void);
void pulse_init(void);
unsigned long scaled_millis(void);
void scaled_delay(unsigned long ms);

#endif