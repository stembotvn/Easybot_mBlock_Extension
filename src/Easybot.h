/*
Class for Stembot platform 
an open source STEM robotics for kids
http://stembot.vn

Stembot V1.0 
   Base: 2 wheel DC motor 
   Sensor:  Line following Sensor 3 channels Analog with Enable Pin to active Sensor
   
            Ultra Sonic Range finder sensor SR-04 for detect object
	HC-06 Bluetooth Interface Via Software Serial, HM10 for BLE 
    NRF24L01 Interface	
   		 

*/
#ifndef Easybot_H_
#define Easybot_H_

#include "Arduino.h"
#include "stdint.h"

#include "EasyRF.h"
#include "EasySonar.h"
#include "EasyMotor.h"
#include "ServoTimer2.h"
#include "NegendoSounds.h"
#include "Adafruit_NeoPixel.h"

#include <SoftwareSerial.h>

#include "RF24.h"
#include "EEPROM.h"

#include "Scratch.h"
///////////////////////////////////////////////////////////
#define DEBUG 1

////define for I/O Pins////////////////////////////////////
#define _EasybotIO										///
#define leftline_pin        0							///
#define rightline_pin       2							///
#define centerline_pin      1	
#define lineSensor_enable   A3
#define leftline_pin2       
#define rightline_pin2			              			///
   					///
#define SR04_Trig             4							///
#define SR04_Echo             3							///
//#define Servo1_pin           11                         ///
///////////////////////////////////////////////////////////
//define for EasybotNano Board with L9110S Driver
#define leftMotor_pinA    5          //_pinB1A   ///
#define leftMotor_pinB    6          //_pinB1B      ///

#define rightMotor_pinA   9          //_pinB1A      ///
#define rightMotor_pinB   10         //_pinB1B      ///
                 ///
/*
//define for NanoBoard with L298/L293 Driver ///
#define leftMotorDir_pin      9      //_pinB1A       ///
#define leftMotorPWM_pin      6      //_pinB1B       ///
#define rightMotorDir_pin     10     //_pinB1A       ///
#define rightMotorPWM_pin     11       //_pinB1B     ///
*/
////////////////////////////////////////////////////////

////define for action paramet er
#define Right_angle           0   //angle for Head Serov
#define Left_angle            180
#define Center_angle          90
#define speed_forward         100  //speed (%)
#define lane_adjust           20  //20% speed adjust for lane control
#define turn_duration_time    1200   //turn for 1200ms           
#define deadband_time         50    //gap time btw reverse direction, microseconds
#ifndef line_detect
  #define line_detect     	  400   //default threshold value for line detection              ///Default threshold for line detection is 200, if value from sensor > 200 or < 200, the line sensor status is detected or not detected
#endif
#define linefollow_adj        80      //adjust volume for speed control (%)


#define LEFT                   1
#define RIGHT                 -1
#define CENTER                 0
#define BLACK                  1
#define WHITE                  0

#define LEFTSENSOR            leftline_pin
#define RIGHTSENSOR           rightline_pin
#define CENTERSENSOR          centerline_pin
#ifndef LINE_COLOR			
  #define LINE_COLOR            BLACK      
#endif        ///default setting is black line   -> #define LINE_COLOR  WHITE  in the Sketch before #include "Easybot.h" to set line to WHITE
// #define BT                    SoftSerial
#define BT_Tx_Pin 7               
#define BT_Rx_Pin 8
#define Servo_Pin 7
#define SET A7

#define CE_PIN   A4
#define CSN_PIN  A5

