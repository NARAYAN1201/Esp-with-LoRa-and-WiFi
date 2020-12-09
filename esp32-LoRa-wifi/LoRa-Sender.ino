#include <SPI.h>
#include <LoRa.h>



void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(868.1E6) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("Data that you want to send"); 
  // use LoRa.print() to send data to the LoRa server 
  
  LoRa.endPacket();

  counter++;

  delay(5000);
}
