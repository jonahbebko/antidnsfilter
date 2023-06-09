#include <LiquidCrystal.h>

#define DATA_RX  3
#define DATA_CLK 2

char message[7];
char line[17];
volatile byte rx_byte = 0;
volatile unsigned int bit_position = 0;
volatile bool update_lcd = false;

LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  strcpy(message, "");
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("[   Testing:   ]");
  lcd.setCursor(0, 1);
  lcd.print("[    ------    ]");
  attachInterrupt(digitalPinToInterrupt(DATA_CLK), onClockPulse, RISING);
}

void onClockPulse() {

  if (strlen(message) == 6) {
    strcpy(message, "");
  }
  
  bool rx_bit = digitalRead(DATA_RX);

  if (bit_position == 8) {
    rx_byte = 0;
    bit_position = 0;
  }

  if (rx_bit) {
    rx_byte |= (0x80 >> bit_position);
  }

  bit_position += 1;

  if (bit_position == 8) {
    strncat(message, &rx_byte, 1);
  }

  update_lcd = true;
}

void loop() {
  if (update_lcd) {
    //lcd.clear();
    update_lcd = false;
    lcd.setCursor(5, 1);
    lcd.print(message);
  }
}
