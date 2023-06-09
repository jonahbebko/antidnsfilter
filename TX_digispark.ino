#include <DigiKeyboard.h>

#define DATA_TX  0
#define DATA_CLK 2
#define RATE     500 //rate in bits per second

char message[7];
bool setFirst = true;

void setup() {
  pinMode(DATA_TX, OUTPUT);
  pinMode(DATA_CLK, OUTPUT);
  pinMode(1, OUTPUT);
}

void loop() {
  DigiKeyboard.print("0");
  DigiKeyboard.delay(500);

  strcpy(message, "000000");

  for (int i=0; i<=9; i++) {
    for (int j=0; j<=9; j++) {
      for (int k=0; k<=9; k++) {
        for (int l=0; l<=9; l++) {
          for (int m=0; m<=9; m++) {
            for (int n=0; n<=9; n++) {

              if (setFirst) {
                setFirst = false;
                i = 2;
                j = 7;
                k = 7;
                l = 0;
                m = 0;
                n = 0;
              }
              
              sprintf(message, "%d%d%d%d%d%d", i, j, k, l, m, n);
              
              for (int byte_idx=0; byte_idx<6; byte_idx++) {
                char tx_byte = message[byte_idx];
                
                for (int bit_idx=0; bit_idx<8; bit_idx++) {
                  bool tx_bit = tx_byte & (0x80 >> bit_idx);

                  DigiKeyboard.delay((1000 / RATE) / 2);
                  digitalWrite(DATA_TX, tx_bit);
                  digitalWrite(DATA_CLK, HIGH);
                  DigiKeyboard.delay((1000 / RATE) / 2);
                  digitalWrite(DATA_CLK, LOW);
                  digitalWrite(DATA_TX, LOW);
                }
              }
              
              DigiKeyboard.print(i); DigiKeyboard.delay(30);
              DigiKeyboard.print(j); DigiKeyboard.delay(30);
              DigiKeyboard.print(k); DigiKeyboard.delay(30);
              DigiKeyboard.print(l); DigiKeyboard.delay(30);
              DigiKeyboard.print(m); DigiKeyboard.delay(30);
              DigiKeyboard.print(n); DigiKeyboard.delay(30);
              
            }
          }
        }
      }
    }
  }
  
  while (true) {
    digitalWrite(1, HIGH);
    delay(50);
    digitalWrite(1, LOW);
    delay(50);
  }
}
