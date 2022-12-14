#include <SPI.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"
// #include "image.h"

// Frequency data
int freq_vals[] = {2500, 1666, 1250, 1000, 833};
// int duty_cycle_vals[] = {50, 33, 25, 20, 17};
// float duty_cycle_vals[] = {0.05, 0.04, 0.03, 0.02, 0.01}; // for 200Hz (1250): 50, 33, 25, 20, 17 ticks respectively
float duty_cycle_vals[] = {0.3, 0.25, 0.2, 0.15, 0.10}; // for 200Hz (1250): 50, 33, 25, 20, 17 ticks respectively

int freq_sel = 2;
int dCycle_sel = 3;

// Rotary Encoder Setup
#define CW 0    // Clockwise
#define CCW 1   // Counterclockwise

int a_in = 16;   // Rotary encoder switch at pin 2
int b_in = 17;   // Rotary encoder phase-shifted switch at pin 4
int curr_state;
int last_state;

int attribute_sel = 0;
int counter = 2;
String dir;

// Push button Setup
int pb_master = 20;

// LCD Communication Setup
char freq_buff[8];
char dCycle_buff[8];

// Clock setup
unsigned int minute = 0;
unsigned int hour = 0;
char min_buff[2];   // buffer
char hrs_buff[2];

// UI/UX menu attributes
enum
{
  freq,
  dutyCycle,
  none
} selected_attribute;

// Fucntion Prototypes
void lock_screen();
void unlocked_screen();
void update_freq(int freq);
void update_dCycle(int dCycle);
void select_freq();
void select_dutyCycle();
void update_clock(int min_p, int hrs_p);
void freq_up();
void freq_down();
void duty_cycle_up();
void duty_cycle_down();

void setup() 
{
  // System clock is 16 MHz
  // CLK_TCA is 250 KHz with a prescaler from system clock of 64
  // The longest period of TCA is (1/250 KHz) * 2^16 bits = 262 ms (lowest frequency of 4 Hz)
  // The resolution of TCA is 1/250 KHz = 4 us
  // The period of the 200 Hz PWM signal is (1/200 Hz) / 4 us = 1250 ticks
  // The pulse width of the 100 us pulse is 100 us / 4 us = 25 ticks
  pinMode(5, OUTPUT);
  analogWrite(5, 128);
  pinMode(3, OUTPUT);  // ~ON
  digitalWrite(3, LOW);
  TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm;  // Turn off timer while we change parameters.
  TCA0.SINGLE.PERBUF = freq_vals[freq_sel];         // select default frequency with 200 Hz
  int dCycle_tick = freq_vals[freq_sel] * duty_cycle_vals[dCycle_sel];  // Calculate duty cycle ticks
  TCA0.SINGLE.CMP2BUF = dCycle_tick;  // select default duty cycle as 0.02 (actual 0.98)
  TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;

  // ////////// External Interrupt Setup ///////////
  // attachInterrupt(digitalPinToInterrupt(2), freq_up, FALLING);  // use pin 2 for external interrupt trigger on falling edge
  // attachInterrupt(digitalPinToInterrupt(3), freq_down, FALLING);  // use pin 2 for external interrupt trigger on falling edge

  // Rotary switch input setup
  pinMode(a_in, INPUT_PULLUP);
  pinMode(b_in, INPUT_PULLUP);

  last_state = digitalRead(a_in);

  // Push button setup
  pinMode(pb_master, INPUT_PULLUP);

  // LCD Setup
  Config_Init();
  Serial.print("Initiating...\r\n");
  LCD_Init();
  LCD_SetBacklight(1000);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, BLACK);

  // Display Lock Screen
  lock_screen();
  long myTime = -1;

  Serial.print("Break point 1\r\n");
  // Unlock mechanism: need to press down the button for at least 1 second to unlock
  int lock_counter = 0;
  update_clock(minute, hour);
  while (1) 
  {
    myTime++;
    Serial.println(myTime);
    if (myTime != 0 && myTime % 3600 == 0)
    {
      hour++;
      minute = 0;
      Serial.print("Clock update-> ");
      Serial.print(hour);
      Serial.print(" : ");
      Serial.println(minute);
      update_clock(minute, hour);
    }
    else if (myTime != 0 && myTime % 60 == 0)
    {
      minute++;
      Serial.print("Clock update-> ");
      Serial.print(hour);
      Serial.print(" : ");
      Serial.println(minute);
      update_clock(minute, hour);
    }
    bool locker = (bool) digitalRead(pb_master);
    if (!locker) 
    {
      if (lock_counter == 0) 
      {
        lock_counter++;
      } 
      else if (lock_counter == 1) 
      {
        lock_counter = 0;
        break;
      }
    } 
    else 
    {
      lock_counter = 0;
    }
    delay(999);
  }

  unlocked_screen();
  delay(2);
  Paint_Clear(BLACK);
  selected_attribute = none;
  display_stats(freq_vals[freq_sel], duty_cycle_vals[dCycle_sel]);
}

