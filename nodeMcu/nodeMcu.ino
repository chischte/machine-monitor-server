#include <ESP8266WiFi.h>
//*********************************************************************************
//PINGER
//*********************************************************************************
#include <Pinger.h> // https://github.com/bluemurder/esp8266-ping.git
extern "C"
{
#include <lwip/icmp.h> // needed for icmp packet definitions
}
//*********************************************************************************
char *ssid;
char *pass;

WiFiClient client;
Pinger pinger;

void setup()
{
  getLogins(); // assigns values to *ssid and *pass
  //void getLogins(){} contains:
  //ssid="ssid-name";
  //pass="password";
  Serial.begin(9600);
  delay(10);

  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay (5000);
  // GET A PING FROM MACHINE-DB-SERVER:
  pingServer();
}

void loop()
{
  Serial.print(".");
  delay(2000);
}
