// transmissor

#include "heltec.h"
// trocar a banda! 433E6, 866E6, 915E6
#define BAND    915E6


int contador = 0;

void setup() {
  Heltec.begin(true /*Display*/, true /*LoRa */, true /*Serial*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Serial.begin(9600);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 0, "Transmissor");
  Heltec.display->display();
}

void loop() {
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "Transmissor");
  Heltec.display->display();
  Heltec.display->drawString(0, 10, "Enviando...");
  Heltec.display->display();
  Heltec.display->drawString(0, 20, "Contador: ");
  Heltec.display->drawString(60, 20, String(contador));
  Heltec.display->display();
  LoRa.beginPacket();
  LoRa.print(contador);
  LoRa.endPacket();
  Serial.print("contagem: ");
  Serial.println(contador);
  contador++;
  delay(200);
  }



