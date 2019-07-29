#include <LiquidCrystal.h>     //inclui biblioteca no programa 
 
LiquidCrystal lcd(2,3,4,5,6,7);
 /*Cria objeto lcd da classe LiquidCrystal
RS     2
Enable 3
DB4    4
DB5    5
DB6    6
DB7    7
*/
 
//Cria um smile
byte smile[8] = {
  B11111,
  B00000,
  B01010,
  B00000,
  B10001,
  B01110,
  B00000,
  B00100,
};
 
//Cria outro smile
byte smile2[8] = {
  B00000,
  B00000,
  B01010,
  B01010,
  B00000,
  B10001,
  B11111,
  B00000,
};
 
void setup(){
  lcd.begin(16,2);            //Inicializa display de 2 linhas x 16 colunas
  lcd.createChar(0, smile);   //Cria o smile e o associa ao 0
  lcd.createChar(1, smile2);  //Cria o smile2 e o associa ao 1
  lcd.home();                 //Posiciona cursor no canto superior esquerdo
  lcd.print("3 ");            //Executa uma pequena contagem regressiva
  delay(500);
  lcd.print("2 ");
  delay(500);
  lcd.print("1 ");
  delay(500);
  lcd.clear();                //Limpa a tela do LCD
  lcd.print("Vida de Silício");  //Escreve Vida de Silício
  lcd.setCursor(6,1);         //Posiciona o cursor na posição (6,1)
  lcd.write(byte(0));         //Escreve o smile
  lcd.setCursor(8,1);         //Posiciona o cursor na posição (8,1)
  lcd.write(1);               //Escreve smile2
}
 
void loop(){
 
}
