#include <Wire.h> // Protocolo I2C

#include <LiquidCrystal.h>

LiquidCrystal lcd(53,51,49,47,45,43);
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

void setup() {
  Serial.begin(9600);
  //Wire.begin(8); //Nano - 8
  //pinMode(13, OUTPUT);
  lcd.begin(16, 2); // Quantidade de colunas e linhas

  Wire.begin();              // Configura o barramento I2C

  lcd.print("Selector Automa-");
    lcd.setCursor(0, 1);
    lcd.print("tizado de Resist!");

}


void loop() {

  if (Serial.available()) {
    char inst = Serial.read();
    if (inst == ',') {
      if (instrucao_rx == "status_arduino") {

        str_temp = Serial.readString();
        if (str_temp == "0") {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Arduino");
          lcd.setCursor(0, 1);
          lcd.print("Desconectado!");
          lcd.write(byte(144)); //Espaço
          lcd.write(byte(144)); //Espaço 15
          str_temp = "";
        }
        if (str_temp == "1") {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Conectado! ");
          lcd.setCursor(0, 1);
          lcd.print("Aguardando...");
          str_temp = "";
        }
        if (str_temp == "2") {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Selector Automa-");
          lcd.setCursor(0, 1);
          lcd.print("tizado de Resist!");
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
        lcd.clear();
        lcd.setCursor(0, 0);
        //lcd.noCursor();
        lcd.print("Valor desejado: ");
        lcd.setCursor(0, 1);
        lcd.print(r1);
        lcd.write(byte(144)); //Espaço
        lcd.write(byte(244));
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
          Wire.beginTransmission(44);
          Wire.write(5);
          //Wire.write("1");
          Wire.endTransmission();
          delay(500);
          Serial.println("Mandando comando!");
          /* -- Fazer um procedimento para que quando receber o valor
           *  // Fazer um serial.print para o programa
          Serial.print("Resistencia = ");
          Serial.println(resistencia);
          Serial.print("Referencia utilizada: ");
          Serial.println(ref);
          Serial.println();

          lcd.clear();
          lcd.print("Valor: ");
          lcd.print(resistencia);
          lcd.write(byte(244));

          lcd.setCursor(0, 1);
          lcd.print("Ref: ");
          lcd.print(ref);
          lcd.write(byte(244));*/
        }


        if (leitura_rapida == "0") {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Leitura Externa");
          lcd.setCursor(0, 1);
          lcd.print("Desabilitada!");
        }
        if (leitura_rapida == "2") {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Leitura Externa");
          lcd.setCursor(0, 1);
          lcd.print("Habilitada!");
          str_temp = "";
          delay(500);
          
          Wire.beginTransmission(44);
          Wire.write(4);
          //Wire.write("1");
          Wire.endTransmission();
          delay(500);
          Serial.println("Mandando comando!");
        }
        /*
              if (leitura_rapida == "2"){ // Codigo para dizer mostrar no display que foi habilitado a opção de leitura externa.
                  lcd.clear();
                  lcd.setCursor(0,0);
                  lcd.print("Leitura Externa");
                  lcd.setCursor(0,1);
                  lcd.print("Habilitada!");

                }*/


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
      // Faz com que guardamos a nomeclatura da instrução antes, na instrucao_rx
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
