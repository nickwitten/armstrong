#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL lcd(p28, p27, p29);

int main() {
    lcd.locate(1, 3);
    lcd.color(RED);
    lcd.printf("%.3f\r\n", 3.14159);
}
