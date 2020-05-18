#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>

int I2C_ADDRESS = 2;
bool ENABLE_SERIAL = false;
bool TH_DEBUG = false;
float currentTemp[14];
int temperatures[14] = {-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768};

const int sensorCycle = 2*1000;
const int sensorScale = 100;
unsigned long sensorLoopMillis = 0;
unsigned long currentMillis = 0;
 
// OneWire instances (IO pin):
OneWire oneWire0(0);
OneWire oneWire1(1);
OneWire oneWire2(2);
OneWire oneWire3(3);
OneWire oneWire4(4);
OneWire oneWire5(5);
OneWire oneWire6(6);
OneWire oneWire7(7);
OneWire oneWire8(8);
OneWire oneWire9(9);
OneWire oneWire10(10);
OneWire oneWire11(11);
OneWire oneWire12(12);
OneWire oneWire13(13);

// initialising sensors
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

void setup() {
  Wire.begin(I2C_ADDRESS); // join i2c bus with address #2
  Wire.onRequest(requestEvent);
  if(ENABLE_SERIAL) {
    Serial.begin(115200); // start serial for output
    Serial.println("I2C backpack controller for Dallas DS18B20 temperatures");  
  }

  // start sensors
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
  // we dont want to update failed temperatures
  if(currentTemp[index] != -127) {
    temperatures[index] = convertFloatToInt(currentTemp[index]);
  }
}

int convertFloatToInt (float temperature) {
  int conv = round(temperature * sensorScale);
  return conv;
}

void readTemperature(int index, DallasTemperature sensor) {
  sensor.requestTemperatures();
  currentTemp[index] = float(sensor.getTempCByIndex(0));
  verifyTemp(index);
}

void debugTemperatures(int index) {
  if(ENABLE_SERIAL) {
    Serial.print(index);
    Serial.print(" Temperature is... current: ");
    Serial.print(currentTemp[index]); 
    Serial.print(" / int:");
    Serial.print(temperatures[index]);
  }
}

void sensorLoop() {

  if(currentMillis >= sensorLoopMillis + sensorCycle) {
    // store new value to sensorLoopMillis
    sensorLoopMillis = currentMillis;

    for(int index=0; index < 14; index++) {  
      
      if(index == 0) readTemperature(index,sensors0);
      if(index == 1) readTemperature(index,sensors1);
      if(index == 2) readTemperature(index,sensors2);
      if(index == 3) readTemperature(index,sensors3);
      if(index == 4) readTemperature(index,sensors4);
      if(index == 5) readTemperature(index,sensors5);
      if(index == 6) readTemperature(index,sensors6);
      if(index == 7) readTemperature(index,sensors7);
      if(index == 8) readTemperature(index,sensors8);
      if(index == 9) readTemperature(index,sensors9);
      if(index == 10) readTemperature(index,sensors10);
      if(index == 11) readTemperature(index,sensors11);
      if(index == 12) readTemperature(index,sensors12);
      if(index == 13) readTemperature(index,sensors13);

      if(TH_DEBUG) debugTemperatures(index);
      
    }
  }
}  

void requestEvent(int howMany) {
  if(ENABLE_SERIAL) Serial.println("sending...");

  for(int i=0, th=0;i<28;i++) {
    Wire.write(temperatures[th] >> 8);
    Wire.write(temperatures[th]);
    th++;
  }
}

void loop() {
  currentMillis = millis(); 
  sensorLoop();
}
