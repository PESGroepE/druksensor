#include <SPI.h>
#include <ESP8266WiFi.h>

int drukPin = A0;               //pin waar de sensor op is aangesloten
int druk;                       //analoge waarde gelezen door de sensor

const char* ssid = "pigroep5";  //SSID van het WiFi-netwerk
const char* pass = "pigroep5";  //Wachtwoord van het WiFi-netwerk
const char* host = "10.0.10.1"; //IP-adres van de Pi
const int port = 8080;          //Poort van de server


void setup(void) {
  Serial.begin(9600);
  pinMode(drukPin, INPUT);

  WiFi.begin("pigroep5", "pigroep5"); // probeer te verbinden met de wifi
  Serial.println("Connecting to pigroep5 WiFi");
  while (WiFi.status() != WL_CONNECTED) // wacht totdat hij is verbonden
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop(void) {
  druk = analogRead(drukPin);

  Serial.print("Analoge waarde = ");
  Serial.print(druk);     //print rauwe analoge output

  sendHttpRequest(druk);

  delay(1000);
}

void sendHttpRequest(int druk) {
  WiFiClient client;

  if (!client.connect(host, port)) {
    Serial.println(F("Failed to connect to server"));
    return;
  }

  //Maak HTTP-verzoek met druk waardes
  String request = "/druksensor/druk?value=";

  // Stuur HTTP-verzoek
  client.print(String("POST ") + request + druk + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(10);
  client.stop();

  Serial.println(F("HTTP request sent to server"));
}


void connectWiFi() {
  WiFi.begin(ssid, pass); //Probeer verbinding te maken met het WiFi-netwerk.
  Serial.println("Connecting to Pi WiFi");
  while (WiFi.status() != WL_CONNECTED) //Wacht tot verbonden.
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}






