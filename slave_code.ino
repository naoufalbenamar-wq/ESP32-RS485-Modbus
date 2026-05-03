#include <ModbusRTU.h>
#include <DHT.h>

// Définition des pins
#define RXD2 16
#define TXD2 17
#define RS485_EN 4

#define DHTPIN 21
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
ModbusRTU mb;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  pinMode(RS485_EN, OUTPUT);

  dht.begin();

  // Initialisation Modbus en mode SLAVE (ID = 1)
  mb.begin(&Serial2, RS485_EN);
  mb.slave(1);

  // Création du registre 0 (température)
  mb.addHreg(0);

  Serial.println("Slave prêt...");
}

void loop() {
  float temp = dht.readTemperature();

  // Vérification si lecture valide
  if (!isnan(temp)) {
    mb.Hreg(0, temp * 10); // on multiplie par 10 pour garder précision
  }

  mb.task();
}
