#include <Arduino_GFX_Library.h>
#include <arduino-timer.h>


#define GFX_BL 9 // default backlight pin, you may replace df_gfx_bl to actual backlight pin
#define GFX_DC 7
#define GFX_RST 8

/* more data bus class: https://github.com/moononournation/arduino_gfx/wiki/data-bus-class */
Arduino_DataBus *bus = new Arduino_HWSPI(GFX_DC, GFX_NOT_DEFINED);

/* more display class: https://github.com/moononournation/arduino_gfx/wiki/display-class */
Arduino_GFX *gfx = new Arduino_GC9A01(bus, GFX_RST, 0 /* rotation */, false /* ips */);

#define CURVE_WIDTH 8
#define CURVE_COLOR 0XEEA8
#define BG_COLOR 0xFFFF
#define MAX_X 240
#define MAX_Y 240

uint8_t enc1 = 16;
uint8_t enc2 = 17;

int curve_position = 180;
int val = 50;

Timer<10, micros> timer;

void update_curve(int update_position, int curve_rad) {
    // update_position = 10 * (update_position / 10);  // Round down to closest 10
    if (update_position == curve_position) {
        return;
    }
    if (update_position > curve_position) {
        gfx->fillArc(MAX_X / 2, MAX_Y / 2, curve_rad, curve_rad - CURVE_WIDTH, curve_position, update_position, CURVE_COLOR);
    } else {
        gfx->fillArc(MAX_X / 2, MAX_Y / 2, curve_rad, curve_rad - CURVE_WIDTH, update_position, curve_position, BG_COLOR);
    }
    curve_position = update_position;
}

void erase_number(void) {
    int start_x = MAX_X / 2 - 50 * (3.0 / 2);
    int start_y = MAX_Y / 2 - 30;
    int end_x = MAX_X / 2 + 50 * (3.0 / 2);
    int end_y = MAX_Y / 2 + 30;
    gfx->fillRect(start_x, start_y, end_x - start_x, end_y - start_y, BG_COLOR);
}


void update_number(const char *c, int size) {
    static int prev_size;
    if (prev_size != size) {
        erase_number();
    }
    int i = 0;
    while (*c != NULL) {
        Serial.print(c);
        int x = MAX_X / 2 + 20 * (i - (float)size / 2);
        int y = MAX_Y / 2;
        Serial.print(x);
        gfx->drawChar(x, y, *c, CURVE_COLOR, BG_COLOR);
        c++;
        i++;
    }
    prev_size = size;
}

void update_value(int *value, int new_value, int minimum, int maximum) {
    if (new_value > maximum) {
        *value = maximum;
    } else if (new_value < minimum) {
        *value = minimum;
    } else {
        *value = new_value;
    }
    update_curve(180 + 180.0f / (maximum - minimum) * (*value), 100);
    char num_string_buf[4];
    int size = snprintf(num_string_buf, 4, "%d", *value);
    update_number(num_string_buf, size);
}

void setup(void)
{
    gfx->begin();
    gfx->fillScreen(BG_COLOR);
    gfx->setTextSize(3);

    pinMode(GFX_BL, OUTPUT);
    digitalWrite(GFX_BL, HIGH);

    pinMode(enc1, INPUT_PULLUP);
    pinMode(enc2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(enc1), encoder_ISR, CHANGE);

    Serial.begin(9600);
}

void loop()
{
//     while (val < 100) {
//         update_value(&val, val + 10, 0, 100);
//         delay(1000);
//     }
//     while (val > 0) {
//         update_value(&val, val - 10, 0, 100);
//         delay(1000);
//     }
    timer.tick();
}

bool encoder_stable;
void encoder_update(void) {
    timer.cancel();
    Serial.print(encoder_stable);
    if (!encoder_stable) {
        encoder_stable = true;
        timer.in(500, encoder_update);
        return;
    }
    int8_t dir;
    if (digitalRead(enc1) == digitalRead(enc2)) {
        dir = -1;
    } else {
        dir = 1;
    }
    update_value(&val, val + dir, 0, 100);
}



void encoder_ISR(void) {
    encoder_stable = false;
    encoder_update();
}
