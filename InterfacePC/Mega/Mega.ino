//#include <Wire.h> // Protocolo I2C
#include <AFMotor.h>

AF_DCMotor motor1(2); 

// instrucao_rx = Diferencia quais sãos os valores (valor1, valor2 e valor3)
// valor1_str,valor2_str e valor3_str = Valores das resistências requeridas


String instrucao_rx, valor1_str, valor2_str, valor3_str, leitura_rapida, velocidade_str, str_temp; //sentido_str;
String valores; // h
int qtd1,qtd2,qtd3; //velocidade
float r1, r2, r3;

// Botão para iniciar o processo de leitura, para implementar depois, o algoritimo
// para comparar com o valor desejado
const int botao = 30;
int estadoBotao = 0;



const int analogPin = A11; // Porta analogica para leitura
const int pin_qtd = 5; // Quantidade de resistores de referência utilizado + 1
const int qtd_amostra = 20; // Quantidade de leituras que serão feitas para cada resistor

const int pin[pin_qtd] = { 42, 38, 36, 34, 32 }; // Onde os resistores de referência estão conectado
//const float res_referencia[pin_qtd] = { 62.0, 221.0, 9780.0, 4620.0, 327.0 };
//const float res_referencia[pin_qtd] = { 9710.0, 323.0, 61.3, 987.0, 4580.0, 218.0 }; // Os valores dos resistores de referência
const float res_referencia[pin_qtd] = { 9810.0, 63.1, 999.0, 4632.0, 222.3};
float ref; // Variável para guardar o valor de referência utilizado.



void setup() {
	Serial.begin(9600);
	//Wire.begin(8); //Nano - 8
	//pinMode(13, OUTPUT);

	for (int i = 0; i<pin_qtd; i++) {
		pinMode(pin[i], OUTPUT); 
		digitalWrite(pin[i], LOW);
		pinMode(pin[i], INPUT); 
	}

 motor1.setSpeed(200); 
 pinMode(botao,INPUT);
 instrucao_rx = "leitura";
}

float tensaoMedia() {
	float total = 0.0;
	for (int i = 0; i<qtd_amostra; i++) {
		delay(0);
		total += float(analogRead(analogPin));

       /* Serial.print("Tensao = ");
        Serial.println(analogRead(analogPin));
        Serial.print("Pino utilizado: ");
        Serial.println(teste);
        Serial.println();*/
	}
        /*Serial.print("Tensao Total = ");
        Serial.println(5.0*total / (qtd_amostra*1023.0));
        Serial.println();*/
	return 5.0*total / (qtd_amostra*1023.0);
        
}

float calcularResistencia(float r, float v) {
	return r / (5.0 / v - 1.0);
}

void loop() {

//FORWARD (move o motor no sentido horário), BACKWARD (sentido inverso/anti-horário) ou RELEASE, que determina a parada do motor :

  estadoBotao = digitalRead(botao);

  if (estadoBotao == HIGH) {
  //  serial.println("Motor em funcionamento");
  motor1.run(FORWARD); 
  delay(2000);
  //delay (1000);
  motor1.run(RELEASE); // Para
  delay(500);
  //delay(500);
 
  
  } else {
  motor1.run(RELEASE); 
     
  }
	
}
