
#include <OneWire.h>
#include <DallasTemperature.h>

// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include <Wire.h>

// Data wire is plugged into pin 2 on the Arduino Uno
#define ONE_WIRE_BUS1 0
#define ONE_WIRE_BUS2 1
#define ONE_WIRE_BUS3 2
#define ONE_WIRE_BUS4 3
#define ONE_WIRE_BUS5 4
#define ONE_WIRE_BUS6 5
#define ONE_WIRE_BUS7 6
#define ONE_WIRE_BUS8 7
#define ONE_WIRE_BUS9 8
#define ONE_WIRE_BUS10 9
#define ONE_WIRE_BUS11 10
#define ONE_WIRE_BUS12 11
#define ONE_WIRE_BUS13 12
#define ONE_WIRE_BUS14 13

 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)


OneWire oneWire0(ONE_WIRE_BUS1);
OneWire oneWire1(ONE_WIRE_BUS2);
OneWire oneWire2(ONE_WIRE_BUS3);
OneWire oneWire3(ONE_WIRE_BUS4);
OneWire oneWire4(ONE_WIRE_BUS5);
OneWire oneWire5(ONE_WIRE_BUS6);
OneWire oneWire6(ONE_WIRE_BUS7);
OneWire oneWire7(ONE_WIRE_BUS8);
OneWire oneWire8(ONE_WIRE_BUS9);
OneWire oneWire9(ONE_WIRE_BUS10);
OneWire oneWire10(ONE_WIRE_BUS11);
OneWire oneWire11(ONE_WIRE_BUS12);
OneWire oneWire12(ONE_WIRE_BUS13);
OneWire oneWire13(ONE_WIRE_BUS14);


//DallasTemperature sensors3(&oneWire3); 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors0(&oneWire0);
DallasTemperature sensors1(&oneWire1);
DallasTemperature sensors2(&oneWire2);
DallasTemperature sensors3(&oneWire3);
DallasTemperature sensors4(&oneWire4);
DallasTemperature sensors5(&oneWire5);
DallasTemperature sensors6(&oneWire6);
DallasTemperature sensors7(&oneWire7);
DallasTemperature sensors8(&oneWire8);
DallasTemperature sensors9(&oneWire9);
DallasTemperature sensors10(&oneWire10);
DallasTemperature sensors11(&oneWire11);
DallasTemperature sensors12(&oneWire12);
DallasTemperature sensors13(&oneWire13);

bool DEBUG = false;
float temperatures[14]; // = {0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00}; // array of 14 floats
float currentTemp[14]; // = {0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00}; // working temp

void setup()
{
  
  Wire.begin(2);                // join i2c bus with address #2
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(57600);           // start serial for output

  // start serial port
  Serial.println("Dallas Temperature I2C Control");

  // Start up the library
  sensors0.begin();  
  sensors1.begin();
  sensors2.begin();
  sensors3.begin();
  sensors4.begin();
  sensors5.begin();
  sensors6.begin();
  sensors7.begin();
  sensors8.begin();
  sensors9.begin();
  sensors10.begin();
  sensors11.begin();
  sensors12.begin();
  sensors13.begin();

}

void verifyTemp(int index) {
  // we dont want to update fail temperatures
  if(currentTemp[index] != -127) {
    temperatures[index] = currentTemp[index];
  }
}

void sensorLoop() {

  for(int index=0; index < 14; index++) {

    if(index == 0) sensors0.requestTemperatures();
    if(index == 1) sensors1.requestTemperatures();
    if(index == 2) sensors2.requestTemperatures();
    if(index == 3) sensors3.requestTemperatures();
    if(index == 4) sensors4.requestTemperatures();
    if(index == 5) sensors5.requestTemperatures();
    if(index == 6) sensors6.requestTemperatures();
    if(index == 7) sensors7.requestTemperatures();
    if(index == 8) sensors8.requestTemperatures();
    if(index == 9) sensors9.requestTemperatures();
    if(index == 10) sensors10.requestTemperatures();
    if(index == 11) sensors11.requestTemperatures();
    if(index == 12) sensors12.requestTemperatures();
    if(index == 13) sensors13.requestTemperatures();
  
  
    if(index == 0) { currentTemp[index] = float(sensors0.getTempCByIndex(0)); }  
    if(index == 1) { currentTemp[index] = float(sensors1.getTempCByIndex(0)); }
    if(index == 2) { currentTemp[index] = float(sensors2.getTempCByIndex(0)); }
    if(index == 3) { currentTemp[index] = float(sensors3.getTempCByIndex(0)); }
    if(index == 4) { currentTemp[index] = float(sensors4.getTempCByIndex(0)); }
    if(index == 5) { currentTemp[index] = float(sensors5.getTempCByIndex(0)); }
    if(index == 6) { currentTemp[index] = float(sensors6.getTempCByIndex(0)); }
    if(index == 7) { currentTemp[index] = float(sensors7.getTempCByIndex(0)); }
    if(index == 8) { currentTemp[index] = float(sensors8.getTempCByIndex(0)); }
    if(index == 9) { currentTemp[index] = float(sensors9.getTempCByIndex(0)); }
    if(index == 10) { currentTemp[index] = float(sensors10.getTempCByIndex(0)); }
    if(index == 11) { currentTemp[index] = float(sensors11.getTempCByIndex(0)); }
    if(index == 12) { currentTemp[index] = float(sensors12.getTempCByIndex(0)); }
    if(index == 13) { currentTemp[index] = float(sensors13.getTempCByIndex(0)); }
    
    verifyTemp(index);
    if(DEBUG) {
      Serial.print(index);
      Serial.print(" Temperature is: ");
      Serial.print(currentTemp[index]); 
      Serial.print(" / ");
      Serial.println(temperatures[index]);       
    }


//    delay(30); //!??!
  }  


}

void loop()
{
//  Serial.println("loop start");
  sensorLoop();
  delay(2000);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()

void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}
