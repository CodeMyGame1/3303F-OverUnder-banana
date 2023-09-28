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
 * 
 * TODO: consider using "!pros::Motor::get_port()" to define the ports for the pros::Motor_Group "cata"
*/

// used to transfer the catapult's motors to the chassis, and vice versa
pros::Motor cataLeft1 (4);
pros::Motor cataLeft2 (-5);
pros::Motor cataRight1 (7);
pros::Motor cataRight2 (-8);

pros::Motor_Group cata ({
    -4, 5, -7, 8
});

// pros::Motor_Group cata ({
//     ,
//     cataLeft2.get_port(),
//     cataRight1.get_port(),
//     cataRight2.get_port()
// });
// std:: << (signed char)cataLeft1.get_port();

bool cataReset = false;
bool cata_state = false;


/** LEGACY:
 * 
 * A negative value means that the catapult is being pulled back.
 * A positive value means that the catapult is throwing (literally, and maybe figuratively).
 */
// pulling back negative; throwing forward positive
pros::Rotation rotSensor(1);

/** LEGACY:
 * 
 * A value of 0 means that the catapult is enabled.
 * A value of 1 means that the drivetrain is enabled.
 */
pros::ADIDigitalOut cata_piston ('E');
/** TODO:
 * 
 * Should the piston start in the off position or the on position?
*/
bool piston_state = false;


void catapult() {
    // old code courtesy of pranesh :P
    
    // treats "cata" as the catapult motor group when the piston is not extended (catapult is enabled)
    if (!piston_state) {
        // resets rotation sensor at the beginning (we assume catapult is in the fired position at the time of program start)
        if (!cataReset) {
            rotSensor.reset();
            cata_piston.set_value(piston_state);
            cataReset = true;
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
    /**
     * TODO: not working; should comment out?
    */
    if (master.get_digital_new_press(DIGITAL_X) && master.get_digital_new_press(DIGITAL_UP)) {
        piston_state = !piston_state;
        cata_piston.set_value(!piston_state);

        chassis.left_motors.push_back(cataLeft1);
        chassis.left_motors.push_back(cataLeft2);
        chassis.right_motors.push_back(cataRight1);
        chassis.right_motors.push_back(cataRight2);
    }
}