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




void controlmotor_addlimit(const String input[] , int motor_num , const int motorPWM[] , const int motor_A[] , const int motor_B[], const int limit[][2]) {

  int limit_read_on = HIGH;     // ค่าเริ่มต้นกรณีไม่มี limit switch
  int limit_read_bottom = HIGH; // ค่าเริ่มต้นกรณีไม่มี limit switch

  // ตรวจสอบว่า limit switch มีการกำหนดพินหรือไม่
  if (limit[motor_num][0] != -1) {
    limit_read_on = digitalRead(limit[motor_num][0]);
  }
  if (limit[motor_num][1] != -1) {
    limit_read_bottom = digitalRead(limit[motor_num][1]);
  }

  //ขึ้น
  if (input[motor_num] == ("forword_motor") + String(motor_num) && limit_read_on != LOW) {
    analogWrite(motor_PWM[motor_num], 150);
    analogWrite(motor_A[motor_num], 255);
    analogWrite(motor_B[motor_num], 0);
    //    Serial.println("Limit " + String(motor_num * 2) + ": " + String(limit_read_on)); // ใช้ String() แปลงค่า
  }
  //ลง
  else if (input[motor_num] == ("backword_motor") + String(motor_num) && limit_read_bottom != LOW) {
    analogWrite(motor_PWM[motor_num], 150);
    analogWrite(motor_A[motor_num], 0);
    analogWrite(motor_B[motor_num], 255);
    //    Serial.println("Limit " + String(motor_num * 2 + 1) + ": " + String(limit_read_on)); // ใช้ String() แปลงค่า
  }
  else {
    analogWrite(motor_PWM[motor_num], 0);
    analogWrite(motor_A[motor_num]  , 0);
    analogWrite(motor_B[motor_num]  , 0);
    //    Serial.println("Limit " + String(motor_num * 2) + ": " + String(limit_read_on));
    //    Serial.println("Limit " + String(motor_num * 2 + 1) + ": " + String(limit_read_on));
  }


}

void controlmotor_addlimit2(String input , int motor_num , const int motorPWM[] , const int motor_A[] , const int motor_B[], const int limit[][2]) {

  int limit_read_on = HIGH;     // ค่าเริ่มต้นกรณีไม่มี limit switch
  int limit_read_bottom = HIGH; // ค่าเริ่มต้นกรณีไม่มี limit switch

  // ตรวจสอบว่า limit switch มีการกำหนดพินหรือไม่
  if (limit[motor_num][0] != -1) {
    limit_read_on = digitalRead(limit[motor_num][0]);
  }
  if (limit[motor_num][1] != -1) {
    limit_read_bottom = digitalRead(limit[motor_num][1]);
  }

  //ขึ้น
  if (input == ("forword_motor") + String(motor_num) && limit_read_on != LOW) {
    analogWrite(motor_PWM[motor_num], 150);
    analogWrite(motor_A[motor_num], 255);
    analogWrite(motor_B[motor_num], 0);
    //    Serial.println("Limit " + String(motor_num * 2) + ": " + String(limit_read_on)); // ใช้ String() แปลงค่า
  }
  //ลง
  else if (input == ("backword_motor") + String(motor_num) && limit_read_bottom != LOW) {
    analogWrite(motor_PWM[motor_num], 150);
    analogWrite(motor_A[motor_num], 0);
    analogWrite(motor_B[motor_num], 255);
    //    Serial.println("Limit " + String(motor_num * 2 + 1) + ": " + String(limit_read_on)); // ใช้ String() แปลงค่า
  }
  else {
    analogWrite(motor_PWM[motor_num], 0);
    analogWrite(motor_A[motor_num]  , 0);
    analogWrite(motor_B[motor_num]  , 0);
    //    Serial.println("Limit " + String(motor_num * 2) + ": " + String(limit_read_on));
    //    Serial.println("Limit " + String(motor_num * 2 + 1) + ": " + String(limit_read_on));
  }


}




