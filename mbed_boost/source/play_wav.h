#include "mbed.h"
#include "SDFileSystem.h"
#include "wave_player.h"

SDFileSystem sd(p5, p6, p7, p8, "sd");
AnalogOut aout(p18);
wave_player player(&aout);

int main() {
    FILE *fp = fopen("/sd/audio/imperial_march_16KHz.wav", "r");
    player.play(fp);
}
