#define SYS_FREQ 16000000
#define BOOST_FREQ 10000
#define PULSE_FREQ 200
#define PULSE_DUTY 0.2
#define QUICKSTART_DUTY 0

uint32_t boost_period_ticks;
uint32_t boost_pulse_count_on = BOOST_FREQ / PULSE_FREQ * PULSE_DUTY;
uint32_t boost_pulse_count_quickstart_on = BOOST_FREQ / PULSE_FREQ * QUICKSTART_DUTY;
uint32_t boost_pulse_count_total = BOOST_FREQ / PULSE_FREQ;
volatile uint32_t boost_count = 0;
volatile float boost_duty = 0.9;
uint32_t TCA_frequency;
void setup() {
  PORTB.DIRSET = PIN0_bm;  // D9, PB0
  PORTE.DIRSET = PIN3_bm;  // D8, PE3
  PORTD.DIRSET = PIN0_bm;

  // Timer A Setup
  TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_WGMODE_SINGLESLOPE_gc;  // Single slope and enable channel 0
  TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_CLKSEL_gm;  // Clear clock bits
  TCA0.SINGLE.CTRLA |= TCA_SINGLE_CLKSEL_DIV1_gc;  // Set clock
  TCA_frequency = SYS_FREQ / 1;
  boost_period_ticks = TCA_frequency / BOOST_FREQ;
  TCA0.SINGLE.PERBUF = boost_period_ticks;  // Set the period
  TCA0.SINGLE.CMP0BUF = boost_period_ticks * boost_duty;  // Set the pulse width
  TCA0.SINGLE.INTCTRL = TCA_SINGLE_CMP0_bm | TCA_SINGLE_OVF_bm;  // Setup interrupts to fire on cmp2
  TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;

//  Serial.begin(9600);
//  Serial.write("hi");
//  char string[50];
//  sprintf(string, "%d\n", boost_pulse_count_quickstart_on);
//  Serial.write(string);
//  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {}

ISR(TCA0_CMP0_vect) {
  TCA0.SINGLE.INTFLAGS |= TCA_SINGLE_CMP0_bm;
}

ISR(TCA0_OVF_vect) {
  if (boost_count < boost_pulse_count_quickstart_on) {
    TCA0.SINGLE.CMP0BUF = boost_period_ticks;  // Set to constant on for quick start
  } else if (boost_count == boost_pulse_count_quickstart_on) {
    PORTD.OUTSET = PIN0_bm;  // Enable output
    TCA0.SINGLE.CMP0BUF = boost_period_ticks * boost_duty;  // Set the duty cycle
  } else if (boost_count >= boost_pulse_count_on + boost_pulse_count_quickstart_on) {
    PORTD.OUTCLR = PIN0_bm;
    TCA0.SINGLE.CMP0BUF = 0;
  }

  if (boost_count >= boost_pulse_count_total - 1) {
    boost_count = 0;
  } else {
    boost_count++;
  }
  
  TCA0.SINGLE.INTFLAGS |= TCA_SINGLE_OVF_bm;  // Clear interrupt flag
}
