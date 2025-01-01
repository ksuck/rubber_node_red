#include <Arduino_FreeRTOS.h>
#include "config_eq.h";

//String input
String option_setting = "empty";
String input = "";
String last_input = "";

//status limit array
//byte lastState_limit[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int lastState_distance[] = {0, 0};
long duration[2];

//status motor
byte lastState_A[] = {0, 0, 0, 0, 0};
byte lastState_B[] = {0, 0, 0, 0, 0};
int  lastState_PWM[] = {0, 0, 0, 0, 0};
String manual_stage[] = {"", "", "", ""};

void setup() {
  Serial.begin(9600); // กำหนด Baud Rate

  //กำหนดขา servo
  direct_servo.attach(pinservo);
  direct_servo.write(0);

  //กำหนดขา litmit
  for (int i = 0; i <= (size_limit) - 1; i++) {
    pinMode(limit[i][0], INPUT_PULLUP);
    pinMode(limit[i][1], INPUT_PULLUP);
  }
  //กำหนดขา ultrasonic
  for (int i = 0; i <= (size_ultra) - 1; i++) {
    pinMode(ultra_trig[i], OUTPUT);
    pinMode(ulta_echo[i], INPUT);
  }
  //motor
  for (int i = 0; i <= (size_motor) - 1; i++) {
    pinMode(motor_PWM[i], OUTPUT);
    pinMode(motor_A[i], OUTPUT);
    pinMode(motor_B[i], OUTPUT);
  }
  //inductive
  for (int i = 0; i <= (size_induct) - 1; i++) {
    pinMode(induct, INPUT);

  }



  //Task main
  xTaskCreate(
    maintask, // function in task
    "main_loop",
    128,
    NULL,
    1,
    NULL
  );
  //ultrasonic1
  xTaskCreate(
    ultrasonictask1, // function in task
    "ultrasonic",
    128,
    NULL,
    1,
    NULL
  );
  //ultrasonic1
  xTaskCreate(
    ultrasonictask2, // function in task
    "ultrasonic",
    128,
    NULL,
    1,
    NULL
  );
}

void loop() {}


void maintask(void *pvParameters) {
  //<------------------------- ติดต่อ ----------------------------------->
  while (1) {
    if (Serial.available() > 0)
    { // ตรวจสอบว่ามีข้อมูลใน Serial Buffer
      input = Serial.readStringUntil('\n'); // อ่านข้อมูลจนถึง newline ('\n')
      input.trim(); // ลบช่องว่างและ newline ออก
      if (input.length() > 0 && input != last_input) { // ตรวจสอบว่าข้อมูลไม่ว่างเปล่า
        input.replace(" ", "\n");

        //option
        if (input == "manual" && option_setting != "manual") {
          option_setting = "manual";
          Serial.println("Manual: START");
        }
        else if (input == "auto" && option_setting != "auto") {
          option_setting = "auto";
          Serial.println("Auto: START");
        }
        else if (input == "auto_pid" && option_setting != "auto_pid") {
          option_setting = "auto_pid";
          Serial.println("Auto_pid: START");
        }
        else if (input == "empty") {
          option_setting = "empty";
          Serial.println("STOP");
        }
      }

      //Serial.println("Received: " + sizeof(limit)); // ส่งข้อมูลกลับเพื่อทดสอบ
    } else {
      input = "";
    }
    //<------------------------- ติดต่อ ----------------------------------->
    if (option_setting == "manual")
    {

      manual_option(input);
    }
  }
}
