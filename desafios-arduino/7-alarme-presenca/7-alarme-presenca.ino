/*
 * Esse alarme também deve tocar, caso acionado e uma pessoa seja detectada;
 */

#include <Ultrasonic.h> //Inclui biblioteca no código.
Ultrasonic ultrassom(8,7); // define o nome do sensor(ultrassom) 
//e onde esta ligado o trig(8) e o echo(7) respectivamente.

const int buzzer 9;
  
void setup() {  // Esta função "setup" roda uma vez quando a placa e ligada ou resetada
  Serial.begin(9600); //Habilita Comunicação Serial a uma taxa de 9600 bauds.  long distancia;  
  pinMode(buzzer, OUTPUT); //Define pino do buzzer como saída.
}
 
void loop() { // Função que se repete infinitamente quando a placa é ligada
  
  distancia = ultrassom.Ranging(CM); // ultrassom.Ranging(CM) retorna a distancia em                                
  // centímetros(CM) ou polegadas(INC)    
  
  if (distancia <= 40 && distancia > 0) { // Define as distâncias bases de verificação
    tone(buzzer, 200, 6000);
  } else{
    noTone(buzzer); 
  }
    
  delay(100);  
} 
