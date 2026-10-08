#define BLYNK_TEMPLATE_ID "TMPL2BAUuQ1Mh"
#define BLYNK_TEMPLATE_NAME "smart"
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <BlynkSimpleEsp32.h>

// Firebase credentials
#define FIREBASE_HOST "https://smartpark-fd2b1-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "d8qgEZYypszmWL6uCrLswu3GMVrC5ZzNqriLFXf8"

const int trigPin1 = 15; // Trigger pin for ultrasonic sensor 1
const int echoPin1 = 2;  // Echo pin for ultrasonic sensor 1
const int trigPin2 = 4;  // Trigger pin for ultrasonic sensor 2
const int echoPin2 = 5;  // Echo pin for ultrasonic sensor 2

#define ssid "joe"
#define Password "Connectio"

// Your Blynk authentication token
char auth[] = "rPftjSrei8SWTBSYxi744hY9m26vaQ9q";

FirebaseData firebaseData;
FirebaseAuth authData;
FirebaseConfig config;

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32-C3!");
  Serial.print("Connecting to WiFi");
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, Password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  
  Blynk.begin(auth, ssid, Password);

  // Configure Firebase
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&config, &authData);
  Firebase.reconnectWiFi(true);

  // Configure the trigger pins to output mode
  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);

  // Set the echo pins as inputs
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
}

void loop() {
  Blynk.run();

  long distance1 = getDistance(trigPin1, echoPin1);
  long distance2 = getDistance(trigPin2, echoPin2);

  // Print distances to the serial monitor
  Serial.print("Distance 1: ");
  Serial.print(distance1);
  Serial.print(" cm, Distance 2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  String status1 = "free";

  if (distance1 <= 120 && distance2 <= 120) {
    Serial.println("SPACE OCCUPIED");
    Blynk.virtualWrite(V2, "SLOT 2 OCCUPIED");
    status1 = "occupied";
  } else if (distance1 >= 120 && distance2 >= 120) {
    Serial.println("SPACE FREE");
    Blynk.virtualWrite(V2, "SLOT 2 FREE");
    status1 = "free";
  } else {
    Serial.println("OBSTRUCTION DETECTED");
    Blynk.virtualWrite(V2, "SLOT 2 OBSTRUCTION");
    status1 = "obstruction";
  }

  // Send data to Firebase
  Firebase.setString(firebaseData, "/parking/slot1/status", status1);
}

long getDistance(int trigPin, int echoPin) {
  // Send a pulse to trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance (in cm) based on the speed of sound
  long distance = duration * 0.034 / 2;

  return distance;
}
