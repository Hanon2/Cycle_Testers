void Move_with_hall_sensor_and_relay()
{
    Serial.println("Please input number of failures");
    delay(1000);

    while (c != 1)
    {
        char failures_key;
        if (Serial.available() > 0)
        {
            failures_key = Serial.read(); 
        }
        if (failures_key)
        {
            if (isDigit(failures_key))
            {
                Serial.println(failures_key);
                String num3 = String(failures_key);
                failures_number = num3.toInt();
                ++c; // just a counter to get out of the loop
            }
            else if (failures_key == '*')
            {
                Serial.println("cleared");
                delay(2000);
                c = 0;
                failures_number = 0;
            }
            else
            {
                c = 0;
            }
        }
    }
    Serial.println("please input number of digits");
    delay(1000);

    while (x != 1)
    {
        if (Serial.available() > 0)
        {
            array_size_key = Serial.read();
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
            if (array_size > 6)
            {
                Serial.println("Max is 6 please");
                delay(500);
                Serial.println("please reinput");
                delay(500);
                x = 0;
                array_size = 0;
            }
            if (array_size_key == '*')
            {
                Serial.println("cleared");
                delay(1000);
                x = 0;
                array_size = 0;
            }
        }
    }
    int cycles_array[array_size]; // an array to store the number of cycles in it
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
                delay(1000);
                cycles_iterator = 0;
                cycle_counter = 0;
            }
        }
    }
    Serial.println("please input distance in mm");
    delay(1000);
    while (distance_counter != 3)
    {
        char cy;
        if (Serial.available() > 0)
        {
            cy = Serial.read();
        }
        if (cy)
        {

            if ((isDigit(cy)))
            {
                String cyc = String(cy);
                distance_array[distance_iterator] = cyc.toInt();
                Serial.println(distance_array[distance_iterator]);
                ++distance_iterator;
                ++distance_counter;
            }
            if (cy == '*')
            {
                distance_array[0] = 0;
                distance_array[1] = 0;
                distance_array[2] = 0;
                Serial.println("cleared");
                delay(1000);
                distance_counter = 0;
                distance_iterator = 0;
            }
        }
    }
    while (p < 1)
    {
        if (p < 1)
        {
            ++p;
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
            
            distance_third_val = distance_array[0];
            distance_second_val = distance_array[1];
            distance_first_val = distance_array[2];

            distance_second_val = distance_second_val * 10;
            distance_third_val = distance_third_val * 100;

            distance = distance_first_val + distance_second_val + distance_third_val;
            ratio = distance / 94.82;
            cycles = cycles_first_val + cycles_second_val + cycles_third_val + cycles_fourth_val + cycles_fifth_val + cycles_sixth_val + cycles_seventh_val;
            if (distance > 249)
            {
                Serial.println("Max is 249 mm, please reinput");
                delay(1000);
                distance_counter = 0;
                while (distance_counter != 3)
                {
                    distance_array[0] = 0;
                    distance_array[1] = 0;
                    distance_array[2] = 0;
                    char cy;
                    if (Serial.available() > 0)
                    {
                        cy = Serial.read();
                    }

                    if (cy)
                    {

                        if ((isDigit(cy)))
                        {
                            String cyc = String(cy);
                            distance_array[distance_iterator] = cyc.toInt();
                            Serial.println(distance_array[distance_iterator]);

                            ++distance_iterator;
                            ++distance_counter;
                        }
                        if (cy == '*')
                        {
                            distance_array[0] = 0;
                            distance_array[1] = 0;
                            distance_array[2] = 0;
                            Serial.println("cleared");
                            delay(1000);
                            distance_counter = 0;
                            distance_iterator = 0;
                        }
                    }
                }
                distance_third_val = distance_array[0];
                distance_second_val = distance_array[1];
                distance_first_val = distance_array[2];
                if (distance_second_val != 0)
                {
                    distance_second_val = distance_second_val * 10;
                }

                distance_third_val = distance_third_val * 100;

                distance = distance_first_val + distance_second_val + distance_third_val; // had to manually assign the values and add them because arduino doesn't read it properly
                ratio = distance / 94.82; // 94.82 is the total distance of the actuator, and this ratio is being used to calculate time and distance per cycle
            }
        }
    }
    Serial.print("You entered: "); 
    Serial.print(cycles);
    Serial.println(" cycles");
    delay(500);
    Serial.print("Distance is: ");
    Serial.print(distance);
    Serial.println(" mm");
    delay(500);
    steps = steps * ratio;
    seconds = seconds * ratio;
    seconds_disp = seconds_disp * ratio;
    unsigned long time = cycles * seconds;
    float hours = time / 3600;
    float days = hours / 24;
    Serial.print("time period is: ");
    Serial.print(hours);
    Serial.println(" hours");
    delay(500);
    Serial.print("time period is: ");
    Serial.print(days);
    delay(4000);
    //Used the disp values for display
    cycles_disp = cycles; 
    time_disp = cycles * seconds_disp;
    hours_disp = time_disp / 3600;
    days_disp = hours_disp / 24;

    for (unsigned long i = 1; i <= cycles_disp; ++i)
    {
        Serial.print("cycles remaining: ");
        Serial.println(cycles);
        Serial.print(days_disp);
        Serial.println(" days remaining");
        if (days_disp <= 0)
        {
            Serial.print("cycles remaining:");
            Serial.println(cycles);
            Serial.println("Will finish soon");
        }

        digitalWrite(relayPin, HIGH); // Turn the relay ON for 0.5 second
        delay(500);
        digitalWrite(relayPin, LOW); // Turn the relay Off for 1 second
        delay(1000);
        /*Switch one is if the item under test is touching the left side of the actuator
        * Switch two is if the item under test is touching the right side of the actuator
        */
        limitSwitch_1.loop();
        int state_1 = limitSwitch_1.getState();
        if (state_1 == LOW)
        {
            stepper.stop();
            stepper.moveTo(1000);  //  Move it 1000 steps to the right if it is touching the actuator
            stepper.runToPosition();
            stepper.setCurrentPosition(0);
        }
        limitSwitch_2.loop();
        int state_2 = limitSwitch_2.getState();
        if (state_2 == LOW) 
        {
            stepper.stop();
            stepper.moveTo(-1000); //  Move it 1000 steps to the left if it is touching the actuator
            stepper.runToPosition();
            stepper.setCurrentPosition(0);
        }
        stepper.moveTo(1000);
        // Run to target position with set speed and acceleration/deceleration:
        stepper.runToPosition();
        limitSwitch.loop();
        int hall_Sensor_pin = limitSwitch.getState(); // used this pin for failures

        if (hall_Sensor_pin == LOW)
        {
            ++number_of_failures;
        }
        if (number_of_failures == failures_number)
        {
            Serial.println("failed");
            exit(0);
        }
        // Set the target position:
        stepper.moveTo(steps - 1000);
        // Run to target position with set speed and acceleration/deceleration:
        stepper.runToPosition();
        delay(1000);
        stepper.setCurrentPosition(0);

        digitalWrite(relayPin, HIGH); // Turn the relay ON for 0.5 second
        delay(500);
        digitalWrite(relayPin, LOW); // Turn the relay Off for 1 second
        delay(1000);
        // recheck after the end of the cycle
        limitSwitch_1.loop();
        state_1 = limitSwitch_1.getState();
        if (state_1 == LOW)
        {
            stepper.stop();
            stepper.moveTo(1000);
            stepper.runToPosition();
            stepper.setCurrentPosition(0);
        }
        limitSwitch_2.loop();
        state_2 = limitSwitch_2.getState();
        if (state_2 == LOW)
        {
            stepper.stop();
            stepper.moveTo(-1000);
            stepper.runToPosition();
            stepper.setCurrentPosition(0);
        }
        stepper.moveTo(-1000);

        stepper.runToPosition();
        stepper.setCurrentPosition(0);

        stepper.moveTo(-steps + 1000);

        stepper.runToPosition();
        stepper.setCurrentPosition(0);

        cycles = cycles - 1;
        hours_disp = hours_disp - (0.00027778 * 10);
        days_disp = days_disp - (0.00001157 * 10);

        if (days_disp == 0)
        {
            Serial.print("current cycle: ");
            Serial.println(cycles);
            Serial.println("Will finish soon");
        }
    }

    if (cycles == 0)
    {
        Serial.println("done");
    }
}