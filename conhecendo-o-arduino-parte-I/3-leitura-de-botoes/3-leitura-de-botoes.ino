
const int botao = 2; // variável que guarda em que pino o botão está conectado.
const int led = 3; // em que pino o led está conectado.
int estadoBotao = 0; // variável para guardar o valor do estado do botão (pressionado ou não).

void setup() {                          
  Serial.begin(9600); // inicialização do monitor serial.
  pinMode(led, OUTPUT); // inicialização do pino do led como saída (OUTPUT).
  pinMode(botao, INPUT); // inicialização do pino do botão como entrada .  
}

void loop() {               
  estadoBotao = digitalRead(botao); // Lê o estado do botão (que pode ser 0 ou 1).
  
  if (estadoBotao == 1) { // Checa o estado do botão. Se estiver apertado (1):
    digitalWrite(led, 1); // acende o LED
    Serial.println("1"); // imprime "1" no monitor serial 
  } else { // Senão:
    digitalWrite(led, 0); // apaga o LED
    Serial.println("0"); // imprime "0" no monitor serial 
  }
}

