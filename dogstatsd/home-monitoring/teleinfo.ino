#include <ESP8266WiFi.h>
#include <LibTeleinfo.h>
#include <Ticker.h>
#include <WiFiUdp.h>
#include <Statsd.h>

int timeSinceLastRead = 0;

const char* host = "192.168.1.138";
const uint16_t port = 8888;
IPAddress server(192,168,1,138);

TInfo tinfo; // Teleinfo object

WiFiClient client;
Ticker every_sec; // Send data to Datadog

// Electricity prices
const float HP_PRICE = 0.1639;
const String HP = "HP..";
const float HC_PRICE = 0.1239;
const String HC = "HC..";

// Create the UDP object and configure the StatsD client.
WiFiUDP udp; // or EthernetUDP, as appropriate.
// The last argument is the comma separated list of tags to be applied to
// all metrics emitted by this client.
Statsd statsd(udp, "192.168.1.9", 8125, "sensor,location:electric_table,host:home");

void ticker_update() {
    // How long should be that array?
    char label_value[30];
    int int_value = 0;
    char *ret = NULL;

    // PAPP = Puissance Apparente
    ret = tinfo.valueGet("PAPP", label_value);
    if (ret != NULL) {
        int_value = atoi(label_value);
        statsd.gauge("home.elec.apparent_power", int_value, "", 1.0);
    }


    // IINST = Courant instantané
    ret = tinfo.valueGet("IINST", label_value);
    if (ret != NULL) {
        int_value = atoi(label_value);
        statsd.gauge("home.elec.instant_intensity", int_value, "", 1.0);
    }

    // HCHC = Index Heure Creuse
    ret = tinfo.valueGet("HCHC", label_value);
    if (ret != NULL) {
        int_value = atoi(label_value);
        statsd.gauge("home.elec.index_heure_creuse", int_value, "", 1.0);
    }

    // HCHP = Index Heure Pleine
    ret = tinfo.valueGet("HCHP", label_value);
    if (ret != NULL) {
        int_value = atoi(label_value);
        statsd.gauge("home.elec.index_heure_pleine", int_value, "", 1.0);
    }

    // PTEC = Plage Tarifaire En Cours
    ret = tinfo.valueGet("PTEC", label_value);

    if (ret != NULL) {
      String str = String(ret);
      if (str == HP) {
        statsd.gauge("home.elec.plage_tarifaire", 1, "", 1.0);
        statsd.gauge("home.elec.current_cost", HP_PRICE, "", 1.0);
      } else if (str == HC) {
        statsd.gauge("home.elec.plage_tarifaire", 0, "", 1.0);
        statsd.gauge("home.elec.current_cost", HC_PRICE, "", 1.0);
      } else {
        // Something weird
        statsd.gauge("home.elec.plage_tarifaire", -1, "", 1.0);
      }
    }


}

void setup()
{
    const char *ssid = "<WIFI-SSID>";
    const char *wifi_password = "<WIFI-PASSWORD>";

    // Configure Teleinfo Soft serial
    // La téléinfo est connectee sur D3
    // ceci permet d'eviter les conflits avec la
    // vraie serial lors des uploads
    Serial.begin(1200, SERIAL_7E1);

    // Connect to Wifi.
    WiFi.begin(ssid, wifi_password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }

    // Init teleinfo
    tinfo.init();

    delay(100);


    // Once connected tell client to begin.
    statsd.begin();
    statsd.setTagStyle(TAG_STYLE_DATADOG);

    // Attach ticker
    every_sec.attach(5, ticker_update);
}

void loop()
{
//    // Use WiFiClient class to create TCP connections
//    if (!client.connected()) {
//        if (!client.connect(server, port)) {
//          delay(1000);
//          return;
//        }
//        client.println("Connected and ready to go");
//    }

    static char c;


    if ( Serial.available() ) {
        c = Serial.read();
        tinfo.process(c);

//        // Print in wifi client
//        if (c!=TINFO_STX && c!=TINFO_ETX) {
//            client.print(c);
//        }
    }

}
