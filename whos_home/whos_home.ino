#include <ArduinoHttpClient.h>
#include <WiFi101.h>
#include "secrets.h"

const int rm1_pin = 9;
const int rm2_pin = 10;
const int rm3_pin = 11;
const int rm4_pin = 12; // TODO check pin vals

const int REFRESH_RATE = 600000; // 10 minutes

int rm1_ishome = 0;
int rm2_ishome = 0;
int rm3_ishome = 0;
int rm4_ishome = 0;

char ssid[] = SSID;
char pass[] = SSID_PASS;
char serverAddress[] = sprintf("https://api.meraki.com/api/v0/networks/%s/clients");
int port = 443;

char roommate1_addr = "";
char roommate2_addr = "";
char roommate3_addr = "";
char roommate4_addr = "";

char *rm_pins[] = {9, 10, 11, 12};
char *rm_devices[] = {ROOMMATE_ONE, ROOMMATE_TWO, ROOMMATE_THREE, ROOMMATE_FOUR};
char *device_endpoint[] = {9, 10, 11, 12};
int *is_home[] = {0, 0, 0, 0};


WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);
int status = WL_IDLE_STATUS;
String response;
int statusCode = 0;

void setup() {
  Serial.begin(9600);

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
  }

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);


  pinMode(rm1_pin, OUTPUT);
  pinMode(rm2_pin, OUTPUT);
  pinMode(rm3_pin, OUTPUT);
  pinMode(rm4_pin, OUTPUT);


}

void loop() {

  client.get("/");

  // read the status code and body of the response
  statusCode = client.responseStatusCode();
  response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
  Serial.println("Wait five seconds");
  delay(5000);

  // Light up who's home!
  analogWrite(rm1_pin, rm1_ishome);
  analogWrite(rm1_pin, rm2_ishome );
  analogWrite(rm1_pin, rm3_ishome);
  analogWrite(rm1_pin, rm4_ishome);

}