#define LDR1  A6
#define LDR2  A7
#define RGB_Pin 8
#define NumLedRGB 1
#define Buzzer_Pin 2
///////////////////// RF24 Dogle ////////////////////////
////////define State 
#define READ_RF   0
#define PARSING   1
#define RUN_CMD  2
#define GET_DATA 3
#define RC       4
#define WRITE_RF 5
#define IN_CONFIG 6
///define for operation Mode
#define RUN_MODE 0
#define CONFIG_MODE 1
#define RC_MODE 2
////////////////////////////
#define RC_MANUAL  0
#define LIGHT_FOLLOW    1
#define AVOID_OBSTACLE 2
#define CREATE_SOUND  3
///////////////////////////
#define NETWORK 1
#define PAIRING 0
///////////////////////////
#define MASTER_NODE 0
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EasybotNano //: public SoftwareSerial
{//: public EasyMotor  
public: 	

  EasybotNano():  RightMotor(rightMotor_pinA,rightMotor_pinB), LeftMotor(leftMotor_pinA,leftMotor_pinB), Distance(SR04_Trig,SR04_Echo)//, BT(BT_RX_Pin,BT_TX_Pin)
	{} //initializer list for objects using within this Class
  void init(int _address);
  void initNRF(int _address);
  void load_address();        // Chuyển đổi địa chỉ lưu từ EEPROM
  bool inConfig();        // Nhận địa chỉ ngẫu nhiên từ Transmitter
  ///State Function/////
  void config_Address(uint16_t myaddress,uint16_t toAddress);
  void readRF();
  void parseData();
  void writeRF();
  void RC_Run();
  void run();
  ////
  void PrintDebug(unsigned char *buf,int len);
  void remoteProcessing();
  ////
  int State = 0;
  uint8_t keyState = 0;
  uint8_t varSlide = 0;
  uint8_t RC_type = RC_MANUAL;
  bool connection = PAIRING; 
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //void begin();       
  //void waitStart(int distance);  //wait for signing in front of Robot with distance             
  void moveForward(int speed);           // move forward function, Hàm chạy thẳng 
  void moveForward(int Leftspeed,int rightspeed);  // move forward with manual adjust Left, Right Wheel Speed || Hàm chạy thẳng với tham số bánh trái và phải tùy chỉnh
  void moveBack(int speed);            //  
  void moveRight(int speed);           // move to the right  || Hàm chạy xiêng về bên phải
  void moveLeft(int speed);            // move to the left   || Hàm chạy xiêng về bên trái
 	void stop();						 // stop the robot       || Hàm dừng robot
	void turnRight(int speed);           // turn to the right   || Quay robot sang phải 
	void turnRight(int speed,int time);  //turn to the right, time interval is 100ms <-> const angle
	void turnLeft(int speed);            //turn robot to the left || Quay robot sang trái
	void turnLeft(int speed,int time);   //turn to the left, time interval is 100ms <-> const angle
  void setup_lineSensor(int color, int threshold_detect);
	int  readSensor(int channel);        ///Read line sensor with customized channel, return raw value, Channel is LEFTSENSOR, RIGHTSENSOR, CENTERSENSOR
	bool leftSensor();                   //Read sensor detection, return 1 if detect line, return 0 if not detect line
	bool rightSensor();                  //Read Right line sensor, return 1 if detect line, return 0 if not detect line
	bool centerSensor();				 //Read Center line Sensor, return 1 if detect line, return 0 if not detect line
  float readSonar();            		 ///read the distance || Đọc khoảng cách ex: int khoangcach = robot.readSonar();
  void setServo(int angle);
  void disableServo() {servo.detach();}

  float  getDistance();        //get Distance in CM
  int  getLight(byte side);  // get Light  level in %

  void setColor(byte R, byte G, byte B);
  void offRGB();
  bool readButton();

  RF24 myRadio=RF24(CE_PIN,CSN_PIN);
  EasyRF Radio = EasyRF(myRadio);

  NegendoSounds Sound = NegendoSounds(Buzzer_Pin);
  Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NumLedRGB, RGB_Pin, NEO_GRB + NEO_KHZ800);

private:
  EasyMotorL9110 RightMotor;
  EasyMotorL9110 LeftMotor;
  EasySonar Distance;
  ServoTimer2 servo;
  int _LINE_COLOR = BLACK;
  int _line_detect = 400; 
  int LDRR;
  int LDRL;

  double timeStart;
  int speed = 70;
  int songname = 3;

  int medium;

  uint16_t myNode = 2; 
  uint16_t toNode;
  uint16_t new_addr; 
  uint16_t  Default_Addr = 1000;
  uint16_t  Multicast_Node = 255;
  bool first_run = true;
  bool actionDone = false; 
  uint8_t Mode = RUN_MODE; 
  int _Add[1];
  long _startTime;
  long _timeout = 10000L;
  int  RFread_size; 
  bool _readDone = false; 
  char _buffer[64];
	bool  isAvailable = false;
  bool isStart=false;
  unsigned char prevc=0;
  int index = 0;
  int ind = 0; 
  int dataLen;
  unsigned char buffer[32]; //for reading RF
  unsigned char RF_buf[32]; //for writing RF
  uint8_t command_index = 0;

  union
  {
    byte byteVal[4];
    float floatVal;
    long longVal;
   
  }val;

  union
  {
    byte byteVal[8];
    double doubleVal;
  }valDouble;

  union
  {
    byte byteVal[2];
    short shortVal;
  }valShort;
  /////////////////////////////////////////
  void writeHead();
  void writeEnd();
  /////////////////////////////////////////
  unsigned char readBuffer(int index);  //read RF Comming buffer
  void writeBuffer(int index,unsigned char c); //write to RF Sending Buffer
  void clearBuffer(unsigned char *buf, int leng);
  /////////////////////////////////
  void callOK();
  void sendByte(char c);
  void sendString(String s);
  void sendFloat(float value);
  void sendShort(double value);
  void sendDouble(double value);
  short readShort(int idx);
  float readFloat(int idx);
  long readLong(int idx);

  void runFunction(int device);
  int searchServoPin(int pin);
  void readSensors(int device);
  //////////////////////////////////////////
  void EEPROM_writeInt(int address,uint16_t value);
  uint16_t EEPROM_readInt(int address);
 
};
#endif
////////////////////////////////////// 
