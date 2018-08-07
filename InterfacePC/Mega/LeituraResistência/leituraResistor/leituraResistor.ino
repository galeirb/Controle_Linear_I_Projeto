//#include <Wire.h> // Protocolo I2C

//#include <LiquidCrystal.h>

//LiquidCrystal lcd(5, 2, 4, 5,3);
//lcd(RS,E,x,x,x,x);

// Portas utilizada no I2C
//4 (SDA) e 5(SCL) - Nano
//20 (SDA) e 21 (SCL) - Mega

// instrucao_rx = Diferencia quais sãos os valores (valor1, valor2 e valor3)
// valor1_str= Valor da resistência requerida


String instrucao_rx, valor1_str, leitura_rapida, velocidade_str, str_temp; //sentido_str;
String valores; // h
//int qtd1,qtd2,qtd3; //velocidade
float r1;

// Variáveis para realização da leitura
const int analogPin = A6; // Porta analogica para leitura
const int pin_qtd = 7; // Quantidade de resistores de referência utilizado + 1
const int qtd_amostra = 20; // Quantidade de leituras que serão feitas para cada resistor

const int pin[pin_qtd] = { 6,7,8,9,10,11,12 }; // Onde os resistores de referência estão conectado
const float res_referencia[pin_qtd] = { 326.0, 9850.0, 62.3,4595.0, 222.0, 998.0, 466.1 }; // Os valores dos resistores de referência
float ref; // Variável para guardar o valor de referência utilizado.


void setup() {
  Serial.begin(9600);
  //Wire.begin(8); //Nano - 8
  //pinMode(13, OUTPUT);
  //lcd.begin(16, 2); // Quantidade de colunas e linhas

  for (int i = 0; i < pin_qtd; i++) {
    pinMode(pin[i], OUTPUT);
    digitalWrite(pin[i], LOW);
    pinMode(pin[i], INPUT);
    //lcd.print("Selector Automa-");
   // lcd.setCursor(0, 1);
   // lcd.print("tizado de Resist!");
  }

  // I2C
 // Wire.begin(15);                //Barramento I2C do endereço 15
  //Wire.onReceive(receiveEvent);  //Recepção de dados (chama função auxiliar)

  
}

float tensaoMedia() {
  float total = 0.0;
  for (int i = 0; i < qtd_amostra; i++) {
    delay(0);
    total += float(analogRead(analogPin));
  }
  
  return 5.0 * total / (qtd_amostra * 1023.0);

}

float calcularResistencia(float r, float v) {
  return r / (5.0 / v - 1.0);
}

void loop() {

  if (Serial.available()) {
    char inst = Serial.read();
    if (inst == ',') {
      if (instrucao_rx == "status_arduino") {

        str_temp = Serial.readString();
        if (str_temp == "0") {
         // lcd.clear();
        //  lcd.setCursor(0, 0);
        //  lcd.print("Arduino");
        //  lcd.setCursor(0, 1);
        //  lcd.print("Desconectado!");
       //   lcd.write(byte(144)); //Espaço
        //  lcd.write(byte(144)); //Espaço 15
          str_temp = "";
        }
        if (str_temp == "1") {
         // lcd.clear();
        //  lcd.setCursor(0, 0);
        //  lcd.print("Conectado! ");
        //  lcd.setCursor(0, 1);
         // lcd.print("Aguardando...");
          str_temp = "";
        }
        if (str_temp == "2") {
        //  lcd.clear();
        //  lcd.setCursor(0, 0);
        //  lcd.print("Selector Automa-");
        //  lcd.setCursor(0, 1);
         // lcd.print("tizado de Resist!");
          str_temp = "";
        }



      }

      if (instrucao_rx == "receberv1") {
        str_temp = Serial.readString(); // Valor em formado de String - Caractere

        //Exemplo valor1_str = 220  e r1 =220.00
        valor1_str = str_temp; // Nessa variável possuimos o valor que queremos do resistor
        r1 = valor1_str.toFloat(); // Valor no formato Float - Número

        // Manda esses dados para o PC

        Serial.print("--> Valor recebido: ");
       // lcd.clear();
       // lcd.setCursor(0, 0);
        //lcd.noCursor();
       // lcd.print("Valor desejado: ");
       // lcd.setCursor(0, 1);
       // lcd.print(r1);

        //lcd.write(byte(144)); //Espaço
       // lcd.write(byte(244));
        Serial.print(r1);
        Serial.println(" ohms");
        str_temp = ""; // Deixa a variável em branco
        delay(500);
      }

      if (instrucao_rx == "leitura") {
        str_temp = Serial.readString();
        leitura_rapida = str_temp;

        //Teste para visualização do comando do PC
        /*
          Serial.print(instrucao_rx);
          Serial.print("---");
          Serial.println(str_temp);*/

        // Calculo para leitura realizada
        if (leitura_rapida == "1") {
          str_temp = "";
          float minimo = 2.5;
          float resistencia = 100000000.0;

          for (int i = 0; i < pin_qtd; i++) {
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

         // lcd.clear();
         // lcd.print("Valor: ");
         // lcd.print(resistencia);
         // lcd.write(byte(244));

         // lcd.setCursor(0, 1);
         // lcd.print("Ref: ");
         // lcd.print(ref);
        //  lcd.write(byte(244));
        }


        if (leitura_rapida == "0") {
          //lcd.clear();
         // lcd.setCursor(0, 0);
         // lcd.print("Leitura Externa");
         // lcd.setCursor(0, 1);
         // lcd.print("Desabilitada!");
        }
        if (leitura_rapida == "2") {
         // lcd.clear();
         // lcd.setCursor(0, 0);
         // lcd.print("Leitura Externa");
         // lcd.setCursor(0, 1);
         // lcd.print("Habilitada!");
          str_temp = "";
          delay(500);
        }
        

      }

      /////////
      instrucao_rx = ""; // Zera a variável, depois de ter pego os valores
      /////////
    }
    else {
      // Faz com que guardamos a nomeclatura da instrução antes, na instrucao_rx
      instrucao_rx += inst; // instrucao_rx = instrucao_rx + inst
    }
  }

}
