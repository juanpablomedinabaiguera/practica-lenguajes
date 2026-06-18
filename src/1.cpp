/*En una fábrica se diseña en una línea de montaje un sistema de seguimiento el cual cuenta con 4 sensores
 ubicados en las distintas partes por las que el producto pasa y hace su proceso de producción. Tener en cuenta
 que cuando arribe recién va a estar en la parte 1. Cada sensor (cuando sense) enviará un 1 por su salida y un 0
 cuando no se sense. Se requiere hacer una solución programable para realizar el seguimiento del producto y
 mostrar por cual etapa va mediante un 7 segmentos. Cuando el producto terminé (10 segundos luego de que pase
 por la cuarta estación) deberá mostrarse una C de completado y titilando cada medio segundo. Cuando el personal
 detecte que el producto terminó el proceso, presionará un botón para sacar el estado de terminado y dejando un
 guión medio hasta que se sense que un producto empezó de nuevo la cadena de producción.*/
 #include "Arduino.h"

int sens[4]={1,2,3,4};
int puls=5;
int pin_seg[7]={6,7,8,9,10,11,12};
int d7s[6][7]={
                {0,1,1,0,0,0,0},        //1
                {1,1,0,1,1,0,1},        //2
                {1,1,1,1,0,0,1},        //3
                {0,1,1,0,0,1,1},        //4
                {1,0,0,1,1,1,0},        //C
                {0,0,0,0,0,0,1}         //-
            };

volatile int sensor_activo=0;

bool c = true;

unsigned long t_actual=0;

unsigned long t_previo1=0;
unsigned long t_delay1=10000;

unsigned long t_previo2=0;
unsigned long t_delay2=500;

void IRAM_ATTR sensor1(){
    sensor_activo=1;
}

void IRAM_ATTR sensor2(){
    sensor_activo=2;
}

void IRAM_ATTR sensor3(){
    sensor_activo=3;
}

void IRAM_ATTR sensor4(){
    sensor_activo=4;
}

void IRAM_ATTR sepulsador(){
    sensor_activo=5;
}

void setup(){
    for(int i=0;i<4;i++){
        pinMode(sens[i],INPUT);
    }

    attachInterrupt(digitalPinToInterrupt(sens[1]), sensor1, RISING);
    attachInterrupt(digitalPinToInterrupt(sens[2]), sensor2, RISING);
    attachInterrupt(digitalPinToInterrupt(sens[3]), sensor3, RISING);
    attachInterrupt(digitalPinToInterrupt(sens[4]), sensor4, RISING);

    for(int i=0;i<7;i++){
        pinMode(pin_seg[7],OUTPUT);
    }

    pinMode(puls, INPUT_PULLUP);    
}

void loop(){
    switch(sensor_activo){
        case 0:
                for(int i=0;i<7;i++){
                    digitalWrite(pin_seg[i],d7s[5][i]);     //enciendo guion
                }
                break;

        case 1:
                for(int i=0;i<7;i++){
                    digitalWrite(pin_seg[i],d7s[0][i]);     //enciende 1
                }
                break;
        
        case 2:
                for(int i=0;i<7;i++){
                    digitalWrite(pin_seg[i],d7s[1][i]);     //enciende 2
                }
                break;
        
        case 3:
                for(int i=0;i<7;i++){
                    digitalWrite(pin_seg[i],d7s[2][i]);     //enciende 3
                }
                break;

        case 4:
                t_actual = millis();
                if(t_actual - t_previo1 >= t_delay1){
                    t_previo1 = t_actual;
                    for(int i=0;i<7;i++) digitalWrite(pin_seg[i],d7s[3][i]);     //enciende 4
                }else{
                    if(t_actual - t_previo2 >= t_delay2){
                        t_previo2 = t_actual;
                        c != c;
                        if(c){
                            for(int i=0;i<7;i++) digitalWrite(pin_seg[i],d7s[4][i]);
                        }else{
                            for(int i=0;i<7;i++) digitalWrite(pin_seg[i],LOW);
                        }
                    }
                }
                
                break;
                
    }
}