/*
 * Detectar a presença de uma pessoa usando o sensor ultrassom. 
 * (Você também poderá utilizar um sensor de presença PIR que,
 * apesar de não ter sido explicado em nossa apostila, é muito 
 * simples de usar;
 */
 
#include <Ultrasonic.h> //Inclui biblioteca no código.
#define LIMITE 40

Ultrasonic ultrassom(8,7); // define o nome do sensor(ultrassom) 
//e onde esta ligado o trig(8) e o echo(7) respectivamente.
  
void setup(){  // Esta função "setup" roda uma vez quando a placa e ligada ou resetada
  Serial.begin(9600); //Habilita Comunicação Serial a uma taxa de 9600 bauds.  long distancia;  
}
 
void loop(){ // Função que se repete infinitamente quando a placa é ligada
  
  distancia = ultrassom.Ranging(CM); // ultrassom.Ranging(CM) retorna a distancia em                                
  // centímetros(CM) ou polegadas(INC)    
  
  if (distancia <= LIMITE && distancia > 0){ // Define as distâncias bases de verificação
    Serial.println("Pessoa Detectada!");
  }     
  delay(100);  
} 
