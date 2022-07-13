/*************************************************************
 Worked
 *************************************************************/
#define BLYNK_TEMPLATE_ID           "TMPLKqF2TOVa"
#define BLYNK_DEVICE_NAME           "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "1KEMnT-EvQ83G28v2AB6vNqLqNNoY9C0"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
char ssid[] = "V2026";
char pass[] = "hehehehe";

#define potent A0
#define button 16
BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
//BLYNK_WRITE(V0)
//{
//  // Set incoming value from pin V0 to a variable
//  int value = param.asInt();
//
//  // Update state
//  Blynk.virtualWrite(V1, value);
//}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

void uploadPotent(){
  int value_potent = analogRead(potent);
  Serial.println("Potentiometer: " + String(value_potent));
  Blynk.virtualWrite(V4, value_potent);
}

void uploadButton(){
  int value_button = digitalRead(button);
  Serial.println("Button: " + String(value_button));
  Blynk.virtualWrite(V5, value_button);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  analogReference(DEFAULT);
  Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
  timer.setInterval(100L, uploadPotent);
  timer.setInterval(100L, uploadButton);
}

void loop()
{
  Blynk.run();
  timer.run();
}

  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
