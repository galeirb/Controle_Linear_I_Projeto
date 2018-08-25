/*#include <SoftwareSerial.h> // para receber dados da Serial pelo Nano
  SoftwareSerial portNano(17, 16); // (RX,TX);
*/
#include <Wire.h> // Protocolo I2C

#include <LiquidCrystal.h>

#include <Servo.h>
Servo servoLeitura;
int val = 15; //Ponto inicial
int movimento_leitura = 73; // Leitura

LiquidCrystal lcd(41, 43, 35, 37, 48, 50);
//lcd(RS,E,x,x,x,x);

// Portas utilizada no I2C
//4 (SDA) e 5(SCL) - Nano
//20 (SDA) e 21 (SCL) - Mega

// instrucao_rx = Diferencia quais sãos os valores (valor1, valor2 e valor3)
// valor1_str= Valor da resistência requerida


String instrucao_rx, valor1_str, leitura_rapida, velocidade_str, str_temp, resistencia_lida, r_lido; //sentido_str;
String valores; // h
//int qtd1,qtd2,qtd3; //velocidade
float r1;
float variavel_float, valorResistencia;

// Variável para indentificar quando se deve mover o motor de passo
int moverMotor = 0;

byte byte1, byte2, byte3, byte4;

unsigned int aux;

//-----------------------------------
// Variáveis para o motor de passo
int A = 44;
int B = 32;
int C = 34;
int D = 36;
int tempo_ativacao = 50;
int delay_cada_passo = 1000;

int quant_passos_realizados = 0;
//-----------------------------------

void setup() {
  Serial.begin(9600);
  //portNano.begin(9600);
  Serial1.begin(9600);
  //Wire.begin(8); //Mega - 8 // Nano - 44
  //Wire.onReceive(receiveEvent);
  //pinMode(13, OUTPUT);
  lcd.begin(16, 2); // Quantidade de colunas e linhas

  Wire.begin();              // Configura o barramento I2C

  lcd.print("Seletor Automa-");
  lcd.setCursor(0, 1);
  lcd.print("tizado de Resist!");

  // Deixados os pinos como saída para o controle do motor

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);

  // Servo 1 no pino D10 e Servo 2 no pino D9
  // Servo 1 - Leitura
  servoLeitura.attach(10);  
  Serial.begin(9600);
  servoLeitura.write(val);

}

// Função para mandar o nano realizar a leitura do resistor
// -----------------------------------------------
float realizarLeitura() {

  //-------------------------------------------------------------
  // Código para ativar o servo motor (Pressionar o resistor)
  servoLeitura.write(movimento_leitura);
  delay(500);
  //-------------------------------------------------------------

  Wire.beginTransmission(44);
  Wire.write(8); // Solicita o valor do resistor lido
  //Wire.write("1");
  Wire.endTransmission();
  delay(500);
}
// -----------------------------------------------


