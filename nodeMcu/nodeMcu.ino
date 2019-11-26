#include <ESP8266WiFi.h>
//*********************************************************************************
//PINGER
//*********************************************************************************
#include <Pinger.h>
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
//*************************************************
  
  pinger.OnReceive([](const PingerResponse& response)
  {
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
  
  pinger.OnEnd([](const PingerResponse& response)
  {
    // Evaluate lost packet percentage
    float loss = 100;
    if(response.TotalReceivedResponses > 0)
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
    if(response.TotalReceivedResponses > 0)
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
    if(response.DestMacAddress != nullptr)
    {
      Serial.printf(
        "    MAC address: " MACSTR "\n",
        MAC2STR(response.DestMacAddress->addr));
    }
    if(response.DestHostname != "")
    {
      Serial.printf(
        "    DNS name: %s\n",
        response.DestHostname.c_str());
    }

    return true;
  });
  
  // Ping default gateway
  Serial.printf(
    "\n\nPinging default gateway with IP %s\n",
    WiFi.gatewayIP().toString().c_str());
  if(pinger.Ping(WiFi.gatewayIP()) == false)
  {
    Serial.println("Error during last ping command.");
  }
  
  delay(5000);
  
  // Ping technologytourist.com
  Serial.printf("\n\nPinging machinelogger.synology.me\n");
  if(pinger.Ping("machinelogger.synology.me") == false)
  {
    Serial.println("Error during ping command.");
  }

  delay(5000);

  // Ping undefinedname
  Serial.printf("\n\nPinging undefinedname\n");
  if(pinger.Ping("undefinedname") == false)
  {
    Serial.println("Error during ping command.");
  }

  delay(5000);

  // Ping invalid ip
  Serial.printf("\n\nPinging invalid ip 1.2.3.4\n");
  if(pinger.Ping(IPAddress(1,2,3,4)) == false)
  {
    Serial.println("Error during ping command.");
  }


}

void loop()
{
  Serial.print("Connected / IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("ok");
  Serial.println(ssid);
  delay(2000);

}
