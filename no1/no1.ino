#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

const int ledVermelhoPin = 8; // Pino digital para o LED vermelho
const int ledVerdePin = 7; // Pino digital para o LED verde
int umidade = 0; // Valor de umidade definido manualmente

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(0xF0F0F0F0E1LL); // Endereço de escrita
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(0x4c);
  
  pinMode(ledVermelhoPin, OUTPUT);
  pinMode(ledVerdePin, OUTPUT);
  digitalWrite(ledVermelhoPin, LOW); // Inicialmente, LEDs apagados
  digitalWrite(ledVerdePin, LOW);
}

void loop() {
  // Atribuir manualmente o valor de umidade para simulação
  // Altere o valor de 'umidade' conforme necessário para testar o sistema
  umidade = 50; // Exemplo: você pode alterar este valor para testar

  bool umidadeBaixa = umidade >= 0 && umidade <= 60;

  if (umidadeBaixa) {
    digitalWrite(ledVermelhoPin, HIGH); // Acende o LED vermelho
    digitalWrite(ledVerdePin, LOW); // Apaga o LED verde
  } else {
    digitalWrite(ledVermelhoPin, LOW); // Apaga o LED vermelho
    digitalWrite(ledVerdePin, HIGH); // Acende o LED verde
  }

  radio.write(&umidadeBaixa, sizeof(umidadeBaixa)); // Envia o status da umidade
  delay(2000); // Aguarda 2 segundos antes da próxima leitura
}
