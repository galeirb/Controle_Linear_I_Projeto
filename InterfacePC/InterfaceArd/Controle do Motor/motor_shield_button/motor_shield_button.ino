// Carrega a biblioteca AFMotor
#include <AFMotor.h>

// Define o motor1 ligado a conexao 1
AF_DCMotor motor1(3); 


// Opção de trabalho
int opcao = 0;

// Botão
const int botao = 34; //Botão para acionar o motor na opção 0
const int led_on = 35;
const int led_off = 37;


/*
 *  0 - Controlar a rotaçao do motor, sendo acionado com o botão, 
 *  1 - Teste como o reed switch
 * 
 * 
 */

//Variável que conterá os estados do botão (0 LOW, 1 HIGH).
int estadoBotao = 0;
 
void setup()
{
  // Define a velocidade maxima para os motores 1
  motor1.setSpeed(170); 
  pinMode(botao,INPUT);
  pinMode(led_on,OUTPUT);
  pinMode(led_off,OUTPUT);
  //Serial.begin(9600); 

  // Para o reed switch
  #if (opcao == 1)
    //pinMode(led_on, OUTPUT); // Configura o pino 13 (led interno) como saída;
    //pinMode(50, INPUT_PULLUP); // Configura pino 8 como entrada e habilita pull up interno;
    pinMode(50, INPUT);

   #endif
  

}
 
void loop()
{


  if (opcao == 0){

  //serial.println("Motor no aguardado");

  //FORWARD (move o motor no sentido horário), BACKWARD (sentido inverso/anti-horário) ou RELEASE, que determina a parada do motor :

  estadoBotao = digitalRead(botao);

  if (estadoBotao == HIGH) {
//  serial.println("Motor em funcionamento");
  motor1.run(FORWARD); 
  delay(20);
  //delay (1000);
  motor1.run(RELEASE); 
  delay(1000);
  digitalWrite(led_on,HIGH);
  digitalWrite(led_off,LOW);
  //delay(500);
 
  
  } else {
  motor1.run(RELEASE); 
  digitalWrite(led_on,LOW);
  digitalWrite(led_off,HIGH);
     
  }       

  delay(100);

  }
  //Controle do servo motor
  if (opcao == 1) {
    digitalWrite(led_on,LOW);
    digitalWrite(led_off,HIGH);
    
    
    }
  
    if (opcao == 1){
       if (digitalRead(50) == HIGH) { // Botão Pressionado;
          digitalWrite(led_on, HIGH); // Liga led.
      }
      else { // Botão Não Pressionado
          digitalWrite(led_on, LOW); // Desliga led.
      }
      
    }
  
}
