/////////////////////////////
//   CODED BY NICOLÁS 🗿  //
/////////////////////////////

// 🕹️ INICIALIZAR REMOTEXY //

#define REMOTEXY_MODE__ESP32CORE_BLUETOOTH
#include <BluetoothSerial.h>
#include <RemoteXY.h>
#define REMOTEXY_BLUETOOTH_NAME "Wall-e"
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 69 bytes
  { 255,7,0,0,0,59,0,16,79,0,1,0,34,6,10,10,34,31,240,159,
  152,130,0,1,0,44,6,10,10,94,31,240,159,142,181,0,5,32,5,16,
  35,35,27,31,31,5,32,60,16,35,35,27,31,31,1,0,54,6,10,10,
  177,31,226,154,161,0 };
struct {
  uint8_t emote_1; // =1 if button pressed, else =0 
  uint8_t emote_2; // =1 if button pressed, else =0 
  int8_t joystick_1_x; // from -100 to 100  
  int8_t joystick_1_y; // from -100 to 100  
  int8_t joystick_2_x; // from -100 to 100  
  int8_t joystick_2_y; // from -100 to 100  
  uint8_t emote_3; // =1 if button pressed, else =0 
 
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////

// 🦾 INICIALIZAR SERVOS //

#include <ESP32Servo.h>

const int pinServo1 = 33; // Puedes cambiar este valor según la conexión física
int servoVal1;
const int pinServo2 = 32; // Puedes cambiar este valor según la conexión física
int servoVal2;
const int pinServo3 = 23; // Puedes cambiar este valor según la conexión física
int servoVal3;

Servo miServo1;
Servo miServo2;
Servo miServo3;

/////////////////////////

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

/////////////////////////

/*💀*/ void setup() //////////////////////////////////////
{
// 🕹️ INICIALIZAR REMOTEXY // 

  RemoteXY_Init (); 
  Serial.begin(9600);

/////////////////////////

// 🦾 INICIALIZAR SERVOS //

  miServo1.setPeriodHertz(100); // Establecer la frecuencia en 50 Hz (estándar para servos)
  miServo1.attach(pinServo1, 500, 2400); // Configurar el pin del servo y los límites del pulso

  miServo2.setPeriodHertz(100); // Establecer la frecuencia en 50 Hz (estándar para servos)
  miServo2.attach(pinServo2, 500, 2400); // Configurar el pin del servo y los límites del pulso

  miServo3.setPeriodHertz(100); // Establecer la frecuencia en 50 Hz (estándar para servos)
  miServo3.attach(pinServo3, 500, 2400); // Configurar el pin del servo y los límites del pulso

/////////////////////////

// 🚗 MOTORES //
  
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  pinMode(enablePin1, OUTPUT);

/////////////////////////
}

/*💀*/  void loop() //////////////////////////////////////
{

RemoteXY_Handler ();
  
// 🗿 ESCRITURA DE VARIABLES //

  xVal1 = RemoteXY.joystick_1_x;
  yVal1 = RemoteXY.joystick_1_y;
  xVal2 = RemoteXY.joystick_2_x;
  yVal2 = RemoteXY.joystick_2_y;

  emoteButtonVal = RemoteXY.emote_1;
  musicButtonVal = RemoteXY.emote_2;
  shockButtonVal = RemoteXY.emote_3;
  
  Serial.print("Joystick 1 X: ");
  Serial.print(xVal1);

  Serial.print("   Joystick 1 Y: ");
  Serial.print(yVal1);

  Serial.print("       Joystick 2 X: ");
  Serial.print(xVal2);

  Serial.print("   Joystick 2 Y: ");
  Serial.print(yVal2);

  Serial.print("         Emote Button: ");
  Serial.print(emoteButtonVal);

  Serial.print("   Music Button: ");
  Serial.print(musicButtonVal);

  Serial.print("   Shock Button: ");
  Serial.println(shockButtonVal);

/////////////////////////

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

// 🦾 CONTROL DE SERVOS //

servoVal1 = map(yVal2, 100, -100, 0, 115);
miServo1.write(servoVal1);
servoVal2 = map(yVal2, 100, -100, 180, 58);
miServo2.write(servoVal2);
servoVal3 = map(xVal2, 100, -100, 180, 0);
miServo3.write(servoVal3);

/////////////////////////

}
