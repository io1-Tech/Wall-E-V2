/////////////////////////////////
/////////////////////////////////
////   CODED BY NICOLÁS      ////
/////////////////////////////////
/////////////////////////////////

// INITIALIZE 🔴🟢🔵 RGB LED //

int redPin = 15;
int greenPin = 2;
int pinIn = 4;
int volVal;

/////////////////////////////////

// INITIALIZE LAZER 💥 //

int laser = 19;

//////////////////////////

// 🎵 INITIALIZE DFPLAYER //

#include <DFRobotDFPlayerMini.h>
#include "Arduino.h"
#define FPSerial Serial1
DFRobotDFPlayerMini myDFPlayer;

/////////////////////////////

// 🦾 INITIALIZE SERVOS //

#include <ESP32Servo.h>

const int pinServo1 = 23; // right_arm
int servoVal1;
const int pinServo2 = 33; // left_arm
int servoVal2;
const int pinServo3 = 32; // Head servo
int servoValR3;
int servoValL3;

Servo miServo1;
Servo miServo2;
Servo miServo3;

/////////////////////////

// 🎮 INITIALIZE XBOX REMOTE //

#include <XboxSeriesXControllerESP32_asukiaaa.hpp>
XboxSeriesXControllerESP32_asukiaaa::Core xboxController;
XboxSeriesXHIDReportBuilder_asukiaaa::ReportBase repo;

////////////////////////////////

// 💪 VARIABLES //

  int xVal1;
  int yVal1;
  int xVal2;
  int yVal2;
  int emoteButtonVal;
  int musicButtonVal;
  bool reverseState = false;

  int motor1Pin1 = 12;
  int motor1Pin2 = 14;
  int motor2Pin1 = 27;
  int motor2Pin2 = 26;
  int enablePin1 = 13;
  int enablePin2 = 25;

  int relayPin = 18;

  int busyVal;

/////////////////////////

