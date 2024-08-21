#include <SPI.h>
#include "RF24.h"

#define CE_PIN 7
#define CSN_PIN 8
#define LED_VERDE 3
#define LED_VERMELHO 4

RF24 radio(CE_PIN, CSN_PIN);

uint8_t address[][6] = { "1Node", "2Node" };
bool radioNumber = 1;
bool role = false;

int umidade = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}
  }

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  Serial.println(F("RF24 - Transmissor e Receptor com LEDs Indicadores"));

  Serial.println(F("Qual o número do rádio? Digite '0' ou '1'. Default é '0'"));
  while (!Serial.available()) {}

  char input = Serial.parseInt();
  radioNumber = input == 1;
  Serial.print(F("radioNumber = "));
  Serial.println((int)radioNumber);

  Serial.println(F("*** PRESS 'T' para iniciar a transmissão, 'R' para alternar para recepção"));

  radio.setPALevel(RF24_PA_LOW);

  radio.openWritingPipe(address[radioNumber]);
  radio.openReadingPipe(1, address[!radioNumber]);

  if (role) {
    radio.stopListening();
  } else {
    radio.startListening();
  }
}

void loop() {
  if (role) {
    umidade = random(0, 101);

    if (umidade <= 60) {
      digitalWrite(LED_VERMELHO, HIGH);
      digitalWrite(LED_VERDE, LOW);
    } else {
      digitalWrite(LED_VERMELHO, LOW);
      digitalWrite(LED_VERDE, HIGH);
    }

    if (radio.write(&umidade, sizeof(umidade))) {
      Serial.print(F("Transmissão bem-sucedida! Umidade enviada: "));
      Serial.println(umidade);
    } else {
      Serial.println(F("Falha na transmissão"));
    }

    delay(2000);  // Atualiza a umidade a cada 2 segundos
  } else {
    if (radio.available()) {
      radio.read(&umidade, sizeof(umidade));

      Serial.print(F("Umidade recebida: "));
      Serial.println(umidade);

      if (umidade <= 60) {
        digitalWrite(LED_VERMELHO, HIGH);
        digitalWrite(LED_VERDE, LOW);
        Serial.println(F("Umidade baixa! LED vermelho aceso, ligando a bomba!."));
      } else {
        digitalWrite(LED_VERMELHO, LOW);
        digitalWrite(LED_VERDE, HIGH);
        Serial.println(F("Umidade alta! LED verde aceso, desligando a bomba!."));
      }
    }
  }

  if (Serial.available()) {
    char c = toupper(Serial.read());
    if (c == 'T' && !role) {
      role = true;
      Serial.println(F("*** MUDANDO PARA MODO TRANSMISSOR -- DIGITE 'R' PARA VOLTAR"));
      radio.stopListening();
    } else if (c == 'R' && role) {
      role = false;
      Serial.println(F("*** MUDANDO PARA MODO RECEPTOR -- DIGITE 'T' PARA VOLTAR"));
      radio.startListening();
    }
  }
}