void loop() 
{ 
  // Menu level 1
  curr_state = digitalRead(a_in);
  if (curr_state != last_state && curr_state == 0) 
  {
    // Clockwise rotation once
    if(digitalRead(b_in) == curr_state) 
    {
      if (attribute_sel < 1) 
      {
        attribute_sel++;
        select_freq();
      }
      dir = "CCW";
    } 
    // Counter clockwise rotation once
    else 
    {
      if (attribute_sel > 0) 
      {
        attribute_sel--;
        select_dutyCycle();
      }
      dir = "CW";
    }
    Serial.print("Menu lvl 2: ");
    Serial.print("Direction: ");
    Serial.print(dir);
    Serial.print(" | attribute_sel: ");
    Serial.println(attribute_sel);
  }
  last_state = curr_state;
  delayMicroseconds(200);

  ///////////// Menu level 2 begins /////////////
  if (!digitalRead(pb_master))
  {
    // Menu lvl 1 -> selected to adjust freq
    if (selected_attribute == freq)
    {
      // Highlight confirmed attribute
      Serial.println("Freq is confirmed!");
      String freq_out = String(freq_vals[freq_sel]);
      freq_out.toCharArray(freq_buff, sizeof(freq_buff));
      Paint_DrawString_EN(12, 120, freq_buff, &Font16, BLACK, RED);   // Paint red to selected attribute text to highlight

      /////////// Menu lvl 2 while loop ///////////

      // Rotate to change selected attribute
      last_state = digitalRead(a_in);
      while(1)
      {
        curr_state = digitalRead(a_in);
        if (curr_state != last_state && curr_state == 0)
        {
          // Clockwise rotation once
          if(digitalRead(b_in) == curr_state) 
          {
            if (counter < 4) 
            {
              counter++;
              freq_up();
              // Serial.println("Freq up!");
              update_freq(freq_vals[freq_sel]);
            }
            dir = "CCW";
          } 
          // Counter clockwise rotation once
          else 
          {
            if (counter > 0) 
            {
              counter--;
              freq_down();
              // Serial.println("Freq down!");
              update_freq(freq_vals[freq_sel]);
            }
            dir = "CW";
          }
          Serial.print("Menu lvl 2: ");
          Serial.print("Direction: ");
          Serial.print(dir);
          Serial.print(" | Counter: ");
          Serial.print(counter);
          Serial.print(" | Freq_sel: ");
          Serial.println(freq_sel);
        }

        // return to the previous menu (lvl 1)
        if (!digitalRead(pb_master))
        {
          Serial.println("Exit menu lvl 2!");
          selected_attribute = none;
          String freq_out = String(freq_vals[freq_sel]);
          freq_out.toCharArray(freq_buff, sizeof(freq_buff));
          Paint_DrawString_EN(12, 120, freq_buff, &Font16, BLACK, WHITE);   // reset selected attribute color -> freq
          Paint_DrawString_EN(10, 70, "Freq", &Font16, BLACK, BLUE);
          break;
        }

        last_state = curr_state;
        delayMicroseconds(200);
      }
      /////////// End menu lvl 2 while loop ///////////

    }
    // Menu lvl 1 -> selected to adjust duty cycle
    else if (selected_attribute == dutyCycle)
    {
      // Highlght confirmed attribute
      Serial.println("Duty cycle is confirmed!");
      String dCycle_out = String(duty_cycle_vals[dCycle_sel]);
      dCycle_out.toCharArray(dCycle_buff, sizeof(dCycle_buff));
      Paint_DrawString_EN(110, 120, dCycle_buff, &Font16, BLACK, RED);    // Paint red to selected attribute text to highlight

      /////////// Menu lvl 2 while loop ///////////

      // Rotate to change selected attribute
      last_state = digitalRead(a_in);
      while(1)
      {
        curr_state = digitalRead(a_in);
        if (curr_state != last_state && curr_state == 0) 
        {
          // Clockwise rotation once
          if(digitalRead(b_in) == curr_state) 
          {
            if (counter < 4) 
            {
              counter++;
              duty_cycle_up();
              update_dCycle(duty_cycle_vals[dCycle_sel]);
            }
            dir = "CCW";
          } 
          // Counter clockwise rotation once
          else 
          {
            if (counter > 0) 
            {
              counter--;
              duty_cycle_down();
              update_dCycle(duty_cycle_vals[dCycle_sel]);
            }
            dir = "CW";
          }
          Serial.print("Menu lvl 2: ");
          Serial.print("Direction: ");
          Serial.print(dir);
          Serial.print(" | Counter: ");
          Serial.print(counter);
          Serial.print(" | duty cycle select: ");
          Serial.println(dCycle_sel);
        }

        // return to the previous menu (lvl 1)
        if (!digitalRead(pb_master))
        {
          Serial.println("Exit menu lvl 2!");
          selected_attribute = none;
          String dCycle_out = String(duty_cycle_vals[dCycle_sel]);
          dCycle_out.toCharArray(dCycle_buff, sizeof(dCycle_buff));
          Paint_DrawString_EN(110, 120, dCycle_buff, &Font16, BLACK, WHITE);
          Paint_DrawString_EN(10, 70, "Freq", &Font16, BLACK, BLUE);
          break;
        }

        last_state = curr_state;
        delayMicroseconds(200);
      }
      /////////// End menu lvl 2 while loop ///////////

    } 
    // Menu lvl 1 -> nothing is selected
    else
    {
      // display current frequency value
      String freq_out = String(freq_vals[freq_sel]);
      freq_out.toCharArray(freq_buff, sizeof(freq_buff));
      Paint_DrawString_EN(12, 120, freq_buff, &Font16, BLACK, WHITE);

      // display current duty cycle value
      String dCycle_out = String(duty_cycle_vals[dCycle_sel]);
      dCycle_out.toCharArray(dCycle_buff, sizeof(dCycle_buff));
      Paint_DrawString_EN(110, 120, dCycle_buff, &Font16, BLACK, WHITE);
    }

    // switch(selected_attribute)
    // {
    //   case dutyCycle:
    //     Serial.println("Duty cycle is confirmed!");
    //     String dCycle_out = String(50);
    //     dCycle_out.toCharArray(dCycle_buff, sizeof(dCycle_buff));
    //     Paint_DrawString_EN(110, 120, dCycle_buff, &Font16, BLACK, RED);
    //     break;

    //   case freq:
    //     Serial.println("Freq is confirmed!");
    //     String freq_out = String(freq_vals[freq_sel]);
    //     freq_out.toCharArray(freq_buff, sizeof(freq_buff));
    //     Paint_DrawString_EN(12, 120, freq_buff, &Font16, BLACK, RED);
    //     break;
    // }
  }
  
  // delay(1);
}

