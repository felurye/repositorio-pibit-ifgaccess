/*
 * Detectar se está de noite através de um sensor de luz LDR;
 */

#define LIMITE 800

const int ldrPin = 0; //LDR no pino analígico A0
int ldrValor = 0; //Valor lido do LDR   

void setup() {  
  Serial.begin(9600); //Inicia a comunicação serial 
}   

void loop() {    
    ldrValor = analogRead(ldrPin); //ler o valor do LDR
    //O valor lido será entre 0 e 1023    
    
    if (ldrValor <= LIMITE){ //se o valor lido for menor ou igual à 800, escreve na tela "Noite!!" 
      Serial.println("Noite!!");  
    }
     
    delay(100); 
} 
