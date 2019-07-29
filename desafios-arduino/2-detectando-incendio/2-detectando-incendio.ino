/*
 * Detectar um incêndio através da temperatura muito alta 
 * da casa usando um LM35.
 */

 #define LIMITE 40 
 
const int LM35 = A0; // Define o pino que lera a saída do LM35 
float temperatura = 0; // Variável que armazenará a temperatura medida  

void setup(){ //Função que será executada uma vez quando ligar ou resetar o Arduino 
  Serial.begin(9600); // inicializa a comunicação serial 
}    
  
void loop() { //Função que será executada continuamente
  
    temperatura = (float(analogRead(LM35))*5/(1023))/0.01; //Faz a leitura do sensor, convertendo para float e logo em seguida faz
    //calculos para exibir o valor em Celsius.

    if(temperatura > LIMITE){
      Serial.println("Temperatura alta!! Incêndio!!!!");
    }
    delay(1000); 
}