// LCD functions
void lock_screen()
{
  Paint_Clear(BLACK);
  Paint_DrawString_EN(10, 123, "Press to Unlock", &Font20, BLACK, GREEN);
}

void unlocked_screen()
{
  Paint_Clear(BLACK);
  Paint_DrawString_EN(10, 123, "Unlocked", &Font20, BLACK, BLUE);
}

void display_stats(int freq, float dCycle)
{
  String freq_out = String(freq);
  String dCycle_out = String(dCycle);
  freq_out.toCharArray(freq_buff, sizeof(freq_buff));
  dCycle_out.toCharArray(dCycle_buff, sizeof(dCycle_buff));
  Paint_DrawString_EN(10, 70, "Freq", &Font16, BLACK, BLUE);
  Paint_DrawString_EN(12, 120, freq_buff, &Font16, BLACK, WHITE);
  Paint_DrawString_EN(80, 70, "Duty Cycle (%)", &Font16, BLACK, BLUE);
  Paint_DrawString_EN(110, 120, dCycle_buff, &Font16, BLACK, WHITE);
}

void update_freq(int freq)
{
  String freq_out = String(freq);
  freq_out.toCharArray(freq_buff, sizeof(freq_buff));
  Paint_DrawString_EN(12, 120, freq_buff, &Font16, BLACK, RED);
}

