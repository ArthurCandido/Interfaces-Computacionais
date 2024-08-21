#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

const int ledVermelhoPin = 8; 
const int ledVerdePin = 7; 
int umidade = 0; 

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(0xF0F0F0F0E1LL); 
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(100);
  
  pinMode(ledVermelhoPin, OUTPUT);
  pinMode(ledVerdePin, OUTPUT);
  digitalWrite(ledVermelhoPin, LOW); 
  digitalWrite(ledVerdePin, LOW);
}

void loop() {
  umidade = 1; 

  bool umidadeBaixa = umidade >= 0 && umidade <= 60;

  if (umidadeBaixa) {
    digitalWrite(ledVermelhoPin, HIGH); 
    digitalWrite(ledVerdePin, LOW); 
  } else {
    digitalWrite(ledVermelhoPin, LOW); 
    digitalWrite(ledVerdePin, HIGH); 

  radio.write(&umidadeBaixa, sizeof(umidadeBaixa)); 
  delay(10000); 
}}
