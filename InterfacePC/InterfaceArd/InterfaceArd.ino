#include <Wire.h> // Protocolo I2C

// instrucao_rx = Diferencia quais sãos os valores (valor1, valor2 e valor3)
// valor1_str,valor2_str e valor3_str = Valores das resistências requeridas


String instrucao_rx, valor1_str, valor2_str, valor3_str, velocidade_str, str_temp; //sentido_str;
String valores; // h
int qtd1,qtd2,qtd3; //velocidade
float r1, r2, r3, lido_m1,lido_m2,lido_m3, r_ref,r1_lido,r2_lido,r3_lido;
char d;

int raw1,raw2,raw3,i;
int Vin = 5;
float Vout1,Vout2,Vout3;
/////////// DECLARAR AS RESIST�NCIAS DE REFER�NCIA ///////////
float r_ref1 = 1000;
float r_ref2 = 1000;
float r_ref3 = 1000;
//////////////////////////////////////////////////////////////
float buffer1,buffer2,buffer3 = 0;

void setup() {
	Serial.begin(9600);
	Wire.begin(8); //Nano - 8
	pinMode(13, OUTPUT);
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
				Serial.print("-- Valor de R1 recebido: "); 
				Serial.print(valor1_str);
				Serial.println(" ohms");
				str_temp = ""; // Deixa a variável em branco
			}

			if (instrucao_rx == "receberv2") {
				str_temp = Serial.readString();
				valor2_str = str_temp;
				r2 = valor2_str.toFloat();
				Serial.print("-- Valor de R2 recebido: ");
				Serial.print(valor2_str);
				Serial.println(" ohms");
				str_temp = "";
			}

			if (instrucao_rx == "receberv3") {
				str_temp = Serial.readString();
				valor3_str = str_temp;
				r3 = valor3_str.toFloat();
				Serial.print("-- Valor de R3 recebido: ");
				Serial.print(valor3_str);
				Serial.println(" ohms\n");
				str_temp = "";
			}

			// Instruções para o controle do sentido do motor pelo software
			/*
			if (instrucao_rx == "sentido") {
				str_temp = Serial.readString();
				sentido_str = str_temp;

				Wire.beginTransmission(8);
				Wire.write(sentido_str.c_str());
				Wire.endTransmission();

				Serial.print("-- Sentido de rota��o desejado: ");
				Serial.println(sentido_str);
				str_temp = "";
			}
			*/

			// Instruções para o controle de velocidade do motor pelo software
			/*if (instrucao_rx == "velocidade") {
				str_temp = Serial.readString();
				velocidade_str = str_temp;
				velocidade = velocidade_str.toInt();

				Wire.beginTransmission(8);
				Wire.write(velocidade_str.c_str());
				Wire.endTransmission();

				Serial.print("-- Velocidade desejada recebida: ");
				Serial.print(velocidade_str);
				Serial.println(" rpm\n");
				str_temp = "";
			}*/

			/////////
			instrucao_rx = ""; // Zera a variável, depois de ter pego os valores
			/////////
		}
		else {
			instrucao_rx += inst; // instrucao_rx = instrucao_rx + inst
		}
	}

		if (i<3)
		{
			i+=1;
			
      valores = strcat("Valores,",valor1_str,",",valor2_str",",valor3_str);
		}
		else
		{
			Wire.beginTransmission(15); // O enderenço que queremos transmitir
			Wire.write("Exemplo:");
			Wire.write(valor1_str);
			Wire.endTransmission; // Acaba a transmissão com esse dispositivo
			i = 0;
			Serial.printf(valores);
		}
	
	
/*
	/////////// TRECHO PARA SERVO 1 ///////////
	raw1 = analogRead(A0);
	if (raw1 && r1)
	{
		buffer1 = raw1 * Vin;
		Vout1 = (buffer1) / 1024.0;
		buffer1 = (Vin / Vout1) - 1;
		r1_lido = r_ref1 * buffer1;
		Serial.println(r1_lido);
	}

	if (r1_lido - 0.05*r1_lido < r1 && r1_lido + 0.05*r1_lido > r1)
	{
		qtd1++;
		Serial.print("Resistor de ");
		Serial.print(r2_lido);
		Serial.println(" ohms encontrado.");
		// c�digo do servo 1
	}
	/////////// FIM DO SERVO 1 ///////////

	/////////// TRECHO PARA SERVO 2 ///////////
	raw2 = analogRead(A1);
	if (raw2 && r2)
	{
		buffer2 = raw2 * Vin;
		Vout2 = (buffer2) / 1024.0;
		buffer2 = (Vin / Vout2) - 1;
		r2_lido = r_ref2 * buffer2;
		Serial.println(r2_lido);
	}

	if (r2_lido - 0.05*r2_lido < r2 && r2_lido + 0.05*r2_lido > r2)
	{
		qtd2++;
		Serial.print("Resistor de ");
		Serial.print(r2_lido);
		Serial.println(" ohms encontrado.");
		// c�digo do servo 2
	}
	/////////// FIM DO SERVO 2 ///////////

	/////////// TRECHO PARA SERVO 3 ///////////
	raw3 = analogRead(A3);
	if (raw3 && r3)
	{
		buffer3 = raw3 * Vin;
		Vout3 = (buffer3) / 1024.0;
		buffer3 = (Vin / Vout3) - 1;
		r3_lido = r_ref3 * buffer3;
		Serial.println(r3_lido);
	}

	if (r3_lido - 0.05*r3_lido < r3 && r3_lido + 0.05*r3_lido > r3)
	{
		qtd3++;
		Serial.print("Resistor de ");
		Serial.print(r3_lido);
		Serial.println(" ohms encontrado.");
		// c�digo do servo 3
	}
	/////////// FIM DO SERVO 3 ///////////
   */
}
