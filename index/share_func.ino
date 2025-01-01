// ultrasonic
void ultrasonictask1(void *pvParameters) {
  int number_ult = 0;//val ultasonic
  while (1) {
    // ส่ง Pulse ไปที่ Trig
    digitalWrite(ultra_trig[number_ult], LOW);
    delayMicroseconds(2);
    digitalWrite(ultra_trig[number_ult], HIGH);
    delayMicroseconds(10);
    digitalWrite(ultra_trig[number_ult], LOW);

    // อ่านค่า Echo
    duration[0] = pulseIn(ulta_echo[number_ult], HIGH);
    lastState_distance[number_ult] = (duration[0] * 0.034) / 2;

    vTaskDelay(1000 / portTICK_PERIOD_MS);  // หน่วงเวลา 1 วินาที
  }
}

void ultrasonictask2(void *pvParameters) {
  int number_ult = 1;
  while (1) {
//    for (int i = 0; i <= (size_limit - 1) ; i++) {
//      int lastState_limit1 = digitalRead(limit[i][0]);
//      int lastState_limit2 = digitalRead(limit[i][1]);
//      if (lastState_limit1 == LOW) {
//        Serial.println("Limit " + String(i * 2) + ": " + String(lastState_limit1)); // ใช้ String() แปลงค่า
//      } else {
//        Serial.println("Limit " + String(i * 2) + ": " + String(lastState_limit1)); // ใช้ String() แปลงค่า
//      }
//      if (lastState_limit2 == LOW) {
//        Serial.println("Limit " + String(i * 2 + 1) + ": " + String(lastState_limit2)); // ใช้ String() แปลงค่า
//      } else {
//        Serial.println("Limit " + String(i * 2 + 1) + ": " + String(lastState_limit2)); // ใช้ String() แปลงค่า
//      }
//
//    }
//
//    //
//    for (int i = 0; i <= (size_induct - 1) ; i++) {
//      int lastState_inductive = digitalRead(induct[i]);
//      if (lastState_inductive == LOW) {
//        Serial.println("induct " + String(i) + ": " + String(lastState_inductive)); // ใช้ String() แปลงค่า
//      } else {
//        Serial.println("induct " + String(i) + ": " + String(lastState_inductive)); // ใช้ String() แปลงค่า
//      }
//
//    }



    vTaskDelay(1000 / portTICK_PERIOD_MS);  // หน่วงเวลา 1 วินาที
  }
}

void controlmotor_addlimit(const String input[] , int motor_num , const int motorPWM[] , const int motor_A[] , const int motor_B[], const int limit[][2]) {

  int limit_read_on = digitalRead(limit[motor_num][0]);
  int limit_read_bottom = digitalRead(limit[motor_num][1]);

  //ขึ้น
  if (input[motor_num] == ("forword_motor") + String(motor_num) && limit_read_on != LOW) {
    analogWrite(motor_PWM[motor_num], 255);
    analogWrite(motor_A[motor_num], 255);
    analogWrite(motor_B[motor_num], 0);
    Serial.println("Limit " + String(motor_num * 2) + ": " + String(limit_read_on)); // ใช้ String() แปลงค่า
  }
  //ลง
  else if (input[motor_num] == ("backword_motor") + String(motor_num) && limit_read_bottom != LOW) {
    analogWrite(motor_PWM[motor_num], 255);
    analogWrite(motor_A[motor_num], 0);
    analogWrite(motor_B[motor_num], 255);
    Serial.println("Limit " + String(motor_num * 2 + 1) + ": " + String(limit_read_on)); // ใช้ String() แปลงค่า
  }
  else {
    analogWrite(motor_PWM[motor_num], 0);
    analogWrite(motor_A[motor_num]  , 0);
    analogWrite(motor_B[motor_num]  , 0);
    Serial.println("Limit " + String(motor_num * 2) + ": " + String(limit_read_on));
    Serial.println("Limit " + String(motor_num * 2 + 1) + ": " + String(limit_read_on));
  }


}
