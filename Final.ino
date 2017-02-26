#include <OneWire.h>
#include <DallasTemperature.h>
#define RELAY 7  
//#define RELAY1 14  
#include <LiquidCrystal.h>
#define echoPin 13 // Echo Pin
#define trigPin 8 // Trigger Pin
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
//int RELAY1 = 14;
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//int maximumRange = 200; // Maximum range needed
//int minimumRange = 0; // Minimum range needed
long duration, distance, temp; // Duration used to calculate distance

void setup()

{  
Serial.begin(9600);  
//lcd.print("Level :");

//Serial.begin(9600);
  pinMode(RELAY, OUTPUT);     
lcd.begin(16, 2);
  // Print a message to the LCD.
   pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT); 
// pinMode(RELAY1, OUTPUT);
 pinMode(A2, OUTPUT);
 sensors.begin(); // IC Default 9 bit. If you have troubles consider upping it 12. Ups the delay giving the IC more time to process the temperature measurement

}

  void loop()

{
lcd.setCursor(0, 0);
lcd.print("Level: ");
Serial.print("Level: ");
/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
digitalWrite(trigPin, LOW);  //output 
 delayMicroseconds(2); 
 digitalWrite(trigPin, HIGH);   //output
 delayMicroseconds(1000); 
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
 

 Serial.print(distance);
 Serial.print("cm  ");
if(distance <= 15 && distance > 2)
{
digitalWrite(RELAY,0);           // Turns ON Relays

 lcd.print(distance);
// Serial.print(distance);
 //Serial.print("cm  ");
 lcd.print(" CM");
 //lcd.println();
}
else if(distance <= 2)
{
  
  digitalWrite(RELAY,1);    // Turns OFF Relays
   lcd.print(distance);
 lcd.print(" CM");
// Serial.print(distance);
// Serial.print("CM");
  //lcd.println();
}

//temp=sensors.getTempCByIndex(0);
lcd.setCursor(0,1);
lcd.print("Temp: ");
 sensors.requestTemperatures(); // Send the command to get temperatures
Serial.print(sensors.getTempCByIndex(0) );

if(sensors.getTempCByIndex(0) < 33)
{
 
//digitalWrite(RELAY1,0);    // Turns ON Relays
digitalWrite(A2,0); 
 lcd.print(sensors.getTempCByIndex(0));
 lcd.print(" C");
 //Serial.print(sensors.getTempCByIndex(0));

}

else if(sensors.getTempCByIndex(0) > 33)
{
  
//digitalWrite(RELAY1,1);    // Turns OFF Relays
digitalWrite(A2,1); 
  lcd.print(sensors.getTempCByIndex(0));
  lcd.print(" C");
  //Serial.print(sensors.getTempCByIndex(0));

}


 delay(500);

   
}
