#define BLYNK_TEMPLATE_ID "TMPL3Ce6brFfH"
#define BLYNK_TEMPLATE_NAME "smart garbage"
#define BLYNK_AUTH_TOKEN "HND8CwSqbxGX0HqyMH0jxfveeKZ4JJJ5"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "vivoV235G";
char pass[] = "70867086";
BlynkTimer timer;
#define echoPin 32
#define trigPin 33
#include<ESP32Servo.h>
Servo servo;
long duration;
int distance;
int binLevel=0;
void SMESensor()
{
 int ir=digitalRead(34);
 if(ir==HIGH)
 {
 servo.write(90);
 for(int i=0; i<10; i++)
 {
 Blynk.virtualWrite(V2, 90);
 ultrasonic();
delay(100);
 }
 servo.write(0);

 Blynk.virtualWrite(V2, 0);
 }
 if(ir==LOW)
 {

 ultrasonic();
 delay(200);
 }
}
void ultrasonic()
{
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 distance = duration * 0.034 / 2; //formula to calculate the distance for ultrasonic sensor
 binLevel=map(distance, 12, 0, 0,140); // ADJUST BIN HEIGHT HERE
 Blynk.virtualWrite(V0, distance);
 Blynk.virtualWrite(V1, binLevel);
}
void setup()
{
 Serial.begin(9600);
 servo.attach(13);
 pinMode(34, INPUT);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 Blynk.begin(auth, ssid, pass);
 delay(2000);
 timer.setInterval(1000L, SMESensor);
 // Move the servo to a known position during setup for calibration/debugging
 servo.write(90);
14
 delay(5000); // Wait for the servo to move
 Serial.println("Servo initialized at 90 degrees");
}
void loop()
{
 Blynk.run();
 timer.run();
}
