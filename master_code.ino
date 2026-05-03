#include <ModbusRTU.h>

// Définition des pins
#define RXD2 16
#define TXD2 17
#define RS485_EN 4

ModbusRTU mb;
uint16_t temp; // variable pour stocker la température

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  pinMode(RS485_EN, OUTPUT);

  // Initialisation Modbus en mode MASTER
  mb.begin(&Serial2, RS485_EN);
  mb.master();

  Serial.println("Master prêt...");
}

void loop() {
  // Lecture du registre 0 de l'esclave ID=1
  if (!mb.slave()) {
    mb.readHreg(1, 0, &temp, 1); // (slave ID, adresse registre, variable, nb registres)
  }

  mb.task();

  // Affichage température (division par 10 pour précision)
  Serial.print("Température : ");
  Serial.print(temp / 10.0);
  Serial.println(" °C");

  delay(1000);
}
