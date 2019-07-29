/*
 * Configura um servidor na ESP-01S; a ideia é, pelo navegador, permitir:
 *   - controlar um atuador (liga ou desliga LED da Arduino);
 *   - ler um sensor (abre uma página com valor de leitura de conversão AD).
 */

#include "SoftwareSerial.h"

#define TIMEOUT 5000 // mS
#define LED 13

SoftwareSerial mySerial(6, 7); // RX, TX
const int button = 8;
const int LDR = A0;
int LDR_value = 0;
 
void setup()
{
 pinMode(LED,OUTPUT);
 
 Serial.begin(9600);
 mySerial.begin(9600);
 SendCommand("AT+RST", "Ready");
 delay(5000);

 SendCommand("AT+CWMODE=1","OK");
 SendCommand("AT+CIFSR", "OK");
 SendCommand("AT+CIPMUX=1","OK");
 SendCommand("AT+CIPSERVER=1,80","OK");
}
 
void loop(){
 LDR_value = analogRead(LDR);
  
 String IncomingString="";
 boolean StringReady = false;
 
 while (mySerial.available()){
   IncomingString=mySerial.readString();
   StringReady= true;
  }
 
  if (StringReady){
    Serial.println("Received String: " + IncomingString);
  
  if (IncomingString.indexOf("LED=ON") != -1) {
    digitalWrite(LED,HIGH);
    mySerial.println("AT+CIPSEND=0,18");
    delay(100);
    mySerial.println("<h1>LED Aceso</h1>");
    delay(1000);
    SendCommand("AT+CIPCLOSE=0","OK");
   }
 
  if (IncomingString.indexOf("LED=OFF") != -1) {
    digitalWrite(LED,LOW);
    mySerial.println("AT+CIPSEND=0,20");
    delay(100);
    mySerial.println("<h1>LED Apagado</h1>");
    delay(1000);
    SendCommand("AT+CIPCLOSE=0","OK");
   }

  if(IncomingString.indexOf("LDR") != -1)    {
    char valueStr[4];
    sprintf(valueStr,"%04d",LDR_value);
    Serial.println(valueStr);
    mySerial.println("AT+CIPSEND=0,4");
    delay(100);
    mySerial.println(valueStr);
    delay(1000);
    SendCommand("AT+CIPCLOSE=0","OK");
   }
   
  }
 }
 
boolean SendCommand(String cmd, String ack){
  mySerial.println(cmd); // Send "AT+" command to module
  if (!echoFind(ack)) // timed out waiting for ack string
    return true; // ack blank or ack found
}
 
boolean echoFind(String keyword){
 byte current_char = 0;
 byte keyword_length = keyword.length();
 long deadline = millis() + TIMEOUT;
 while(millis() < deadline){
  if (mySerial.available()){
    char ch = mySerial.read();
    Serial.write(ch);
    if (ch == keyword[current_char])
      if (++current_char == keyword_length){
       Serial.println();
       return true;
    }
   }
  }
 return false; // Timed out
}
