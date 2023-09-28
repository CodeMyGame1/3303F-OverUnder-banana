#include "main.h"

pros::ADIDigitalOut wing_left('A');
pros::ADIDigitalOut wing_right('C');
bool wings_enabled = false;

void wings() {
    // toggles wing states
    if (master.get_digital_new_press(DIGITAL_L2)) {
      wings_enabled = !wings_enabled;

      wing_left.set_value(wings_enabled);
      wing_right.set_value(wings_enabled);
    }
}