void update_dCycle(float dCycle)
{
  String dCycle_out = String(dCycle);
  dCycle_out.toCharArray(dCycle_buff, sizeof(dCycle_buff));
  Paint_DrawString_EN(110, 120, dCycle_buff, &Font16, BLACK, RED);
}

void select_freq()
{
  selected_attribute = freq;
  Paint_DrawString_EN(80, 70, "Duty Cycle (%)", &Font16, BLACK, BLUE);
  Paint_DrawString_EN(10, 70, "Freq", &Font16, BLACK, RED);  
}

void select_dutyCycle()
{
  selected_attribute = dutyCycle;
  Paint_DrawString_EN(10, 70, "Freq", &Font16, BLACK, BLUE);  
  Paint_DrawString_EN(80, 70, "Duty Cycle (%)", &Font16, BLACK, RED);
}

void update_clock(unsigned int min_p, unsigned int hrs_p)
{
  String min_elapsed = String(min_p);
  String hrs_elapsed = String(hrs_p);
  min_elapsed.toCharArray(min_buff, sizeof(min_buff));
  hrs_elapsed.toCharArray(hrs_buff, sizeof(hrs_buff));
  // Paint_ClearWindows(50, 70, 150, 100, BLACK);
  Paint_DrawString_EN(80, 70, hrs_buff, &Font20, BLACK, WHITE);
  Paint_DrawString_EN(140, 70, min_buff, &Font20, BLACK, WHITE);
  Paint_DrawString_EN(95, 70, " : ", &Font20, BLACK, WHITE);
}

// Frequency Control Functions
void freq_up() 
{
  if (freq_sel >= 0 && freq_sel < 4) 
    freq_sel++;
  
  // Serial.println("Freq up!");
  TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm;  // Turn off timer while we change parameters.
  TCA0.SINGLE.PERBUF = freq_vals[freq_sel];         // select default frequency with 200 Hz
  int dCycle_tick = freq_vals[freq_sel] * duty_cycle_vals[dCycle_sel];  // Calculate duty cycle ticks
  TCA0.SINGLE.CMP2BUF = dCycle_tick;  // select default duty cycle as 0.02 (actual 0.98)
  TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}

void freq_down() 
{
  if (freq_sel > 0 && freq_sel <= 4) 
    freq_sel--;

  // Serial.println("Freq down!");
  TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm;  // Turn off timer while we change parameters.
  TCA0.SINGLE.PERBUF = freq_vals[freq_sel];         // select default frequency with 200 Hz
  int dCycle_tick = freq_vals[freq_sel] * duty_cycle_vals[dCycle_sel];  // Calculate duty cycle ticks
  TCA0.SINGLE.CMP2BUF = dCycle_tick;  // select default duty cycle as 0.02 (actual 0.98)
  TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}

// Duty cycle control functions
void duty_cycle_up() 
{
  if (dCycle_sel >= 0 && dCycle_sel < 4) 
    dCycle_sel++;

  TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm;  // Turn off timer while we change parameters.
  TCA0.SINGLE.PERBUF = freq_vals[freq_sel];         // select default frequency with 200 Hz
  int dCycle_tick = freq_vals[freq_sel] * duty_cycle_vals[dCycle_sel];  // Calculate duty cycle ticks
  TCA0.SINGLE.CMP2BUF = dCycle_tick;  // select default duty cycle as 0.02 (actual 0.98)
  TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}

void duty_cycle_down() 
{
  if (dCycle_sel > 0 && dCycle_sel <= 4) 
    dCycle_sel--;
  
  TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm;  // Turn off timer while we change parameters.
  TCA0.SINGLE.PERBUF = freq_vals[freq_sel];         // select default frequency with 200 Hz
  int dCycle_tick = freq_vals[freq_sel] * duty_cycle_vals[dCycle_sel];  // Calculate duty cycle ticks
  TCA0.SINGLE.CMP2BUF = dCycle_tick;  // select default duty cycle as 0.02 (actual 0.98)
  TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}
