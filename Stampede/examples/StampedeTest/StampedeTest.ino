
#include <Servo.h>
#include <Stampede.h>


#define THROTTLE_PIN 10  // attach ESC to pin 10
#define STEERING_PIN 9   // attach steering servo to pin 9
#define MOTOR 0
#define STEERING 1

Stampede stampede(THROTTLE_PIN,STEERING_PIN);


char incomingByte;
int speed = 0;
int mode = MOTOR;
int steer;
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
			value = 5;
			break;
			case '2':
			Serial.print("Forward fast");
			value = 10;
			break;
			case '3':
			Serial.print("Forward  super fast");
			value = 20;
			break;
			case '4':
			Serial.print("Forward ultra fast");
			value = 40;
			break;
			case '9':
			Serial.print("Reverse"); // back-neutral then back again !!!
			value = -10;
			break;

			case 'p':
			Serial.print("Increment");
			value += 2;
			break;

			case 'o':
			Serial.print("Decrement");
			value -= 2;
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