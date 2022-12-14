#include "firmware.h"


const uint32_t boost_period_ticks = TCA_FREQ / BOOST_FREQ;
const uint8_t pulse_delay_ticks = 1;

volatile uint32_t ovf_count = 0;
volatile uint8_t dir = 0;

volatile uint32_t pulse_period_ovf;
volatile uint32_t pulse_duty_ovf;
volatile float boost_duty;
volatile uint8_t waveform_type;

void waveform_param_set(uint32_t frequency, float duty, float amplitude, enum waveform type) {
    if (type == OFF) {
        TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm;
    } else {
        TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
    }
    pulse_period_ovf = BOOST_FREQ / frequency;  // Amount of TCA0 overflows for pulse period
    pulse_duty_ovf = BOOST_FREQ / frequency * duty;  // Amount of TCA0 overflows for pulse duty
    boost_duty = amplitude;
    waveform_type = type;
}

unsigned long scaled_millis(void) {
    return millis() / 16;  // TCA is running 16 times the normal speed
}

void scaled_delay(unsigned long ms) {
    delay(ms * 16);  // TCA is running 16 times the normal speed
}

void loop() {}

void setup() {
    pulse_init();
    waveform_param_set(100, 0.1, 0.4, PULSE);
}


/* Turn on the high side to either output line
   direction:
        0 - line 1
        >= 1 - line 2
*/
static inline void set_pulse_line_on(uint8_t direction) {
    if (direction) {
        PORTF.OUTCLR = PIN5_bm;  // Turn off H_DRIVE1
        PORTC.OUTCLR = PIN6_bm;  // Turn off L_DRIVE2
        PORTA.OUTSET = PIN0_bm;  // Turn on L_DRIVE1
        PORTF.OUTSET = PIN4_bm;  // Turn on H_DRIVE2
    } else {
        PORTF.OUTCLR = PIN4_bm;  // Turn off H_DRIVE2
        PORTA.OUTCLR = PIN0_bm;  // Turn off L_DRIVE1
        PORTC.OUTSET = PIN6_bm;  // Turn on L_DRIVE2
        PORTF.OUTSET = PIN5_bm;  // Turn on H_DRIVE1
    }
}

static inline void set_pulse_line_off(void) {
    PORTF.OUTCLR = PIN5_bm;  // Turn off H_DRIVE1
    PORTF.OUTCLR = PIN4_bm;  // Turn off H_DRIVE2
}

void pulse_init(void) {
    // Digital writes
    PORTF.DIRSET = PIN5_bm;  // H_DRIVE1
    PORTF.DIRSET = PIN4_bm;  // H_DRIVE2
    PORTA.DIRSET = PIN0_bm;  // L_DRIVE1
    PORTC.DIRSET = PIN6_bm;  // L_DRIVE2

    // PWM TCA Output Channel
    PORTB.DIRSET = PIN2_bm;  // D5, PB2 TCA_CMP2

    // Timer A Setup
    #ifdef TCA_FREQ
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV4_gc;  // Set clock, TCA_FREQ should correspond to this div value
    #endif
    TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP2EN_bm | TCA_SINGLE_WGMODE_SINGLESLOPE_gc;  // Single slope and enable channel 2
    TCA0.SINGLE.PERBUF = boost_period_ticks;  // Set the period
    TCA0.SINGLE.CMP2BUF = 0;  // Set the duty-cycle
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_CMP2_bm | TCA_SINGLE_OVF_bm;  // Setup interrupts to fire on cmp2  

    // Initialize timing parameters
    waveform_param_set(100, 0, 0, OFF);

    // Enable timer
    TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}

ISR(TCA0_CMP2_vect) {
    TCA0.SINGLE.INTFLAGS |= TCA_SINGLE_CMP2_bm;
}

ISR(TCA0_OVF_vect) {
    if (ovf_count < pulse_duty_ovf + pulse_delay_ticks) {
        TCA0.SINGLE.CMP2BUF = boost_period_ticks * boost_duty;  // Set the duty-cycle
        if (ovf_count >= pulse_delay_ticks) {
            set_pulse_line_on(dir);
        }
    } else {
        set_pulse_line_off();
        // TCA0.SINGLE.CMP2BUF = 0;
    }

    if (ovf_count >= pulse_period_ovf - 1) {  // End of pulse period
        if (waveform_type == DIFFERENTIAL | waveform_type == ASCENDING_DIFFERENTIAL) {
            dir = ~dir;
        }
        ovf_count = 0;
    } else {
        ovf_count++;
    }

    TCA0.SINGLE.INTFLAGS |= TCA_SINGLE_OVF_bm;  // Clear interrupt flag
}
