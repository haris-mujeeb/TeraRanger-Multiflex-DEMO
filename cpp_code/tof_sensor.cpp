#include <Arduino.h>

#define SERIAL_RX_PIN 16  // Define your RX pin
#define SERIAL_TX_PIN 17  // Define your TX pin
#define BAUD_RATE 115200  // Teraranger default baud rate

HardwareSerial terarangerSerial(1); // Using UART1

void setup() {
    Serial.begin(115200);
    terarangerSerial.begin(BAUD_RATE, SERIAL_8N1, SERIAL_RX_PIN, SERIAL_TX_PIN);

    delay(1000);
    Serial.println("Teraranger Multiplex Sensor Initialized");
}

void loop() {
    if (terarangerSerial.available()) {
        String sensorData = terarangerSerial.readStringUntil('\n');  // Read data until newline
        Serial.print("Distance: ");
        Serial.println(sensorData);
    }
    delay(100);  // Adjust as needed
}
