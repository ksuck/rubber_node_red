void auto_option(String input) {
  if (stage == 9) {
    if (step_count != 0) {
      controlstepping_addlimit2("backword_motor5", 5, motor_PWM, motor_A, motor_B, limit);
      step_count--;
    }

    else if (step_count == 0) {
      controlstepping_addlimit2("forword_motor5", 5, motor_PWM, motor_A, motor_B, limit);
      Serial.println("check pass5");
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      stage = 10;
    }

  }

  //---------------------------------------------------------------------------------------------------------------------------
  if (stage == 8) {
    direct_servo.write(180);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    stage = 9;

    //Serial.println(total_distance);
  }
  //เอาขึ้น
  if (stage == 7) {
    if (step_count != 10000) {
      controlstepping_addlimit2("forword_motor5", 5, motor_PWM, motor_A, motor_B, limit);
      step_count++;
    }

    else if (step_count == 10000) {
      controlstepping_addlimit2("forword_motor5", 5, motor_PWM, motor_A, motor_B, limit);
      Serial.println("check pass5");
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      stage = 8;
    }
  }
  //-----------------------------------------------------------------------------------------
  if (stage == 6) {
    if (digitalRead(induct[0]) != LOW) {
      controlmotor_addlimit2("stop_motor0", 0, motor_PWM, motor_A, motor_B, limit);
      controlmotor_addlimit2("stop_motor1", 1, motor_PWM, motor_A, motor_B, limit);
      stage = 4;
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    else if  (digitalRead(induct[0]) == LOW) {
      controlmotor_addlimit2("stop_motor0", 0, motor_PWM, motor_A, motor_B, limit);
      controlmotor_addlimit2("stop_motor1", 1, motor_PWM, motor_A, motor_B, limit);
      Serial.println("check pass4");
      prox1 = 0;
      prox2 = 0;
      //next stage
      stage = 7;
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
  }


  if (stage == 5) {
    if (prox1 == 0 && digitalRead(induct[0]) != LOW) {
      controlmotor_addlimit2("forword_motor1", 1, motor_PWM, motor_A, motor_B, limit);
      vTaskDelay(20 / portTICK_PERIOD_MS);
      controlmotor_addlimit2("stop_motor1", 1, motor_PWM, motor_A, motor_B, limit);
    }

    else if  (prox1 == 0 && digitalRead(induct[0]) == LOW) {
      controlmotor_addlimit2("stop_motor0", 0, motor_PWM, motor_A, motor_B, limit);
      controlmotor_addlimit2("stop_motor1", 1, motor_PWM, motor_A, motor_B, limit);
      Serial.println("stop stage 5");
      prox1 = 1;
      prox2 = 0;
      //next stage
      stage = 6;
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
  }
  //วิ้งกลับ
  if (stage == 4) {
    if (prox1 == 1 && digitalRead(induct[0]) != LOW) {
      controlmotor_addlimit2("backword_motor1", 1, motor_PWM, motor_A, motor_B, limit);
      vTaskDelay(20 / portTICK_PERIOD_MS);
      controlmotor_addlimit2("stop_motor1", 1, motor_PWM, motor_A, motor_B, limit);
    }

    else if  (prox1 == 1 && digitalRead(induct[0]) == LOW) {
      controlmotor_addlimit2("stop_motor0", 0, motor_PWM, motor_A, motor_B, limit);
      controlmotor_addlimit2("stop_motor1", 1, motor_PWM, motor_A, motor_B, limit);
      Serial.println("stop stage 4");
      prox1 = 0;
      prox2 = 0;
      //next stage
      stage = 5;
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
  }
  //เช็คตำแหน่ง prox บน
  if (stage == 3) {
    if (digitalRead(induct[1]) != LOW) {
      controlmotor_addlimit2("stop_motor0", 0, motor_PWM, motor_A, motor_B, limit);
      controlmotor_addlimit2("stop_motor1", 1, motor_PWM, motor_A, motor_B, limit);
      stage = 1;
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    else if  (digitalRead(induct[1]) == LOW) {
      controlmotor_addlimit2("stop_motor0", 0, motor_PWM, motor_A, motor_B, limit);
      controlmotor_addlimit2("stop_motor1", 1, motor_PWM, motor_A, motor_B, limit);
      Serial.println("check pass3");
      prox1 = 1;
      prox2 = 0;
      //next stage
      stage = 4;
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

  }

  //วิ้งไป
  if (stage == 2) {
    if (prox2 == 0 && digitalRead(induct[1]) != LOW) {
      controlmotor_addlimit2("forword_motor0", 0, motor_PWM, motor_A, motor_B, limit);
      vTaskDelay(100 / portTICK_PERIOD_MS);
      controlmotor_addlimit2("stop_motor0", 0, motor_PWM, motor_A, motor_B, limit);
    }

    else if  (prox2 == 0 && digitalRead(induct[1]) == LOW) {
      controlmotor_addlimit2("stop_motor0", 0, motor_PWM, motor_A, motor_B, limit);
      controlmotor_addlimit2("stop_motor1", 1, motor_PWM, motor_A, motor_B, limit);
      Serial.println("stop stage 2");
      prox1 = 1;
      prox2 = 1;
      //next stage
      stage = 3;
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

  }
  //วิ้งกลับ
  if (stage == 1) {

    if (prox2 == 1 && digitalRead(induct[1]) != LOW) {
      controlmotor_addlimit2("backword_motor0", 0, motor_PWM, motor_A, motor_B, limit);
      vTaskDelay(100 / portTICK_PERIOD_MS);
      controlmotor_addlimit2("stop_motor0", 0, motor_PWM, motor_A, motor_B, limit);
    }

    else if  (prox2 == 1 && digitalRead(induct[1]) == LOW) {
      controlmotor_addlimit2("stop_motor0", 0, motor_PWM, motor_A, motor_B, limit);
      controlmotor_addlimit2("stop_motor1", 1, motor_PWM, motor_A, motor_B, limit);
      Serial.println("stop stage 1");
      prox1 = 1;
      prox2 = 0;
      //next stage
      stage = 2;
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }



  }


  if (stage == 0) {
    if (digitalRead(induct[1]) == LOW) {
      stage_input[0] = "axist_stop";
      controlaxist(stage_input[0], 0, 1, motor_PWM, motor_A, motor_B, limit);
      Serial.println("induct " + String(0) + ": " + String(digitalRead(induct[0]))); // ใช้ String() แปลงค่า
      //
      prox2 = 1;
      //next stage
      stage = 1;//ต้องใส่ให้มันสั่งครั้งเดียว
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }


    if (digitalRead(induct[1]) == HIGH) {
      //Serial.println("stage0: move"); // ใช้ String() แปลงค่า
      stage_input[0] = "axist_left";
      controlaxist(stage_input[0], 0, 1, motor_PWM, motor_A, motor_B, limit);
    }
  }



}
