//servo
#include <Servo.h>
Servo direct_servo;
#define pinservo 31

// ประกาศ array limit[] ในที่นี้
//       1       2       3      4
const int limit[][2] = {{49, 2}, {11, 12} , {3, 10}, {33, 8},{-1,-1},{50, 9}}; //<แก้ array เป็น 2 มิติ ที่ limit
const int size_limit = sizeof(limit) / sizeof(limit[0]);

//ultrasonic
const int ultra_trig[] = {4, 5};
const int ulta_echo[] = {44, 45};
const int size_ultra = sizeof(ultra_trig) / sizeof(ultra_trig[0]);

//DC MOTOR
const int motor_PWM[] = {34,  36, 38,  40 , 42, -1}; //-1
const int motor_A[] =   {A0,  A2, A4,  A8,  46, A11}; // A11
const int motor_B[] =   {A1,  A9, A12, A7 , 47, A10}; //A10
const int size_motor = sizeof(motor_PWM) / sizeof(motor_PWM[0]);
//steping 
int step_count = 0;
float total_distance =0;

//inductive
const int induct[] = {7,6};
const int size_induct = sizeof(induct) / sizeof(induct[0]);
