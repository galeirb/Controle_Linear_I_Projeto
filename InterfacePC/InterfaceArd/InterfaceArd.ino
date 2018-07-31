#include <Wire.h> // Protocolo I2C

#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,3,4,5,6);

// Portas utilizada no I2C
//4 (SDA) e 5(SCL) - Nano
//20 (SDA) e 21 (SCL) - Mega

// instrucao_rx = Diferencia quais sãos os valores (valor1, valor2 e valor3)
// valor1_str,valor2_str e valor3_str = Valores das resistências requeridas


String instrucao_rx, valor1_str, valor2_str, valor3_str, leitura_rapida, velocidade_str, str_temp; //sentido_str;
String valores; // h
int qtd1,qtd2,qtd3; //velocidade
float r1, r2, r3;


const int analogPin = A1; // Porta analogica para leitura
const int pin_qtd = 5; // Quantidade de resistores de referência utilizado + 1
const int qtd_amostra = 20; // Quantidade de leituras que serão feitas para cada resistor

const int pin[pin_qtd] = { 2, 7, 8, 9, 10 }; // Onde os resistores de referência estão conectado
//const float res_referencia[pin_qtd] = { 62.0, 221.0, 9780.0, 4620.0, 327.0 };
const float res_referencia[pin_qtd] = { 323.0, 61.3, 987.0, 4580.0, 218.0 }; // Os valores dos resistores de referência
float ref; // Variável para guardar o valor de referência utilizado.


void setup() {
	Serial.begin(9600);
	Wire.begin(8); //Nano - 8
	//pinMode(13, OUTPUT);
  lcd.begin(16,2); // Quantidade de colunas e linhas

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

	if (Serial.available()) {
		char inst = Serial.read();
		if (inst == ',') {

			if (instrucao_rx == "receberv1") {
				str_temp = Serial.readString(); // Valor em formado de String - Caractere
				valor1_str = str_temp; // Nessa variável possuimos o valor que queremos
				r1 = valor1_str.toFloat(); // Valor no formato Float - Número

				// Manda esses dados para o PC

        //lcd.clear();

				Serial.print("-- Valor de R1 recebido: "); 
        lcd.clear();
        lcd.print("Valor de R1: ");
        lcd.setCursor(0,1);
        lcd.print(r1);
        
        lcd.write(byte(144));
        lcd.write(byte(244));        
				Serial.print(valor1_str);
				Serial.println(" ohms");
				str_temp = ""; // Deixa a variável em branco
        delay(500);
			}

			if (instrucao_rx == "receberv2") {
				str_temp = Serial.readString();
				valor2_str = str_temp;
				r2 = valor2_str.toFloat();
				Serial.print("-- Valor de R2 recebido: ");
        lcd.clear();
        lcd.print("Valor de R2: ");
        lcd.setCursor(0,1);
        lcd.print(r2);
        
        lcd.write(byte(144));
        lcd.write(byte(244));  
				Serial.print(valor2_str);
				Serial.println(" ohms");
				str_temp = "";
			}

			if (instrucao_rx == "receberv3") {
				str_temp = Serial.readString();
				valor3_str = str_temp;
				r3 = valor3_str.toFloat();
				Serial.print("-- Valor de R3 recebido: ");
        lcd.clear();
        lcd.print("Valor de R3: ");
        lcd.setCursor(0,1);
        lcd.print(r3);
        
        lcd.write(byte(144));
        lcd.write(byte(244));  
				Serial.print(valor3_str);
				Serial.println(" ohms\n");
				str_temp = "";
			}

			if (instrucao_rx == "leitura") {
				str_temp = Serial.readString();
				leitura_rapida = str_temp;
        		//r3 = leitura_rapida.toFloat();

//teste, para saber a resposta em relação a leitura rapida
				//Serial.print("leitura rapida: ");
				//Serial.print(leitura_rapida);
				//Serial.println(".\n");


			// Calculo para leitura realizada
				if (leitura_rapida == "1"){
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
						resistencia = calcularResistencia(res_referencia[i], v);
						ref = res_referencia[i];
					}
				}
				Serial.print("Resistencia = ");
				Serial.println(resistencia);
				Serial.print("Referencia utilizada: ");
				Serial.println(ref);
				Serial.println();

        lcd.clear();
        lcd.print("Valor: ");
        lcd.print(resistencia);
        lcd.write(byte(244)); 
                
        lcd.setCursor(0,1); 
        lcd.print("Ref: ");
        lcd.print(ref);
        lcd.write(byte(244));  
				}


				//Wire.beginTransmission(15);
				//Wire.write(leitura_rapida.c_str());
				//Wire.write("LER");
				//Wire.endTransmission();

			}

			/////////
			instrucao_rx = ""; // Zera a variável, depois de ter pego os valores
			/////////
		}
		else {
			instrucao_rx += inst; // instrucao_rx = instrucao_rx + inst
		}
	}

		/*if (i<3)
		{
			i+=1;
			
      valores = strcat("Valores,",valor1_str,",",valor2_str",",valor3_str);
		}
		else
		{
			Wire.beginTransmission(15); // O enderenço que queremos transmitir
			Wire.write("LER");
			Wire.write(valor1_str);
			Wire.endTransmission; // Acaba a transmissão com esse dispositivo
			i = 0;
			Serial.printf(valores);
		}*/

    /*  
     Wire.beginTransmission(15); // O enderenço que queremos transmitir
     Wire.write("LER");
      Wire.write(valor1_str);
      Wire.endTransmission; // Acaba a transmissão com esse dispositivo
      i = 0;
      Serial.printf(valores);

      */

}
