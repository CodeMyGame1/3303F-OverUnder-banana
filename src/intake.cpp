#include <main.h>

pros::Motor intake_(4);

void intake() {
    if (master.get_digital(DIGITAL_R1)) {
        intake_.move(127);
    } else if (master.get_digital(DIGITAL_L1)) {
        intake_.move(-127);
    }
}