int led = 3;

void interrupcao(){
  digitalWrite(led, HIGH); // Liga o LED (HIGH = nível lógico alto).
  delay(5000);
}

// Esta função "setup" roda uma vez quando a placa e ligada ou resetada.
void setup() {
 pinMode(led, OUTPUT); // Configura o pino do led (digital) como saída.
 attachInterrupt(0, interrupcao, RISING); //Configurando a interrupção.
}

// Função que se repete infinitamente quando a placa é ligada.
void loop() {
  digitalWrite(led, HIGH); // Liga o LED (HIGH = nível lógico alto).
  delay(1000); // Espera um segundo.
  digitalWrite(led, LOW); // Desliga o LED (LOW = nível lógico baixo).
  delay(1000); // Espera um segundo.
}

/*  =============== EXPLICAÇÃO ===============   */

/*
Esse programa em seu funcionamento padrão ocorre apenas um blink, que nada mais é que o led acender e apagar repetidamente,
mas assim que o botão é pressionado a função attachInterrupt, configurada no setup é ativada, pois o botão mudou
o seu estado, de 0V para 5V, occorrendo isso o led permanece ligado durante 5 segundo (5000 milisegundos), isso porque foi
configurado na função interrupcao que é chamada no attachInterrupt , e depois volta ao seu funcionamento padrão.
*/

