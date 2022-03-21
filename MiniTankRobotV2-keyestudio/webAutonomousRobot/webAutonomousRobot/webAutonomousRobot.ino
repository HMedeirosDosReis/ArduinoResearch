#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "AndroidAP";
char pass[] = "hhxm1542";
int status = WL_IDLE_STATUS;
WiFiServer server(80); // server socket

WiFiClient client = server.available();

int ledPin = LED_BUILTIN;
// int ledPin = LED_BUILTIN;2
#define SCL_Pin A5 // Set clock pin to A5
#define SDA_Pin A4 // Set data pin to A4

#define ML_Ctrl 13  // define the direction control pin of left motor
#define ML_PWM 11   // define PWM control pin of left motor
#define MR_Ctrl 12  // define the direction control pin of right motor
#define MR_PWM 3    // define PWM control pin of right motor
#define servoPin 10 // pin of servo
int pulsewidth;     // save the pulse width value of servo

int trigPin = 5; // ultrasonic trig Pin
int echoPin = 4; // ultrasonic echo Pin
long duration, cm;
int random2;
int a;
int a1;
int a2;
void setup()
{
  Serial.begin(9600);
  // motors
  pinMode(ML_Ctrl, OUTPUT);
  pinMode(ML_PWM, OUTPUT);
  pinMode(MR_Ctrl, OUTPUT);
  pinMode(MR_PWM, OUTPUT);
  // trig echo
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // servo
  pinMode(servoPin, OUTPUT);
  procedure(90);

  while (!Serial)
    ;

  enable_WiFi();
  connect_WiFi();

  server.begin();
  printWifiStatus();
}

void loop()
{
  client = server.available();

  if (client)
  {
    printWEB();
  }
}

void printWifiStatus()
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");

  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

void enable_WiFi()
{
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true)
      ;
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0")
  {
    Serial.println("Please upgrade the firmware");
  }
}

void connect_WiFi()
{
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
}
/*functions for driving should come here ***********/
void printWEB()
{

  if (client)
  {                               // if you get a client,
    Serial.println("new client"); // print a message out the serial port
    String currentLine = "";      // make a String to hold incoming data from the client
    while (client.connected())
    { // loop while the client's connected
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c);        // print it out the serial monitor
        if (c == '\n')
        { // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0)
          {

            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // create the buttons
            client.print("Click <a href=\"/R\">here</a> to turn right<br>");
            client.print("Click <a href=\"/L\">here</a> to turn left<br>");
            client.print("Click <a href=\"/F\">here</a> to go foward<br>");
            client.print("Click <a href=\"/B\">here</a> to go backward<br><br>");
            client.print("Click <a href=\"/A\">here</a> to turn on autopilot<br>");
            client.print("Click <a href=\"/O\">here</a> to turn off autopilot<br>");

            // int randomReading = analogRead(A1);
            // client.print("Random reading from analog pin: ");
            // client.print(randomReading);

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else
          { // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r')
        {                   // if you got anything else but a carriage return character,
          currentLine += c; // add it to the end of the currentLine
        }

        if (currentLine.endsWith("GET /R"))
        {
          carRight(); // should go right
        }
        if (currentLine.endsWith("GET /L"))
        {
          carLeft(); // should go left
        }
        if (currentLine.endsWith("GET /F"))
        {
          carFront(); // should go foward
        }
        if (currentLine.endsWith("GET /B"))
        {
          carBack(); // should go back
        }
        // needs testing
        while (currentLine.endsWith("GET /A"))
        {
          carAuto(); // should turn on autopilot
        }
        if (currentLine.endsWith("GET /O"))
        {
          carStop(); // should turn off autopilot
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
/*servo control---needs work*/
void procedure(int myangle)
{
  for (int i = 0; i <= 50; i = i + (1))
  {
    pulsewidth = myangle * 11 + 500;
    digitalWrite(servoPin, HIGH);
    delayMicroseconds(pulsewidth);
    digitalWrite(servoPin, LOW);
    delay((20 - pulsewidth / 1000));
  }
}
/*drive*/
void carFront()
{
  digitalWrite(MR_Ctrl, LOW);
  analogWrite(MR_PWM, 200);
  digitalWrite(ML_Ctrl, LOW);
  analogWrite(ML_PWM, 200);
}
void carBack()
{
  digitalWrite(MR_Ctrl, HIGH);
  analogWrite(MR_PWM, 200);
  digitalWrite(ML_Ctrl, HIGH);
  analogWrite(ML_PWM, 200);
}
void carLeft()
{
  digitalWrite(MR_Ctrl, LOW);
  analogWrite(MR_PWM, 255);
  digitalWrite(ML_Ctrl, HIGH);
  analogWrite(ML_PWM, 255);
}
void carRight()
{
  digitalWrite(MR_Ctrl, HIGH);
  analogWrite(MR_PWM, 255);
  digitalWrite(ML_Ctrl, LOW);
  analogWrite(ML_PWM, 255);
}
void carStop()
{
  digitalWrite(MR_Ctrl, LOW);
  analogWrite(MR_PWM, 0);
  digitalWrite(ML_Ctrl, LOW);
  analogWrite(ML_PWM, 0);
}

// The function to control ultrasonic sensor
float checkdistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float distance = pulseIn(echoPin, HIGH) / 58.00; // 58.20, that is, 2*29.1=58.2
  delay(10);
  Serial.println(distance);
  return distance;
}
// autopilot
void carAuto()
{
  // Serial.println(distance);
  random2 = random(1, 100);
  a = checkdistance(); // assign the front distance detected by ultrasonic sensor to variable a

  if (a < 20) // when the front distance detected is less than 20
  {
    carStop();      // robot stops
    delay(500);     // delay in 500ms
    procedure(160); // Ultrasonic platform turns left
    for (int j = 1; j <= 10; j = j + (1))
    {                       // for statement, the data will be more accurate if ultrasonic sensor detect a few times.
      a1 = checkdistance(); // assign the left distance detected by ultrasonic sensor to variable a1
    }
    delay(300);
    procedure(20); // Ultrasonic platform turns right
    for (int k = 1; k <= 10; k = k + (1))
    {
      a2 = checkdistance(); // assign the right distance detected by ultrasonic sensor to variable a2
    }

    if (a1 < 50 || a2 < 50) // robot will turn to the longer distance side when left or right distance is less than 50cm.
    {
      if (a1 > a2) // left distance is greater than right side
      {
        procedure(90); // Ultrasonic platform turns back to right ahead
        carLeft();     // robot turns left
        delay(500);    // turn left for 500ms
        carFront();    // go front
      }
      else
      {
        procedure(90);
        carRight(); // robot turns right
        delay(500);
        carFront(); // go front
      }
    }
    else // If both side is greater than or equal to 50cm, turn left or right randomly
    {
      if ((long)(random2) % (long)(2) == 0) // When the random number is even
      {
        procedure(90);
        carLeft(); // tank robot turns left
        delay(500);
        carFront(); // go front
      }
      else
      {
        procedure(90);
        carRight(); // robot turns right
        delay(500);
        carFront(); // go front
      }
    }
  }
  else // If the front distance is greater than or equal to 20cm, robot car will go front
  {
    carFront(); // go front
  }
}
