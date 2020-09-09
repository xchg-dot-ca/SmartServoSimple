/* 
 *  Designed for Adafruit Trinket M0
    Receives commands via I2C and moves servo to specified position
	Using 12 bit ADC to read voltage from the servo position potentiometer
	Sends read value converted to angle ( position ) back to I2C master
*/

#include <Servo.h>
#include <Wire.h>

Servo myservo;
int m_currentServoAngle = 0;  // variable to store the servo position, unused
int m_desiredServoAngle = 0;  // servo angle that servo should reach, unused
const int SERVO_PIN = 4;
const int I2C_DEVICE_ID = 4;

/* Structure representing received message */
struct messageI2C {
  char buffer[1024] = {};		// Buffer
  bool processed = true;		// Indicated if it was processed 
  int bytes = 0;  				// bytes in message
} t_message;

messageI2C message; 			// Instantiate the message structure

void setup() {
  
  // Set to use default (3V) voltage reference
  analogReference(AR_DEFAULT);
  // Use 12 bit ADC
  analogReadResolution(12);
  // attaches the servo on pin 4
  myservo.attach(SERVO_PIN); 

  // Initialize i2C
  Wire.begin(I2C_DEVICE_ID); // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register receive event
  Wire.onRequest(requestEvent); // register request event
}

// Misc variuable to read analog data
int samples = 5;
int val,val1,val2,val3,val4 = 0;
int values[5];
float stdDeviation = 0;

int sampling() {
    int i, sum = 0, mean = 0 , variance = 0;

    for(i = 0; i < samples; ++i) {
        values[i] = analogRead(A0);  // read the input pin
        Serial.print(values[i]); Serial.print(" | ");          // debug value
    }
    Serial.println("");
  
    for(i = 0; i < samples; ++i) {
      sum += values[i];
    }
    mean = sum / samples;

/* Calculate some extra values 
    for(i = 0; i < samples; ++i) {
      variance += pow(values[i] - mean, 2);
    }
    variance = variance / samples;
    stdDeviation = sqrt(variance);

    Serial.print("Average: "); Serial.println(mean);
    Serial.print("Variance: "); Serial.println(variance);
    Serial.print("Standard Deviation: "); Serial.println(stdDeviation);
*/
    return mean;
}

/* Event handler for master requesting data from the servo */
void requestEvent()
{
  char currentPos = map(sampling(), 493, 3500, 0, 180);
  Serial.print("Sending Current Servo Angle: ");
  Serial.println(currentPos, DEC);
  Wire.write(currentPos);
}

/* Event handler for master sending data to the servo */
void receiveEvent(int numBytes) {
  Serial.println("Message Available");
  for(int i = 0; i < numBytes; i++) {
    message.buffer[i] = Wire.read();
  }
  message.bytes = numBytes;
  message.processed = false;
}

void loop() {
	// Processing messages
    if(!message.processed) {
      // Getting very first value of the buffer
      myservo.write(message.buffer[0]);
      message.processed = true;
      Serial.print("New Servo Angle: ");
      Serial.println(message.buffer[0], DEC);
    }
}
