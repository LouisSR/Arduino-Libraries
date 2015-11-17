
#include <Servo.h>
#include <Stampede.h>


#define THROTTLE_PIN 10  // attach ESC to pin 10
#define STEERING_PIN 9   // attach steering servo to pin 9

Stampede stampede(THROTTLE_PIN,STEERING_PIN);

int speed_0 = 90;
int speed_1 = 90;
int incomingByte = 0;

void setup() 
{  
  stampede.begin();
  delay(1000); // wait for ESC
  // start serial port
  Serial.begin(19200);
  Serial.println("Stampede Test: Enter speed [-100,100]");
}

void loop() {
   if (Serial.available() > 0) 
   {
                
                // read the incoming byte:
                incomingByte = Serial.read();
                switch(incomingByte)
                {
                
                case '0':
                  Serial.print("Neutral\n");
                  incomingByte = 0;
                   break;
                case '1':
                  Serial.print("Forward\n");
                   incomingByte = 10;
                    break;
                case '2':
                  Serial.print("Reverse\n"); // back-neutral then back again !!!
                   incomingByte = -10;
                    break;
                 default : 
                   Serial.print("Error\n");
                   incomingByte = 0;
                }
  }
  stampede.setSpeed(incomingByte);
  Serial.println(incomingByte);
  delay(500);
}