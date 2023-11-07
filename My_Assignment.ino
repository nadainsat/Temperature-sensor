#include <TimerOne.h> // Timing library
#define LM35_PIN A0  // Analog pin where LM35 is connected
#define LED_PIN 13   // Arduino's onboard LED
int Temperature = 0 ; // Variables used to store temperature readings
int DelayCounter = 0 ; // Variables used to count delays
int PinState = 0 ;  // Variables used to store LED state

typedef enum 
{
  SENSOR_State_Cold,
  SENSOR_State_HOT
}SENSOR_States;

SENSOR_States SENSOR_Current_State = SENSOR_State_Cold ; // Variable to keep track of the current state

 void ToggleLed () 
 {
  if ( PinState ) { digitalWrite ( 13 , LOW ) ; }
  else { digitalWrite ( 13 , HIGH ) ; }
 }

 int ReadTemperature () { 
  int rawValue = analogRead(LM35_PIN); //Reading the value from sensor
  float voltage = (rawValue / 1023.0) * 5.0; // Convert to voltage (5V reference)
  float celsius = (voltage - 0.5) * 100.0;    // LM35 sensor's scale
  Serial.print("Temperature: ");
  Serial.print(celsius);
  Serial.println(" °C");
  return celsius;   
 }
void setup() {
Serial.begin(9600); // Initializes the Serial communication with a baud rate of 9600
Timer1.initialize(250000); // Initializes a timer with a 250,000-microsecond (250 ms) interval
pinMode(13,OUTPUT);
pinMode( LM35_PIN , INPUT ) ;

}
void Blinkled()
     {
      Temperature = ReadTemperature () ; // Read temperature from the sensor
      if ( Temperature > 30 ) { SENSOR_Current_State = SENSOR_State_HOT ; }
      else { SENSOR_Current_State = SENSOR_State_Cold ; }
      
      switch ( SENSOR_Current_State ) 
      {
        case SENSOR_State_Cold :
        DelayCounter ++ ; 
        if  ( DelayCounter == 1 ) // means 250 ms passed
        {
          ToggleLed() ;
          DelayCounter = 0 ; 
        }
        break ;  
        case SENSOR_State_HOT : 
        DelayCounter ++ ; 
        if  ( DelayCounter == 2 ) // means 250 * 2 = 500 ms passed 
        {
          ToggleLed() ;
          DelayCounter = 0 ;
        }
        break ;
      }
     }

void loop() {
   Timer1.attachInterrupt(Blinkled); // Execution periodically based on the timer interval
   
    
}
