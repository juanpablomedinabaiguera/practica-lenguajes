/*El hijo de puta de Freddy le pinto salir de la pizzeria y abrió cuatro telos. En uno de ellos quiere hacer una solucion programable
  en la cual se enciendan 4 luces (2 en los laterales y 2 en cada mesita de luz) en una habitacion. Tambien quiere agregar un boton
  para configurar que luces se prenderan, osea 3 modos:
                                                        1:Todas encendidas
                                                        2:Solo las laterales
                                                        3:Solo las de la mesita de luz
  Y como es recontra ambicioso, tambien quiere un boton para apagar todas las luces.
  Pero alto, alto, alto, para embarrarla aun mas, se deberar mostrar a traves de un display de siete segmentos en cual configuracion}
  se esta, y cuando esten apagadas todas las luces, se mostrara una "D" titilando cada medio segundo
  
  Lo que mostrara el display sera lo siguiente:
                                                A:Todas las luces prendidas
                                                b:Solo las luces de los laterales
                                                C:Solo las luces de la mesita de luz
                                                d:Todas las luces apagadas
  vamos a ver si satisfaces a Fredy, sino te metera en un traje*/

#include <Arduino.h>

int luces[4] = {1,2,3,4};
int puls_config = 5;
int puls_off = 6;
int pines_segmentos[7] = {7,8,9,10,11,12,13};
int d7s[4][7] = {
                  {1,1,1,0,1,1,1},    //A
                  {0,0,1,1,1,1,1},    //b
                  {1,0,0,1,1,1,0},    //C
                  {0,1,1,1,1,0,1}     //d
                  };

unsigned long t_delay = 500;
unsigned long t_previo = 0;
unsigned long t_actual = 0;

volatile int config = 0;
volatile int off = 0;

bool light = true;

void IRAM_ATTR configuracion(){
    config = config + 1;
    if(config > 3) config = 0;
}

void IRAM_ATTR apagado(){
    off = 1;
}

void setup (){

    for(int i = 0 ; i < 4 ; i++) pinMode(luces[i], OUTPUT);
    for(int i = 0 ; i < 7 ; i++) pinMode(pines_segmentos[i], OUTPUT);

    pinMode(puls_config, INPUT_PULLUP);
    pinMode(puls_off, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(puls_config), configuracion, RISING);
    attachInterrupt(digitalPinToInterrupt(puls_off), apagado, RISING);
}

void loop(){
    if(off == 0){
        switch(config){
            case 0:
                    for(int i = 0 ; i < 4 ; i++) digitalWrite(luces[i], HIGH);
                    for(int i = 0 ; i < 7 ; i++) digitalWrite(pines_segmentos[i], d7s[0][i]);       //todas las luces encendidas
                    break;
            
            case 1:
                    for(int i = 0 ; i < 2 ; i++) digitalWrite(luces[i], HIGH);
                    for(int i = 0 ; i < 7 ; i++) digitalWrite(pines_segmentos[i], d7s[1][i]);       //aca yo dije que las luces 1 y 2 son 
                    break;                                                                          //luces laterales. Sin embargo puede
                                                                                                    //ser alreves
            case 2:
                    for(int i = 2 ; i < 4 ; i++) digitalWrite(luces[i], HIGH);
                    for(int i = 0 ; i < 7 ; i++) digitalWrite(pines_segmentos[i], d7s[2][i]);       //⬆⬆⬆ lo mismo para aca ⬆⬆⬆
                    break;

            default:
                    break;
        }
    }else{
            t_actual = millis();
            for(int i = 0 ; i < 4 ; i++) digitalWrite(luces[i], LOW);
            if(t_actual - t_previo >= t_delay){
                t_previo = t_actual;
                light != light;
                if(light){
                    for(int i = 0 ; i < 7 ; i++) digitalWrite(pines_segmentos[i], d7s[3][i]);
                }else{
                    for(int i = 0 ; i < 7 ; i++) digitalWrite(pines_segmentos[i], LOW);
                }
            }
    }
}