void controlstepping_addlimit(const String input[] , int motor_num , const int motorPWM[] , const int motor_A[] , const int motor_B[], const int limit[][2]) {
  const float step_distance_mm = 0.01;

  int limit_read_on = digitalRead(limit[motor_num][0]);
  int limit_read_bottom = digitalRead(limit[motor_num][1]);

  //ขึ้น
  if (input[motor_num] == ("forword_motor") + String(motor_num) && limit_read_on != LOW) {
    digitalWrite(motor_A[motor_num], LOW);

    digitalWrite(motor_B[motor_num], HIGH);
    delayMicroseconds(100);
    digitalWrite(motor_B[motor_num], LOW);
    delayMicroseconds(100);
    //Serial.println("Limit " + String(motor_num * 2) + ": " + String(limit_read_on)); // ใช้ String() แปลงค่า

    
  }
  //ลง
  else if (input[motor_num] == ("backword_motor") + String(motor_num) && limit_read_bottom != LOW) {
    digitalWrite(motor_A[motor_num], HIGH);

    digitalWrite(motor_B[motor_num], HIGH);
    delayMicroseconds(100);
    digitalWrite(motor_B[motor_num], LOW);
    delayMicroseconds(100);
    //Serial.println("Limit " + String(motor_num * 2 + 1) + ": " + String(limit_read_on)); // ใช้ String() แปลงค่า

 
  }
  else {
    digitalWrite(motor_B[motor_num], LOW);
    digitalWrite(motor_B[motor_num], LOW);
    //Serial.println("Limit " + String(motor_num * 2) + ": " + String(limit_read_on));
    //Serial.println("Limit " + String(motor_num * 2 + 1) + ": " + String(limit_read_on));


  }
}

void controlstepping_addlimit2(const String input , int motor_num , const int motorPWM[] , const int motor_A[] , const int motor_B[], const int limit[][2]) {

  int limit_read_on = digitalRead(limit[motor_num][0]);
  int limit_read_bottom = digitalRead(limit[motor_num][1]);

  //ขึ้น
  if (input == ("forword_motor") + String(motor_num) && limit_read_on != LOW) {
    digitalWrite(motor_A[motor_num], LOW);

    digitalWrite(motor_B[motor_num], HIGH);
    delayMicroseconds(100);
    digitalWrite(motor_B[motor_num], LOW);
    delayMicroseconds(100);
    //Serial.println("Limit " + String(motor_num * 2) + ": " + String(limit_read_on)); // ใช้ String() แปลงค่า
  }
  //ลง
  else if (input == ("backword_motor") + String(motor_num) && limit_read_bottom != LOW) {
    digitalWrite(motor_A[motor_num], HIGH);

    digitalWrite(motor_B[motor_num], HIGH);
    delayMicroseconds(100);
    digitalWrite(motor_B[motor_num], LOW);
    delayMicroseconds(100);
    //Serial.println("Limit " + String(motor_num * 2 + 1) + ": " + String(limit_read_on)); // ใช้ String() แปลงค่า

   
  }
  else {
    digitalWrite(motor_B[motor_num], LOW);
    digitalWrite(motor_B[motor_num], LOW);
    //Serial.println("Limit " + String(motor_num * 2) + ": " + String(limit_read_on));
    //Serial.println("Limit " + String(motor_num * 2 + 1) + ": " + String(limit_read_on));


  }

}


void controlaxist(const String input , int motor_num1 , int motor_num2 , const int motorPWM[] , const int motor_A[] , const int motor_B[], const int limit[][2]) {
  int limit_read_on1 = digitalRead(limit[motor_num1][0]);
  int limit_read_bottom1 = digitalRead(limit[motor_num1][1]);

  int limit_read_on2 = digitalRead(limit[motor_num2][0]);
  int limit_read_bottom2 = digitalRead(limit[motor_num2][1]);


  if (input == "axist_left" && limit_read_on1 != LOW && limit_read_on2 != LOW) {

    analogWrite(motor_PWM[motor_num1], 150); // PWM สูงสุดเพื่อเริ่มต้น
    analogWrite(motor_PWM[motor_num2], 150);

    analogWrite(motor_A[motor_num1], 255);
    analogWrite(motor_B[motor_num1], 0);

    analogWrite(motor_A[motor_num2], 255);
    analogWrite(motor_B[motor_num2], 0);

    delay(100);
    analogWrite(motor_PWM[motor_num1], 255); // ลดความเร็ว
    analogWrite(motor_PWM[motor_num2], 255);

  }
  else if (input == "axist_right" && limit_read_bottom1 != LOW && limit_read_bottom2 != LOW) {
    analogWrite(motor_PWM[motor_num1], 150);
    analogWrite(motor_PWM[motor_num2], 150);

    analogWrite(motor_A[motor_num1], 0);
    analogWrite(motor_B[motor_num1], 255);

    analogWrite(motor_A[motor_num2], 0);
    analogWrite(motor_B[motor_num2], 255);

    delay(100);
    analogWrite(motor_PWM[motor_num1], 255);
    analogWrite(motor_PWM[motor_num2], 255);
  }
  else {
    analogWrite(motor_PWM[motor_num1], 0);
    analogWrite(motor_A[motor_num1], 0);
    analogWrite(motor_B[motor_num1], 0);

    analogWrite(motor_PWM[motor_num2], 0);
    analogWrite(motor_A[motor_num2], 0);
    analogWrite(motor_B[motor_num2], 0);
  }

}
