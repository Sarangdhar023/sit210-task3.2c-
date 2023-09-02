#include <WiFiNINA.h>
#include <BH1750.h>
#include <Wire.h>

// wifi connection data
char wifiName[] = "Sarang";
char password[] = "9876543210";

WiFiClient customer;
BH1750 lightSensor;

char   Name[] = "maker.ifttt.com";
String Path  = "/trigger/email_light/json/with/key/p1TnSwkGeQbRlECj6nRGGOGvCUSJaTtdO2E7xAfnsDm";
String queryString = "?value1=57&value2=25";

void setup() {

  Serial.begin(9600);
  Serial.print("Begin");
  while (!Serial);

  // connect to web server :
     WiFi.begin(wifiName, password);
     Wire.begin();
while(true)
  {
  if (customer.connect(Name, 80)) {
    // if connected:
    Serial.println("Connected to server");
    break;
  }
  else
  {                                                // if not connected:
    Serial.println("connection not stablished");
    
  }
  delay(500);
}
lightSensor.begin();
Serial.println("Connection stablished");
}
void loop() {
  Serial.print("START");
  float lux = lightSensor.readLightLevel();


  queryString +="?value1=" ;
  queryString += lux;
  Serial.println(queryString);

  if (lux > 500) {

    // make a HTTP request:
    // send HTTP header
    customer.println("GET " + Path + queryString + " HTTP/1.1");
    customer.println("Host: " + String(Name));
    customer.println("Connection: close");
    customer.println(); // end HTTP header


    while (customer.connected()) {
      if (customer.available()) {
        // read an incoming byte from the server and print it to serial monitor:
        char c = customer.read();
        Serial.print(c);
      }
    }

    // the server's disconnected, stop the customer:
    customer.stop();
    Serial.println();
    Serial.println("disconnected");
  }
  queryString = "";
  delay(3000);
}