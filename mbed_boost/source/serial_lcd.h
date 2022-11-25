#include "mbed.h"
#include "uLCD_4DGL.h"

#define BUFFSIZE 30

uLCD_4DGL lcd(p28, p27, p29);
Serial pc(USBTX, USBRX);

int main() {
    char buff[BUFFSIZE];
    while (1) {
        char fmt[5];
        sprintf(fmt, "%%%is", BUFFSIZE);
        pc.scanf(fmt, buff);
        lcd.cls();
        lcd.printf("%s", buff);
    }
}
