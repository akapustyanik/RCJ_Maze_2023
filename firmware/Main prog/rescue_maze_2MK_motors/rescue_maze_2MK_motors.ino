#include "mazeLib.h"

#define mA_IN1 4
#define mA_IN2 5
#define mB_IN1 6
#define mB_IN2 7
#define mC_IN1 8
#define mC_IN2 9
#define mD_IN1 11
#define mD_IN2 10

#define EncPin_A 18
#define EncPin_B 19
#define EncPin_C 2
#define EncPin_D 3

#define Rx 17
#define Tx 16

#define rpm 170 //скорость в об/мин
#define d 77 //диаметр в мм

MOTOR motorA(mA_IN1, mA_IN2, A, rpm, d, 3);
MOTOR motorB(mB_IN1, mB_IN2, B, rpm, d, 3);
MOTOR motorC(mC_IN1, mC_IN2, C, rpm, d, 3);
MOTOR motorD(mD_IN1, mD_IN2, D, rpm, d, 3);

unsigned long mill_A = 0, mill_B = 0, mill_C = 0, mill_D = 0;
int EncMA = 0, EncMB = 0, EncMC = 0, EncMD = 0;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  attachInterrupt(5, enc_A, RISING);
  attachInterrupt(4, enc_B, RISING);
  attachInterrupt(0, enc_C, RISING);
  attachInterrupt(1, enc_D, RISING);
  pinMode(EncPin_A, INPUT); // Инициализируем пин Encoder_output_A на вход
  pinMode(EncPin_B, INPUT); // Инициализируем пин Encoder_output_B на вход
  pinMode(EncPin_C, INPUT); // Инициализируем пин Encoder_output_C на вход
  pinMode(EncPin_D, INPUT); // Инициализируем пин Encoder_output_D на вход
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

}
struct Str {
  int left;
  int front;
  int right;
  int button1;
  float x;
  float y;
  float z;
};
int left_wall;
int front_wall;
int right_wall;
int button1;
float x;
float y;
float z;
bool a = true, activate = false;
float errP, errI;
float alpha = 0;
int state = 0, distance = 30;
long timer = millis(), old_timer = 0;
float diam = d / 10;
//while ((abs(motorA.encoder()) + abs(motorB.encoder()) + abs(motorC.encoder()) + abs(motorD.encoder())) / 4 < 360 / (diam * 3.14) * distance)
void loop() {
  Str buf;
  timer = millis();
  Serial.println(z);
  if (Serial2.readBytes((byte*)&buf, sizeof(buf))) {
    left_wall = buf.left;
    front_wall = buf.front;
    right_wall = buf.right;
    button1 = buf.button1;
    x = buf.x;
    y = buf.y;
    z = buf.z;
  }
  if (button1 == 1 && old_timer + 200 < timer)
  {
    if (activate)
    {
      activate = false;
    }
    else
    {
      activate = true; 
    }
    old_timer = millis();
  }
  if (activate)
  {
    if (state == 0)
    {
      if (!right_wall)
      {
        alpha = alpha + 15;
        state = 2;
      }
      else
      {
        if (!front_wall)
        {
          clearAllEnc();
          state = 3;
        }
        else
        {
          alpha = alpha - 4;
          state = 1;
        }
      }
    }
    if (state == 1)
    {
      left();
      if (abs(alpha) <= abs(z))
      {
        motorA.justSpeed(0);
        motorB.justSpeed(0);
        motorC.justSpeed(0);
        motorD.justSpeed(0);
        state = 0;
        errI = 0;
        delay(200);
      }
    }
    if (state == 2)
    {
      right();
      if (abs(alpha) <= abs(z))
      {
        motorA.justSpeed(0);
        motorB.justSpeed(0);
        motorC.justSpeed(0);
        motorD.justSpeed(0);
        clearAllEnc();
        state = 3;
        errI = 0;
        delay(200);
      }
    }
    if (state == 3)
    {
      forward(30);
      if ((abs(motorA.encoder()) + abs(motorB.encoder()) + abs(motorC.encoder()) + abs(motorD.encoder())) / 4 > 360 / (7.7 * 3.141592) * distance)
      {
        motorA.justSpeed(0);
        motorB.justSpeed(0);
        motorC.justSpeed(0);
        motorD.justSpeed(0);
        state = 0;
        delay(200);
      }
    }
  }
  delay(5);
}
