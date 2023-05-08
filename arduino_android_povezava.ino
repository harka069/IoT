#include <ArduinoBLE.h>

BLEService service("19B10000-E8F2-537E-4F6C-D104768A1214");
BLECharacteristic characteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite, 20);

void setup() {


  Serial.begin(9600);

  if (!BLE.begin()) {
    Serial.println("Failed to initialize BLE");
    while (1);
  }

  BLE.setLocalName("Nano33BLE");
  BLE.setAdvertisedService(service);

  service.addCharacteristic(characteristic);
  BLE.addService(service);

  BLE.advertise();

  Serial.println("BLE Peripheral - String Sender");
}

void loop() {
  if (BLE.connected()) {
    String message = "Hello, world!";
  characteristic.writeValue(message.c_str());


    Serial.print("Sent: ");
    Serial.println(message);

    delay(1000);
  }
}
