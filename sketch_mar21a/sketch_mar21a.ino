// Sensor pins pin D6 LED output, pin A0 analog Input
#include "pitches.h"
#include <LiquidCrystal.h>

#define ledPin 6
#define sensorPin A0

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int duration = 500;  // 500 miliseconds
int buzzer = 8;
bool flooded = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Safe!");

}

void ring(){
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // pin8 output the voice, every scale is 0.5 sencond
    tone(buzzer, melody[thisNote], duration);
     
    // Output the voice after several minutes
    if (thisNote == 7) {
      noTone(buzzer);
      break;
    }
    
  }

}

void loop() {

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
 
  // print the number of seconds since reset:
    
  int time = millis() / 1000;
  int sensorValue = analogRead(sensorPin);
  if (sensorValue >= 100) {
    
    lcd.begin(16, 2);
    lcd.print("Flood Alert!!!");
  
    lcd.setCursor(0, 1);
    lcd.print( millis() / 1000);
    int outputValue = map(sensorValue, 100, 800, 0, 255);
    Serial.println(outputValue);

    analogWrite(ledPin, outputValue); // generate PWM signal
    ring();
    
  } 
  /* } else {
    lcd.setCursor(0, 1);
    lcd.print(time);
    int outputValue = map(sensorValue, 100, 800, 0, 255);
    Serial.println(outputValue);

    analogWrite(ledPin, outputValue); // generate PWM signal
    ring();
  }
  */

}
