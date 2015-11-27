/*
	I2C.h - Library for communicating through I2C.
	Created by Louis SR, November 26, 2015.
	Released into the public domain.
*/
#ifndef I2C_h
#define I2C_h

#include <Arduino.h>
#include <Wire.h>

#define COM_IN_LENGTH 6 // Length of I2C recieved data
#define COM_OUT_LENGTH 5 // Length of I2C sent data
#define START_BYTE 15


void i2cBegin(uint8_t slaveAdress);
boolean i2cGetMessage(uint8_t* message);
void i2cSetMessage(uint8_t* message);
void i2cSendData();
void i2cReceiveData(int byteCount);

#endif