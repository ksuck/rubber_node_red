void manual_option(String input) {
  if (input.length() > 0) {
    Serial.println(String(input));
    stage_input[0] = String(input);

    //---------------------- motor ------------------------
    for (int i = 0; i <= (size_motor - 1); i++) {
      if (input == ("forword_motor") + String(i)) {
        manual_stage[i] = String(input);
      }
      if (input == ("backword_motor") + String(i)) {
        manual_stage[i] = String(input);
      }
      if (input == ("stop_motor") + String(i)) {
        manual_stage[i] = String(input);
      }


    }
    //----------------------- servo ---------------------
    if (input.startsWith("Servo")) {
      int colonIndex = input.indexOf(':');
      if (colonIndex != -1) {
        String value1 = input.substring(colonIndex + 1);
        int angle = value1.toInt();
        direct_servo.write(angle);
      }
    }
    

  }
  ///////////////////////////////////////////////////////////////////
  // motor1
  for (int i = 0; i <= (4); i++) {
    controlmotor_addlimit(manual_stage, i, motor_PWM, motor_A, motor_B, limit);
  }
  for (int i = 5; i <= (5); i++) {
    controlstepping_addlimit(manual_stage, i, motor_PWM, motor_A, motor_B, limit);
  }


  //axist left right
  controlaxist(stage_input[0], 0, 1, motor_PWM, motor_A, motor_B, limit);




  // แสดงผลระยะทาง
  //Serial.println("Distance1: " + String(lastState_distance[0]));

  //// แสดงผลระยะทาง
  //Serial.println("Distance2: " + String(lastState_distance[1]));

  //limit show
  //  for (int i = 0; i <= (size_limit - 1) ; i++) {
  //    int lastState_limit1 = digitalRead(limit[i][0]);
  //    int lastState_limit2 = digitalRead(limit[i][1]);
  //    if (lastState_limit1 == LOW) {
  //
  //      Serial.println("Limit " + String(i * 2) + ": " + String(lastState_limit1)); // ใช้ String() แปลงค่า
  //    } else {
  //      Serial.println("Limit " + String(i * 2) + ": " + String(lastState_limit1)); // ใช้ String() แปลงค่า
  //    }
  //    if (lastState_limit2 == LOW) {
  //      Serial.println("Limit " + String(i * 2 + 1) + ": " + String(lastState_limit2)); // ใช้ String() แปลงค่า
  //    } else {
  //      Serial.println("Limit " + String(i * 2 + 1) + ": " + String(lastState_limit2)); // ใช้ String() แปลงค่า
  //    }
  //
  //  }


//      for (int i = 0; i <= (size_induct - 1) ; i++) {
//        int lastState_inductive = digitalRead(induct[i]);
//        if (lastState_inductive == LOW) {
//          Serial.println("induct " + String(i) + ": " + String(lastState_inductive)); // ใช้ String() แปลงค่า
//        } else {
//          Serial.println("induct " + String(i) + ": " + String(lastState_inductive)); // ใช้ String() แปลงค่า
//        }
//  
//      }
//  



}
