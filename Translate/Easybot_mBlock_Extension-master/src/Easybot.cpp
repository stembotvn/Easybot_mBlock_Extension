#include "Arduino.h"
#include "Easybot.h"




/*void EasybotNano::begin(){
 
}*/


///////////////////////////////////////
void EasybotNano::moveForward(int speed){
 int movespeed = (float)speed*255/100; 
 LeftMotor.run(_Lcal*movespeed);
 RightMotor.run(_Rcal*movespeed);
}
////
void EasybotNano::moveBack(int speed){
int  movespeed = (float)speed*255/100; 
 LeftMotor.run(-movespeed*_Lcal);
 RightMotor.run(-movespeed*_Rcal);	
}
////////////////////////////////////////////
 void EasybotNano::moveForward(int leftspeed,int rightspeed)
 {
 	int Lspeed = _Lcal*leftspeed*255/100;
 	int Rspeed = _Rcal*rightspeed*255/100;
 	LeftMotor.run(Lspeed);
 	RightMotor.run(Rspeed);
 }

 void EasybotNano::moveRight(int speed)
 {
//int rspeed;
//rspeed = speed*255/100; 	
moveForward(_Rcal*speed,0);

 }
 ///
 void EasybotNano::moveLeft(int speed)
 {
//int rspeed;
//rspeed = speed*255/100; 	
moveForward(0,_Lcal*speed);
 }
 
//////////////////////////////
void EasybotNano::stop()
{
	LeftMotor.stop();
  RightMotor.stop();
}
///////////////////////////////
///////////////////////////////
void EasybotNano::turnRight(int speed){
int turnspeed = (float)speed*255/100;

LeftMotor.run(_Lcal*turnspeed);
RightMotor.run(-turnspeed*_Rcal);

}
/////////////////////////////////////////
void EasybotNano::turnRight(int speed,int time)
{
int turnspeed = (float)speed*255/100;
int i = 0;

LeftMotor.run(_Lcal*turnspeed);
RightMotor.run(-turnspeed*_Rcal);
for (i=0;i<time;i++)
 {
  delay(100);
 }
 stop();
 delay(200);
}
/////////////////////
void EasybotNano::turnLeft(int speed){
int turnspeed = (float)speed*255/100;
//LeftMotor.stop();
//RightMotor.stop();
//delayMicroseconds(deadband_time);
	 LeftMotor.run(-turnspeed*_Lcal);
	 RightMotor.run(turnspeed*_Rcal);
//delay(turn_duration_time);
//LeftMotor.stop();
//RightMotor.stop();
//delay(deadband_time);
}
//////////
void EasybotNano::turnLeft(int speed,int time)
{
int turnspeed = (float)speed*255/100;
int i = 0;

LeftMotor.run(-turnspeed*_Lcal);
RightMotor.run(turnspeed*_Rcal);

for (i=0;i<time;i++)
 {
  delay(100);
 }
 stop();
 delay(200);

}
////////////////////////////////
void EasybotNano::setup_lineSensor(int color, int threshold_detect){
_LINE_COLOR = color;
_line_detect = threshold_detect; 
pinMode(lineSensor_enable,OUTPUT);
}

//////////////////////////////////
int EasybotNano::readSensor(int channel)
{
digitalWrite(lineSensor_enable,HIGH);
 int line_value = analogRead(channel);
digitalWrite(lineSensor_enable,LOW);

 return line_value;
}
///////////////////////////////////////////////////////
bool EasybotNano::leftSensor(){
bool color;	
int value;
digitalWrite(lineSensor_enable,HIGH);
value = analogRead(leftline_pin);
digitalWrite(lineSensor_enable,LOW);

color  =  _LINE_COLOR; 
   if (color == BLACK) 
    {
     if (value>_line_detect) return 1;
     else return 0;
    }
   else 
   {
      if (value<_line_detect) return 1;
      else return 0;
   }
}
////////////////////////////////////////////////////////
bool EasybotNano::rightSensor(){
bool color;
int value;		

digitalWrite(lineSensor_enable,HIGH);
 value = analogRead(rightline_pin);
digitalWrite(lineSensor_enable,LOW);

 color  =  _LINE_COLOR; 
   if (color == BLACK) 
    {
     if (value>_line_detect) return 1;
     else return 0;
    }
   else 
   {
      if (value<_line_detect) return 1;
      else return 0;
   }

}
///////////////////////////////////////////////////
bool EasybotNano::centerSensor(){
bool color;
int value;	

digitalWrite(lineSensor_enable,HIGH);
 value = analogRead(centerline_pin);
digitalWrite(lineSensor_enable,LOW);
 
 color  =  _LINE_COLOR; 
   if (color == BLACK) 
    {
     if (value>_line_detect) return 1;
     else return 0;
    }
   else 
   {
      if (value<_line_detect) return 1;
      else return 0;
   }
}

///////////////////////////////////
float EasybotNano::readSonar() {
  float range = Distance.Ranging(CM);
  delay(100);
return range;
    }
 /////////////////////////////////////////////////////////////////////////////////   
/*
 //////////////////////////////////
 
void Easybot::lookright()
{
	
Headservo.attach(Servo1_pin);   	
Headservo.write(Right_angle);
delay(500);
Headservo.detach();//release for using PWM on Pin 9,10


}

//////
void Easybot::lookleft()
{

Headservo.attach(Servo1_pin); 	
Headservo.write(Left_angle);
delay(500);
Headservo.detach();//release for using PWM on Pin 9,10


}
///
void Easybot::lookfront()
{

Headservo.attach(Servo1_pin); 
Headservo.write(Center_angle);
delay(500);
Headservo.detach();//release for using PWM on Pin 9,10


}

*/
