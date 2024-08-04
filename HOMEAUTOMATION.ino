#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Replace these with your Blynk credentials
#define BLYNK_TEMPLATE_ID "TMPL3gvDlC6p2"
#define BLYNK_TEMPLATE_NAME "Homeautomation"
#define BLYNK_AUTH_TOKEN "-5E0Ib3YlD-3aztFRp0zZKoRyb4nk5Om"

// Replace with your network credentials
const char* ssid = "Airtel_iqba_9101";
const char* password = "air53618";

// Define the relay pin
const int relayPin = D1; // Change this to the pin you're using

// Initialize Blynk
BlynkTimer timer;

void setup()
{
  // Debug console
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  
  // Set the relay pin as an output
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Ensure relay is off at startup
  
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensorData);
}

void loop()
{
  // Run Blynk.run() to keep the connection to Blynk alive
  Blynk.run();
  
  // Run the timer
  timer.run();
}

// Function to send sensor data (modify as needed)
void sendSensorData()
{
  // Example: Send a dummy value to a virtual pin
  int sensorValue = analogRead(A0); // Read from analog pin A0
  Blynk.virtualWrite(V5, sensorValue); // Send value to virtual pin V5
}

// Function to control the relay
BLYNK_WRITE(V1) // Virtual pin V1 to control the relay
{
  int relayState = param.asInt(); // Get the state from the app
  digitalWrite(relayPin, relayState); // Control the relay
}
