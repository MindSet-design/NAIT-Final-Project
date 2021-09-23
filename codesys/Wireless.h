#include <WiFiNINA.h>

char ssid[] = "CL";          //  your network SSID (name)
char pass[] = "Lcsd150150150";   // your network password

int status = WL_IDLE_STATUS;
byte ip[] = {192, 168, 1,86} ; // drink machine

// Initialize the client library
WiFiClient client;
////////////////////////
//function connect_wifi
//inputs none
//outputs none
// connects to the wifi
///////////////////////
void connect_wifi() {
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network.
    status = WiFi.begin(ssid, pass);
    String response = client.readStringUntil('\n');
    Serial.println(response);
    // wait 10 seconds for connection:
    delay(10000);
  }
}
///////////////////////////////////////
//function: Send_Command
//inputs string Command
//outputs none
//sends the drink machine an instruction
/////////////////////////////////////////
String Send_Command(String Command) {
  if (client.connect(ip, 80)) {//connects to client 
    Serial.println("connected");
    client.print(Command);
    String response = client.readStringUntil('\n');
    client.stop();
    return response;
  }
}
//prints wifi status
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
