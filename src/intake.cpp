#include "main.h"

/**
 * TODO: extend piston at beginning!
*/

/**
 * TODO: add ports to code!
*/
pros::Motor intake_(5);
pros::ADIDigitalIn intake_button('B');
bool intakeReset = false;
bool intakeRunning = false;

void intake() {
    // // set intake motor's brake mode in the beginning
    // if (!intakeReset) {
    //     intake_.set_brake_mode(MOTOR_BRAKE_HOLD);
    //     intakeReset = true;
    // }

    // // 1 means button not being pressed, 0 means button AHHHHHHHHH
    // // do not attempt to crush le button if crushing is already taking place
    // if (master.get_digital(DIGITAL_R1) && !intake_button.get_value()) {
    //     intakeRunning = true;
    //     intake_.move(87);
    // } else if (!master.get_digital(DIGITAL_R1) && intakeRunning) {
    //     intakeRunning = false;
    //     intake_.brake();
    // } else if (master.get_digital(DIGITAL_R2)) {
    //     intakeRunning = true;

    //     /**
    //      * TODO: outtake is not running powerfully
    //     */
    //     intake_.move(-127);
    // } else if (!master.get_digital(DIGITAL_R2) && intakeRunning) {
    //     intakeRunning = false;
    //     intake_.brake();
    // }

    if (master.get_digital(DIGITAL_R1) && !intake_button.get_value()) {
        intake_.move(127);
    } else if (master.get_digital(DIGITAL_R2)) {
        intake_.move(-127);
    } else { intake_.brake(); }

    pros::lcd::set_text(0, std::to_string((bool)intake_button.get_value()));
}