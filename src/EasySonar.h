// Ultrasonic - Library for HR-SC04 Ultrasonic Ranging Module.
// GitHub: https://github.com/JRodrigoTech/Ultrasonic-HC-SR04
// #### LICENSE ####
// This code is licensed under Creative Commons Share alike 
// and Attribution by J.Rodrigo ( http://www.jrodrigo.net ).

#ifndef EasySonar_h
#define EasySonar_h

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define CM 1
#define INC 0

class EasySonar
{
  public:
    EasySonar(int TP, int EP);
  	EasySonar(int TP, int EP, long TO);
    long Timing();
    float Ranging(int sys);

  private:
    int Trig_pin;
    int Echo_pin;
	long Time_out;
    float duration,distance_cm,distance_inc;
};

#endif
