#include <Wire.h>
#include <Keypad.h>
#include <ezButton.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
ezButton limitSwitch(28);   
ezButton limitSwitch_1(30); 
ezButton limitSwitch_2(31); 
#define enablepin 34
#define dirPin 35
#define stepPin 36
#define motorInterfaceType 1
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
int relayPin = 27;
char choice;
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
void Move_with_hall_sensor_and_relay();
void Move_with_no_relay();
void position_adjust();
void Move_with_relay();
void setup()
{
    Serial.begin(9600);
    digitalWrite(dirPin, LOW);
    pinMode(relayPin, OUTPUT);
    limitSwitch.setDebounceTime(50);   // set debounce time to 50 milliseconds
    limitSwitch_1.setDebounceTime(50); // set debounce time to 50 milliseconds
    limitSwitch_2.setDebounceTime(50); // set debounce time to 50 milliseconds
    Serial.println("Choose your system");
    delay(1000);
    stepper.setMaxSpeed(3000000);     // maximum speed that the motor will reach at the end of the cycle
    stepper.setAcceleration(1000000); // stepper motor acceleration
    stepper.setSpeed(2000000);        // regular speed
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
                Serial.println(choice);
                if (choice == 'A' || choice == 'a' || choice == 'B' || choice == 'b' || choice == 'C' || choice == 'c' || choice == 'D' || choice == 'd')
                {
                    ++count;
                }
                else if (choice == '*')
                {
                    Serial.println("cleared");
                    delay(1000);
                    count = 0;
                }
                else
                {
                    count = 0;
                }
                if (choice == '*')
                {
                    Serial.println("cleared");
                    delay(1000);
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
            choice = 'z';
        }
    }
    exit(0);
}
