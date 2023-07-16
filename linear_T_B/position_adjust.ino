void position_adjust()
{
    char pos_key; // 
    char pos_stopper = 'z';
    int pos_counter = 0;
    Serial.println("for left enter L");
    delay(500);
    Serial.println("for right enter R");
    delay(500);
    while (pos_counter != 1)
    {
        if (Serial.available() > 0)
        {
            pos_key = Serial.read();
        }
        if (pos_key == 'R' || pos_key == 'r')
        {
            ++pos_counter;
            Serial.println("Right");
            delay(1000);
        }
        else if (pos_key == 'L' || pos_key == 'l')
        {
            ++pos_counter;
            Serial.println("Left");
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
            stepper.moveTo(1000);
            stepper.runToPosition();
            stepper.setCurrentPosition(0);
            pos_stop_counter = 0;
            Serial.println("moving left");
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
            stepper.moveTo(-1000);
            stepper.runToPosition();
            stepper.setCurrentPosition(0);
            Serial.println("moving right");
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
    }
    exit(0);
}