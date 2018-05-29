
/*
* halfStepper.h
* stteper-motor half-stepp library for Arduino.
* control the stteper-motor in the half-step.
* Created by Satoshi_Hirazawa on 2016/03/03.
*
*/

#ifndef halfStepper_h
#define halfStepper_h

    void _pinForOut(bool _lvA, bool _lvB, bool _lvA_, bool _lvB_);
    void _stepMotor(int _thisStep);



/* --------------------------------
 * Constant
 * -------------------------------- */


/* --------------------------------
 * Class Declaration
 * -------------------------------- */
class halfStepper {
public:
    // init
    halfStepper(int _stepsNum, int _pin_1, int _pin_2, int _pin_3, int _pin_4);
    // mover method:
    void step(int _stepsToMove, unsigned int _time);
    // void _pinForOut(bool _lvA, bool _lvB, bool _lvA_, bool _lvB_);
    // void _stepMotor(int _thisStep);

private:


    bool direction;        // Direction of rotation
    int steps_left;

    int step_number;        // which step the motor is on
    int now_steps;
    uint32_t step_delay;
    unsigned long last_step_time;

};

#endif


