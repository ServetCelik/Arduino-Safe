/* Servet Can Celik
    06/10/2021
    operation SAFE
*/

#include "Display.h"
const int buttonRight = 8;          //these are the component which we will use on this project.
const int buttonLeft = 9;
const int ledRed = 4;
const int ledGreen = 5;
const int ledYellow = 7;
const int buzzer = 3;
const int LDR = A2;

int firstnumber = 1;                //Firstly we declared 4 int for our 4 digit on the screen.
int secondnumber = 1;
int thirdnumber = 1;
int fourthnumber = 1;

const String password = "1112";     //Our password is a constant string.
String numberSelected;              //This is the number which we made it from our 4 numbers.
bool alarmActivated = true;        //these 2 bool's are declared to understand whether the alarm is activated or the door closed.
bool doorClosed = true;
bool state = true;                  // I used this variable to show "-" symbol before each digit.
int pos = 1;
int counter = 0;                    // With this variable, we will count everytime when the door is opened.
int counterWrong = 0;               //With this variable, we will count every false password input attempt.
int counterSafe;
int lastbuttonState = HIGH;         //These 3 variables are for preventing bouncing.
int buttonState;
int buttonNumber;

String number1Str;                  //These 4 numbers are the string version of our 4 digits.
String number2Str;
String number3Str;
String number4Str;

String first2Number;                //These number are concatenated version of our digits.
String first3Number;
String first4Number;

int thresholdLow;
int thresholdHigh;
int rangeHalf = 70;

void setup() {
  pinMode(buttonRight, INPUT_PULLUP);
  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(LDR, INPUT);
  int val = analogRead(LDR);
  thresholdLow = val - rangeHalf;
  thresholdHigh = val + rangeHalf;

  Serial.begin(9600);
}

