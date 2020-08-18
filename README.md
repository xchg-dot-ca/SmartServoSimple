# SmartServoSimple

This is simple Proof Of Concept project where we make servo a bit smarter by adding dedicated microcontroller.
We will be talking to microcontroller via I2C protocol.
Smaer Servo then can be chained and each will have decicate i2C bus address.
Microcontroller will control servo position and will read voltage at servo potentiometer to allow position report.
Communication is jut one byte - repsesenting angle in degrees of the servo shaft.
