#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 7
#define CSN_PIN 8

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
}

void loop() {
  if (radio.available()) {
    int umidade;
    radio.read(&umidade, sizeof(umidade));

    // Envia os dados de umidade para o computador via Serial
    Serial.println(umidade);
  }

  delay(2000);  // Espera antes de verificar novamente
}
