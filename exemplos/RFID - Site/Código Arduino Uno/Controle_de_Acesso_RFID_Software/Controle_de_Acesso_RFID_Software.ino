/*

   CONTROLE DE ACESSO


   Desenvolvido por  >>>>>>    BGautomacoes    <<<<<<<<

   Canal YouTube
   https://www.youtube.com/channel/UCV0Izow6n1wyt03qW1vb9yA?view_as=subscriber

   Sistema opera em conjunto com software e Banco de Dados

   obs: Banco de dados deve estar dentro da pasta em que foi deixada o software do sistema


   SCA - Pino 10
   SCK - Pino 13 e em paralelo o led branco
   MOSI - Pino 11
   MISO - Pino 12
   IRQ - Nao utilizado
   Reset - Pino 9
   VCC - 3.3v    -      Não utilizar 5V pois queima o módulo


   Led Vermelho - Pino 2  > Acesso negado
   Led Verde    - Pino 3  > Acesso permitido


*/



#include <AddicoreRFID.h>
#include <SPI.h>
String readString;
#define  uchar unsigned char
#define uint  unsigned int
uchar fifobytes;
uchar fifoValue;
AddicoreRFID Meu_Sensor_RFID; // Cria um modulo RFID
const int AtivaRFID = 10;
const int Reset = 9;
#define MAX_LEN 16

void setup()
{
  Serial.begin(9600);                   // Inicia serial em 9600
  SPI.begin(); // Inicia a biblioteca
  pinMode(AtivaRFID, OUTPUT);           // Define o pino digital 10 como saída para conectá-lo ao RFID / ATIVAR
  digitalWrite(AtivaRFID, LOW);         // Ativa o leitor RFID
  pinMode(Reset, OUTPUT);               // Seta o pino para não resetar, em LOW reseta
  digitalWrite(Reset, HIGH);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(2, 0);
  digitalWrite(3, 0);
  Meu_Sensor_RFID.AddicoreRFID_Init();  // Inicia RFID
}

void loop()
{
  char c = Serial.read();
  if (c == 's')
  {
    digitalWrite(3, HIGH);
    digitalWrite(2, LOW);
    delay(2500);
    digitalWrite(3, LOW);
  }
  if (c == 'n')
  {
    digitalWrite(2, 0);
    for (int a = 0; a < 10; a++)
    {
      digitalWrite(2, 1);
      delay(100);
      digitalWrite(2, 0);
      delay(100);
    }
  }
  uchar i, tmp, checksum1;
  uchar status;
  uchar str[MAX_LEN];
  uchar RC_size;
  uchar blockAddr; // Endereço de bloco operação de seleção 0 a 63
  String mynum = "";
  str[1] = 0x4400;
  // Encontre tag's , tipo de tag de retorno
  status = Meu_Sensor_RFID.AddicoreRFID_Request(PICC_REQIDL, str);
  // Tag retorna numero de série de 4 Bytes
  status = Meu_Sensor_RFID.AddicoreRFID_Anticoll(str);
  if (status == MI_OK)
  {
    Serial.print(str[0]);     // Primeiro byte da tag
    Serial.print(str[1]);     // Segundo byte da tag
    Serial.print(str[2]);     // Terceiro byte da tag
    Serial.print(str[3]);     // Quarto byte da tag
    Serial.println("*");
    delay(800);
  }
  Meu_Sensor_RFID.AddicoreRFID_Halt();      // Comando para hibernar a tag
}

