void Rotate_with_relay() {
  Serial.println("please input number of digits");
  delay(1000);
  while (x != 1) 
  {

    if (Serial.available() > 0) 
    {
      array_size_key = Serial.read();  //get input through serial comm
    }
    if (array_size_key) 
    {

      if (isDigit(array_size_key)) 
      {

        String num2 = String(array_size_key);
        array_size = num2.toInt();
        Serial.println(array_size);
        ++x;

      } 
      else if (array_size_key == '*') 
      {
        Serial.println("cleared");
        delay(1000);
        x = 0;
        array_size = 0;
      } 
      else 
      {
        x = 0;
        array_size = 0;
      }
      if (array_size > 6) {
        Serial.println("Max is 6 please reinput");
        delay(1000);
        x = 0;
        array_size = 0;
      }
      if (array_size_key == '*') 
      {
        Serial.println("cleared");
        delay(500);
        x = 0;
        array_size = 0;
      }
    }
  }
  int cycles_array[array_size]; // an arrray to store cycles in it
  Serial.println("please input number of cycles");
  delay(1000);
  while (cycle_counter != array_size) 
  {

    char key;
    if (Serial.available() > 0) 
    {
      key = Serial.read();
    }

    if (key) 
    {

      if ((isDigit(key))) 
      {
        String num = String(key);
        cycles_array[cycles_iterator] = num.toInt();
        Serial.println(cycles_array[cycles_iterator]);
        ++cycles_iterator;
        ++cycle_counter;
      }
      if (key == '*') 
      {
        cycles_array[0] = 0;
        cycles_array[1] = 0;
        cycles_array[2] = 0;
        cycles_array[3] = 0;
        cycles_array[4] = 0;
        cycles_array[5] = 0;
        cycles_array[6] = 0;
        Serial.println("cleared");
        delay(500);
        cycles_iterator = 0;
        cycle_counter = 0;
      }
    }
  }
  Serial.println("please input the desired angle");
  delay(500);
  while (angles_counter != 3) {
    char cy;
    if (Serial.available() > 0) {
      cy = Serial.read();
    }

    if (cy) {

      if ((isDigit(cy))) {
        String cyc = String(cy);
        angles_array[angles_iterator] = cyc.toInt();
        Serial.println(angles_array[angles_iterator]);

        ++angles_iterator;
        ++angles_counter;
      }
      if (cy == '*') {
        angles_array[0] = 0;
        angles_array[1] = 0;
        angles_array[2] = 0;
        Serial.println("cleared");
        delay(500);
        angles_counter = 0;
        angles_iterator = 0;
      }
    }
  }
  cycles_sixth_val = cycles_array[0];
  cycles_fifth_val = cycles_array[1];
  cycles_fourth_val = cycles_array[2];
  cycles_third_val = cycles_array[3];
  cycles_second_val = cycles_array[4];
  cycles_first_val = cycles_array[5];

  cycles_second_val = cycles_second_val * 10;
  cycles_third_val = cycles_third_val * 100;
  cycles_fourth_val = cycles_fourth_val * 1000;
  cycles_fifth_val = cycles_fifth_val * 10000;
  cycles_sixth_val = cycles_sixth_val * 100000;

  angle_third_val = angles_array[0];
  angle_second_val = angles_array[1];
  angle_first_val = angles_array[2];

  angle_second_val = angle_second_val * 10;
  angle_third_val = angle_third_val * 100;

  angle = angle_first_val + angle_second_val + angle_third_val;
  ratio = angle / 90.00; // This ratio is being used to calculate the time, and the amount of steps for the desired angle. 
  cycles = cycles_first_val + cycles_second_val + cycles_third_val + cycles_fourth_val + cycles_fifth_val + cycles_sixth_val + cycles_seventh_val;

  Serial.print("You entered: ");
  Serial.print(cycles);
  Serial.println(" cycles");
  delay(2000);
  Serial.print("Your angle is: ");
  Serial.println(angle);
  delay(2000);
  steps = steps * ratio; 
  seconds = seconds * ratio;
  seconds_disp = seconds_disp * ratio;
  unsigned long time = cycles * seconds;
  float hours = time / 3600;
  float days = hours / 24;
  Serial.print("Time period is: "); 
  Serial.println(hours);
  delay(2000);
  Serial.print("Time period is: "); 
  Serial.println(days);
  delay(2000);

  cycles_disp = cycles;
  time_disp = cycles * seconds_disp;
  hours_disp = time_disp / 3600;
  days_disp = hours_disp / 24;
  for (unsigned long i = 1; i <= cycles; ++i) 
  {

    if (days_disp <= 0) 
    {
      Serial.print("Cycles remaining: ");
      Serial.println(cycles_disp);
      Serial.println("Will finish soon");
    }

    Serial.print("Cycles remaining: ");
    Serial.println(cycles_disp); 
    Serial.print("Days remaining: ");
    Serial.println(days_disp);

    digitalWrite(relayPin, HIGH);  //Turn the relay ON for 0.5 second
    delay(500);
    digitalWrite(relayPin, LOW);  //Turn the relay Off for 1 second
    delay(1000);
    // Set the target position:
    stepper.moveTo(-steps);
    // Run to target position with set speed and acceleration/deceleration:
    stepper.runToPosition();
    delay(1000);
    stepper.setCurrentPosition(0);
    stepper.moveTo(1000);
    // Run to target position with set speed and acceleration/deceleration:
    stepper.runToPosition();
    stepper.setCurrentPosition(0);
    stepper.moveTo(steps - 1000);

    stepper.runToPosition();
    stepper.setCurrentPosition(0);
    delay(1000);


    cycles_disp = cycles_disp - 1;
    hours_disp = hours_disp - (0.00027778 * 10);
    days_disp = days_disp - (0.00001157 * 10);
  }
  if (cycles_disp == 0) 
  {
    Serial.println("done");
  }
}
