
# Arduino Half Stepper Library

This library allows you to control unipolar or bipolar stepper motors the half steps.   
To use it you will need a stepper motor, and the appropriate hardware to control it. 


### Functions

- Set the control pin and 360 degree step number

`Stepper(int stepsNum, int pin1, int pin2, int pin3, int pin4)`


- Set time and step for rotate.

`step(int steps, int time)`
