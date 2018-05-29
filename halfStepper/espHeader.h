
/*
* stepperTimer.h
* stteper-motor half-stepp library for Arduino.
* control the stteper-motor in the half-step.
* Created by Satoshi_Hirazawa on 2016/03/03.
*
*/

#ifndef espHeader_h
#define espHeader_h

/* --------------------------------
 * Constant
 * -------------------------------- */


/* --------------------------------
 * Class Declaration
 * -------------------------------- */
class espHeader {
public:

    bool direction;        // Direction of rotation
    int steps_left;

    int step_number;        // which step the motor is on
    int now_steps;
    int step_delay;
    unsigned long last_step_time;

private:

};

#endif


