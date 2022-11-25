void setup() {
  // System clock is 16 MHz
  // CLK_TCA is 250 KHz with a prescaler from system clock of 64
  // The longest period of TCA is (1/250 KHz) * 2^16 bits = 262 ms (lowest frequency of 4 Hz)
  // The resolution of TCA is 1/250 KHz = 4 us
  // The period of the 200 Hz PWM signal is (1/200 Hz) / 4 us = 1250 ticks
  // The pulse width of the 100 us pulse is 100 us / 4 us = 25 ticks
  pinMode(5, OUTPUT);
  analogWrite(5, 128);
  TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm;  // Turn off timer while we change parameters.
  TCA0.SINGLE.PERBUF = 1250;
  TCA0.SINGLE.CMP2BUF = 1250 - 400;
  TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}

void loop() {}
