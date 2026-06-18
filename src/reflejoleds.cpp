#include <Arduino.h>

int leds[5] = {0, 2, 4, 5, 18};
int puls = 25;
int cont = 0;

volatile bool flag = false;
volatile bool acierto = false;
volatile int j = 0;
volatile uint32_t t = 1000;

void IRAM_ATTR toggle() {
  flag = true;
  if(j == 2) {acierto = true;
  cont++;
  t = t * 0.7;}
  else{acierto = false;
  cont=0;
  t=1000;
  }
}

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(puls, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(puls), toggle, FALLING);
  Serial.begin(115200);
}

void loop() {
  for (j = 0; j < 5; j++) {
    digitalWrite(leds[j], HIGH);
    delay(t);
    digitalWrite(leds[j], LOW);

    if (flag) {
      flag = false;
      if (acierto) {
        Serial.print("muy bien pebe, aciertos:");
        Serial.println(cont);
      } else {
        Serial.print("serapio");
      }
    }
  }
}