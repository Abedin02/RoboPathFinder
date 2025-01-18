#include<stdio.h>
#include<regex.h>
#include<fcntl.h>
#include<unistd.h>
#include<bcm2835.h>
#include"I2C.h"

#define BUFFERSIZE 4096



extern int i2cInit(int address){

	//i2c initialization should also go here.
	
	//Initialize the GPIO headers
	if (!bcm2835_init())
    	{
     		printf("bcm2835_init failed. Are you running as root??\n");
      		return 1;
    	}//if bcm_init
	
	//Prepare the hat for i2c communication
	if (!bcm2835_i2c_begin())
    	{
		printf("bcm2835_i2c_begin failed. Are you running as root??\n");
		return 1;
	}//if i2c_begin

	//Set the address of the hat you are communicating with 
	bcm2835_i2c_setSlaveAddress(address); //set HAT address to 0x41 for servo
	return 0;
	
	
}

/*
Keep in mind, that the i2cInit() function must be called ONCE, prior 
to using these functions or you will get a core dump.
*/
extern void write8(unsigned char reg, unsigned char value){
	

	//Error checking should be done for the completion of this
	//function.  This code should work, if you get errors, you need
	//to use the Reason codes returned to check for them.

	unsigned char buf[2];
	buff[0] = reg;
	buff[1] = value;
	bcm_i2c_write(buff, 2);

}

unsigned int readU8(unsigned char reg){
	

	
	//Error checking should be done for the completion of this
	//function.  This code should work, if you get errors, you need
	//to use the Reason codes returned to check for them.
	unsigned char buff[2];
	buff[0] = reg;
	bcm2835_i2c_read(buff, 2);
	return buff[0];

}

