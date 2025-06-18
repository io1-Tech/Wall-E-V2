/////////////////////////////////
/////////////////////////////////
////   CODED BY NICOLÁS 🗿  ////
/////////////////////////////////
/////////////////////////////////

// INICIALIZAR 🔴🟢🔵 RGB LED //

int redPin = 15;
int greenPin = 2;
int pinIn = 4;
int volVal;

/////////////////////////////////

// 🎵 INICIALIZAR DFPLAYER //

#include <DFRobotDFPlayerMini.h>
#include "Arduino.h"
#define FPSerial Serial1
DFRobotDFPlayerMini myDFPlayer;

/////////////////////////////

// 🦾 INICIALIZAR SERVOS //

#include <ESP32Servo.h>

const int pinServo1 = 23; // Puedes cambiar este valor según la conexión física
int servoVal1;
const int pinServo2 = 33; // Puedes cambiar este valor según la conexión física
int servoVal2;
const int pinServo3 = 32; // Puedes cambiar este valor según la conexión física
int servoVal3;

Servo miServo1;
Servo miServo2;
Servo miServo3;

/////////////////////////

// 🎮 INICIALIZAR XBOX REMOTE //

#include <XboxSeriesXHIDReportBuilder_asukiaaa.hpp>
#include <XboxControllerNotificationParser.h>
#include <NimBLEDevice.h>
#include <XboxSeriesXControllerESP32_asukiaaa.hpp>
XboxSeriesXControllerESP32_asukiaaa::Core xboxController;

////////////////////////////////

// 💪 VARIABLES //

  int xVal1;
  int yVal1;
  int xVal2;
  int yVal2;
  int emoteButtonVal;
  int musicButtonVal;
  int shockButtonVal;

  int motor1Pin1 = 12;
  int motor1Pin2 = 14;
  int motor2Pin1 = 27;
  int motor2Pin2 = 26;
  int enablePin1 = 13;
  int enablePin2 = 25;

  int relayPin = 34;

  int busyVal;

/////////////////////////

/*💀*/ void setup() //////////////////////////////////////
{
// 🎮 INICIALIZAR XBOX REMOTE // 

  Serial.begin(115200);
  Serial.println("Starting NimBLE Client");
  xboxController.begin();

/////////////////////////
  
// 🐧 INICIALIZAR PINES //
  
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  pinMode(enablePin1, OUTPUT);
  pinMode(relayPin, OUTPUT);

/////////////////////////

// 🦾 INICIALIZAR SERVOS //

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

// INICIALIZAR 🔴🟢🔵 RGB LED //

pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(pinIn, INPUT);

/////////////////////////////////

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

// 🚗 CONTROL DE MOTORES: //

// ❌ DETENER MOTORES //


if(xVal1 == 0){
digitalWrite(enablePin1,LOW);
digitalWrite(enablePin2,LOW);
}


// ⬆️⬇️ ARRIBA Y ABAJO //
 if(yVal1 == 100){
digitalWrite(motor1Pin1, LOW);
digitalWrite(motor1Pin2, HIGH);
digitalWrite(motor2Pin1, LOW);
digitalWrite(motor2Pin2, HIGH);
digitalWrite(enablePin2,HIGH);
digitalWrite(enablePin1,HIGH);
  }

if(yVal1 == -100){
digitalWrite(motor1Pin1, HIGH);
digitalWrite(motor1Pin2, LOW);
digitalWrite(motor2Pin1, HIGH);
digitalWrite(motor2Pin2, LOW);
digitalWrite(enablePin1,HIGH);
digitalWrite(enablePin2,HIGH);

  }


// ➡️⬅️ DERECHA E IZQUIERDA //
if(xVal1 == 100){
digitalWrite(motor1Pin1, HIGH);
digitalWrite(motor1Pin2, LOW);
digitalWrite(motor2Pin1, LOW);
digitalWrite(motor2Pin2, HIGH);
digitalWrite(enablePin1,HIGH);
digitalWrite(enablePin2,HIGH);

  }

if(xVal1 == -100){
digitalWrite(motor1Pin1, LOW);
digitalWrite(motor1Pin2, HIGH);
digitalWrite(motor2Pin1, HIGH);
digitalWrite(motor2Pin2, LOW);
digitalWrite(enablePin1,HIGH);
digitalWrite(enablePin2,HIGH);

  }

/////////////////////////

// ⚡ CONTROL SHOCK //

if (shockButtonVal == 1) {
    digitalWrite(relayPin, HIGH);
  }  
if (shockButtonVal == 0) {
    digitalWrite(relayPin, LOW);
  }

/////////////////////////

// 🎵 CONTROL DE DFPLAYER //

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

// 🦾 CONTROL DE SERVOS //

servoVal1 = map(xboxController.xboxNotif.joyLVert, 0, 65535, 180, 70);
miServo1.write(servoVal1);
//servoVal1 = map(yVal2, 100, -100, 0, 115);
//miServo1.write(servoVal1);
servoVal2 = map(xboxController.xboxNotif.joyRVert, 0, 65535, 180, 58);
miServo2.write(servoVal2);
if (xboxController.xboxNotif.btnRB == 1)
{
 miServo3.write(180);
}
else if (xboxController.xboxNotif.btnLB == 1)
{
 miServo3.write(0);
}
 
 else {miServo3.write(90);}

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

}
