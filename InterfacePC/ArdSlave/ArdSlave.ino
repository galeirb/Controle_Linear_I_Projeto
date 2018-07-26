#include <Wire.h>

const int analogPin = A7;
const int pin_qtd = 6;
const int qtd_amostra = 10;
String instrucao_rx;

const int pin[pin_qtd] = { 2, 3, 4, 5, 6, 7 };
const float r1[pin_qtd] = { 62.0, 221.0, 9780.0, 4620.0, 327.0 };
float ref;

char c;
int x;


void setup() {
	Serial.begin(9600);
	Wire.begin(15); // MEGA - 15
	Wire.onReceive(receiveEvent); //Recep��o dos dados (chama fun��o auxiliar)
  
	for (int i = 0; i<pin_qtd; i++) {
		pinMode(pin[i], OUTPUT);
		digitalWrite(pin[i], LOW);
		pinMode(pin[i], INPUT);
	}
}

float tensaoMedia() {
	float total = 0.0;
	for (int i = 0; i<qtd_amostra; i++) {
		delay(0);
		total += float(analogRead(analogPin));
	}
	return 5.0*total / (qtd_amostra*1023.0);
}

float calcularResistencia(float r, float v) {
	return r / (5.0 / v - 1.0);
}

void receiveEvent(int howMany)
{
  while (1 < Wire.available()) //Loop para receber toda String de dados
  {
    if (Wire.read() == "1"); {
    	Serial.print("Deu certo");           //Imprime na Serial
    }  

    if (Wire.read() == "1")
  	{
  		Serial.print("Fechado"); 
  	}  
    
  }
 	 
}

void loop() {
	if (Serial.available()) {
		char inst = Serial.read();
		if (inst == ',') {

			if (instrucao_rx == "leitura") {
				float minimo = 2.5;
				float resistencia = 100000000.0;

				for (int i = 0; i<pin_qtd; i++) {
					pinMode(pin[i], OUTPUT);
					digitalWrite(pin[i], HIGH);
					float v = tensaoMedia();
					digitalWrite(pin[i], LOW);
					pinMode(pin[i], INPUT);
					float diferenca = abs(v - 2.5);

					if (5.0 > v && diferenca < minimo) {
						minimo = diferenca;
						resistencia = calcularResistencia(r1[i], v);
						ref = r1[i];
					}
				}
				Serial.print("Resistencia = ");
				Serial.println(resistencia);
				Serial.print("Referencia utilizada: ");
				Serial.println(ref);
				Serial.println();
			}

			/////////
			instrucao_rx = "";
			/////////
		}
		else {
			instrucao_rx += inst;
		}
	}
}
