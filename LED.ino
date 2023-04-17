/*
  LED

  This example creates a Bluetooth® Low Energy peripheral with service that contains a
  characteristic to control an LED.

  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.

  You can use a generic Bluetooth® Low Energy central app, like LightBlue (iOS and Android) or
  nRF Connect (Android), to interact with the services and characteristics
  created in this sketch.

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>


#define LED_RED 22     
#define LED_BLUE 24     
#define LED_GREEN 23
#define LED_PWR 25


BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // Bluetooth® Low Energy LED Service

// Bluetooth® Low Energy LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

const int ledPin = LED_BUILTIN; // pin to use for the LED
unsigned long time_now=0;
unsigned long start_time=0;
int stevec_iteracij=0;
void setup() {
  Serial.begin(9600);
  while (!Serial);//čaka na serijski terminal

  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_POWER, OUTPUT);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_POWER, HIGH);
  start_time = millis();
  
  
  
  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName("LED_kristof");
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);

  // add service
  BLE.addService(ledService);

  // set the initial value for the characeristic:
  switchCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();

  Serial.println("BLE LED Peripheral");
}

void loop() {
  utripaj(); //cakannje
  // listen for Bluetooth® Low Energy peripherals to connect:
  BLEDevice central = BLE.central();
  
  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());
    
      
      
  
    
     
    
    
    

    


    // while the central is still connected to peripheral:
    while (central.connected()) {
      digitalWrite(LED_GREEN,LOW);
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:
      if (switchCharacteristic.written()) {
        if (switchCharacteristic.value()) {   // any value other than 0
          Serial.println("LED on");
          digitalWrite(ledPin, HIGH);         // will turn the LED on
        } else {                              // a 0 value
          Serial.println(F("LED off"));
          digitalWrite(ledPin, LOW);          // will turn the LED off
        }
      }
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}

int utripaj(){
  time_now = millis();
  if (time_now - start_time >= 500){ //test whether the period has elapsed
        digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));  //if so, change the state of the LED.  Uses a neat trick to change the state
        Serial.println("waiting for connection");
        stevec_iteracij++;
        start_time = time_now;  //IMPORTANT to save the start time of the current LED state.
        
  } 
}


