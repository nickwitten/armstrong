bool clock_div16 = false;

void wait_ms(long ms) {
  if (clock_div16) {
    delay(ms << 2);  // TCA is running 4 times faster than usual
  } else {
    delay(ms);
  }
}

void setup() {
  pinMode(5, OUTPUT);
  pinMode(2, OUTPUT);
  analogWrite(5, 128);
  // System clock is 16 MHz
  // CLK_PER is 16 MHz with a prescaler from CLK_MAIN of 1 (assumed by measurement)
  // CLK_TCA is 1 MHz with a prescaler from CLK_PER of 16
  // Normally the prescaler is set to 64
  // The longest period of TCA is (1/1 MHz) * 2^16 bits = 65.536 ms (lowest frequency of 15 Hz)
  // The resolution of TCA is 1/1 MHz = 1 us
  // The period of the 200 Hz PWM signal is (1/200 Hz) / 1 us = 5000 ticks
  // The pulse width of the 100 us pulse is 100 us / 1 us = 100 ticks
  TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm;  // Turn off timer while we change parameters.
  TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_CLKSEL_gm;  // Clear all CLKSEL bits.
  TCA0.SINGLE.CTRLA |= TCA_SINGLE_CLKSEL_DIV16_gc;  // Set prescaler to 16
  clock_div16 = true;
  TCA0.SINGLE.PERBUF = 5000;
  TCA0.SINGLE.CMP2BUF = 5000 - 100;
  TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}

void loop() {
  // put your main code here, to run repeatedly:
  static bool is_on = false;
  is_on = !is_on;
  digitalWrite(2, is_on);
  wait_ms(1000);
}
