#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* ssid = "SSID";
const char* password = "Password";
#define BOTtoken "Bot-Token"
#define CHAT_ID "Chat-ID"
//#define CHAT_ID2"Chat-ID2"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int const trigPin = 4;
int const echoPin = D1;
int const buzzPin = 12;
const int LED1 = 13;


void setup() {
  
  Serial.begin(115200);
  configTime(0, 0, "pool.ntp.org");
  client.setTrustAnchors(&cert);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(LED1 , OUTPUT);

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  bot.sendMessage(CHAT_ID, "Wifi Connected!", "");
//  bot.sendMessage(CHAT_ID2, "Wifi Connected!", "");
  bot.sendMessage(CHAT_ID, "System has Started!!", "");
 // bot.sendMessage(CHAT_ID2, "System has Started!!", "");
}

bool messageSent = false; // Flag to track if message is sent // Flag to track if message is sent

void loop() {
  int alert = digitalRead(echoPin); // Read the state of the echo pin

  if (alert == HIGH && !messageSent) { // Send message only when logic low (0) is received on echo pin and message is not already sent
    bot.sendMessage(CHAT_ID, "Alert!! Saline Level is Below Threshold!!", "");
   // bot.sendMessage(CHAT_ID2, "Alert!!", "");
    digitalWrite(buzzPin, HIGH);
    digitalWrite(LED1, HIGH);
    delay(1000); // Delay to prevent continuous alerts
    digitalWrite(buzzPin, LOW); // Turn off buzzer after delay
    digitalWrite(LED1, LOW); // Turn off LED after delay
    messageSent = true;
    digitalWrite(echoPin,LOW); // Set flag to true indicating message is sent
  }

  if (messageSent) {
    return; // Exit loop() function after sending message
  }

  delay(100); // Delay to prevent excessive loop iterations
}
