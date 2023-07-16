void position_adjust() {
  char pos_key;
  char pos_stopper = 'z';
  int pos_counter = 0;
  Serial.println("For left enter L"); 
  delay(1000);
  Serial.println("For Right enter R");
  delay(1000);
  while (pos_counter != 1) 
  {
    if (Serial.available() > 0) 
    {
      pos_key = Serial.read();
    }
    if (pos_key == 'R' || pos_key == 'r' || pos_key == 'L' || pos_key == 'l') 
    {
      ++pos_counter;
      Serial.println(pos_key);
      delay(1000);
    }
    else 
    {
      pos_counter = 0;
    }
  }
  int pos_stop_counter = 0;
  while (pos_stop_counter != 1) 
  {
    if (pos_key == 'L' || pos_key == 'l') 
    {
      digitalWrite(dirPin, HIGH);
      stepper.moveTo(1000); //move left 1000 steps every time it goes through the loop until the user enter s
      stepper.runToPosition();
      stepper.setCurrentPosition(0);
      Serial.println("Moving left");
      pos_stop_counter = 0;
      if (Serial.available() > 0) 
      {
        pos_stopper = Serial.read();
      }
      if (pos_stopper == 'S' || pos_stopper == 's') 
      {
        Serial.println("Stopped");
        pos_stop_counter = 1;
      }

    } 
    else if (pos_key == 'R' || pos_key == 'r') 
    {
      digitalWrite(dirPin, HIGH);
      stepper.moveTo(-1000); //move right 1000 steps every time it goes through the loop until the user enter s
      stepper.runToPosition();
      stepper.setCurrentPosition(0);
      Serial.println("Moving right");
      pos_stop_counter = 0;
      if (Serial.available() > 0) {
        pos_stopper = Serial.read();
      }
      if (pos_stopper == 'S' || pos_stopper == 's') {
        Serial.println("Stopped");
        pos_stop_counter = 1;
      }
    }
  }
  exit(0);
}