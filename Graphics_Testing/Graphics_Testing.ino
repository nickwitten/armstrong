#include <Arduino_GFX_Library.h>


#define GFX_BL 9 // default backlight pin, you may replace df_gfx_bl to actual backlight pin
#define GFX_DC 7
#define GFX_RST 8

/* more data bus class: https://github.com/moononournation/arduino_gfx/wiki/data-bus-class */
Arduino_DataBus *bus = new Arduino_HWSPI(GFX_DC, GFX_NOT_DEFINED);

/* more display class: https://github.com/moononournation/arduino_gfx/wiki/display-class */
Arduino_GFX *gfx = new Arduino_GC9A01(bus, GFX_RST, 0 /* rotation */, false /* ips */);

#define CURVE_WIDTH 8
uint8_t curve_end[CURVE_WIDTH] = {
//     0b10000000,
//     0b11111000,
//     0b11111110,
//     0b11111111,
//     0b11111111,
//     0b11111110,
//     0b11111000,
//     0b10000000,
    0b00011000,
    0b00111100,
    0b00111100,
    0b01111110,
    0b01111110,
    0b01111110,
    0b01111110,
    0b11111111,
};


float curve_position;

#define CURVE_RES 10
#define CURVE_RAD 100
#define CURVE_COLOR 0XEEA8
#define MAX_X 240
#define MAX_Y 240
// Position is a 0 - 32 int
void update_curve(float update_position) {
    if (update_position > curve_position) {
        do {
            gfx->fillArc(MAX_X / 2, MAX_Y / 2, CURVE_RAD, CURVE_RAD - CURVE_WIDTH, curve_position, curve_position + CURVE_RES, CURVE_COLOR);
            // gfx->fillArc(MAX_X / 2, MAX_Y / 2, CURVE_RAD, CURVE_RAD - CURVE_WIDTH, 0.0, 180.0, CURVE_COLOR);
            curve_position += CURVE_RES;
        } while (curve_position < update_position);
    }
//     while (curve_position >= update_position) {
//         for (int i = 0; i < CURVE_WIDTH * 8; i++) {
//             uint8_t x = i % 8;
//             uint8_t y_inv = i / 8;
//             uint16_t color = (curve_end[y_inv] & 1 << x) ? 0xFFFF : 0x4444;
//             float mag = sqrt(pow(x, 2) + pow(y_inv, 2));
//             float ang = atan((float)y_inv / x);
//             ang += curve_position * CURVE_RES;
//             x = mag * cos(ang);
//             y_inv = mag * sin(ang);
//             x += CURVE_RAD * cos(curve_position * CURVE_RES) + MAX_X / 2;
//             y_inv += CURVE_RAD * sin(curve_position * CURVE_RES) + MAX_Y / 2;
//             gfx->startWrite();
//             gfx->writePixelPreclipped(x, MAX_Y - y_inv, color);
//         }
//         curve_position--;
//     }
}

void setup(void)
{
    curve_position = 180.0;

    gfx->begin();
    gfx->fillScreen(0xFFFF);

    pinMode(GFX_BL, OUTPUT);
    digitalWrite(GFX_BL, HIGH);

}

void loop()
{
    update_curve(270.0);
    delay(2000);
    update_curve(360);
    update_curve(270.0);
    delay(2000);
    update_curve(0);
    delay(2000);
}

