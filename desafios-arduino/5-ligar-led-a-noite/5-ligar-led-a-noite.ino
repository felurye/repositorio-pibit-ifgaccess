/*
 * Acender 1 LED de alta intensidade, caso seja noite;
 */


int led= 13; //Pino do LED.
int ldrPin = 0; //LDR no pino analígico 8 int 
int ldrValor = 0; //Valor lido do LDR   

void setup() {  
  pinMode(led, OUTPUT);
  Serial.begin(9600); //Inicia a comunicação serial 
}   


void loop() {    
    ldrValor = analogRead(ldrPin); //ler o valor do LDR
    //O valor lido será entre 0 e 1023    
    
    if (ldrValor<= 800){ //se o valor lido for menor ou igual à 800, liga o led.
        digitalWrite(led, HIGH);
    }else{ 
      digitalWrite(led, LOW);  
    }  
    delay(100); 
} 
