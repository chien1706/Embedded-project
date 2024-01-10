#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int analogInPin = A0; // ESP8266 Analog Pin ADC0 = A0

int sensorValue = 0; // value read from the pot

int ledPin = 7; // pin of led
int cambien = 2;//Chân cảm biến nối chân số 8 Arduino
int giatri ;

#define echoPin 5
#define trigPin 6
long duration, distance;



// set increase pin and initial to time turn on led
int setOnHourPin = 13;
int setOnMinPin =12;
int setOnHour = 0;
int setOnMin = 0;

// set decrease pin and initial to time turn on led
int setOnHourPin_decrease = 9;
int setOnMinPin_decrease =8;
int setOnHour_decrease = 0;
int setOnMin_decrease = 0;

// set pin and initial to time turn off led
int setOffHourPin = 11;
int setOffMinPin = 10;
int setOffHour = 0;
int setOffMin = 0;

// set pin and initial to time turn off led
int setOffHourPin_decrease = 4;
int setOffMinPin_decrease = 3;
int setOffHour_decrease = 0;
int setOffMin_decrease = 0;

RTC_DS1307 rtc;



void setup()
{
    lcd.init();
    lcd.backlight();
    lcd.print("Embbeded Project");
    lcd.setCursor(0, 1);
    lcd.print("CHIEN & MINH");
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");

    // initialize serial communication at 115200
    Serial.begin(115200);

    // set pin mode to timer turn on led
    pinMode(setOnHourPin, INPUT);
    pinMode(setOnMinPin, INPUT);

    // set pin mode to timer turn off led
    pinMode(setOffHourPin, INPUT);
    pinMode(setOffMinPin, INPUT);

  pinMode(cambien, INPUT);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // set pin mode of led pid
    pinMode(ledPin, OUTPUT);
    if (!rtc.begin())
    {
        Serial.print("Couldn't find RTC");
        while (1)
            ;
    }

    if (!rtc.isrunning())
    {
        Serial.print("RTC is NOT running!");
        Serial.println();
    }
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void loop()
{
    int t = 2;
    // read the analog in value
      giatri = digitalRead(cambien); //Đọc giá trị digital từ cảm biến và gán vào biến giatri
    sensorValue = analogRead(analogInPin);
     Serial.print("Giá trị cảm biến là: ");
  Serial.println(sensorValue);
digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    
    digitalWrite(echoPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    
    distance = duration/40;

    DateTime now = rtc.now();
    // Print to LCD current time
    lcd.setCursor(0, 0);
    lcd.print("Cur time: ");
    if (now.hour() <= 9)
    {
        lcd.print("0");
        lcd.print(now.hour());
    }
    else
    {
        lcd.print(now.hour());
    }
    lcd.print(':');
    if (now.minute() <= 9)
    {
        lcd.print("0");
        lcd.print(now.minute());
    }
    else
    {
        lcd.print(now.minute());
    }
    // print to LCD ON time
    lcd.setCursor(0, 1);
    lcd.print("ON");
    if (setOnHour <= 9)
    {
        lcd.print("0");
        lcd.print(setOnHour);
    }
    else
    {
        lcd.print(setOnHour);
    }
    lcd.print(':');
    if (setOnMin <= 9)
    {
        lcd.print("0");
        lcd.print(setOnMin);
    }
    else
    {
        lcd.print(setOnMin);
    }
    // Set ON time
    if (digitalRead(setOnHourPin) == HIGH)
    {
        setOnHour++;
        if (setOnHour > 23)
            setOnHour = 0;
    }

    if (digitalRead(setOnMinPin) == HIGH)
    {
        setOnMin++;
        if (setOnMin > 59)
            setOnMin = 0;
    }

    // Set ON time decrease
    if (digitalRead(setOnHourPin_decrease) == HIGH)
    {
        setOnHour--;
        if (setOnHour < 0)
            setOnHour = 23;
    }

    if (digitalRead(setOnMinPin_decrease) == HIGH)
    {
        setOnMin--;
        if (setOnMin < 0)
            setOnMin = 59;
    }

    // Print to LCD OFF Time

    lcd.setCursor(8, 1);
    lcd.print("OFF");
    if (setOffHour <= 9)
    {
        lcd.print("0");
        lcd.print(setOffHour);
    }
    else
    {
        lcd.print(setOffHour);
    }
    lcd.print(':');
    if (setOffMin <= 9)
    {
        lcd.print("0");
        lcd.print(setOffMin);
    }
    else
    {
        lcd.print(setOffMin);
    }
    // Set OFF time
    if (digitalRead(setOffHourPin) == HIGH)
    {
        setOffHour++;
        if (setOffHour > 23)
            setOffHour = 0;
    }

    if (digitalRead(setOffMinPin) == HIGH)
    {
        setOffMin++;
        if (setOffMin > 59)
            setOffMin = 0;
    }


  // Set OFF time decrease
    if (digitalRead(setOffHourPin_decrease) == HIGH)
    {
        setOffHour--;
        if (setOffHour < 0)
            setOffHour = 23;
    }

    if (digitalRead(setOffMinPin_decrease) == HIGH)
    {
        setOffMin--;
        if (setOffMin < 0)
            setOffMin = 59;
    }
    // Logic
    // Turn ON/OFF depend on timer

    if ( (now.hour() * 60 + now.minute() - (setOnHour* 60 + setOnMin) ) >= 0 && (now.hour() * 60 + now.minute() - (setOffHour* 60 + setOffMin) < 0)) 
    {
        t = 0;
    }

    else {
      t = 1;
    }

    if (t == 1)
      {
        digitalWrite(ledPin, LOW);
        
      }
    if(t==0){
      digitalWrite(ledPin, HIGH);
      delay(1000);
    }
      

    //turn ON/OFF depend on sensor
    if (sensorValue < 50)
    {
      digitalWrite(ledPin, HIGH);
      delay(1000);
    }
    if (sensorValue > 50)
    {
      digitalWrite(ledPin, LOW);
    }
   delay(100);
   if (giatri == 1)
  {
    digitalWrite(ledPin, HIGH);
    delay(3000);
  }
  else
  {
   digitalWrite(ledPin, LOW);
  }
    if(distance<40)
        {
        digitalWrite(ledPin, HIGH);
        delay(3000);
    }
    else
        {
        digitalWrite(ledPin, LOW);
}
}


