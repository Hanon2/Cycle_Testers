#include <HX711_ADC.h>
#include <Wire.h>
#include <Keypad.h>
#include <ezButton.h>
HX711_ADC LoadCell(24, 25); // dt pin, sck pin
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#include <AccelStepper.h>
#include <MultiStepper.h>
ezButton limitSwitch(28);   // create ezButton object that attach to pin 7;
ezButton limitSwitch_1(30); // create ezButton object that attach to pin 7;
ezButton limitSwitch_2(31); // create ezButton object that attach to pin 7;
#define enablepin 34
#define dirPin 35
#define stepPin 36
#define motorInterfaceType 1
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
int relayPin = 27;
char choice;
byte rowPins[ROWS] = {11, 10, 9, 8}; // R1,R2,R3,R4
// connect to the column pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; // C1,C2,C3,C4
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
char array_size_key;     // input for number of digits (in type char)
int array_size;          // array_size_key converted to type int
int cycle_counter = 0;   // counter for while loop for cycles input
int cycles_iterator = 0; // iterator to iterate by 1 to store the values in the array
int distance_array[3];
int distance_counter = 0;  // counter for while loop for distance input
int distance_iterator = 0; // iterator to iterate by 1 to store the values in the array
int failures_array[2];
unsigned long distance_first_val = 0;  // store 1st value of the distance array
unsigned long distance_second_val = 0; // store 2nd value of the distance array
unsigned long distance_third_val = 0;  // store 3rd value of the distance array
unsigned long cycles;                  // add the values of the cycles array and store them in this int in type unsigned long
float distance;                        // add the values of the distance array and store them in this decimal variable in type float
int p = 0;
int x = 0;
int c = 0;
unsigned long steps = 30000;          // microsteps that the stepper motor will take to travel 94mm (used it for the ratio)
float seconds = 16.13;                // time the stepper motor will take to travel 94mm
float seconds_disp = 16.13;           // time the stepper motor will take to travel 94mm (displayed on the LCD)
float ratio = 0.00;                   // ratio between the steps and the 90 degrees (used it to calculate the time and distance) : 94/steps = distance/steps the steps that will be taken for the angles input by user
unsigned long cycles_disp;            // display of cycles
unsigned long time_disp;              // display of time
float hours_disp;                     // display of hours
float days_disp;                      // display of days
unsigned long cycles_first_val = 0;   // store first value of the cycles array
unsigned long cycles_second_val = 0;  // store first value of the cycles array
unsigned long cycles_third_val = 0;   // store first value of the cycles array
unsigned long cycles_fourth_val = 0;  // store first value of the cycles array
unsigned long cycles_fifth_val = 0;   // store first value of the cycles array
unsigned long cycles_sixth_val = 0;   // store first value of the cycles array
unsigned long cycles_seventh_val = 0; // store first value of the cycles array
int failures_number;                  // number of failures the user will input
int number_of_failures;               // store the number of failures
int digits_num[2];
int counter;
#include <Elegoo_GFX.h>
#include <Elegoo_TFTLCD.h>

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
void setup()
{
    Serial.begin(9600);
    LoadCell.begin();     // start connection to HX711
    LoadCell.start(1000); // load cells gets 1000ms of time to stabilize
    LoadCell.setCalFactor(375);
    digitalWrite(dirPin, LOW);
    pinMode(relayPin, OUTPUT);
    limitSwitch.setDebounceTime(50);   // set debounce time to 50 milliseconds
    limitSwitch_1.setDebounceTime(50); // set debounce time to 50 milliseconds
    limitSwitch_2.setDebounceTime(50); // set debounce time to 50 milliseconds
    tft.reset();
    tft.begin(0x9341);

    tft.fillScreen(BLACK);
    tft.setRotation(1);
    tft.setCursor(5, 5);

    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.println("welcome to");
    Serial.println("welcome to Invue");
    tft.setTextColor(YELLOW);
    tft.println("InVue");
    delay(2000);

    tft.reset();
    tft.begin(0x9341);

    tft.fillScreen(BLACK);
    tft.setRotation(1);
    tft.setCursor(5, 5);

    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    Serial.println("Choose your system");
    tft.println("Choose your");
    tft.println("System");
    delay(2000);
    lcd.clear();
    stepper.setMaxSpeed(3000000);     // maximum speed that the motor will reach at the end of the cycle
    stepper.setAcceleration(1000000); // stepper motor acceleration
    stepper.setSpeed(2000000);        // regular speed
}

