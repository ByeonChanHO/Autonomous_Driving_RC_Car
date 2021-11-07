#include <LiquidCrystal.h>


LiquidCrystal lcd(44, 45, 46, 47, 48, 49);
int PWM1 = 39;
int ENB1 = 9;
int DIR1 = 38;
int time_set = 3600;
int time_current;
const int buttonPin = 3; 
const int ledPin = 2;
const int fanPin = 4;
int fanon = 0;

int ledbuttonstate = 0;
int fanbuttonstate = 0;
int pfanbuttonstate = 0;
int ledstate = 0;

int selected_State = 0;
int buttonp = 0;
int button = 0;



void setup() {
 Serial.begin(9600);
 lcd.begin(16, 2);
  pinMode(PWM1,OUTPUT);
  pinMode(ENB1,OUTPUT);
  pinMode(DIR1,OUTPUT);
  pinMode(ledPin, OUTPUT); 
  pinMode(fanPin, OUTPUT);
  pinMode(buttonPin, INPUT); 
}
void readTemperature() {

 int reading = analogRead(55); 
 
  float voltage = reading * 5.0 / 1024.0;
  Serial.print (voltage);
  Serial.print (" V : ");
  float temp_C = voltage * 100;
  Serial.print (temp_C);
  Serial.print (" C, ");
  float temp_F = (temp_C * 9.0/5.0)+32;
  Serial.print (temp_F);
  Serial.println(" F");
}

void readIlluminance() {
  int reading1 = analogRead(56);
  int reading = analogRead(56); 
  Serial.print("ADC : ");
  Serial.print(reading);
  float voltage = reading * 5.0 / 1024.0;
  Serial.print(", Voltage : ");
  Serial.println(voltage);
}
void clapLEDActivator(){
  ledbuttonstate = digitalRead(buttonPin);
  ledstate = digitalRead(ledPin);
  if (ledstate == HIGH && ledbuttonstate == LOW) { 
    delay(250);
    digitalWrite(ledPin, LOW); 
  }
  if (ledstate == LOW && ledbuttonstate == LOW) { 
    delay(250);
    digitalWrite(ledPin, HIGH);
  }
  }
void clapFANActivator(){
  fanbuttonstate = digitalRead(buttonPin);
  digitalWrite(ENB1, HIGH);
  Serial.println(fanbuttonstate);
if ( fanbuttonstate != pfanbuttonstate){
    if(fanbuttonstate==1)
      fanon = 1;
    else
      fanon = 0;
  pfanbuttonstate = fanbuttonstate;
  }
  if(fanon == 1) { 
    delay(250);
    digitalWrite(ENB1, HIGH);
    digitalWrite(DIR1, HIGH);
    analogWrite(PWM1,0);
  }
  
}
  
void automode(){


  
}
void Clock(){
  int seconds;
  int minutes;
  int hours;
  seconds = time_set + time_current ;
  Serial.println(time_set);
  hours = seconds / 3600 ;
  minutes = (seconds%3600)/60 ;
  int seconds_output = (seconds% 3600)%60;
  lcd.setCursor(0, 1);
  lcd.print(String(hours)  + ":" + minutes + ":" + seconds_output);
  
}
void loop(){
time_current = millis()/1000;  
button = digitalRead(14);
if ( button != buttonp){
    if(button==1){
      selected_State++;
      lcd.clear(); 
      if (selected_State==4)
        selected_State=0;
  }
  buttonp = button;
  }
  Serial.println(selected_State);
switch(selected_State) {
    case 0 : //automode
        lcd.setCursor(0, 0);
        lcd.print("AutoMode");
        automode();
        break;
    case 1 : //clapmode light
        lcd.setCursor(0, 0);
        lcd.print("Light control");
        clapLEDActivator();
        break;
    case 2 : //clapmode fan
        lcd.setCursor(0, 0);
        lcd.print("FAN control");
        clapFANActivator();
        break;
    case 3 :  //clock
        lcd.setCursor(0, 0);
        lcd.print("Clock");
        Clock();
        break;
        }
}
