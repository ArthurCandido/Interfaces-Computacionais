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
  radio.openReadingPipe(1, address);
  radio.startListening();
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
}

void loop() {
  if (radio.available()) {
    int umidade;
    radio.read(&umidade, sizeof(umidade));

    Serial.print(F("Umidade recebida: "));
    Serial.println(umidade);

    if (umidade <= 60) {
      digitalWrite(LED_VERMELHO, HIGH);
      digitalWrite(LED_VERDE, LOW);
      Serial.println(F("Umidade baixa! LED vermelho aceso, ligando a bomba."));
    } else {
      digitalWrite(LED_VERMELHO, LOW);
      digitalWrite(LED_VERDE, HIGH);
      Serial.println(F("Umidade alta! LED verde aceso, desligando a bomba."));
    }
  }

  delay(2000);  // Aguardar antes de verificar novamente
}