void loop() {
  /*
     portNano.listen();
    if (portNano.available()) {
      Serial.println("Valores recibido do nano");

      }*/

  if (Serial1.available()) {
    //Serial.println("Valores recibido do nano");
    char inst = Serial1.read();
    if (inst == ',') {

      //Processo para leitura externa
      if (instrucao_rx == "valoresLidos") {
        servoLeitura.write(val);
        str_temp = Serial1.readString();
        resistencia_lida = str_temp;

        r_lido = resistencia_lida.toFloat(); // Valor no formato Float - Número

        Serial.print("-> Valor lido: ");
        //Serial.print();
        Serial.print(r_lido);
        Serial.println(" ohms.");

        lcd.clear();
        lcd.setCursor(0, 0);
        //lcd.noCursor();
        lcd.print("Valor Lido: ");
        lcd.setCursor(0, 1);
        lcd.print(r_lido);
        lcd.write(byte(144)); //Espaço
        lcd.write(byte(244));

      }
      //Processo para realização das leituras na esteira
      if (instrucao_rx == "valorEsteira") {
        str_temp = Serial1.readString();
        resistencia_lida = str_temp;

        r_lido = resistencia_lida.toFloat(); // Valor no formato Float - Número


        //-------------------------------------------------------------
        // Código para desativar o servo motor (Deixar de pressionar o resistor)
        servoLeitura.write(val);
        //-------------------------------------------------------------

        Serial.print("-> Valor lido: ");
        //Serial.print();
        Serial.print(r_lido);
        Serial.println(" ohms.");

        lcd.clear();
        lcd.setCursor(0, 0);
        //lcd.noCursor();
        lcd.print("Valor Lido: ");
        lcd.setCursor(0, 1);
        lcd.print(r_lido);
        lcd.write(byte(144)); //Espaço
        lcd.write(byte(244));

        //float resisten = r_lido.toFloat();
        // Calculo para uma torelância de 11%
        float intervalo_min = (valor1_str.toFloat() * 89 / 100); //-11%
        float intervalo_max = ((valor1_str.toFloat() * 11) / 100);//+11%
        intervalo_max = (330 + intervalo_max);

        //Serial.print("Minimo: ");
        //Serial.println(intervalo_min);
        //Serial.print("Maximo: ");
        //Serial.println(intervalo_max);

        if (r_lido.toFloat() >= intervalo_min && r_lido.toFloat() <= intervalo_max) {
          // Valor da resistência está OK
          Serial.println("Resistor Encontrado");

          lcd.clear();
        lcd.setCursor(0, 0);
        //lcd.noCursor();
        lcd.print("Encontrado!! ");
        lcd.setCursor(0, 1);
        lcd.print("Lido: ");
        lcd.print(r_lido);
        //lcd.write(byte(144)); //Espaço
        lcd.write(byte(244));
        }
        else {
          Serial.println("Nao encontrado");
          moverMotor = 1;
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
  //-----------------------------------
  // Movimentação do motor de passo
  if (moverMotor != 0) {
    Serial.println("Devera mover o motor!");

    for (int i = 0; i < 5; i++) {
      digitalWrite(A, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(tempo_ativacao);                       // wait for a second
      digitalWrite(A, LOW);    // turn the LED off by making the voltage LOW
      delay(delay_cada_passo);                       // wait for a second

      digitalWrite(B, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(tempo_ativacao);                       // wait for a second
      digitalWrite(B, LOW);    // turn the LED off by making the voltage LOW
      delay(delay_cada_passo);                       // wait for a second

      digitalWrite(C, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(tempo_ativacao);                       // wait for a second
      digitalWrite(C, LOW);    // turn the LED off by making the voltage LOW
      delay(delay_cada_passo);                       // wait for a second

      digitalWrite(D, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(tempo_ativacao);                       // wait for a second
      digitalWrite(D, LOW);    // turn the LED off by making the voltage LOW
      delay(delay_cada_passo);
    }

    moverMotor = 0;
    if (quant_passos_realizados <10){
      quant_passos_realizados ++;
      realizarLeitura();
      }
      else{
        Serial.println("Valor do resistor nao foi encontrado!");
        }
    
  }
  //-----------------------------------


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

        
        quant_passos_realizados = 0;
        realizarLeitura(); // Função que manda o nano realizar a leitura do resistor

        // ------------------------------------------------------------------------------------------------

        // Protocolo I2C utilizando antes.
        // Mandar esse valor para o NANO

        /*
                float valorResistencia = r1;
                // Para variáveis float positivas
                // Ajustando o número antes da vírgula
                aux = (unsigned int) valorResistencia;  // aux = 46689, Pega somente a parte inteira da variável float (0 - 65536)
                byte2 = aux;                          // byte2 = 0B01100001, pega apenas os primeros 8 bits
                byte1 = (aux >> 8);                   // byte1 = 0B10110110, pega os 8 ultimos bits

                // Ajustando o número depois da vírgula
                valorResistencia -= aux;                // Deixa apenas o número depois da vírgula. Ex: 0.8750
                valorResistencia *= 100;              // Multiplica por 100 para pegar 2 dígitos após a vírgula Ex.:87
                aux = (unsigned int) valorResistencia;  // Pega somente o valor antes da vírgula
                byte3 = aux;                    // byte3 = 0B00100010, pega os 8 ultimos bits
                /*
                        Serial.print("byte1:");
                        Serial.println(byte1);
                        Serial.print("byte2:");
                        Serial.println(byte2);
                        Serial.print("byte3:");
                        Serial.println(byte3);
                        //Serial.print("byte4:");
                        //Serial.println(byte4);


                Wire.beginTransmission(44);           // Começa transmissão para o escravo 0x2C
                Wire.write(3); // Esse é para ele receber o valor da resistÊncia
                Wire.write(byte1);                    // Envia os bytes do número antes da vírgua e depois da vírgula
                Wire.write(byte2);
                Wire.write(byte3);
                //Wire.write(byte4);

                Wire.endTransmission();   */            // Termina a transmissão
        // ------------------------------------------------------------------------------------------------
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
        if (leitura_rapida == "1") { // Foi solicitado a realização da leitura do resistor
          // O nano, irá realizar a leitura do resitor
          // Tem duas etapas
          // - Leitura externa - Apenas realizar a leitura e mandar de volta
          // - Leitura interna - Realizar leitura e comparar com o requisitado.
          str_temp = "";

          
          // Servo motor desce
          // ---------------------------
          servoLeitura.write(movimento_leitura);
          delay(500);
          // ---------------------------
          Wire.beginTransmission(44);
          Wire.write(5);
          //Wire.write("1");
          Wire.endTransmission();
          delay(500);
          //Serial.println("Mandando comando!");
          /* -- Fazer um procedimento para que quando receber o valor
              // Fazer um serial.print para o programa
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


        if (leitura_rapida == "0") { // Foi desabilitado a leitura externa
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Leitura Externa");
          lcd.setCursor(0, 1);
          lcd.print("Desabilitada!");
        }
        if (leitura_rapida == "2") { // Leitura Externa Habilitada
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Leitura Externa");
          lcd.setCursor(0, 1);
          lcd.print("Habilitada!");
          str_temp = "";
          delay(500);
          /*
                    Wire.beginTransmission(44);
                    Wire.write(2);
                    //Wire.write("1");
                    Wire.endTransmission();
                    delay(500);
                    Serial.println("Mandando comando!");*/
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
/*
  void receiveEvent(int howMany) {
  if (Wire.available()) {
    char c = Wire.read();
    if (c== 7){

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
      Serial.print("--> Valor lido: ");
      Serial.print(variavel_float);
      Serial.println(" ohms");
      delay(2000);

      }

    //Serial.println("Veio ate aqui");
    /////////
    instrucao_rx = ""; // Zera a variável, depois de ter pego os valores
    /////////
    // }

  }
  }*/
