#include "main.h"

pros::ADIDigitalOut wing_left('A');
pros::ADIDigitalOut wing_right('C');
bool wings_enabled = false;
bool wings_reset = false;

void wings() {
    // closes wings when the robot starts up
    if (!wings_reset) {
      wing_left.set_value(0);
      wing_right.set_value(0);

      wings_reset = true;
    }

    // toggles wing states
    if (master.get_digital_new_press(DIGITAL_L2)) {
      wings_enabled = !wings_enabled;

      wing_left.set_value(wings_enabled);
      wing_right.set_value(wings_enabled);
    }
}