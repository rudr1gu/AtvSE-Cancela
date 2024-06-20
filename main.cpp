#include <Keypad.h>
#include <Servo.h>

const byte linha = 4; // Quatro Linhas
const byte coluna = 4; // Quatro colunas
char keys[linha][coluna] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte linPins[linha] = {A0, A1, A2, A3}; // Conectores das linhas
byte colPins[coluna] = {5, 4, 3, 2}; //Conectores da coluna

Keypad keypad = Keypad( makeKeymap(keys), linPins, colPins, linha, coluna );

Servo myservo;
const int ledRed = 13;
const int ledGreen = 12;
const int buzzer = 11;

String senha = "1234"; // Definindo a senha
String inputsenha = "";

void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(buzzer, OUTPUT);
  myservo.attach(10);  //definindo a porta de saida do servo

  digitalWrite(ledRed, HIGH);
  digitalWrite(ledGreen, LOW);
  myservo.write(0); // posição inicial do servo motor
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      if (inputsenha == senha) {
        abrirCancela();
      }
      inputsenha = ""; // Clear the input
    } else {
      inputsenha += key; // Append the pressed key to the input
    }
  }
}

void abrirCancela() {
  digitalWrite(ledRed, LOW); 
  digitalWrite(ledGreen, HIGH);
  tone(buzzer, 1000, 200);
  myservo.write(90); // Passando a Posição de 90 graus para o servo motor
  delay(5000); // adicionando um delay de 5 segundos
  myservo.write(0); 
  digitalWrite(ledGreen, LOW); 
  digitalWrite(ledRed, HIGH); 
}
