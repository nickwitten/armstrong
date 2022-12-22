#include "firmware.h"


int pb = 20;

void setup() {
    pinMode(pb, INPUT_PULLUP);
    pulse_init();
}

void loop() {
    if (!digitalRead(pb)) {
        waveform_param_set(80, 0.1, 0.9, DIFFERENTIAL);
    } else {
        waveform_param_set(80, 0.1, 0.9, OFF);
    }
}
