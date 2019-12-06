#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "getLogins.h"

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

//char *ssid="chäfernetz";
//char *pass="pizzakurier321";
//ssid = "chäfernetz";
//pass = "pizzakurier321";

WiFiClient client;
Pinger pinger;

void pingServer()
{
  pinger.OnReceive([](const PingerResponse &response) {
    if (response.ReceivedResponse)
    {
      Serial.printf(
          "Reply from %s: bytes=%d time=%lums TTL=%d\n",
          response.DestIPAddress.toString().c_str(),
          response.EchoMessageSize - sizeof(struct icmp_echo_hdr),
          response.ResponseTime,
          response.TimeToLive);
    }
    else
    {
      Serial.printf("Request timed out.\n");
    }

    // Return true to continue the ping sequence.
    // If current event returns false, the ping sequence is interrupted.
    return true;
  });

  pinger.OnEnd([](const PingerResponse &response) {
    // Evaluate lost packet percentage
    float loss = 100;
    if (response.TotalReceivedResponses > 0)
    {
      loss = (response.TotalSentRequests - response.TotalReceivedResponses) * 100 / response.TotalSentRequests;
    }

    // Print packet trip data
    Serial.printf(
        "Ping statistics for %s:\n",
        response.DestIPAddress.toString().c_str());
    Serial.printf(
        "    Packets: Sent = %lu, Received = %lu, Lost = %lu (%.2f%% loss),\n",
        response.TotalSentRequests,
        response.TotalReceivedResponses,
        response.TotalSentRequests - response.TotalReceivedResponses,
        loss);

    // Print time information
    if (response.TotalReceivedResponses > 0)
    {
      Serial.printf("Approximate round trip times in milli-seconds:\n");
      Serial.printf(
          "    Minimum = %lums, Maximum = %lums, Average = %.2fms\n",
          response.MinResponseTime,
          response.MaxResponseTime,
          response.AvgResponseTime);
    }

    // Print host data
    Serial.printf("Destination host data:\n");
    Serial.printf(
        "    IP address: %s\n",
        response.DestIPAddress.toString().c_str());
    if (response.DestMacAddress != nullptr)
    {
      Serial.printf(
          "    MAC address: " MACSTR "\n",
          MAC2STR(response.DestMacAddress->addr));
    }
    if (response.DestHostname != "")
    {
      Serial.printf(
          "    DNS name: %s\n",
          response.DestHostname.c_str());
    }

    return true;
  });

  // Ping machine server
  //Serial.printf("\n\nPinging machinelogger.synology.me\n");
  if (pinger.Ping("machinelogger.synology.me") == false)
    // LOCAL PING:
    if (pinger.Ping("55.55.55.55") == false)
    {
      Serial.println("Error during ping command.");
    }

  delay(7000);
}
//*/

void setup()
{
  ssid = getSsid();
  pass = getPass();

  // char *getSsid()
  // {
  //   char *charToReturn = "ssid";
  //   return charToReturn;
  // }

  // char *getPass()
  // {
  //   char *charToReturn = "password";
  //   return charToReturn;
  // }

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
  delay(5000);
  // GET A PING FROM MACHINE-DB-SERVER:
  pingServer();
}

void loop()
{
  Serial.print(".");
  delay(2000);
}

///*