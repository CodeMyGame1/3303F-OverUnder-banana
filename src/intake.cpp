#include "main.h"

pros::Motor intake_(6);

pros::ADIDigitalOut intake_piston('C');
bool intake_piston_enabled = false;
bool intake_reset = false;

void intake() {
    // at the beginning of the program...
    if (!intake_reset) {
        // set intake motor's brake mode in the beginning
        intake_.set_brake_mode(MOTOR_BRAKE_HOLD);
        // push the intake out, if it's not already in that position
        // temporarily disabled
        // intake_piston.set_value(1);
        
        intake_reset = true;
    }

    /**
     * 1 means button not being pressed (triball not in possession), 0 means button is being pressed
     */    
    // intake
    if (master.get_digital(DIGITAL_R1)) {
        intake_.move(-127);
    // outtake
    } else if (master.get_digital(DIGITAL_R2)) {
        intake_.move(127);
    } else { intake_.brake(); }
 
    // pros::lcd::set_text(0, std::to_string((bool)intake_button.get_value()));
}