void Move_with_no_relay()
{
    //          tft.reset();
    // tft.begin(0x9341);
    //
    // tft.fillScreen(BLACK);
    // tft.setRotation(1);
    // tft.setCursor(5, 5);
    //
    // tft.setTextColor(WHITE);
    // tft.setTextSize(2);
    Serial.println("please input number of digits");
    tft.println("please input ");
    tft.println("number of digits");
    delay(2000);
    while (x != 1)
    {
        if (Serial.available() > 0)
        {
            array_size_key = Serial.read();
        }

        //  array_size_key=keypad.getKey();
        if (array_size_key)
        {

            if (isDigit(array_size_key))
            {

                String num2 = String(array_size_key);
                array_size = num2.toInt();
                tft.println(array_size);
                Serial.println(array_size);
                ++x;
            }
            else if (array_size_key == '*')
            {
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
                Serial.println("cleared");
                tft.println("cleared");
                delay(2000);
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
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
                Serial.println("Max is 6");
                tft.println("Max is 6");
                Serial.println("please reinput");
                tft.println("please");
                tft.println("reinput");
                x = 0;
                array_size = 0;
                delay(2000);
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
            }
            if (array_size_key == '*')
            {
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
                Serial.println("cleared");
                tft.println("cleared");
                delay(2000);
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
                x = 0;

                array_size = 0;
            }
        }
    }
    int cycles_array[array_size];
    tft.reset();
    tft.begin(0x9341);

    tft.fillScreen(BLACK);
    tft.setRotation(1);
    tft.setCursor(5, 5);

    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    Serial.println("please input");
    tft.println("please input");
    Serial.println("number of cycles");
    tft.println("number of cycles");
    delay(2000);
    lcd.clear();
    while (cycle_counter != array_size)
    {
        char key;
        //      char key = keypad.getKey();
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
                tft.println(cycles_array[cycles_iterator]);

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
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
                Serial.println("cleared");
                tft.println("cleared");
                delay(2000);
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
                cycles_iterator = 0;
                cycle_counter = 0;
            }
        }
    }
    tft.reset();
    tft.begin(0x9341);

    tft.fillScreen(BLACK);
    tft.setRotation(1);
    tft.setCursor(5, 5);

    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    Serial.println("please input distance in mm");
    tft.println("please input");
    tft.println("distance in mm");
    delay(2000);
    while (distance_counter != 3)
    {
        char cy;
        if (Serial.available() > 0)
        {
            cy = Serial.read();
        }
        //      char cy = keypad.getKey();

        if (cy)
        {

            if ((isDigit(cy)))
            {
                String cyc = String(cy);
                distance_array[distance_iterator] = cyc.toInt();

                tft.println(distance_array[distance_iterator]);
                Serial.println(distance_array[distance_iterator]);

                ++distance_iterator;
                ++distance_counter;
            }
            if (cy == '*')
            {
                distance_array[0] = 0;
                distance_array[1] = 0;
                distance_array[2] = 0;
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
                Serial.println("cleared");
                tft.println("cleared");
                delay(2000);
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
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
            if (array_size == 1)
            {
                cycles_first_val = cycles_array[0];
            }
            else if (array_size == 2)
            {
                cycles_second_val = cycles_array[0];
                cycles_first_val = cycles_array[1];
                cycles_second_val = cycles_second_val * 10;
            }
            else if (array_size == 3)
            {
                cycles_third_val = cycles_array[0];
                cycles_second_val = cycles_array[1];
                cycles_first_val = cycles_array[2];
                if (cycles_second_val != 0)
                {
                    cycles_second_val = cycles_second_val * 10;
                }

                cycles_third_val = cycles_third_val * 100;
            }
            else if (array_size == 4)
            {
                cycles_fourth_val = cycles_array[0];
                cycles_third_val = cycles_array[1];
                cycles_second_val = cycles_array[2];
                cycles_first_val = cycles_array[3];
                if (cycles_second_val != 0)
                {
                    cycles_second_val = cycles_second_val * 10;
                }
                if (cycles_third_val != 0)
                {
                    cycles_third_val = cycles_third_val * 100;
                }

                cycles_fourth_val = cycles_fourth_val * 1000;
            }
            else if (array_size == 5)
            {
                cycles_fifth_val = cycles_array[0];
                cycles_fourth_val = cycles_array[1];
                cycles_third_val = cycles_array[2];
                cycles_second_val = cycles_array[3];
                cycles_first_val = cycles_array[4];
                if (cycles_second_val != 0)
                {
                    cycles_second_val = cycles_second_val * 10;
                }
                if (cycles_third_val != 0)
                {
                    cycles_third_val = cycles_third_val * 100;
                }
                if (cycles_fourth_val != 0)
                {
                    cycles_fourth_val = cycles_fourth_val * 1000;
                }

                cycles_fifth_val = cycles_fifth_val * 10000;
            }
            else
            {
                cycles_sixth_val = cycles_array[0];
                cycles_fifth_val = cycles_array[1];
                cycles_fourth_val = cycles_array[2];
                cycles_third_val = cycles_array[3];
                cycles_second_val = cycles_array[4];
                cycles_first_val = cycles_array[5];
                if (cycles_second_val != 0)
                {
                    cycles_second_val = cycles_second_val * 10;
                }
                if (cycles_third_val != 0)
                {
                    cycles_third_val = cycles_third_val * 100;
                }
                if (cycles_fourth_val != 0)
                {
                    cycles_fourth_val = cycles_fourth_val * 1000;
                }
                if (cycles_fifth_val != 0)
                {
                    cycles_fifth_val = cycles_fifth_val * 10000;
                }

                cycles_sixth_val = cycles_sixth_val * 100000;
            }

            distance_third_val = distance_array[0];
            distance_second_val = distance_array[1];
            distance_first_val = distance_array[2];
            if (distance_second_val != 0)
            {
                distance_second_val = distance_second_val * 10;
            }

            distance_third_val = distance_third_val * 100;

            distance = distance_first_val + distance_second_val + distance_third_val;
            ratio = distance / 94.82;
            cycles = cycles_first_val + cycles_second_val + cycles_third_val + cycles_fourth_val + cycles_fifth_val + cycles_sixth_val + cycles_seventh_val;
            if (distance > 249)
            {
                Serial.println("Max is 249 mm please reinput");
                tft.println("Max is 249 mm");
                tft.println("please reinput");
                delay(2000);
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
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
                            tft.println(distance_array[distance_iterator]);

                            ++distance_iterator;
                            ++distance_counter;
                        }
                        if (cy == '*')
                        {
                            distance_array[0] = 0;
                            distance_array[1] = 0;
                            distance_array[2] = 0;
                            tft.reset();
                            tft.begin(0x9341);

                            tft.fillScreen(BLACK);
                            tft.setRotation(1);
                            tft.setCursor(5, 5);

                            tft.setTextColor(WHITE);
                            tft.setTextSize(2);
                            Serial.println("cleared");
                            tft.println("cleared");
                            delay(2000);
                            tft.reset();
                            tft.begin(0x9341);

                            tft.fillScreen(BLACK);
                            tft.setRotation(1);
                            tft.setCursor(5, 5);

                            tft.setTextColor(WHITE);
                            tft.setTextSize(2);
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

                distance = distance_first_val + distance_second_val + distance_third_val;
                ratio = distance / 94.82;
            }
        }
    }
    tft.reset();
    tft.begin(0x9341);

    tft.fillScreen(BLACK);
    tft.setRotation(1);
    tft.setCursor(5, 5);

    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.println("you entered");
    tft.println(cycles);
    tft.println("cycles");
    tft.println("distance in mm");
    tft.println("is: ");
    tft.println(distance);
    steps = steps * ratio;
    seconds = seconds * ratio;
    seconds_disp = seconds_disp * ratio;
    unsigned long time = cycles * seconds;
    float hours = time / 3600;
    float days = hours / 24;
    tft.println("time period");
    tft.println(hours);
    tft.println(" hours");
    tft.println("time period");
    tft.println(days);
    tft.println(" days");
    delay(4000);
    cycles_disp = cycles;
    time_disp = cycles * seconds_disp;
    hours_disp = time_disp / 3600;
    days_disp = hours_disp / 24;
    for (unsigned long i = 1; i <= cycles_disp; ++i)
    {
        tft.reset();
        tft.begin(0x9341);

        tft.fillScreen(BLACK);
        tft.setRotation(1);
        tft.setCursor(5, 5);

        tft.setTextColor(WHITE);
        tft.setTextSize(2);
        tft.println("cycles remaining:");
        tft.println(cycles);
        tft.println(days_disp);
        tft.println("days");
        tft.println(" remaining");
        tft.println(hours_disp);
        tft.println("hours remaining");
        if (days_disp <= 0)
        {
            tft.reset();
            tft.begin(0x9341);

            tft.fillScreen(BLACK);
            tft.setRotation(1);
            tft.setCursor(5, 5);

            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.println("cycles remaining:");
            tft.println(cycles);
            tft.println("Will finish soon");
        }
        // tft.println(hours2);
        // tft.println("hours, ");

        // Set the target position:
        limitSwitch_1.loop();
        int state_1 = limitSwitch_1.getState();
        if (state_1 == LOW)
        {
            stepper.stop();
            stepper.moveTo(1000);
            stepper.runToPosition();
            stepper.setCurrentPosition(0);
        }
        limitSwitch_2.loop();
        int state_2 = limitSwitch_2.getState();
        if (state_2 == LOW)
        {
            stepper.stop();
            stepper.moveTo(-1000);
            stepper.runToPosition();
            stepper.setCurrentPosition(0);
        }

        // Set the target position:
        stepper.moveTo(steps);
        // Run to target position with set speed and acceleration/deceleration:
        stepper.runToPosition();
        stepper.setCurrentPosition(0);
        delay(1000);
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
        // Move back to zero:
        stepper.moveTo(-steps);

        stepper.runToPosition();
        stepper.setCurrentPosition(0);

        cycles = cycles - 1;
        hours_disp = hours_disp - (0.00027778 * 10);
        days_disp = days_disp - (0.00001157 * 10);
    }
    if (cycles == 0)
    {
        tft.reset();
        tft.begin(0x9341);

        tft.fillScreen(BLACK);
        tft.setRotation(1);
        tft.setCursor(5, 5);

        tft.setTextColor(WHITE);
        tft.setTextSize(2);
        tft.println("done");
    }
}

