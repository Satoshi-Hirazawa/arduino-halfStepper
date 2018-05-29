
/*
* halfStepper.cpp
* stteper-motor half-stepp library for Arduino.
* control the stteper-motor in the half-step.
* Created by Satoshi_Hirazawa on 2016/03/03.
*
*/

#include "Arduino.h"
#include "halfStepper.h"

#ifdef ESP8266
#include "espHeader.h"
#define REFRESH_INTERVAL 10000
espHeader esp;
#endif

// motor pin numbers:
int f_motor_pin_1;
int f_motor_pin_2;
int f_motor_pin_3;
int f_motor_pin_4;


#ifdef ESP8266
uint32_t inline usToTicks(uint32_t us){
  return clockCyclesPerMicrosecond() / 16 * us;
}

void handler (void){

    noInterrupts();
    if(esp.steps_left != 0) {

        // increment or decrement the step number, depending on direction:
        if (esp.direction == true) {
            esp.step_number++;
        }
        else if(esp.direction == false){
            esp.step_number--;
        }
        // decrement the steps left:
        esp.steps_left--;
        // step the motor to step number 0 ~ 7:
        _stepMotor(esp.step_number % 8);

        timer1_write(usToTicks(esp.step_delay));
        interrupts();
    }
    else {
        noInterrupts();
        esp.now_steps = esp.step_number % 8;
    }
}
#endif
/* ESP8266 end */

halfStepper::halfStepper(int _stepsNum, int _pin_1, int _pin_2, int _pin_3, int _pin_4) {


#ifdef ESP8266
    esp.step_number = 0;      // which step the motor is on
    esp.direction = 0;        // motor this->direction
    esp.now_steps = 0;

    // timer1 init.
    noInterrupts();
    timer1_isr_init();
    timer1_attachInterrupt(handler);
    timer1_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE);
    timer1_write(usToTicks(REFRESH_INTERVAL));

#else
    this->step_number = 0;      // which step the motor is on
    this->direction = 0;        // motor this->direction
    this->now_steps = 0;

#endif

    // Arduino pins for the motor control connection:
    f_motor_pin_1 = _pin_1;   // A phase
    f_motor_pin_2 = _pin_2;   // B phase
    f_motor_pin_3 = _pin_3;   // A_ phase
    f_motor_pin_4 = _pin_4;   // B_ phase

    // setup the pins on the microcontroller:
    pinMode(f_motor_pin_1, OUTPUT);
    pinMode(f_motor_pin_2, OUTPUT);
    pinMode(f_motor_pin_3, OUTPUT);
    pinMode(f_motor_pin_4, OUTPUT);
}

void halfStepper::step(int _step, unsigned int _time){

#ifdef ESP8266
    esp.steps_left = abs(_step);  // how many steps to take
    esp.step_delay = uint32_t((_time / esp.steps_left) * 1000);
    esp.step_number = esp.now_steps;

    if (_step > 0) {
        esp.direction = true;
    }
    if (_step < 0) {
        esp.direction = false;
    }

    timer1_write(usToTicks(esp.step_delay));
    interrupts();
#else
    this->steps_left = abs(_step);  // how many steps to take
    this->step_delay = uint32_t((_time / this->steps_left) * 1000);
    this->step_number = this->now_steps;

    if (_step > 0) {
        this->direction = true;
    }
    if (_step < 0) {
        this->direction = false;
    }

    // decrement the number of steps, moving one step each time:
    while(this->steps_left != 0) {
        unsigned long now = micros();

        if(now - this->last_step_time >= this->step_delay){
            this->last_step_time = now;

            // increment or decrement the step number, depending on this->direction:
            if (this->direction == true) {
                this->step_number++;
            }
            else if(this->direction == false){
                this->step_number--;
            }
            // decrement the steps left:
            this->steps_left--;
            // step the motor to step number 0 ~ 7:
            _stepMotor(this->step_number % 8);
        }
    }
    this->now_steps = this->step_number % 8;
#endif
}


void _pinForOut(bool _lvA, bool _lvB, bool _lvA_, bool _lvB_) {

    digitalWrite(f_motor_pin_1, _lvA);
    digitalWrite(f_motor_pin_2, _lvB);
    digitalWrite(f_motor_pin_3, _lvA_);
    digitalWrite(f_motor_pin_4, _lvB_);

}

void _stepMotor(int _thisStep) {

    switch (_thisStep) {

        case -7: _pinForOut(HIGH, HIGH, LOW,  LOW); break;    // 1100
        case -6: _pinForOut(LOW,  HIGH, LOW,  LOW); break;    // 0100
        case -5: _pinForOut(LOW,  HIGH, HIGH, LOW); break;    // 0110
        case -4: _pinForOut(LOW,  LOW,  HIGH, LOW);  break;   // 0010
        case -3: _pinForOut(LOW,  LOW,  HIGH, HIGH); break;   // 0011
        case -2: _pinForOut(LOW,  LOW,  LOW,  HIGH); break;   // 0001
        case -1: _pinForOut(HIGH, LOW,  LOW,  HIGH); break;   // 1001

        case  0: _pinForOut(HIGH, LOW,  LOW,  LOW); break;    // 1000

        case  1: _pinForOut(HIGH, HIGH, LOW,  LOW); break;    // 1100
        case  2: _pinForOut(LOW,  HIGH, LOW,  LOW); break;    // 0100
        case  3: _pinForOut(LOW,  HIGH, HIGH, LOW); break;    // 0110
        case  4: _pinForOut(LOW,  LOW,  HIGH, LOW);  break;   // 0010
        case  5: _pinForOut(LOW,  LOW,  HIGH, HIGH); break;   // 0011
        case  6: _pinForOut(LOW,  LOW,  LOW,  HIGH); break;   // 0001
        case  7: _pinForOut(HIGH, LOW,  LOW,  HIGH); break;   // 1001
    }
}