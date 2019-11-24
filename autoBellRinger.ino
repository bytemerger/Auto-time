#include <Wire.h>
#include <LiquidCrystal.h>
#include "RTClib.h"

DateTime now;

RTC_DS1307 RTC;
LiquidCrystal lcd(3,4,5,6,7,8); // (rs, e, d4, d5, d6, d7)

void showTime(void);

int hours;
int minutes;
int seconds;
int times;
int period;
int timerem;
int timeremM;
int timeremS;
int startime = 8;
int buzzerpin = 10;
int sec;
int mins;


void setup ()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  //delay(2000);
   // Check to see if the RTC is keeping time.  If it is, load the time from your computer.
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // This will reflect the time that your sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  
  
  //for lcd without potentiometer
  analogWrite(9,150);
  // for buzzer output
  pinMode(10, OUTPUT);
  
  mins=timeremM;
  sec=timeremS;
  
}

void loop () 
{
  now = RTC.now();
  hours = now.hour();
  minutes= now.minute();
  seconds= now.second();
  Serial.println(hours);
  times=(hours*3600) + (minutes*60) + (seconds);
 //compare time with the school timetable time.
// to find out time remaining for period to elapse
  timerem = (times - 28800) % 2100;
  //find out how many minutes remaining
  timeremM= (2100-timerem)/60;
  //find out how many seconds remaining
  timeremS= (2100-timerem)%60;
  //get the particular period
  period = ((times - 28800)/2100)+1;
  
  digitalWrite(10,LOW);
 if(period < 1){
  lcd.setCursor(7,0);
  lcd.print("ASSEMBLY");
  showTime();
  }
 lcd.setCursor(6,0);
 switch (period){
  
  case 1:
    lcd.print("1st Class");
    break;
  case 2:
    lcd.print("2nd Class");
    break;
  case 3:
    lcd.print("3rd Class");
    break;
  case 4:
    lcd.setCursor(7,0);
    lcd.print("4th Class");
    break;
  case 5:
    lcd.print("5th Class");
    break;
  case 6:
    lcd.print("6th Class");
    break;
  case 7:
    lcd.print("B R E A K !!!");
    break;
  case 8:
    lcd.print("7th Class");
    break;
  case 9:
    lcd.print("8th Class");
    break;
  case 10:
    lcd.print("9th Class");
    break;
  case 11:
    lcd.print("10th Class");
    break;
  case 12:
    lcd.print("11th Class");
    break;
  }
     
     if(timeremM<0)
     {
     digitalWrite(10,HIGH);
     //period = period + 1;
     }
     if(timeremM>9)
     {
      //printing the minute for countdown
     lcd.setCursor(0,0);
     lcd.print(timeremM);
      lcd.setCursor(2,0);
     lcd.print(":");
     }
     else
     {
      //if it less than 10
     lcd.setCursor(0,0);
     lcd.print("0"); 
     lcd.setCursor(1,0);
     lcd.print(timeremM);
     lcd.setCursor(2,0);
     lcd.print(":");
     }
      
     if(timeremS>9)
     {
      //printing seconds
     lcd.setCursor(3,0);
     lcd.print(timeremS);
     }
     else
     {
      //if it is less than 10
     lcd.setCursor(3,0);
     lcd.print("0"); 
     lcd.setCursor(4,0);
     lcd.print(timeremS);
     lcd.setCursor(5,0);
     lcd.print(" ");
     }
  
  showTime();
}
//function to show the normal time
 void showTime()
 {
//  clock = RTC.now();
  lcd.setCursor(11,1);
  lcd.print(RTC.now().hour());
  lcd.print(':');
  lcd.print(RTC.now().minute());
} 
