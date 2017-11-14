#include "EasyMotor.h"


EasyMotorL9110::EasyMotorL9110(int PinA,int PinB)
{  
    _PinA = PinA;
    _PinB = PinB;
   pinMode(_PinA,OUTPUT);
   pinMode(_PinB,OUTPUT);
}
////////////////////////////////////////////////////////////////////////
void EasyMotorL9110::run(int speed)
{    
    speed = speed > 255 ? 255 : speed;   // if speed > 255 -> speed = 255
    speed = speed < -255 ? -255 : speed; // if speed < -255 -> speed = -255
   
    // constrain(speed,-255,255);
    if(speed >= 0) {
        analogWrite(_PinB,0);
        analogWrite(_PinA,speed);
    } 
    else {
        analogWrite(_PinA,0);
        analogWrite(_PinB,-speed);
    }
}
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
void EasyMotorL9110::stop()
{
    analogWrite(_PinB,0);
    analogWrite(_PinA,0);
   // delay(deadband);
}   



 EasyMotorL293::EasyMotorL293(int PWM,int Dir)
{  
    _PWM = PWM;
    _Dir = Dir;
   pinMode(_PWM,OUTPUT);
   pinMode(_Dir,OUTPUT);
}
////////////////////////////////////////////////////////////////////////
void EasyMotorL293::run(int speed)
{    
    speed = speed > 255 ? 255 : speed;   // if speed > 255 -> speed = 255
    speed = speed < -255 ? -255 : speed; // if speed < -255 -> speed = -255
   
    // constrain(speed,-255,255);
    if(speed >= 0) {
        digitalWrite(_Dir,0);
        analogWrite(_PWM,speed);
    } 
    else {
        digitalWrite(_Dir,1);
        analogWrite(_PWM,-speed);
    }
}
/////////////////////////////////////////////////////////////////////////
void EasyMotorL293::stop()
{
    digitalWrite(_Dir,0);
    analogWrite(_PWM,0);
   // delay(deadband);
}   
