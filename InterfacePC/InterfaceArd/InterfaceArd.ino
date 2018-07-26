#include <Wire.h>

String instrucao_rx, valor1_str, valor2_str, valor3_str, str_temp,velocidade_str,sentido_str;
String h;
int velocidade, qtd1,qtd2,qtd3;
float r1, r2, r3, lido_m1,lido_m2,lido_m3, r_ref,r1_lido,r2_lido,r3_lido;
char d;
int raw1,raw2,raw3;
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
	Wire.begin(8);
	pinMode(13, OUTPUT);
}

void loop() {

	if (Serial.available()) {
		char inst = Serial.read();
		if (inst == ',') {

			if (instrucao_rx == "receberv1") {
				str_temp = Serial.readString();
				valor1_str = str_temp;
				r1 = valor1_str.toFloat();
				Serial.print("-- Valor de R1 recebido: ");
				Serial.print(valor1_str);
				Serial.println(" ohms");
				str_temp = "";
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

			if (instrucao_rx == "velocidade") {
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
			}

			/////////
			instrucao_rx = "";
			/////////
		}
		else {
			instrucao_rx += inst;
		}
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
