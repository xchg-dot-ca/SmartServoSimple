# SmartServoSimple

This is simple Proof Of Concept project where we make servo a bit smarter by adding dedicated microcontroller.
We will be talking to microcontroller via I2C protocol.

Smart Servos can be chained and each will have decicate i2C bus address.
Microcontroller will control servo position and will read voltage at servo potentiometer to allow position report.
Communication is jut one byte - repsesenting angle in degrees of the servo shaft.

Note: Make sure you are using 3V based logic devices.

TrinketServoController can be used with any microcontroller, but originally designed to be used with Trinket M0 from Adafruit
ServoMasterI2C - can be used with any microcontroller I2C capable.

Flash sketches and connect SDA, SCL, GND from one microcontroller to another, they dont have to share same power source.

ADC running on 3V reference so theoretically it can work with servo up to 6V
( Servo potentiometer divides voltage roughly by half )
