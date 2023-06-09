#include <LiquidCrystal.h>

#define LCD_RS   2
#define LCD_EN   3
#define LCD_D0   4
#define LCD_D1   5
#define LCD_D2   6
#define LCD_D3   7
#define DSPK_CLK 8
#define DSPK_RX  9

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D0, LCD_D1, LCD_D2, LCD_D3);

void setup() {
  for (int i=2; i<8; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  lcd.begin(16, 2);
}

void loop() {
  lcd.setCursor(0, 0);
}