void Move_with_hall_sensor_and_relay()
{
    tft.reset();
    tft.begin(0x9341);

    tft.fillScreen(BLACK);
    tft.setRotation(1);
    tft.setCursor(5, 5);

    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.println("please input");
    tft.println("number of failures");
    Serial.println("Please input number of failures");
    delay(2000);

    while (c != 1)
    {
        char failures_key;
        if (Serial.available() > 0)
        {
            failures_key = Serial.read();
        }
        //  char failures_key = keypad.getKey();
        if (failures_key)
        {
            tft.println(failures_key);
            Serial.println(failures_key);
            if (isDigit(failures_key))
            {
                String num3 = String(failures_key);
                failures_number = num3.toInt();
                ++c;
            }
            else if (failures_key == '*')
            {
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
                tft.println("cleared");
                Serial.println("cleared");
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
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
    tft.reset();
    tft.begin(0x9341);

    tft.fillScreen(BLACK);
    tft.setRotation(1);
    tft.setCursor(5, 5);

    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.println("please input ");
    tft.println("number of digits");
    Serial.println("please input number of digits");
    delay(2000);

    while (x != 1)
    {
        if (Serial.available() > 0)
        {
            array_size_key = Serial.read();
        }

        //  array_size_key=keypad.getKey();
        if (array_size_key)
        {

            if (isDigit(array_size_key))
            {

                String num2 = String(array_size_key);
                array_size = num2.toInt();
                tft.println(array_size);
                Serial.println(array_size);
                ++x;
            }
            else if (array_size_key == '*')
            {
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
                tft.println("cleared");
                Serial.println("cleared");
                delay(2000);
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
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
                tft.println("Max is 6");
                Serial.println("Max is 6 please");
                Serial.println("please");
                Serial.println("reinput");
                tft.println("reinput");
                x = 0;
                array_size = 0;
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
            }
            if (array_size_key == '*')
            {
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
                tft.println("cleared");
                Serial.println("cleared");
                delay(2000);
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
                x = 0;

                array_size = 0;
            }
        }
    }
    int cycles_array[array_size];
    tft.reset();
    tft.begin(0x9341);

    tft.fillScreen(BLACK);
    tft.setRotation(1);
    tft.setCursor(5, 5);

    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.println("please input");
    tft.println("number of cycles");
    Serial.println("please input number of cycles");
    delay(2000);

    while (cycle_counter != array_size)
    {
        char key;
        //      char key = keypad.getKey();
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
                tft.println(cycles_array[cycles_iterator]);

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
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
                Serial.println("cleared");
                tft.println("cleared");
                delay(2000);
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
                cycles_iterator = 0;
                cycle_counter = 0;
            }
        }
    }
    //    tft.reset();
    // tft.begin(0x9341);
    //
    // tft.fillScreen(BLACK);
    // tft.setRotation(1);
    // tft.setCursor(5, 5);
    //
    // tft.setTextColor(WHITE);
    // tft.setTextSize(2);
    tft.println("please input");
    tft.println("distance in mm");
    Serial.println("please input distance in mm");
    delay(2000);
    while (distance_counter != 3)
    {
        char cy;
        if (Serial.available() > 0)
        {
            cy = Serial.read();
        }
        //      char cy = keypad.getKey();

        if (cy)
        {

            if ((isDigit(cy)))
            {
                String cyc = String(cy);
                distance_array[distance_iterator] = cyc.toInt();
                Serial.println(distance_array[distance_iterator]);
                tft.println(distance_array[distance_iterator]);

                ++distance_iterator;
                ++distance_counter;
            }
            if (cy == '*')
            {
                distance_array[0] = 0;
                distance_array[1] = 0;
                distance_array[2] = 0;
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
                Serial.println("cleared");
                tft.println("cleared");
                delay(2000);
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
                distance_counter = 0;
                distance_iterator = 0;
            }
        }
    }
    tft.reset();
    tft.begin(0x9341);

    tft.fillScreen(BLACK);
    tft.setRotation(1);
    tft.setCursor(5, 5);

    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    while (p < 1)
    {
        if (p < 1)
        {
            ++p;
            if (array_size == 1)
            {
                cycles_first_val = cycles_array[0];
            }
            else if (array_size == 2)
            {
                cycles_second_val = cycles_array[0];
                cycles_first_val = cycles_array[1];
                cycles_second_val = cycles_second_val * 10;
            }
            else if (array_size == 3)
            {
                cycles_third_val = cycles_array[0];
                cycles_second_val = cycles_array[1];
                cycles_first_val = cycles_array[2];
                if (cycles_second_val != 0)
                {
                    cycles_second_val = cycles_second_val * 10;
                }

                cycles_third_val = cycles_third_val * 100;
            }
            else if (array_size == 4)
            {
                cycles_fourth_val = cycles_array[0];
                cycles_third_val = cycles_array[1];
                cycles_second_val = cycles_array[2];
                cycles_first_val = cycles_array[3];
                if (cycles_second_val != 0)
                {
                    cycles_second_val = cycles_second_val * 10;
                }
                if (cycles_third_val != 0)
                {
                    cycles_third_val = cycles_third_val * 100;
                }

                cycles_fourth_val = cycles_fourth_val * 1000;
            }
            else if (array_size == 5)
            {
                cycles_fifth_val = cycles_array[0];
                cycles_fourth_val = cycles_array[1];
                cycles_third_val = cycles_array[2];
                cycles_second_val = cycles_array[3];
                cycles_first_val = cycles_array[4];
                if (cycles_second_val != 0)
                {
                    cycles_second_val = cycles_second_val * 10;
                }
                if (cycles_third_val != 0)
                {
                    cycles_third_val = cycles_third_val * 100;
                }
                if (cycles_fourth_val != 0)
                {
                    cycles_fourth_val = cycles_fourth_val * 1000;
                }

                cycles_fifth_val = cycles_fifth_val * 10000;
            }
            else
            {
                cycles_sixth_val = cycles_array[0];
                cycles_fifth_val = cycles_array[1];
                cycles_fourth_val = cycles_array[2];
                cycles_third_val = cycles_array[3];
                cycles_second_val = cycles_array[4];
                cycles_first_val = cycles_array[5];
                if (cycles_second_val != 0)
                {
                    cycles_second_val = cycles_second_val * 10;
                }
                if (cycles_third_val != 0)
                {
                    cycles_third_val = cycles_third_val * 100;
                }
                if (cycles_fourth_val != 0)
                {
                    cycles_fourth_val = cycles_fourth_val * 1000;
                }
                if (cycles_fifth_val != 0)
                {
                    cycles_fifth_val = cycles_fifth_val * 10000;
                }

                cycles_sixth_val = cycles_sixth_val * 100000;
            }

            distance_third_val = distance_array[0];
            distance_second_val = distance_array[1];
            distance_first_val = distance_array[2];
            if (distance_second_val != 0)
            {
                distance_second_val = distance_second_val * 10;
            }

            distance_third_val = distance_third_val * 100;

            distance = distance_first_val + distance_second_val + distance_third_val;
            ratio = distance / 94.82;
            cycles = cycles_first_val + cycles_second_val + cycles_third_val + cycles_fourth_val + cycles_fifth_val + cycles_sixth_val + cycles_seventh_val;
            if (distance > 249)
            {
                tft.println("Max is 249 mm");
                tft.println("please reinput");
                delay(2000);
                Serial.println("Max is 249 mm, please reinput");
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
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
                            tft.println(distance_array[distance_iterator]);

                            ++distance_iterator;
                            ++distance_counter;
                        }
                        if (cy == '*')
                        {
                            distance_array[0] = 0;
                            distance_array[1] = 0;
                            distance_array[2] = 0;
                            tft.reset();
                            tft.begin(0x9341);

                            tft.fillScreen(BLACK);
                            tft.setRotation(1);
                            tft.setCursor(5, 5);

                            tft.setTextColor(WHITE);
                            tft.setTextSize(2);
                            tft.println("cleared");
                            Serial.println("cleared");
                            delay(2000);
                            tft.reset();
                            tft.begin(0x9341);

                            tft.fillScreen(BLACK);
                            tft.setRotation(1);
                            tft.setCursor(5, 5);

                            tft.setTextColor(WHITE);
                            tft.setTextSize(2);
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

                distance = distance_first_val + distance_second_val + distance_third_val;
                ratio = distance / 94.82;
            }
        }
    }
    tft.reset();
    tft.begin(0x9341);

    tft.fillScreen(BLACK);
    tft.setRotation(1);
    tft.setCursor(5, 5);

    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.println("you entered");
    tft.println(cycles);
    tft.println("cycles");
    tft.println("distance in mm");
    tft.println("is: ");
    tft.println(distance);
    steps = steps * ratio;
    seconds = seconds * ratio;
    seconds_disp = seconds_disp * ratio;
    unsigned long time = cycles * seconds;
    float hours = time / 3600;
    float days = hours / 24;
    tft.println("time period");
    tft.println(hours);
    tft.println(" hours");
    tft.println("time period");
    tft.println(days);
    tft.println(" days");
    delay(4000);
    cycles_disp = cycles;
    time_disp = cycles * seconds_disp;
    hours_disp = time_disp / 3600;
    days_disp = hours_disp / 24;

    for (unsigned long i = 1; i <= cycles_disp; ++i)
    {
        tft.reset();
        tft.begin(0x9341);

        tft.fillScreen(BLACK);
        tft.setRotation(1);
        tft.setCursor(5, 5);

        tft.setTextColor(WHITE);
        tft.setTextSize(2);
        tft.println("cycles remaining:");
        tft.println(cycles);
        tft.println(days_disp);
        tft.println("days");
        tft.println(" remaining");
        tft.println(hours_disp);
        tft.println("hours remaining");
        if (days_disp <= 0)
        {
            tft.reset();
            tft.begin(0x9341);

            tft.fillScreen(BLACK);
            tft.setRotation(1);
            tft.setCursor(5, 5);

            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.println("cycles remaining:");
            tft.println(cycles);
            tft.println("Will finish soon");
        }
        // tft.println(hours2);
        // tft.println("hours, ");

        digitalWrite(relayPin, HIGH); // Turn the relay ON for 0.5 second
        delay(500);
        digitalWrite(relayPin, LOW); // Turn the relay Off for 1 second
        delay(1000);
        limitSwitch_1.loop();
        int state_1 = limitSwitch_1.getState();
        if (state_1 == LOW)
        {
            stepper.stop();
            stepper.moveTo(1000);
            stepper.runToPosition();
            stepper.setCurrentPosition(0);
        }
        limitSwitch_2.loop();
        int state_2 = limitSwitch_2.getState();
        if (state_2 == LOW)
        {
            stepper.stop();
            stepper.moveTo(-1000);
            stepper.runToPosition();
            stepper.setCurrentPosition(0);
        }

        //  int state_2 = limitSwitch_2.getState();
        //  if (state_2==LOW){
        //        stepper.stop();
        //    stepper.moveTo(1000);
        //        lcd.clear();
        //    delay(90000);
        //  }
        stepper.moveTo(1000);
        // Run to target position with set speed and acceleration/deceleration:
        stepper.runToPosition();
        limitSwitch.loop();
        int hall_Sensor_pin = limitSwitch.getState();

        if (hall_Sensor_pin == LOW)
        {
            ++number_of_failures;
        }
        if (number_of_failures == failures_number)
        {
            tft.reset();
            tft.begin(0x9341);

            tft.fillScreen(BLACK);
            tft.setRotation(1);
            tft.setCursor(5, 5);

            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.println("failed");
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

        //                    if (hall_Sensor_pin==LOW){
        //                tft.println("LOW");
        //                delay(2000);
        //                        }
        if (number_of_failures == failures_number)
        {
            tft.reset();
            tft.begin(0x9341);

            tft.fillScreen(BLACK);
            tft.setRotation(1);
            tft.setCursor(5, 5);

            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.println("failed");
            exit(0);
        }

        stepper.moveTo(-steps + 1000);

        stepper.runToPosition();
        stepper.setCurrentPosition(0);

        //  if (state_2==LOW){
        //        stepper.stop();
        //    stepper.moveTo(1000);
        //     lcd.clear();
        //     tft.println("H");
        //    delay(90000);
        //  }

        cycles = cycles - 1;
        hours_disp = hours_disp - (0.00027778 * 10);
        days_disp = days_disp - (0.00001157 * 10);

        if (days_disp == 0)
        {
            tft.reset();
            tft.begin(0x9341);

            tft.fillScreen(BLACK);
            tft.setRotation(1);
            tft.setCursor(5, 5);

            tft.setTextColor(WHITE);
            tft.setTextSize(2);
            tft.println("current cycle: ");
            tft.println(cycles);
            tft.println("Will finish soon");
        }
    }

    if (cycles == 0)
    {
        tft.reset();
        tft.begin(0x9341);

        tft.fillScreen(BLACK);
        tft.setRotation(1);
        tft.setCursor(5, 5);

        tft.setTextColor(WHITE);
        tft.setTextSize(2);
        tft.println("done");
    }
}
void position_adjust()
{
    char pos_key;
    char pos_stopper = 'z';
    int pos_counter = 0;
    tft.println("for left enter L");
    tft.println("for right enter R");
    delay(2000);
    lcd.clear();
    while (pos_counter != 1)
    {
        if (Serial.available() > 0)
        {
            pos_key = Serial.read();
        }
        if (pos_key == 'R' || pos_key == 'r')
        {
            ++pos_counter;
            tft.println("Right");
            delay(2000);
        }
        else if (pos_key == 'L' || pos_key == 'l')
        {
            ++pos_counter;
            tft.println("Left");
            delay(2000);
        }
        else
        {
            pos_counter = 0;
        }
    }
    tft.reset();
    tft.begin(0x9341);

    tft.fillScreen(BLACK);
    tft.setRotation(1);
    tft.setCursor(5, 5);

    tft.setTextColor(WHITE);
    tft.setTextSize(2);
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
            tft.println("moving left");
            if (Serial.available() > 0)
            {
                pos_stopper = Serial.read();
            }
            if (pos_stopper == 'S' || pos_stopper == 's')
            {
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
                tft.println("Stopped");
                pos_stop_counter = 1;
            }
        }
        else if (pos_key == 'R' || pos_key == 'r')
        {
            digitalWrite(dirPin, HIGH);
            stepper.moveTo(-1000);
            stepper.runToPosition();
            stepper.setCurrentPosition(0);
            tft.println("moving right");
            pos_stop_counter = 0;
            if (Serial.available() > 0)
            {
                pos_stopper = Serial.read();
            }
            if (pos_stopper == 'S' || pos_stopper == 's')
            {
                tft.reset();
                tft.begin(0x9341);

                tft.fillScreen(BLACK);
                tft.setRotation(1);
                tft.setCursor(5, 5);

                tft.setTextColor(WHITE);
                tft.setTextSize(2);
                tft.println("Stopped");
                pos_stop_counter = 1;
            }
        }
    }
    exit(0);
}
void loop()
{

    int count = 0;
    while (count < 1)
    {

        char choice_num;
        while (count != 1)
        {
            choice;
            if (Serial.available() > 0)
            {
                choice = Serial.read();
            }

            if (choice)
            {
                tft.println(choice);
                Serial.println(choice);
                if (choice == 'A' || choice == 'a')
                {

                    ++count;
                }
                else if (choice == 'B' || choice == 'b')
                {
                    ++count;
                }
                else if (choice == 'C' || choice == 'c')
                {
                    ++count;
                }
                else if (choice == 'D' || choice == 'd')
                {
                    ++count;
                }
                else if (choice == '*')
                {
                    tft.reset();
                    tft.begin(0x9341);

                    tft.fillScreen(BLACK);
                    tft.setRotation(1);
                    tft.setCursor(5, 5);

                    tft.setTextColor(WHITE);
                    tft.setTextSize(2);
                    tft.println("cleared");
                    Serial.println("cleared");
                    delay(2000);
                    tft.reset();
                    tft.begin(0x9341);

                    tft.fillScreen(BLACK);
                    tft.setRotation(1);
                    tft.setCursor(5, 5);

                    tft.setTextColor(WHITE);
                    tft.setTextSize(2);
                    count = 0;
                }
                else
                {
                    count = 0;
                }
                if (choice == '*')
                {
                    tft.reset();
                    tft.begin(0x9341);

                    tft.fillScreen(BLACK);
                    tft.setRotation(1);
                    tft.setCursor(5, 5);

                    tft.setTextColor(WHITE);
                    tft.setTextSize(2);
                    tft.println("cleared");
                    Serial.println("cleared");
                    delay(2000);
                    tft.reset();
                    tft.begin(0x9341);

                    tft.fillScreen(BLACK);
                    tft.setRotation(1);
                    tft.setCursor(5, 5);

                    tft.setTextColor(WHITE);
                    tft.setTextSize(2);
                    count = 0;

                    choice = 'z';
                }
            }
        }
        if (choice == 'A' || choice == 'a')
        {

            Move_with_no_relay();
        }
        else if (choice == 'B' || choice == 'b')
        {
            Move_with_relay();
        }
        else if (choice == 'C' || choice == 'c')
        {
            Move_with_hall_sensor_and_relay();
        }
        else if (choice == 'D' || choice == 'd')
        {
            position_adjust();
        }
        else
        {
            lcd.clear();
            choice = 'z';
        }
    }
    exit(0);
}
