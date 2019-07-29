/*
 * Um alarme, usando o buzzer, deverá tocar, caso a 
 * temperatura do LM35 seja muito alta;
*/

const int buzzer= 9;
const int LM35 = A0; // Define o pino que lera a saída do LM35 
float temperatura = 0; // Variável que armazenará a temperatura medida  
#define LIMITE 40 
#define FREQUENCIA 261.63

void setup(){ //Função que será executada uma vez quando ligar ou resetar o Arduino 
  Serial.begin(9600); // inicializa a comunicação serial 
}    

  
void loop() { //Função que será executada continuamente
    temperatura = (float(analogRead(LM35))*5/(1023))/0.01; //Faz a leitura do sensor, convertendo para float e logo em seguida faz
    //calculos para exibir o valor em Celsius.

    if(temperatura > LIMITE){
      tone(buzzer, FREQUENCIA, 250);
    }else{
      noTone(buzzer);
    }
     
    delay(1000); 
}
