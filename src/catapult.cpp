#include "main.h"

/**
 * TODO: <in general> consider fetching all controller states from opcontrol() in main.cpp instead of fetching individually
*/

/**
 * piston on: wheels
 * piston off: catapult
*/

/**
 * TODO: add ports to code!
 *       (cata_piston) probably change to ADIAnalogOut bc it's a multi-state piston
*/

pros::Motor_Group cata ({3, -4, -7, 8});

// pulling back negative; throwing forward positive
pros::Rotation rotSensor(6);

pros::ADIDigitalOut cata_piston ('E');

bool rotSensorReset = false;
// if the piston is off, then the catapult is being powered; if the piston is on, then the wheels are being powered
bool piston_state = false;
bool cata_state = false;

void catapult() {
    // REEEEEEEEEEEEEESET
    if (!rotSensorReset) {
        rotSensor.reset();
        rotSensorReset = true;
        cata.set_brake_modes(MOTOR_BRAKE_HOLD);

        

        /*if ((abs(rotSensor.get_angle()/100-290) > 7) || fire) {
            CATAPULT.move(65);
            loaded = false;

            if ((abs(rotSensor.get_angle()/100-360) < 5) || abs(rotSensor.get_angle()/100) < 5) {
                fire = false;
            }
        } else {
            CATAPULT.brake();
            loaded = true;
        }*/
    }

    // catapult's piston logic
    if (master.get_digital_new_press(DIGITAL_L2)) {
        piston_state = !piston_state;
        cata_piston.set_value(piston_state);
    } 
    
    // catapult's logic
    if (master.get_digital_new_press(DIGITAL_R2) && !piston_state) {
        // marks catapult as enabled, if not already
        if (!cata_state) cata_state = true;

        cata.move(127);
    } else {        
        // if the controller R2 key just got released...
        if (cata_state) {
            cata_state = !cata_state;

            // start returning it to its original state

        }

        /**
         * TODO: think of adding a guard clause to see if the catapult is already braking 
         * (might lead to bugs, so implement ltr, when you have lots of time to test)
        */
        cata.brake();
    }
}