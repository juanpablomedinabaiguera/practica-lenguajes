/*En una casa de cuatro ambientes se tiene un sensor de movimiento para cada uno, dicho sensor cuenta con una
salida la cual se pondrá en alto cuando sense algo, pero que enviará un estado bajo en caso contrario. Se
requiere realizar una solución programable la cuál muestre por un display 7 segmentos el cuarto sensado
(teniendo en cuenta que cada cuarto será numerado). Cuando no se sense nada deberá mostrarse un guión medio
titilando cada un segundo. Tener en cuenta que habrá un botón el cuál servirá como una suerte de "visto",
el cual cuando sea presionado dejará de mostrarse el número de ambiente en donde se senso algún movimiento
para pasar al guión medio nuevamente.*/

#include <Arduino.h>
int sensores[4]={1,2,3,4};
int puls=5;
int pines_segmento[7]={6,7,8,9,10,11,12};
                     //a,b,c,d,e,f ,g
int d7s[5][7]={
                {0,0,0,0,0,0,1},    //-
                {0,1,1,0,0,0,0},    //1
                {1,0,1,1,0,1,1},    //2
                {1,1,1,1,0,0,1},    //3
                {0,1,1,0,0,1,1}     //4
               //a,b,c,d,e,f,g 
                };
unsigned long t_actual=0;
unsigned long t_previo = 0;
unsigned long t_delay = 1000;

bool guion = true;
volatile int cuarto_activo = 0;


void IRAM_ATTR sensor1() {
    cuarto_activo=1;
    
}

void IRAM_ATTR sensor2() {
    cuarto_activo=2;
    
}

void IRAM_ATTR sensor3() {
    cuarto_activo=3;
    
}

void IRAM_ATTR sensor4() {
    cuarto_activo=4;
    
}
void IRAM_ATTR pulsador() {
    cuarto_activo=0;
    
    }

void setup (){
    for(int i=0;i<4;i++){
        digitalWrite(sensores[i],INPUT);
    }

   attachInterrupt(digitalPinToInterrupt(sensores[1]), sensor1, RISING);
   attachInterrupt(digitalPinToInterrupt(sensores[2]), sensor2, RISING);
   attachInterrupt(digitalPinToInterrupt(sensores[3]), sensor3, RISING);
   attachInterrupt(digitalPinToInterrupt(sensores[4]), sensor4, RISING);

   pinMode(puls,INPUT_PULLDOWN);
   attachInterrupt(digitalPinToInterrupt(puls), pulsador, RISING);

   for(int i=0; i<7;i++)   pinMode(pines_segmento[i], OUTPUT);
}

void loop (){

    if (cuarto_activo==0){
        t_actual=millis();
                if(t_actual - t_previo >= t_delay){
                    t_previo = t_actual;
                    guion != guion;
                    if(guion){
                        for(int i=0;i<7;i++){
                            digitalWrite(pines_segmentos[i],d7s[0][i]);
                        }
                    }else{
                        for(int i=0;i<7;i++){
                            digitalWrite(pines_segmentos[i],LOW);
                        }
                    }
                }
    }else{
        for(int i=0;i<7;i++){
            digitalWrite(pines_segmento[i],d7s[cuarto_activo][i]);
        }
    }
}