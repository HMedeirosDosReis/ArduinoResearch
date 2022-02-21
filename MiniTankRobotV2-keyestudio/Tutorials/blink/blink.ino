
void setup()
{
   pinMode(LED_BUILTIN, OUTPUT); // initialize digital pin 2 as an output.
}
void loop() // the loop function runs over and over again forever

{
   digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
   delay(1000);           // wait for a second
   digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
   delay(1000);           // wait for a second
}
