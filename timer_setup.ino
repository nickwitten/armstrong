void setup() {
  // PWM Output Channels
  PORTB.DIRSET = PIN2_bm;  // D5, PB2 TCA2
  PORTF.DIRSET = PIN4_bm;  // D6, PF4 TCB0
  PORTF.DIRSET = PIN5_bm;  // D3, PF5 TCB1

  // Timer A Setup
  TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV64_gc;  // Set clock
  TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP2EN_bm | TCA_SINGLE_WGMODE_SINGLESLOPE_gc;  // Single slope and enable channel 2
  TCA0.SINGLE.PERBUF = 100;  // Set the period
  TCA0.SINGLE.CMP2BUF = 30;  // Set the duty-cycle
  TCA0.SINGLE.INTCTRL = TCA_SINGLE_CMP2_bm | TCA_SINGLE_OVF_bm;  // Setup interrupts to fire on cmp2  

  // Timer B Setup
  TCB0.CTRLA = TCB_CLKSEL_CLKTCA_gc;  // Set clock
  TCB0.CTRLB = TCB_CNTMODE_PWM8_gc | TCB_CCMPEN_bm;  // PWM mode and enable
  TCB0.CCMPL = 100; // Set the period
  TCB0.CCMPH = 90;  // Set the duty-cycle

  // Enable PWM Output
  TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;  // Enable output
  TCB0.CTRLA |= TCB_ENABLE_bm;  // Enable output
}

void loop() {}
