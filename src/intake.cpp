#include "main.h"

/**
 * TODO: extend piston at beginning!
*/

/**
 * TODO: add ports to code!
*/

pros::Motor intake_(6);
pros::ADIDigitalIn intake_button('B');

pros::ADIDigitalOut intake_piston('D');
bool intake_piston_enabled = false;
bool intake_reset = false;
// bool intakeRunning = false;

void intake() {
    // at the beginning of the program...
    if (!intake_reset) {
        // set intake motor's brake mode in the beginning
        intake_.set_brake_mode(MOTOR_BRAKE_HOLD);
        // push the intake down, if it's not already in that position
        intake_piston.set_value(1);
        
        intake_reset = true;
    }

    /**
     * 1 means button not being pressed (triball not in possession), 0 means button is being pressed
     */    
    // intake
    if (master.get_digital(DIGITAL_R1) && !intake_button.get_value()) {
        intake_.move(-127);
    // outtake
    } else if (master.get_digital(DIGITAL_R2)) {
        intake_.move(127);
    } else { intake_.brake(); }
 
    pros::lcd::set_text(0, std::to_string((bool)intake_button.get_value()));
}