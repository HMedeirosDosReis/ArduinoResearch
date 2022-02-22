int sensorPin = A1;    // select the input pin for the photocell --- in my case photosensor on the left
int sensorValue = 0;  // variable to store the value coming from the sensor
void setup() 
{
Serial.begin(9600);//this is the number that should also go in the serial monitor
}
void loop()
{
sensorValue = analogRead(sensorPin);  // read the value from the sensor:
Serial.println(sensorValue);  //Serial port prints the resistance value
delay(500);
}
