#include "main.h"

pros::ADIDigitalOut wing('A');
bool wings_enabled = true;
bool wings_reset = false;

void wings() {
    // closes wings when the robot starts up
    if (!wings_reset) {
      wing.set_value(0);

      wings_reset = true;
    }

    // toggles wing states
    if (master.get_digital_new_press(DIGITAL_L2)) {
      wings_enabled = !wings_enabled;

      wing.set_value(wings_enabled);
    }
}