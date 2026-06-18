/*En una casa de cuatro ambientes se tiene un sensor de movimiento para cada uno, dicho sensor cuenta con una
salida la cual se pondrá en alto cuando sense algo, pero que enviará un estado bajo en caso contrario. Se
requiere realizar una solución programable la cuál muestre por un display 7 segmentos el cuarto sensado
(teniendo en cuenta que cada cuarto será numerado). Cuando no se sense nada deberá mostrarse un guión medio
titilando cada un segundo. Tener en cuenta que habrá un botón el cuál servirá como una suerte de "visto",
el cual cuando sea presionado dejará de mostrarse el número de ambiente en donde se senso algún movimiento
para pasar al guión medio nuevamente.*/

#include <arduino.h>

int sensores[4]={1,2,3,4};
int pulsador=5;
int pines_segmento[7]={6,7,8,9,10,11,12};
                     //a,b,c,d,e,f ,g
int d7s[5][7]={
                {0,1,1,0,0,0,0},    //1
                {1,0,1,1,0,1,1},    //2
                {1,1,1,1,0,0,1},    //3
                {0,1,1,0,0,1,1},    //4
                {0,0,0,0,0,0,1}     //-
               //a,b,c,d,e,f,g 
                };

unsigned long t_previo = 0;
unsigned long t_delay = 1000;
bool estado_guion = HIGH;

volatile int cuarto_activo = -1;
volatile bool flag = false;

void IRAM_ATTR toggle_sensor() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(sensores[i]) == HIGH) {
      cuarto_activo = i;
      flag = true;
    }
  }
}

void setup (){
    for(int i=0; i<4;i++){
        pinMode(sensores[i], INPUT);
        attachInterrupt(digitalPinToInterrupt(sensores[i]), toggle_sensor, RISING);
    }
    
    pinMode(pulsador,INPUT);
    
    for(int i=0; i<7;i++)   pinMode(sensores[i], OUTPUT);
    
}

void loop (){

    int t_actual = milis();

    if(flag){
        flag = false;
        for(int i=0;i<7;i++){
            digitalWrite(pines_segmento[i],d7s[cuarto_activo][i]);
        }
    }

    if(digitalRead(pulsador)) cuarto_activo == -1;        
    
    if(cuarto_activo == -1){
        if(t_actual - t_previo >= t_delay){
            t_previo = t_actual;
            estado_guion = !estado_guion;
            if(estado_guion){
                for(int i=0;i<7;i++){
                digitalWrite(pines_segmento[i],d7s[5][i]);
                }
            }else digitalWrite(pines_segmento[i],LOW);
        }   

    }
}