/*💀*/ void setup() //////////////////////////////////////
{
// 🎮 INITIALIZE XBOX REMOTE // 

  Serial.begin(115200);
  Serial.println("Starting NimBLE Client");
  xboxController.begin();

/////////////////////////
  
// 🐧 INITIALIZE PINS //
  
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  pinMode(enablePin1, OUTPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(pinServo3, OUTPUT);

/////////////////////////

// 🦾 INITIALIZE SERVOS //

  miServo1.setPeriodHertz(50); // Establecer la frecuencia en 50 Hz (estándar para servos)
  miServo1.attach(pinServo1, 500, 2400); // Configurar el pin del servo y los límites del pulso

  miServo2.setPeriodHertz(50); // Establecer la frecuencia en 50 Hz (estándar para servos)
  miServo2.attach(pinServo2, 500, 2400); // Configurar el pin del servo y los límites del pulso

  miServo3.setPeriodHertz(50); // Establecer la frecuencia en 50 Hz (estándar para servos)
  miServo3.attach(pinServo3, 500, 2400); // Configurar el pin del servo y los límites del pulso

/////////////////////////

// 🎵 DFPLAYER //
 
#if (defined ESP32)
  FPSerial.begin(9600, SERIAL_8N1, /*rx =*/16, /*tx =*/17);
#else
  FPSerial.begin(9600);
#endif

  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(FPSerial, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  
myDFPlayer.volume(20);
myDFPlayer.play(1);

/////////////////////////

// INITIALIZE 🔴🟢🔵 RGB LED //

pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(pinIn, INPUT);

/////////////////////////////////

// INITIALIZE LASER 💥 //

pinMode(laser, OUTPUT);

//////////////////////////

}

/*💀*/  void loop() //////////////////////////////////////
{
// 🎮 XBOX REMOTE //

  xboxController.onLoop();
  if (xboxController.isConnected()) {
    if (xboxController.isWaitingForFirstNotification()) {
      Serial.println("waiting for first notification");
    } else {
      Serial.println("Address: " + xboxController.buildDeviceAddressStr());
      Serial.print(xboxController.xboxNotif.toString());
      unsigned long receivedAt = xboxController.getReceiveNotificationAt();
      uint16_t joystickMax = XboxControllerNotificationParser::maxJoy;
      Serial.print("joyLHori rate: ");
      Serial.println((float)xboxController.xboxNotif.joyLHori / joystickMax);
      Serial.print("joyLVert rate: ");
      Serial.println((float)xboxController.xboxNotif.joyLVert / joystickMax);
      Serial.print("joyRHori rate: ");
      Serial.println((float)xboxController.xboxNotif.joyRHori / joystickMax);
      Serial.print("joyRVert rate: ");
      Serial.println((float)xboxController.xboxNotif.joyRVert / joystickMax);
      Serial.println("battery " + String(xboxController.battery) + "%");
      Serial.println("received at " + String(receivedAt));
    }
  } else {
    Serial.println("not connected");
    if (xboxController.getCountFailedConnection() > 2) {
      ESP.restart();
    }
  }
  Serial.println("at " + String(millis()));
  delay(0);

////////////////////

// ⚡ TASER CONTROL //

if (xboxController.xboxNotif.btnRS == 1 && xboxController.xboxNotif.btnLS == 1 && volVal == 1) {
    digitalWrite(relayPin, HIGH);
  }  
else {
    digitalWrite(relayPin, LOW);
  }

/////////////////////////

// 🎵 DFPLAYER CONTROL //

 if (xboxController.xboxNotif.btnA != 0) {
  int numero = random(1, 4);
  myDFPlayer.play(numero);
 }

 if (xboxController.xboxNotif.btnB != 0) { 
  myDFPlayer.play(5);
 }

 if (xboxController.xboxNotif.btnB != 0 && busyVal != 0){
  myDFPlayer.pause();
 }

 busyVal = myDFPlayer.readState();

/////////////////////////

// 🦾 SERVO CONTROL //

servoValR3 = map(xboxController.xboxNotif.trigRT, 0, 1023, 90, 0);
servoValL3 = map(xboxController.xboxNotif.trigLT, 0, 1023, 90, 180);
if(xboxController.xboxNotif.trigRT != 0)
{
  miServo3.write(servoValR3);
}
if(xboxController.xboxNotif.trigLT != 0)
{
  miServo3.write(servoValL3);
}
else if (xboxController.xboxNotif.trigLT == 0 && xboxController.xboxNotif.trigRT == 0)
{
  miServo3.write(90);
}

servoVal1 = map(xboxController.xboxNotif.joyLVert, 0, 65535, 180, 60);
miServo1.write(servoVal1);

servoVal2 = map(xboxController.xboxNotif.joyRVert, 0, 65535, 58, 180);
miServo2.write(servoVal2);

/////////////////////////

// 🔴🟢🔵 RGB LED //

volVal = digitalRead(pinIn);
Serial.println(volVal);

if(volVal == 1)
  {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
  } 
if(volVal == 0)
  {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  } 

//////////////////////

// LASER 💥 //

if(xboxController.xboxNotif.btnY == 1)
{
 digitalWrite(laser, HIGH);
}
else
{
  digitalWrite(laser, LOW);
}
//////////////////////////

// 🚗 MOTOR CONTROL: //
 
 if(xboxController.xboxNotif.btnX == 1)
 {
  reverseState = !reverseState;
 }

 if(xboxController.xboxNotif.btnRB == 0 && xboxController.xboxNotif.btnLB == 0){
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
    digitalWrite(enablePin1, LOW);
    digitalWrite(enablePin2, LOW);
  }

 if(xboxController.xboxNotif.btnRB != 0 && xboxController.xboxNotif.btnLB == 0){
   digitalWrite(enablePin1, HIGH);
   digitalWrite(motor1Pin1, HIGH);
   digitalWrite(motor1Pin2, LOW);
   digitalWrite(motor2Pin1, LOW);
   digitalWrite(motor2Pin2, HIGH);
   digitalWrite(enablePin2, HIGH);
    repo.v.select.right = false;
    repo.v.select.shake = true;
    repo.v.power.shake = 10;
    xboxController.writeHIDReport(repo);
   }

 if(xboxController.xboxNotif.btnLB != 0 && xboxController.xboxNotif.btnRB == 0){
   digitalWrite(enablePin1, HIGH);
   digitalWrite(motor1Pin1, LOW);
   digitalWrite(motor1Pin2, HIGH);
   digitalWrite(motor2Pin1, HIGH);
   digitalWrite(motor2Pin2, LOW);
   digitalWrite(enablePin2, HIGH);
    repo.v.select.right = false;
    repo.v.select.shake = true;
    repo.v.power.shake = 10;
    xboxController.writeHIDReport(repo);
   }

 if(xboxController.xboxNotif.btnRB != 0 && xboxController.xboxNotif.btnLB != 0 && reverseState == false){
   digitalWrite(enablePin1, HIGH);
   digitalWrite(motor1Pin1, HIGH);
   digitalWrite(motor1Pin2, LOW);
   digitalWrite(motor2Pin1, HIGH);
   digitalWrite(motor2Pin2, LOW);
   digitalWrite(enablePin2, HIGH);
    repo.v.select.right = false;
    repo.v.select.shake = true;
    repo.v.power.shake = 10;
    xboxController.writeHIDReport(repo);
   }

 if(xboxController.xboxNotif.btnRB != 0 && xboxController.xboxNotif.btnLB != 0 && reverseState == true){
   digitalWrite(enablePin1, HIGH);
   digitalWrite(motor1Pin1, LOW);
   digitalWrite(motor1Pin2, HIGH);
   digitalWrite(motor2Pin1, LOW);
   digitalWrite(motor2Pin2, HIGH);
   digitalWrite(enablePin2, HIGH);
    repo.v.select.right = false;
    repo.v.select.shake = true;
    repo.v.power.shake = 10;
    xboxController.writeHIDReport(repo);
   }
/////////////////////////

}
