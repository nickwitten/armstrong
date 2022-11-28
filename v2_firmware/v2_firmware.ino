#define SYS_FREQ 16000000
#define BOOST_FREQ 10000
#define PULSE_FREQ 500
#define PULSE_DUTY 0.2

uint32_t boost_period_ticks;
uint32_t pulse_period_ovf = BOOST_FREQ / PULSE_FREQ;  // Amount of TCA0 overflows for pulse period
uint32_t pulse_duty_ovf = BOOST_FREQ / PULSE_FREQ * PULSE_DUTY;  // Amount of TCA0 overflows for pulse duty
volatile uint32_t ovf_count = 0;
volatile float boost_duty = 0.3;
uint32_t TCA_frequency;
void setup() {
  // Digital writes
  PORTF.DIRSET = PIN5_bm;  // H_DRIVE1
  PORTF.DIRSET = PIN4_bm;  // H_DRIVE2
  PORTA.DIRSET = PIN0_bm;  // L_DRIVE1
  PORTC.DIRSET = PIN6_bm;  // L_DRIVE2

  // PWM TCA Output Channel
  PORTB.DIRSET = PIN2_bm;  // D5, PB2 TCA_CMP2

  // Timer A Setup
  TCA_frequency = SYS_FREQ / 1;
  boost_period_ticks = TCA_frequency / BOOST_FREQ;

  TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc;  // Set clock
  TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP2EN_bm | TCA_SINGLE_WGMODE_SINGLESLOPE_gc;  // Single slope and enable channel 2
  TCA0.SINGLE.PERBUF = boost_period_ticks;  // Set the period
  TCA0.SINGLE.CMP2BUF = 0;  // Set the duty-cycle
  TCA0.SINGLE.INTCTRL = TCA_SINGLE_CMP2_bm | TCA_SINGLE_OVF_bm;  // Setup interrupts to fire on cmp2  

  TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;

//  Serial.begin(9600);
//  Serial.write("hi");
}

void loop() {}

ISR(TCA0_CMP2_vect) {
  TCA0.SINGLE.INTFLAGS |= TCA_SINGLE_CMP2_bm;
}

uint8_t pulse_delay = 1;
ISR(TCA0_OVF_vect) {
  if (ovf_count <= pulse_duty_ovf + pulse_delay) {
    TCA0.SINGLE.CMP2BUF = boost_period_ticks * boost_duty;  // Set the duty-cycle
    if (ovf_count >= pulse_delay) {
        PORTF.OUTSET = PIN5_bm;  // Turn on H_DRIVE1
    }
  } else {
    PORTF.OUTCLR = PIN5_bm;
    TCA0.SINGLE.CMP2BUF = 0;
  }

  if (ovf_count >= pulse_period_ovf - 1) {
    ovf_count = 0;
  } else {
    ovf_count++;
  }

  TCA0.SINGLE.INTFLAGS |= TCA_SINGLE_OVF_bm;  // Clear interrupt flag
}
