
#include <Servo.h>
#include <Stampede.h>
#include <Remote.h>


#define THROTTLE_PIN 10  // attach ESC to pin 10
#define STEERING_PIN 9   // attach steering servo to pin 9
#define MOTOR 0
#define STEERING 1


byte pin[] = {7};
Stampede stampede(THROTTLE_PIN,STEERING_PIN);
Remote remote(pin,1);

int incomingByte = 0;
int speed = 0;
int mode = MOTOR;
int steer;
int rc_value = 0;
int value=0;
void setup() 
{  
	stampede.begin();
	delay(1000); // wait for ESC
	// start serial port
	Serial.begin(19200);
	Serial.println("Stampede Test");
}

void loop() 
{

	rc_value = remote.read(1);
	if (rc_value != 0)
	{
		value = map(rc_value,-500,500,-100,100);
	}
	
	Serial.print("RC Value: ");
	Serial.print(rc_value);
	Serial.print(" ");
	Serial.println(value);

	if (Serial.available() > 0) 
	{		
			// read the incoming byte:
		incomingByte = Serial.read();
		if(incomingByte=='s')
		{
			Serial.print("Steering mode");
			mode = STEERING;
			value = 0;
		}
		else
		{
			Serial.print("Motor mode");
			mode = MOTOR;
		}

		switch(incomingByte)
		{
			
			case '0':
				Serial.print("Neutral");
				value = 0;
				break;
			case '1':
				Serial.print("Forward slow");
				value = 12;
				break;
			case '2':
				Serial.print("Forward fast");
				value = 40;
				break;
			case '3':
				Serial.print("Forward  super fast");
				value = 60;
				break;
			case '4':
				Serial.print("Forward ultra fast");
				value = 80;
				break;
			case '9':
				Serial.print("Reverse"); // back-neutral then back again !!!
				value = -10;
				break;

			case 's':
				break;

			default : 
				Serial.print("Error ");
				Serial.print(incomingByte);
				value = 0;
		}

		
	}
	if(mode == STEERING)
		{
			if(value == 0)
			{
				steer+=5;
				if(steer>100)
				{
					steer=-100;
				}
			}
			else
			{
				steer = value;
			}
			stampede.setSteer(steer);
			Serial.print("\t Steer: ");
			Serial.println(steer);
		}
		else
		{
			Serial.print("\t Speed: ");
			Serial.println(value);
			stampede.setSpeed(value);
		}
		delay(300);
}	