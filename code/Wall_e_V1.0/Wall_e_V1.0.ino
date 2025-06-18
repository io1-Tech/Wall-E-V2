/////////////////////////////
//   CODED BY NICOLÁS 🗿   //
/////////////////////////////

// 🕹️ INICIALIZAR REMOTEXY //

#define REMOTEXY_MODE__ESP32CORE_BLUETOOTH
#include <BluetoothSerial.h>
#include <RemoteXY.h>

#define REMOTEXY_BLUETOOTH_NAME "Wall-e"

#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 69 bytes
  { 255,6,0,0,0,62,0,16,79,0,5,32,5,16,35,35,27,31,31,1,
  0,35,6,10,10,34,31,240,159,152,130,0,1,0,53,6,10,10,94,31,
  240,159,142,181,0,1,0,66,13,19,19,60,31,226,134,145,0,1,0,66,
  33,19,19,60,31,226,134,147,0 };
  
struct {
  int8_t joystick_1_x; //   -100 to 100  
  int8_t joystick_1_y; //   -100 to 100  
  uint8_t emote_1; //       =1 if button pressed, else =0   
  uint8_t emote_2; //       =1 if button pressed, else =0 
  uint8_t button_up; //     =1 if button pressed, else =0 
  uint8_t button_down; //   =1 if button pressed, else =0 


  uint8_t connect_flag;//   =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

// 💪 VARIABLES //

int xVal;
int yVal;
int emoteButtonVal;
int musicButtonVal;


int motor1Pin1 = 12;
int motor1Pin2 = 14;
int motor2Pin1 = 27;
int motor2Pin2 = 26;
int enablePin1 = 13;
int enablePin2 = 25;

/////////////////////////

/*💩*/  void setup() /*                🖤                */
{
  
  RemoteXY_Init (); 
  Serial.begin(9600);
  
// 🚗 MOTORES //
  
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  pinMode(enablePin1, OUTPUT);

/////////////////////////
}

/*💩*/  void loop() /*                🖤                */
{

RemoteXY_Handler ();
  
// 🗿 ESCRITURA DE VARIABLES //

  xVal = RemoteXY.joystick_1_x;
  yVal = RemoteXY.joystick_1_y;

  emoteButtonVal = RemoteXY.emote_1;
  musicButtonVal = RemoteXY.emote_2;
  
  Serial.print("Joystick X: ");
  Serial.print(xVal);

  Serial.print("   Joystick Y: ");
  Serial.print(yVal);

  Serial.print("            Button emote: ");
  Serial.print(emoteButtonVal);

  Serial.print("   Button music: ");
  Serial.println(musicButtonVal);

// 🚗 CONTROL DE MOTORES: //

// ❌ DETENER MOTORES //
if(xVal == 0){
digitalWrite(enablePin1,LOW);
digitalWrite(enablePin2,LOW);
}


// ⬆️⬇️ ARRIBA Y ABAJO //
 if(yVal == 100){
digitalWrite(motor1Pin1, LOW);
digitalWrite(motor1Pin2, HIGH);
digitalWrite(motor2Pin1, LOW);
digitalWrite(motor2Pin2, HIGH);
digitalWrite(enablePin2,HIGH);
digitalWrite(enablePin1,HIGH);
  }

if(yVal == -100){
digitalWrite(motor1Pin1, HIGH);
digitalWrite(motor1Pin2, LOW);
digitalWrite(motor2Pin1, HIGH);
digitalWrite(motor2Pin2, LOW);
digitalWrite(enablePin1,HIGH);
digitalWrite(enablePin2,HIGH);

  }


// ➡️⬅️ DERECHA E IZQUIERDA //
if(xVal == 100){
digitalWrite(motor1Pin1, HIGH);
digitalWrite(motor1Pin2, LOW);
digitalWrite(motor2Pin1, LOW);
digitalWrite(motor2Pin2, HIGH);
digitalWrite(enablePin1,HIGH);
digitalWrite(enablePin2,HIGH);

  }

if(xVal == -100){
digitalWrite(motor1Pin1, LOW);
digitalWrite(motor1Pin2, HIGH);
digitalWrite(motor2Pin1, HIGH);
digitalWrite(motor2Pin2, LOW);
digitalWrite(enablePin1,HIGH);
digitalWrite(enablePin2,HIGH);

  }

/////////////////////////

}
