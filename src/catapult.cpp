#include "main.h"

// piston on: wheels
// piston off: catapult

pros::Motor_Group cata ({1, 2, -9, -10});

pros::ADIDigitalOut cata_piston (0);

bool piston_state = false;
bool state_changing = false;

void catapult() {
    // piston
    if (master.get_digital(DIGITAL_L2) && !state_changing) {
        cata_piston.set_value(!piston_state);
        state_changing = true;

        pros::delay(1000);

        state_changing = false;
    // catapult
    } else if (master.get_digital(DIGITAL_R2)) {
        cata.move(127);
    }
}