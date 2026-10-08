#define BLYNK_TEMPLATE_ID "TMPL2BAUuQ1Mh"
#define BLYNK_TEMPLATE_NAME "smart"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#define TRIG_PIN 1 // ESP32 pin 1 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN 0 // ESP32 pin 0 connected to Ultrasonic Sensor's ECHO pin
#define TRIG__PIN 5 // ESP32 pin 5 connected to Ultrasonic Sensor's TRIG pin
#define ECHO__PIN 4 // ESP32 pin 4 connected to Ultrasonic Sensor's ECHO pin
float duration, distance,duration_, distance_;
#define ssid "Wokwi-GUEST"
#define Password ""
// Your Blynk authentication token
char auth[] = "rPftjSrei8SWTBSYxi744hY9m26vaQ9q";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32-C3!");
  Blynk.begin(auth, ssid, Password);
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,Password,6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  // configure the trigger pin to output mode
  pinMode(TRIG_PIN, OUTPUT);
  // configure the echo pin to input mode
  pinMode(ECHO_PIN, INPUT);
  // configure the trigger pin to output mode
  pinMode(TRIG__PIN, OUTPUT);
  // configure the echo pin to input mode
  pinMode(ECHO__PIN, INPUT);
  
}

void loop() {
  Blynk.run();
  // put your main code here, to run repeatedly:
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG__PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG__PIN, LOW);
 
  // measure duration of pulse from ECHO pin
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2);
  Serial.print(duration);
  Serial.print(distance);
  duration_ = pulseIn(ECHO__PIN, HIGH);
  distance_ = (duration/2);
  Serial.print(duration_);
  Serial.print(distance_);
if (distance <=600 && distance_ <=600) {
Serial.print("SPACE OCCUPIED");
Blynk.virtualWrite(V0, 0);

}
else {
Serial.print("SPACE FREE");
Blynk.virtualWrite(V0, 1);
}
  
}
