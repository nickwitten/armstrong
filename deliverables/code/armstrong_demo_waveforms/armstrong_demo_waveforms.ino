#include "firmware.h"

#define NUM_PARAMS 13


int pb = 20;

struct param {
    int frequency;
    float pulse;
    float amplitude;
    enum waveform wave;
};

struct param params[NUM_PARAMS] = {
    {200, 0.1, 0.1, PULSE},
    {200, 0.1, 0.1, ASCENDING},
    {200, 0.1, 0.1, DIFFERENTIAL},
    {200, 0.1, 0.1, ASCENDING_DIFFERENTIAL},
    {100, 0.1, 0.1, PULSE},
    {300, 0.1, 0.1, PULSE},
    {500, 0.1, 0.1, PULSE},
    {100, 0.1, 0.1, PULSE},
    {100, 0.3, 0.1, PULSE},
    {100, 0.5, 0.1, PULSE},
    {100, 0.1, 0.1, PULSE},
    {100, 0.1, 0.4, PULSE},
    {100, 0.1, 0.6, PULSE},
};
int param_ind = 0;


void setup() {
    pinMode(pb, INPUT_PULLUP);
    pulse_init();
    while (digitalRead(pb)) {
        struct param p = params[param_ind];
        waveform_param_set(p.frequency, p.pulse, p.amplitude, p.wave);
        param_ind++;
        if (param_ind >= NUM_PARAMS) {
            param_ind = 0;
        }
        delay(5000 * 32);
    }
}

void loop() {
    if (!digitalRead(pb)) {
        waveform_param_set(80, 0.1, 0.9, DIFFERENTIAL);
    } else {
        waveform_param_set(80, 0.1, 0.9, OFF);
    }
}
