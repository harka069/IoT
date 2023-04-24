
#include <ArduinoBLE.h>

const int UPDATE_FREQUENCY = 2000;     // Update frequency in ms

long previousMillis = 0; // last time readings were checked, in ms

BLEService environmentService("181A"); // Standard Environmental Sensing service


BLECharacteristic colorCharacteristic("936b6a25-e503-4f7c-9349-bcc76c22b8c3", // Custom Characteristics
                                      BLERead | BLENotify, 1);               // 1234,5678,

BLEDescriptor colorLabelDescriptor("2901", "16-bit ints: r, g, b, a");

void setup() {
    Serial.begin(9600); // Initialize serial communication
    // while (!Serial); // only when connected to laptop
    
    pinMode(LED_BUILTIN, OUTPUT); // Initialize the built-in LED pin

    if (!BLE.begin()) { // Initialize NINA B306 BLE
        Serial.println("starting BLE failed!");
        while (1);
    }

    BLE.setLocalName("LED_kristof");    // Set name for connection
    BLE.setAdvertisedService(environmentService); // Advertise environment service

    environmentService.addCharacteristic(colorCharacteristic);    // Add color characteristic

    colorCharacteristic.addDescriptor(colorLabelDescriptor); // Add color characteristic descriptor

    BLE.addService(environmentService); // Add environment service

    colorCharacteristic.setValue("");   // Set initial color value

    BLE.advertise(); // Start advertising
    Serial.print("Peripheral device MAC: ");
    Serial.println(BLE.address());
    Serial.println("Waiting for connections…");
}

void loop() {
    int num;
    BLEDevice central = BLE.central(); // Wait for a BLE central to connect

    // If central is connected to peripheral
    if (central) {
        Serial.print("Connected to central MAC: ");
        Serial.println(central.address()); // Central's BT address:

        digitalWrite(LED_BUILTIN, HIGH); // Turn on the LED to indicate the connection

        while (central.connected()) {
            long currentMillis = millis();
            // After UPDATE_FREQUENCY ms have passed, check temperature & humidity
            if (currentMillis - previousMillis >= UPDATE_FREQUENCY) {
                previousMillis = currentMillis;
                num = 5;
                colorCharacteristic.writeValue(byte(num), sizeof(num));
            }
        }

        digitalWrite(LED_BUILTIN, LOW); // When the central disconnects, turn off the LED
        Serial.print("Disconnected from central MAC: ");
        Serial.println(central.address());
    }
}
