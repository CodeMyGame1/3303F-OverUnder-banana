#include "main.h"

/**
 * TODO: extend piston at beginning!
*/

pros::Motor intake_(20);
bool intakeReset = false;

void intake() {
    // set intake motor's brake mode in the beginning
    if (!intakeReset) {
        intake_.set_brake_mode(MOTOR_BRAKE_HOLD);
        intakeReset = true;
    }

    if (master.get_digital(DIGITAL_R1)) {
        intake_.move(127);
    } else if (master.get_digital(DIGITAL_L1)) {
        intake_.move(-127);
    }
}