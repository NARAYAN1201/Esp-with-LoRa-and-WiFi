#include <WiFi.h>
#include <SPI.h>
#include <LoRa.h>

//define the pins used by the transceiver module
#define ss 5
#define rst 14
#define dio0 2

const char* ssid     = "SSID";
const char* password = "PASSWORD";

const char* host = "data.sparkfun.com";
const char* streamId   = "....................";
const char* privateKey = "....................";

void setup()
{
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    //---to send data to the server---

    WiFi.disconnect();
    Serial.println("wifi dissconected");//wifi disconnected to start communication between esp32 and lora
    delay(1000);
     

    
}
void loop() {
   Serial.println("LORA RECEIVER");
   while (!Serial);
  Serial.println("LoRa Receiver");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  while (!LoRa.begin(868.1E6)) { //establishing lora
    Serial.println(".");
    delay(500);
  }
   
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
  delay(1000);
  Serial.println("Receiving");
  while(1){
  // try to parse packet
   int packetSize = LoRa.parsePacket();
  
   if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData); 
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    break;
    }
  }
  LoRa.end();\\ending lora to start communication between esp32 and wifi
  delay(500);
  Serial.end();
  delay(500);
  setup();//again calling to connect to the wifi
}
