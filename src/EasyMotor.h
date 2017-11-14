#ifndef EasyMotor_H_
#define EasyMotor_H_

#include "stdint.h"
#include "Arduino.h"
///@brief Class for DC Motor Module
//#define deadband 200

class EasyMotorL9110
{
	
	public:
	   	EasyMotorL9110(int PinA,int PinB);        

	    void run(int speed);
	    void stop();
	private:
		int _PinA;
		int _PinB; 
    
};
class EasyMotorL293
{
	public:
		EasyMotorL293(int PWM,int Dir);
		void run(int speed);
	    void stop();
	private:
        int _PWM;
        int _Dir;
};
#endif