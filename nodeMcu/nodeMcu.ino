#include <ESP8266WiFi.h>

char *ssid;
char *pass;

WiFiClient client;

void setup()
{
  assignLoginData(); // assigns values to *ssid and *pass
  //assignLoginData() contains:
  //ssid="ssid-name"
  //pass="password"
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
}

void loop()
{
  Serial.print("Connected / IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("ok");
  Serial.println(ssid);
  delay(2000);
}
