#include <WiFiNINA.h>

//network information
int status = WL_IDLE_STATUS;
char ssid[] = "CL";
char pass[] = "Lcsd150150150";
WiFiServer server(80);
WiFiClient client = server.available();
//////////////////////////////////////////
//function: connect_wifi
//inputs:none
//Outputs:none
//connects to wifi
//////////////////////////////////////////
void connect_wifi() {
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network.
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
}
//////////////////////////////////////////
//function: Get_Command
//inputs:none
//Outputs:string request
//acts as a server and gets information with TCP/IP
//////////////////////////////////////////
String Get_Command() {
  String currentLine = "";// make a String to hold incoming data from the client
  if (client && client.connected()) {
   Serial.println("connected");
    String request = client.readStringUntil('\n');
    client.print(WaterTemp());
    client.print("\n");
    client.stop();
    return request;
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

//////////////////////////////////////////
//function: command
//inputs:char s , string from clients
//Outputs:int command for switch statment
//changes string command to an int for switch
//////////////////////////////////////////
//switches a command to a number for switch in main loop
int Command(String s)
{
  if (s == "Lleft")
  {
    return 0;
  }
  if (s == "Lpour")
  {
    return 1;
  }
  if (s == "Lright")
  {
    return 2;
  }
  if (s == "Pleft")
  {
    return 3;
  }
  if (s == "Ppour")
  {
    return 4;
  }
  if (s == "Pright")
  {
    return 5;
  }
}
