unsigned int valorLido; //declaração de variável.

// Esta função "setup" roda uma vez quando a placa e ligada ou resetada.
void setup(){
  Serial.begin(9600); //Inicia porta serial e define a velocidade de transmissão. 
} 

// Função que se repete infinitamente quando a placa é ligada.
void loop(){  
  valorLido = analogRead(A0); //Atribui a variável o valor lido do pino passado por parâmetro.
  Serial.println(valorLido); //Imprime no monitor serial o valor lido.
  delay(1000); // Espera um segundo.
}
