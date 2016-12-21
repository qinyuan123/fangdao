#include "key.h"
#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
#include <Adafruit_NeoPixel.h>
#define humanHotSensor 4
#define PIN 8
#define key_pin 10
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);
#define buzzer_pin 6
bool humanHotState = false;
boolean buzzer_speak,add,a;
int i = 200;
void setup() {
  pinMode(humanHotSensor, INPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(key_pin, INPUT);
  strip.begin();
  u8g.firstPage();
  do{
  u8g.setPrintPos(4, 16);
  u8g.print("Program Running!");}
  while(u8g.nextPage());
}
void loop() {
    u8g.setFont(u8g_font_7x13);
  humanHotState = digitalRead(humanHotSensor);
  if (key_get(key_pin, 0))
  {
    noTone(buzzer_pin);
    strip.setPixelColor(0, strip.Color(0, 255, 0));
    strip.show();
    u8g.firstPage();
    do{
    u8g.setPrintPos(4, 16);
    u8g.print("Program Running!");
    u8g.setPrintPos(4, 32);
    u8g.print("You are the host~");}
    while(u8g.nextPage());
    delay(10000);
  }
  if (humanHotState){
    buzzer();
    strip.setPixelColor(0, strip.Color(255, 0, 0));
    strip.show();
    u8g.firstPage();
    do{
    u8g.setPrintPos(4, 16);
    u8g.print("Program Running!");
    u8g.setPrintPos(4, 48);
    u8g.print("There is a thief!");
    }
    while(u8g.nextPage());
    }
  else{
    noTone(buzzer_pin);
    strip.setPixelColor(0, strip.Color(0, 255, 0));
    strip.show();
    u8g.firstPage();
    do{
    u8g.setPrintPos(4, 16);
    u8g.print("Program Running!");
    u8g.setPrintPos(4, 48);
    u8g.print("");}
    while(u8g.nextPage());
    }
}
void buzzer()
{
    if (!add)
    {
      i++;
      if (i >= 800)
        add = true;
    }
    else
    {
      i--;
      if (i <= 200)
        add = false;
    }
    tone(buzzer_pin, i);
}
