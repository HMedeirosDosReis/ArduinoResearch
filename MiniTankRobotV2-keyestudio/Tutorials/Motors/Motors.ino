
#define ML_Ctrl 13  //define the direction control pin of left motor
#define ML_PWM 11   //define the PWM control pin of left motor
#define MR_Ctrl 12  //define direction control pin of right motor
#define MR_PWM 3   // define the PWM control pin of right motor

void setup()
{
  pinMode(ML_Ctrl, OUTPUT);//define direction control pin of left motor as output
  pinMode(ML_PWM, OUTPUT);//define PWM control pin of left motor as output
  pinMode(MR_Ctrl, OUTPUT);//define direction control pin of right motor as output.
  pinMode(MR_PWM, OUTPUT);//define the PWM control pin of right motor as output
}

void loop()
{ 
  digitalWrite(ML_Ctrl,LOW);//set the direction control pin of left motor to LOW
  analogWrite(ML_PWM,200);//set the PWM control speed of left motor to 200
  digitalWrite(MR_Ctrl,LOW);//set the direction control pin of right motor to LOW
  analogWrite(MR_PWM,200);//set the PWM control speed of right motor to 200

  //front
  delay(2000);//delay in 2s
   digitalWrite(ML_Ctrl,HIGH);//set the direction control pin of left motor to HIGH
  analogWrite(ML_PWM,200);//set the PWM control speed of left motor to 200  
digitalWrite(MR_Ctrl,HIGH);//set the direction control pin of right motor to HIGH
  analogWrite(MR_PWM,200);//set the PWM control speed of right motor to 200

   //back
  delay(2000);//delay in 2s 
  digitalWrite(ML_Ctrl,HIGH);//set the direction control pin of left motor to HIGH
  analogWrite(ML_PWM,200);//set the PWM control speed of left motor to 200
  digitalWrite(MR_Ctrl,LOW);//set the direction control pin of right motor to LOW
  analogWrite(MR_PWM,200);//set the PWM control speed of right motor to 200

    //left
  delay(2000);//delay in 2s
   digitalWrite(ML_Ctrl,LOW);//set the direction control pin of left motor to LOW
  analogWrite(ML_PWM,200);//set the PWM control speed of left motor to 200
  digitalWrite(MR_Ctrl,HIGH);//set the direction control pin of right motor to HIGH
  analogWrite(MR_PWM,200);//set the PWM control speed of right motor to 200

   //right
  delay(2000);//delay in 2s
  analogWrite(ML_PWM,0);//set the PWM control speed of left motor to 0
  analogWrite(MR_PWM,0);//set the PWM control speed of right motor to 0

    //stop
  delay(2000);//delay in 2s
}

/*faster

#define ML_Ctrl 13  //define the direction control pin of left motor
#define ML_PWM 11   //define the PWM control pin of left motor
#define MR_Ctrl 12  //define the control pin of right motor
#define MR_PWM 3   //define the PWM control pin of right motor
void setup()
{ pinMode(ML_Ctrl, OUTPUT);//define the direction control pin of left motor as OUTPUT
  pinMode(ML_PWM, OUTPUT);//define the PWM control pin of left motor as OUTPUT
  pinMode(MR_Ctrl, OUTPUT);//define the direction control pin of right motor as OUTPUT
  pinMode(MR_PWM, OUTPUT);//define the PWM control pin of right motor as OUTPUT

}
void loop()
{ digitalWrite(ML_Ctrl,LOW);//Set direction control pin of left motor to LOW
  analogWrite(ML_PWM,100);// Set the PWM control speed of left motor to 100
  digitalWrite(MR_Ctrl,LOW);//Set the direction control pin of right motor to LOW
  analogWrite(MR_PWM,100);//Set the PWM control speed of right motor to 100
  //front
  delay(2000);//define 2s
  digitalWrite(ML_Ctrl,HIGH);//Set direction control pin of left motor to HIGH level
  analogWrite(ML_PWM,100);//Set the PWM control speed of left motor to 100
  digitalWrite(MR_Ctrl,HIGH);//Set direction control pin of right motor to HIGH level
  analogWrite(MR_PWM,100);//Set the PWM control speed of right motor to 100
   //back
  delay(2000);//define 2s
  digitalWrite(ML_Ctrl,HIGH);//Set direction control pin of left motor to HIGH level
  analogWrite(ML_PWM,100);//Set the PWM control speed of left motor to 100
  digitalWrite(MR_Ctrl,LOW);//Set direction control pin of right motor to LOW level
  analogWrite(MR_PWM,100);//Set the PWM control speed of right motor to 100
    //left
  delay(2000);//define 2s
   digitalWrite(ML_Ctrl,LOW);//set the direction control pin of left motor to LOW
  analogWrite(ML_PWM,100);//set the PWM control speed of left motor to 200
  digitalWrite(MR_Ctrl,HIGH);//set the direction control pin of right motor to HIGH
  analogWrite(MR_PWM,100);//set the PWM control speed of right motor to 100
   //right
  delay(2000);//define 2s
  analogWrite(ML_PWM,0);//set the PWM control speed of left motor to 0
  analogWrite(MR_PWM,0);// set the PWM control speed of right motor to 0

    //stop
  delay(2000);//define 2s
}