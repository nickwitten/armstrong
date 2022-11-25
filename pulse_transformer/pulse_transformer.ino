void setup() {
  // System clock is 16 MHz
  // CLK_TCA is 250 KHz with a prescaler from system clock of 64
  // The longest period of TCA is (1/250 KHz) * 2^16 bits = 262 ms (lowest frequency of 4 Hz)
  // The resolution of TCA is 1/250 KHz = 4 us
  // The period of the 200 Hz PWM signal is (1/200 Hz) / 4 us = 1250 ticks
  // The pulse width of the 100 us pulse is 100 us / 4 us = 25 ticks
  pinMode(5, OUTPUT);  // CTRL
  analogWrite(5, 128);
  pinMode(3, OUTPUT);  // ~ON
  digitalWrite(3, LOW);
  TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm;  // Turn off timer while we change parameters.
  TCA0.SINGLE.PERBUF = 1250;
  TCA0.SINGLE.CMP2BUF = 100;
  TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;


  // PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTC_gc;
  TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm;  // Turn off timer while we change parameters.
//  TCA0.SINGLE.PERBUF = 1250;
//  TCA0.SINGLE.CMP2BUF = 300;  // Resulted in about 2 mA of current from transformer circuit
//  TCA0.SINGLE.INTCTRL = TCA_SINGLE_CMP2_bm;
//  sei();
//  TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;

//  int freq = 100;
//  int pulse_width_us = 100;
//  int system_clock_freq = 16 * 1000000;
//  int peripheral_prescale = 64;
//  int peripheral_clock_freq = system_clock_freq / peripheral_prescale;
//  TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm;  // Turn off timer while we change parameters.
//  TCA0.SINGLE.PERBUF = (1/freq) * peripheral_clock_freq;
//  TCA0.SINGLE.CMP2BUF = pulse_width_us * peripheral_clock_freq;
//  TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
    
  
}
//uint32_t count = 0;
//
//ISR(TCA0_CMP2_vect)
//{
// digitalWrite(LED_BUILTIN, HIGH);
// if (count > 0) {
//     // TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm;
// }
// count++;
// TCA0.SINGLE.INTFLAGS = TCA_SINGLE_CMP2_bm;
//}


void loop() {
    delay(50000);
    TCA0.SINGLE.CMP2BUF = 0;
}
