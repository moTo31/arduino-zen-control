#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12

int iCurrentStep = 1; //holds the current position of the stepper motor (1-4)

void setup() {
  Serial.begin(9600); //comment if you dont use a potentiometer
  // put your setup code here, to run once:
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
}

void loop() {

  //move the stepper motor to the new position
  moveStep(iCurrentStep);
  iCurrentStep = (iCurrentStep % 4) + 1; //increase the step, but ensure we dont exceed 4

  //note: if you dont use a potentiometer, comment out the following line and set a fixed delay (e.g. 50 ms)
  int iDelayVal = calculateDelay(analogRead(0)); //based on the potentiometer setting, we wait some time
  delay(iDelayVal);
  //delay(50); //uncomment if you dont use a potentiometer
}

/// @brief Based on the potentiometer value, calculates a delay in milliseconds
/// @param iPotentioVal Potentiometer analogue value (ranges from 0 to 1024)
/// @return delay value in milliseconds, minimum 2 milliseconds
int calculateDelay(int iPotentioVal)
{
  //the bigger the value, the faster, thus the lower the delay
  iPotentioVal = iPotentioVal % 1024; //defensive programming
  //realistic delay ranges from 2 to 100
  double fDelayVal = 0.05 * (double) iPotentioVal + 2;
  int iDelayVal = floor(fDelayVal);
  // Serial.println(iDelayVal);
  return iDelayVal;
}


/// @brief Moves the stepper motor to the target position
/// @param iStepNum the position the stepper motor should move to
void moveStep(int iStepNum)
{
  digitalWrite(STEPPER_PIN_1, iStepNum == 1);
  digitalWrite(STEPPER_PIN_2, iStepNum == 2);
  digitalWrite(STEPPER_PIN_3, iStepNum == 3);
  digitalWrite(STEPPER_PIN_4, iStepNum == 4);
}
