

#include <halfStepper.h>

// one revolution steps.
#define STEPS_PER_REV 40

// set pins A, B, A_, B_.
halfStepper stepper(STEPS_PER_REV, 8, 9, 11, 10);
halfStepper stepper(STEPS_PER_REV, 12, 4, 13, 14);    // use esp

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  // set steps & time.
  stepper.step(40, 1000);
  delay(500);

   stepper.step(-40, 1000);
  delay(500);
}


