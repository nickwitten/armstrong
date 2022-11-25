#include "mbed.h"

Serial pc(USBTX, USBRX);
int main() {
    pc.printf("Hello World!\r\n");
    PwmOut boost(p26);
    boost.period_us(100);
    boost.write(0.01);
}
