
#include <halfStepper.h>

// one revolution steps.
#define STEPS_PER_REV 40

// set pins A, B, A_, B_.
halfStepper stepper(STEPS_PER_REV, 8, 9, 11, 10);
halfStepper stepper(STEPS_PER_REV, 12, 4, 13, 14);    // use esp

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(1000);

  stepper.step(STEPS_PER_REV, 1000);  // motor init
  delay(500);
  Serial.println("Please send degrees.");
}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available()){
    int deg = Serial.parseInt();

    if(deg != 0){
      Serial.println(deg);
      int steps = deg / 9;
      stepper.step(steps, 500);  // set steps & time.
    }
  }
}





