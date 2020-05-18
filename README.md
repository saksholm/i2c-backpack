# i2c-backpack
 I2C backpack for heatpump-node project:
 https://github.com/saksholm/heatpump-node

 This is on Arduino Uno board and connected to Arduino Mega board.
 
- 14 x DS18B20 sensors connected
- values scaled by 100
- board sends high/low bytes buffer
- NOTE! if using Serial, first 2 sensors not working because pins are reserved for Serial communication.
