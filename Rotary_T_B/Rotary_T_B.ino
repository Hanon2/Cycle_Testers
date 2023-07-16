#include <ezButton.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#define enablepin 13
#define dirPin 2
#define stepPin 3
#define motorInterfaceType 1
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
int state_1;
int relayPin = 12;
int solenoid_pin = 22;
int limitSwitch_2 = 28;
char array_size_key;      //input for number of digits (in type char)
int array_size;           // array_size_key converted to type int
int cycle_counter = 0;    //counter for while loop for cycles input
int cycles_iterator = 0;  //iterator to iterate by 1 to store the values in the array
int angles_array[3];
int angles_counter = 0;              //counter for while loop for angle input
int angles_iterator = 0;             //iterator to iterate by 1 to store the values in the array
unsigned long angle_first_val = 0;   //store 1st value of the angle array
unsigned long angle_second_val = 0;  //store 2nd value of the angle array
unsigned long angle_third_val = 0;   //store 3rd value of the angle array
unsigned long cycles;                //add the values of the cycles array and store them in this int in type unsigned long
float angle;                         //add the values of the angle array and store them in this decimal variable in type float
int p = 0;
int x = 0;
int c = 0;
unsigned long steps = 14700;
float seconds = 12.549 + 1.5;
float seconds_disp = 12.549 + 1.5;
float ratio = 0.00;
unsigned long cycles_disp;
unsigned long time_disp;
float hours_disp;
float days_disp;
unsigned long cycles_first_val = 0;
unsigned long cycles_second_val = 0;
unsigned long cycles_third_val = 0;
unsigned long cycles_fourth_val = 0;
unsigned long cycles_fifth_val = 0;
unsigned long cycles_sixth_val = 0;
unsigned long cycles_seventh_val = 0;
int failures_number;
int hall_Sensor_pin = 22;
int number_of_failures;
int digits_num[2];
int counter;
void Rotate_only();
void Rotate_with_relay();
void Rotate_with_hall_sensor_and_relay();
void position_adjust();
void setup() 
{
  pinMode(hall_Sensor_pin, INPUT);  //Pin 2 is connected to the output of proximity sensor
  digitalWrite(dirPin, HIGH);
  pinMode(relayPin, OUTPUT);
  pinMode(solenoid_pin, OUTPUT);
  digitalWrite(solenoid_pin, HIGH);
  digitalWrite(solenoid_pin, LOW);
  pinMode(limitSwitch_2, INPUT);
  Serial.begin(9600);
  Serial.println("welcome to InVue");
  delay(1000);
  Serial.println("Choose your system");
  delay(1000);
  stepper.setMaxSpeed(3000000);
  stepper.setAcceleration(1000000);
  stepper.setSpeed(2000000);

}

void loop() {

  int count = 0;
  while (count < 1) 
  {

    char choice; // choose the system
    while (count != 1) 
    {
      if (Serial.available() > 0) 
      {
        choice = Serial.read();
      }


      if (choice) 
      {

        if (choice == 'A' || choice == 'a' || choice == 'B' || choice == 'b' || choice == 'C' || choice == 'c' || choice == 'D' || choice == 'd') 
        {
          Serial.println(choice);
          ++count;
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
        }
      }
    }
    if (choice == 'A' || choice == 'a') 
    {
      Rotate_only();
    } 
    else if (choice == 'B' || choice == 'b') 
    {
      Rotate_with_relay();
    } 
    else if (choice == 'C' || choice == 'c') 
    {
      Rotate_with_hall_sensor_and_relay();
    } 
    else if (choice == 'D' || choice == 'd') 
    {
      position_adjust();
    }
  }
  exit(0);
}
