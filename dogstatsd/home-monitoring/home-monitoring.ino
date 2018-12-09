#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Statsd.h>
#include "DHT.h"

#define DHTPIN 4      // what digital pin the DHT22 is conected to
#define DHTTYPE DHT22 // there are multiple kinds of DHT sensors

DHT dht(DHTPIN, DHTTYPE);

// Create the UDP object and configure the StatsD client.
WiFiUDP udp; // or EthernetUDP, as appropriate.
// The last argument is the comma separated list of tags to be applied to
// all metrics emitted by this client.
Statsd statsd(udp, "192.168.0.100", 30125, "sensor,location:entrance,host:home");

int timeSinceLastRead = 0;

void setup()
{
    const char *ssid = "<WIFI-SSID>";
    const char *wifi_password = "<WIFI-PASSWORD>";

    Serial.begin(115200);

    // Connect to Wifi.
    Serial.printf("\n\n\nConnecting to %s ", ssid);
    WiFi.begin(ssid, wifi_password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" connected");

    delay(100);

    // Once connected tell client to begin.
    statsd.begin();
    statsd.setTagStyle(TAG_STYLE_DATADOG);
}

void loop()
{
    // Report every 2 seconds.
    if (timeSinceLastRead > 2000)
    {
        // Reading temperature or humidity takes about 250 milliseconds!
        // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
        float h = dht.readHumidity();
        float t = dht.readTemperature();
        float hic = dht.computeHeatIndex(t, h, false);
        if (isnan(t)) {
            Serial.println("t");
        }
        if (isnan(h)) {
            Serial.println("h");
        }
        if (!(isnan(t) || isnan(h))) {
            statsd.gauge("home.temperature", t, "", 1.0);
            statsd.gauge("home.humidity", h, "", 1.0);
            statsd.gauge("home.heat_index", hic, "", 1.0);
            Serial.printf("%f, %f, %f\n", t, h, hic);
        }
        Serial.println("lo");
        timeSinceLastRead = 0;
    }

    delay(100);
    timeSinceLastRead += 100;
}
