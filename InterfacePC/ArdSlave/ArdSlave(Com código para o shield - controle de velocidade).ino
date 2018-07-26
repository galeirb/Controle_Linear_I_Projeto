String comandoRx, sentido;
int velocidade;

void setup() {
	Serial.begin(9600);
	comandoRx = "velocidade_021";
}

void loop() {
	delay(500);

	if (comandoRx == "paolo") {
		digitalWrite(13, !digitalRead(13));
	}

	if (comandoRx.startsWith("velocidade")) {
		comandoRx.remove(0, 11);
		velocidade = comandoRx.toInt();
		Serial.print("A velocidade desejada foi: ");
		Serial.println(velocidade);
		////
		//// CÓDIGO DE VELOCIDADE DO SHIELD
		////
		comandoRx = "";
	}

	if (comandoRx.startsWith("sentido")) { //Testa se uma String começa ou não com os caracteres de uma outra String.
		comandoRx.remove(0, 8);
		sentido = comandoRx;
		if (sentido == "horario") {
			////
			//// CÓDIGO DE SENTIDO DO SHIELD
			////
			Serial.print("O sentido de rotação escolhido foi: horário");
		}
		else {
			////
			//// CÓDIGO DE SENTIDO DO SHIELD
			////
			Serial.println("O sentido de rotação escolhido foi: antihorário");
		}
		comandoRx = "";
	}
}