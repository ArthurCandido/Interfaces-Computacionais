#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

bool umidadeBaixa = false;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, 0xF0F0F0F0E1LL); // Endereço de leitura
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(0x4c);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&umidadeBaixa, sizeof(umidadeBaixa));
    if (umidadeBaixa) {
      Serial.println("Umidade baixa! LED vermelho aceso.");
    } else {
      Serial.println("Umidade alta! LED verde aceso.");
    }
  }
}
