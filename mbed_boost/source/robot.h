#include "mbed.h"
#include "Motor.h"

Motor left(p21, p7, p8);
Motor right(p22, p6, p5);
DigitalIn right_enc(p29, PullUp);
DigitalIn left_enc(p30, PullUp);
Serial pc(USBTX, USBRX);

int main() {
    while (1) {
//         for (float i = -1.0; i <= 1.0; i += 0.1) {
//             left.speed(i);
//             right.speed(i);
//             wait(0.1);
//         }
//         for (float i = 1.0; i >= -1.0; i -= 0.1) {
//             left.speed(i);
//             right.speed(i);
//             wait(0.1);
//         }
        pc.printf("%d %d\r\n", right_enc.read(), left_enc.read());
        wait(0.5);
    }
}
