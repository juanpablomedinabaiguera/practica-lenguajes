/*En una fábrica se diseña en una línea de montaje un sistema de seguimiento el cual cuenta con 4 sensores
 ubicados en las distintas partes por las que el producto pasa y hace su proceso de producción. Tener en cuenta
 que cuando arribe recién va a estar en la parte 1. Cada sensor (cuando sense) enviará un 1 por su salida y un 0
 cuando no se sense. Se requiere hacer una solución programable para realizar el seguimiento del producto y
 mostrar por cual etapa va mediante un 7 segmentos. Cuando el producto terminé (10 segundos luego de que pase
 por la cuarta estación) deberá mostrarse una C de completado y titilando cada medio segundo. Cuando el personal
 detecte que el producto terminó el proceso, presionará un botón para sacar el estado de terminado y dejando un
 guión medio hasta que se sense que un producto empezó de nuevo la cadena de producción.*/
#include <Arduino.h>

int sensores[4] = {1, 2, 3, 4};
int puls = 5;
int segPines[7] = {6, 7, 8, 9, 10, 11, 12};
int sensor_activo;

int d7s[6][7] = {
    {0,1,1,0,0,0,0}, //1
    {1,0,1,1,0,1,1}, //2
    {1,0,0,1,1,1,1}, //3
    {0,1,1,0,0,1,1}, //4
    {1,0,0,1,1,1,0}, //C
    {0,0,0,0,0,0,1}, //-
};

volatile unsigned long t_previo_espera = 0;
unsigned long t_delay_espera = 10000; // 10 segundos

unsigned long t_previo_parpadeo = 0;
unsigned long t_delay_parpadeo = 500; // medio segundo

volatile bool guion_activo = false;

void IRAM_ATTR toggle() {
  // Solo tiene efecto si ya se cumplieron los 10s (o sea, si ya está la C)
  if (millis() - t_previo_espera >= t_delay_espera) {
    guion_activo = true;
  }
}

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(sensores[i], INPUT);
  }

  pinMode(puls, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(puls), toggle, FALLING);

  for (int i = 0; i < 7; i++) {
    pinMode(segPines[i], OUTPUT);
  }
  
}

void loop() {

  if (guion_activo) {
    for (int i = 0; i < 7; i++)
      digitalWrite(segPines[i], d7s[5][i]); // muestra "-"

    if (digitalRead(sensores[0])) {
      guion_activo = false;
      sensor_activo = 0;
      t_previo_espera = 0;
    }
    return;
  }

  for (int j = 0; j < 4; j++) {
    if (digitalRead(sensores[j]))
      sensor_activo = j;
  }

  switch (sensor_activo) {
    case 0:
      t_previo_espera = 0;
      for (int i = 0; i < 7; i++)
        digitalWrite(segPines[i], d7s[0][i]);
      break;

    case 1:
      for (int i = 0; i < 7; i++)
        digitalWrite(segPines[i], d7s[1][i]);
      break;

      case 2:
      for (int i = 0; i < 7; i++)
        digitalWrite(segPines[i], d7s[2][i]);
      break;

    case 3:
      if (t_previo_espera == 0) {
        t_previo_espera = millis();
      }

      if (millis() - t_previo_espera < t_delay_espera) {
        for (int i = 0; i < 7; i++)
          digitalWrite(segPines[i], d7s[3][i]);
      } else {
        if (millis() - t_previo_parpadeo >= t_delay_parpadeo) {
          t_previo_parpadeo = millis();

          if (digitalRead(segPines[0]) == LOW) {
            for (int i = 0; i < 7; i++) digitalWrite(segPines[i], d7s[4][i]);
          } else {
            for (int i = 0; i < 7; i++) digitalWrite(segPines[i], LOW);
          }
        }
      }
      break;

    default:
      break;
  }
}