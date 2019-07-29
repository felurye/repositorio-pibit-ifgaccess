/*
 * Possuir um botão para ligar e desligar um alarme;
 */

/*
 * Possuir um botão para ligar e desligar um alarme;
*/

const int botao = 2; // variável que guarda em que pino o botão está conectado.
const int buzzer = 9; // em que pino o led está conectado.
int estadoBotao = 0; // variável para guardar o valor do estado do botão (pressionado ou não).
int controle= 0;
void interrupcao(){
  if(controle==0){
    noTone(buzzer);
    controle = 1;
  }else{
  tone(buzzer, 200);
    controle = 0;
  }
}

void setup() {                          
  Serial.begin(9600); // inicialização do monitor serial.
  pinMode(9,OUTPUT); //define o pino 9 como saída 
  pinMode(botao, INPUT); // inicialização do pino do botão como entrada.
  attachInterrupt(0, interrupcao, RISING);  
}

void loop() {        
    estadoBotao = digitalRead(botao);
    Serial.println(estadoBotao);
}
