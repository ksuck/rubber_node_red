#include "config_eq.h";

void manual_option() {
  lastState_limit[0] = digitalRead(limit[0]);
  if (lastState_limit[0] == LOW) {
    Serial.println("Limit 0: " + String(lastState_limit[0])); // ใช้ String() แปลงค่า
  }else{
     Serial.println("Limit 0: " + String(lastState_limit[0])); // ใช้ String() แปลงค่า
  }
}
