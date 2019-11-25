#include <ESP8266WiFi.h>

char *ssid;
char *pass;

WiFiClient client;

void setup()
{
  assignLoginData(); // assigns values to *ssid and *pass
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
  delay(2000);
}


