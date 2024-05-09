//  receptor
#include "heltec.h"
#define BAND    915E6

int pacotesPerdidos = 0;
int valorRecebido = 0;
int valorAnterior = 0;

void setup() {
  Heltec.begin(true /*Display*/, true /*LoRa */, true /*Serial*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 0, "Receptor");
  Heltec.display->display();
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    while (LoRa.available()) {
      String mensagem = LoRa.readString();
      valorRecebido = mensagem.toInt();
      // inicializa o "valor anterior" para evitar que o primeiro pacote seja considerado perdido
      if (valorRecebido == 0 || valorAnterior == 0){
        valorAnterior = valorRecebido - 1;
      }
      // verifica se houve perda de pacotes
      if (valorRecebido - valorAnterior > 1) {
        pacotesPerdidos += valorRecebido - valorAnterior - 1;
      } 
      valorAnterior = valorRecebido;

      Heltec.display->clear();
      Heltec.display->drawString(0, 0, "Receptor");
      Heltec.display->display();
      Heltec.display->drawString(0, 10, "Recebido: ");
      Heltec.display->display();
      Heltec.display->drawString(50, 10, mensagem);
      Heltec.display->display();
      Heltec.display->drawString(0, 20, "Perdidos: ");
      Heltec.display->display();
      Heltec.display->drawString(50, 20, String(pacotesPerdidos));
      Heltec.display->display();
    }   
  }
}
