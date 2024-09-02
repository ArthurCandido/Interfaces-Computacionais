#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 7
#define CSN_PIN 8
#define LED_VERDE 3
#define LED_VERMELHO 4

RF24 radio(CE_PIN, CSN_PIN);
uint64_t address = 0xF0F0F0F0E1LL;

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(100);
  radio.setDataRate(RF24_2MBPS);
  radio.setAutoAck(false);
  radio.openWritingPipe(address);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
}

void loop() {
  int umidade = random(0, 101); // Simulação de umidade

  if (umidade <= 60) {
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_VERDE, LOW);
  } else {
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_VERDE, HIGH);
  }

  bool report = radio.write(&umidade, sizeof(umidade));

  if (report) {
    Serial.print(F("Transmissão bem-sucedida! Umidade enviada: "));
    Serial.println(umidade);
  } else {
    Serial.println(F("Falha na transmissão"));
  }

  delay(2000);  // Envia a umidade a cada 2 segundos
}
