#include "config_eq.h";

String option_setting = "empty";
//state limit array
byte lastState_limit[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600); // กำหนด Baud Rate

  //กำหนดขา litmit
  for (int i = 0; i < sizeof(lastState_limit); i++) {
    pinMode(limit[i], INPUT_PULLUP);
  }
}

void loop() {
  //<------------------------- ติดต่อ ----------------------------------->
  if (Serial.available() > 0)
  { // ตรวจสอบว่ามีข้อมูลใน Serial Buffer
    String input = Serial.readStringUntil('\n'); // อ่านข้อมูลจนถึง newline ('\n')
    input.trim(); // ลบช่องว่างและ newline ออก
    if (input.length() > 0) { // ตรวจสอบว่าข้อมูลไม่ว่างเปล่า
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

    //Serial.println("Received: " + input); // ส่งข้อมูลกลับเพื่อทดสอบ

  }

  //<------------------------- ติดต่อ ----------------------------------->
  if (option_setting == "manual")
  {
    manual_option();
  }
}
