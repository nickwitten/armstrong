const int control_pin = 10; // the PWM out pin is D10

void setup() {
  // put your setup code here, to run once:
  pinMode(control_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(control_pin, HIGH);
  delay(5);    // 100Hz PWM out with 50% duty cycle;
  digitalWrite(control_pin, LOW);
  delay(5);
}
