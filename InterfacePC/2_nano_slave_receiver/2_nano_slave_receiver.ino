#include <Wire.h>

float variavel_float;
byte byte1, byte2, byte3, byte4;
unsigned int aux;
int quantidade_bytes_esperados = 3;
//int opcao = 1;
String instrucao_rx, teste;

// Variáveis para realização da leitura
const int analogPin = A6; // Porta analogica para leitura
const int pin_qtd = 7; // Quantidade de resistores de referência utilizado + 1
const int qtd_amostra = 10; // Quantidade de leituras que serão feitas para cada resistor

//const int pin[pin_qtd] = { 53, 51, 49, 47, 45, 43, 41 }; // Onde os resistores de referência estão conectado
//const float res_referencia[pin_qtd] = { 326.0, 9850.0, 62.3, 4595.0, 222.0, 998.0, 466.1 }; // Os valores dos resistores de referência
const int pin[pin_qtd] = { 6,7,8,9,10,11,12 }; // Onde os resistores de referência estão conectado
const float res_referencia[pin_qtd] = { 326.0, 9850.0, 62.3,4595.0, 222.0, 998.0, 466.1 }; // Os valores dos resistores de referência
float ref; // Variável para guardar o valor de referência utilizado.


//0 - Recebendo apenas float

//2- Teste para ser realizado um tratamento antes


void setup() {
  Serial.begin(9600);
  Wire.begin(44);                                   // Inicia como escravo endereço 44
  Wire.onReceive(receiveEvent);                     // Interrupção ativada quando  mestre está enviado os bytes

  for (int i = 0; i < pin_qtd; i++) {
    pinMode(pin[i], OUTPUT);
    digitalWrite(pin[i], LOW);
    pinMode(pin[i], INPUT);
  }
}

void loop() {
  delay(1000);
}

void receiveEvent(int howMany) { // Está código é executado quando "quantidade_bytes_esperados" foi recebido via I2C

  if (Wire.available()) {
    char c = Wire.read();
    //if (c == ',') {
    if (c == "Teste") {

      //Serial.println(instrucao_rx);
      byte1 = Wire.read();                            // Lê os 3 bytes enviados pelo mestre
      byte2 = Wire.read();
      byte3 = Wire.read();
      //byte4 = Wire.read();

      // Ajustando os bytes recebidos para obetr a variavel_float
      //aux = (byte3<<8) | byte4;  //  | - operador de bits OR (operação bit a bit) // Ajusta a parte fracionáia (depois da vírgula)
      aux = byte3;
      variavel_float = (float) (aux * 0.01);        // Atribui a parte fracionária, depois da vírgula
      aux = (byte1 << 8) | byte2;                     // Ajusta a parte inteira (antes da vírgula)
      variavel_float += aux;                          // Atribui a parte iteira
      //Serial.println("Variavel recebida pelo escravo:");
      //Serial.println(variavel_float, DEC);
      //Serial.println(variavel_float, 2);
      Serial.println(variavel_float);
      delay(2000);


    }

    if (c == 4) {
      Serial.println("Habilitado");
      c = "";
    }

    if (c == 5) {


      //teste = Serial.readString();
      //Serial.println(teste);

      float minimo = 2.5;
      float resistencia = 100000000.0;

      for (int i = 0; i < pin_qtd; i++) {
        pinMode(pin[i], OUTPUT);
        digitalWrite(pin[i], HIGH);
        delay(500);
        //Serial.print("Pino usado: ");
        //Serial.println(pin[i]);
        
        
        //float v = tensaoMedia();
        float total = 0.0;
        for (int n = 0; n < qtd_amostra; n++) {
          delay(1);
          total += float(analogRead(analogPin));
        }
        float v = 5.0 * total / (qtd_amostra * 1023.0);

        //Serial.print("Tensão lida: ");
        //Serial.println(v);
        //Serial.print("Tensão total: ");
        //Serial.println(total);
        //Serial.print("Resistencia usada: ");
        //Serial.println(res_referencia[i]);

        
        digitalWrite(pin[i], LOW);
        pinMode(pin[i], INPUT);
        float diferenca = abs(v - 2.5);

        if (5.0 > v && diferenca < minimo) {
          minimo = diferenca;
           //calcularResistencia(res_referencia[i], v);
          resistencia = res_referencia[i] / (5.0 / v - 1.0);
          ref = res_referencia[i];
        }
      }

      Serial.print("Resistencia = ");
      Serial.println(resistencia);
      Serial.print("Referencia utilizada: ");
      Serial.println(ref);
      //Serial.println();

      c = "";
    }

    //Serial.println("Veio ate aqui");
    /////////
    instrucao_rx = ""; // Zera a variável, depois de ter pego os valores
    /////////
    // }

  }
}


