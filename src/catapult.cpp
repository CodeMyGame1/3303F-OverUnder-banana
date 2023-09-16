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
 * 
 * TODO: consider using "!pros::Motor::get_port()" to define the ports for the pros::Motor_Group "cata"
*/

pros::Motor cataLeft1 (-4);
pros::Motor cataLeft2 (5);
pros::Motor cataRight1 (-7);
pros::Motor cataRight2 (8);
pros::Motor_Group cata ({4, -5, 7, -8});

// pulling back negative; throwing forward positive
pros::Rotation rotSensor(1);

pros::ADIDigitalOut cata_piston ('E');

bool rotSensorReset = false;
/**
 * false (off): catapult powered
 * true (on): wheels powered
*/
bool piston_state = false;
bool cata_state = false;

void catapult() {
    // old code courtesy of pranesh :P

    // // REEEEEEEEEEEEEESET
    // if (!rotSensorReset) {
    //     rotSensor.reset();
    //     rotSensorReset = true;
    //     cata.set_brake_modes(MOTOR_BRAKE_HOLD);

        

    //     /*if ((abs(rotSensor.get_angle()/100-290) > 7) || fire) {
    //         CATAPULT.move(65);
    //         loaded = false;

    //         if ((abs(rotSensor.get_angle()/100-360) < 5) || abs(rotSensor.get_angle()/100) < 5) {
    //             fire = false;
    //         }
    //     } else {
    //         CATAPULT.brake();
    //         loaded = true;
    //     }*/
    // }

    // // catapult's piston logic
    // if (master.get_digital_new_press(DIGITAL_L2)) {
    //     piston_state = !piston_state;
    //     cata_piston.set_value(piston_state);
    // } 
    
    // // catapult's logic
    // if (master.get_digital_new_press(DIGITAL_R2) && !piston_state) {
    //     // marks catapult as enabled, if not already
    //     if (!cata_state) cata_state = true;

    //     cata.move(127);
    // } else {        
    //     // if the controller R2 key just got released...
    //     if (cata_state) {
    //         cata_state = !cata_state;

    //         // start returning it to its original state

    //     }

    //     /**
    //      * TODO: think of adding a guard clause to see if the catapult is already braking 
    //      * (might lead to bugs, so implement ltr, when you have lots of time to test)
    //     */
    //     cata.brake();
    // }

    // treats "cata" as the catapult motor group when the piston is not extended (catapult is enabled)
    if (!piston_state) {
        // resets rotation sensor at the beginning (we assume catapult is in the fired position at the time of program start)
        if (!rotSensorReset) {
            rotSensor.reset();
            rotSensorReset = true;
            cata.set_brake_modes(MOTOR_BRAKE_HOLD);
        }

        if (abs(rotSensor.get_angle()/100-75) > 5 || cata_state) {
            cata.move_voltage(12000);
        } else { cata.brake(); }

        if (master.get_digital_new_press(DIGITAL_A)) {
            cata_state = !cata_state;
        }
    }

    // handles switching between catapult and drivetrain powering
    if (master.get_digital_new_press(DIGITAL_X) && master.get_digital_new_press(DIGITAL_UP)) {
        piston_state = true;
        cata_piston.set_value(piston_state);

        chassis.left_motors.push_back(cataLeft1);
        chassis.left_motors.push_back(cataLeft2);
        chassis.right_motors.push_back(cataRight1);
        chassis.right_motors.push_back(cataRight2);
    }
}