void loop() {
  Display.clear();

  int valCurrent = analogRead(LDR);  
  buttonState = digitalRead(buttonLeft);
  buttonNumber = digitalRead(buttonRight);

  if (lastbuttonState != buttonState && buttonState == LOW && alarmActivated)    //These part is made to check the next digit.
  { pos++;
    pos = pos % 5;
    state = true;
    tone(buzzer, 400, 100);
  }
  if (alarmActivated)
  {
    if (pos == 1) {                                                               //Next 4 steps are made to arrange our numbers.
      if (state)
      { Display.show("-");
        if (buttonNumber != lastbuttonState && buttonNumber == LOW)
        {
          state = false;
          tone(buzzer, 200, 100);
        }
      }
      else {
        Display.show(number1Str);
        state = false;
        if (buttonNumber != lastbuttonState && buttonNumber == LOW) {

          firstnumber++;
          tone(buzzer, 200, 100);
          if (firstnumber == 6)
          {
            firstnumber = 1;
          }
        }
      }
    }
    else if (pos == 2)
    {
      if (state)
      { Display.show(number1Str + "-");
        if (buttonNumber != lastbuttonState && buttonNumber == LOW)
        {
          state = false;
          tone(buzzer, 200, 100);
        }
      }
      else {
        first2Number = number1Str + number2Str;
        Display.show(first2Number);
        if (buttonNumber != lastbuttonState && buttonNumber == LOW)

        { secondnumber++;
          tone(buzzer, 200, 100);
          if (secondnumber == 6)
          {
            secondnumber = 1;
          }
        }
      }
    }
    else if (pos == 3) {
      if (state)
      { Display.show(first2Number + "-");
        if (buttonNumber != lastbuttonState && buttonNumber == LOW)
        {
          state = false;
          tone(buzzer, 200, 100);
        }
      }
      else
      {
        first3Number = number1Str + number2Str + thirdnumber;
        Display.show(first3Number);
        if (buttonNumber != lastbuttonState && buttonNumber == LOW)
        { thirdnumber++;
          tone(buzzer, 200, 100);
          if (thirdnumber == 6)
          {
            thirdnumber = 1;
          }
        }
      }
    }
    else if (pos == 4) {
      if (state)
      { Display.show(first3Number + "-");
        if (buttonNumber != lastbuttonState && buttonNumber == LOW)
        {
          state = false;
          tone(buzzer, 200, 100);
        }
      }
      else {
        first4Number = number1Str + number2Str + thirdnumber + fourthnumber;
        Display.show(first4Number);
        if (buttonNumber != lastbuttonState && buttonNumber == LOW)

        { fourthnumber++;
          tone(buzzer, 200, 100);
          if (fourthnumber == 6)
          {
            fourthnumber = 1;
          }
        }
      }
    }
    else  if (pos == 0)                                             //These step is for count wrong input attempts. We count them.
    {
      counterWrong++;
      counterWrong = counterWrong % 4;

      firstnumber = 1;
      secondnumber = 1;
      thirdnumber = 1;
      fourthnumber = 1;
      number1Str =  String(firstnumber);
      number2Str =  String(secondnumber);
      number3Str =  String(thirdnumber);
      number4Str =  String(fourthnumber);
      first2Number = number1Str + number2Str;
      first3Number = number1Str + number2Str + thirdnumber;
      first4Number = number1Str + number2Str + thirdnumber + fourthnumber;

      if (counterWrong == 3)
      {
        Serial.print("ALARM SAFE#");
        tone(buzzer, 400, 1000);
        digitalWrite(ledRed, HIGH);
        delay(1000);
        tone(buzzer, 800, 1000);
        digitalWrite(ledRed, LOW);
        delay(1000);
        tone(buzzer, 400, 1000);
        digitalWrite(ledRed, HIGH);
        delay(1000);
        tone(buzzer, 800, 1000);
        digitalWrite(ledRed, LOW);
        delay(1000);
        tone(buzzer, 400, 1000);
        digitalWrite(ledRed, HIGH);
        delay(1000);
        digitalWrite(ledRed, LOW);
      }
      delay(100);
      pos++;
    }
  }
  lastbuttonState = buttonNumber;
  lastbuttonState = buttonState;

  number1Str =  String(firstnumber);
  number2Str =  String(secondnumber);
  number3Str =  String(thirdnumber);
  number4Str =  String(fourthnumber);

  numberSelected = number1Str + number2Str + number3Str + number4Str;

  if (valCurrent > thresholdHigh)
  {
    doorClosed = false;
    counter++;
  }
  else if (valCurrent < thresholdLow)
  {
    doorClosed = true;
  }
  if (numberSelected == password && doorClosed && alarmActivated)              //If password is true, door is closed and alarm is active, then alarm will be deactivated.
  {
    digitalWrite(ledGreen, HIGH);
    delay(2000);
    digitalWrite(ledGreen, LOW);
    tone(buzzer, 800, 500);
    alarmActivated = false;
    counterSafe = counter;
  }
  else if (numberSelected != password && !doorClosed && alarmActivated)        //If password is true but door is open and alarm is active,red light and our buzzer turns on
  {
    tone(buzzer, 400, 1000);
    digitalWrite(ledRed, HIGH);
    delay(1000);
    tone(buzzer, 800, 1000);
    digitalWrite(ledRed, LOW);
    delay(1000);
    tone(buzzer, 400, 1000);
    digitalWrite(ledRed, HIGH);
    delay(1000);
    tone(buzzer, 800, 1000);
    digitalWrite(ledRed, LOW);
    delay(1000);
    tone(buzzer, 400, 1000);
    digitalWrite(ledRed, HIGH);
    delay(1000);
    digitalWrite(ledRed, LOW);
    alarmActivated = false;
  }
  else if (doorClosed && !alarmActivated && counter > counterSafe)             //After we open and close the door again, alarm will be activated.
  {
    digitalWrite(ledYellow, HIGH);
    delay(1000);
    digitalWrite(ledYellow, LOW);
    tone(buzzer, 800, 500);
    alarmActivated = true;
    firstnumber = 1;
    secondnumber = 1;
    thirdnumber = 1;
    fourthnumber = 1;
    pos = 1;
    state = true;
  }
  delay(200);
}
