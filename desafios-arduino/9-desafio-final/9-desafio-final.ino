/*
 * Ter um display LCD que mostrará os valores lidos em cada sensor, se o
 * alarme está ligado ou desligado e o motivo do alarme, caso dispare.
*/

#include <LiquidCrystal.h> //Biblioteca do LCD.
#include <Ultrasonic.h>    //Biblioteca do Sensor de Presença HC.
#include <dht.h>           //Biblioteca DHT11.

/* Inicio das declarações das variáveis que fazem referencia aos pinos*/
Ultrasonic ULTRASSOM(12, 11); // Define o nome do sensor(ULTRASSOM) e onde esta ligado o trig(12) e o echo(11) respectivamente.
dht DHT;                      // Cria um objeto da classe dht uint32_t
LiquidCrystal LCD(2, 3, 4, 5, 6, 7);
/*Cria objeto LCD da classe LiquidCrystal
RS     2
Enable 3
DB4    4
DB5    5
DB6    6
DB7    7
*/

const int BUZZER = 9;
const int LED = 13;
const int LDR = A0;
const int LM35 = A1;
const int BOTAO = 10;
/* Fim das declarações das variáveis que fazem referencia aos pinos*/

/*Inicio das definições de valores de referência de limites*/
#define LIMITE_TEMPERATURA 40    //Limite para Temperatura.
#define FREQUENCIA_BUZZER 261.63 //Frequência do Buzzer.
#define LIMITE_LUMINOSIDADE 800  //Limite de Luminosidade.
#define LIMITE_DISTANCIA 40      // Limite de Distancia.
/*Fim das definições de valores de referência de limites*/

/*Inicio das declarações de variáveis de controle*/
int luminosidade = 0;  //Valor lido do LDR.
int funcaoA = 0;       //Valor instantaneo enviado pelo botão.
int funcaoB = 0;       //Valor guardado do botão.
int estadoBotao = 0;   //Guarda o valor 0 ou 1 (HIGH ou LOW).
float temperatura = 0; //Variável que armazenará a temperatura medida.
int distancia = 0;     //Variável que armazenará a distancia medida pelo HC.
/*Fim das declarações de variáveis de controle*/

void setup(){
  LCD.begin(16, 2);        //Inicializa display de 2 linhas x 16 colunas
  pinMode(BUZZER, OUTPUT); //Define pino do BUZZER como saída.
  pinMode(LED, OUTPUT);    //Define o pino do LED como saída.
  pinMode(BOTAO, INPUT);   //Define o pino do BOTAO com entrada.
}

void loop(){
  /*Inicio das leituras dos Sensores*/
  temperatura = (float(analogRead(LM35)) * 5 / (1023)) / 0.01;
  //Faz a leitura do sensor, convertendo para float e logo em seguida faz
  //calculos para exibir o valor em Celsius.

  distancia = ULTRASSOM.Ranging(CM);
  //ULTRASSOM.Ranging(CM) retorna a distancia em centímetros(CM) ou polegadas(INC).

  DHT.read11(A2);
  //Chama método de leitura da classe dht, com o pino de transmissão de dados ligado no pino A2.

  luminosidade = analogRead(LDR);
  //ler o valor do LDR. O valor lido será entre 0 e 1023.
  /*Fim das leituras dos Sensores*/

  /*Inicio da escrita no LCD com valores dos Sensores*/
  LCD.setCursor(0, 0); //Posiciona o cursor na posição (0, 0).
  LCD.print("Temp: ");
  LCD.print(temperatura);
  LCD.print("C Umid: ");
  LCD.print(DHT.humidity);
  LCD.print(" %% Lum: ");
  LCD.print(luminosidade);
  LCD.print("Dist: ");
  LCD.print(distancia);
  LCD.print("CM");
  for (int i = 0; i < 40; i++)  {
    lcd.scrollDisplayLeft();
    delay(80);
  }
  /*Fim da escrita no LCD com valores dos Sensores*/

  /*Inicio do condicional para ligar ou desligar o led com base no valor lido de LDR*/
  if (luminosidade <= LIMITE_LUMINOSIDADE){ //Se o valor lido for menor ou igual à 800, liga o LED.
    digitalWrite(LED, HIGH);
  }
  else{ //Senão, permanece desligado.
    digitalWrite(LED, LOW);
  }
  /*Fim do condicional para ligar ou desligar o led com base no valor lido de LDR*/

  /*Inicio do condicional para ler o estado do botao, para poder fazer o controle de ligar e desligar o alarme*/
  funcaoA = digitalRead(BOTAO); //Ler o valor enviado pelo botão: "HIGH" ou "LOW".

  if ((funcaoA == HIGH) & amp; &amp; (funcaoB == LOW)){
    estado = 1 - estado;
    delay(500); // Tempo apertando o botão.
  }
  funcaoB = funcaoA;
  /*Fim do condicional para ler o estado do botao, para poder fazer o controle de ligar e desligar o alarme*/

  /*Inicio da condicional para se o alarme estiver ligado ou não*/
  if (estado == 1){
    LCD.setCursor(0, 1);      //Posiciona o cursor na posição (0, 1).
    LCD.print("Alarme: ON "); //Escreve no LCD o estado do alarme, que nesse caso está ligado.

    /*Inicio da verificação se algo foi detectado*/
    if (distancia <= LIMITE_DISTANCIA && distancia > 0){ //Caso seja detectado uma pessoa ou objeto entre 0 e a distacia limite, o alarme é acionado.
      tone(BUZZER, 200, 6000);
      LCD.print("PRESENÇA!!");
      delay(5000);
    }
    else{
      noTone(BUZZER);
    }
    /*Fim da verificação se algo foi detectado*/

    /*Inicio da verificação da temperatura, para caso de incendio*/
    if (temperatura > LIMITE_TEMPERATURA){ //Caso a temperatura seja maior que o limite, o alarme é acionado.
      tone(BUZZER, FREQUENCIA_BUZZER);
      LCD.print("TEMPERATURA!!");
      delay(5000);
    }
    else{
      noTone(BUZZER);
    }
    /*Fim da verificação da temperatura, para caso de incendio*/
  }
  else{ //Caso o alarme esteja desligado, escreve na tela seu estado "OFF"
    LCD.print("Alarme: OFF");
  }
  /*Fim da condicional para se o alarme estiver ligado ou não*/

  delay(100);
}