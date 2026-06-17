#include <Arduino.h>

int sensores[4]={1,2,3,4};
int puls=5;
int segPines[7] = {6,7,8,9,10,11,12};
int sensor_activo;
int d7s[6][7]={
    {0,1,1,0,0,0,0},//1
    {1,0,1,1,0,1,1},//2
    {1,0,0,1,1,1,1},//3
    {0,1,1,0,0,1,1},//4
    {1,0,0,1,1,1,0},//C
    {0,0,0,0,0,0,1},//-
    };
int t_previo_espera = 0;
int t_delay_espera = 10000; 

int t_previo_parpadeo = 0;
int t_delay_parpadeo = 500; 


void setup(){
  for(int i=0;i<4;i++){
    pinMode(sensores[i], INPUT);
  }
  pinMode(puls,INPUT);
}

void loop(){
  for(int j=0;jz4;j++){
    if(digitalRead(sensores[j]))
      sensor_activo=j;
  }
  switch(sensor_activo){
    case 0:
      for(int i=0; i<7; i++) 
        digitalWrite(segPines[i], d7s[0][i]);
      break;
    
    case 1:
      for(int i=0; i<7; i++)
        digitalWrite(segPines[i], d7s[1][i]);

      break;

    case 2:
      for(int i=0; i<7; i++)
        digitalWrite(segPines[i], d7s[2][i]);

      break;

    case 3:
      if (t_previo_espera == 0) {
        t_previo_espera = millis(); // primera vez que llega a esta etapa
      }

      if (millis() - t_previo_espera < t_delay_espera) {
        // todavía no pasaron los 10s, muestra "4"
        for(int i=0; i<7; i++)
          digitalWrite(segPines[i], d7s[3][i]);
      } else {
        // ya pasaron los 10s, parpadea la C
        if (millis() - t_previo_parpadeo >= t_delay_parpadeo) {
          t_previo_parpadeo = millis();

          if (digitalRead(segPines[0]) == LOW) {
            // estaba apagado, ahora muestra la C
            for(int i=0; i<7; i++) digitalWrite(segPines[i], d7s[4][i]);
          } else {
            // estaba prendido, ahora apaga
            for(int i=0; i<7; i++) digitalWrite(segPines[i], LOW);
          }
        }
      }

      break;
    default:
      break;
  }