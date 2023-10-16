#include "main.h"
using namespace std;

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

pros::Motor& cataLeft1 = chassis.left_motors[2];
pros::Motor& cataLeft2 = chassis.left_motors[3];
pros::Motor& cataRight1 = chassis.right_motors[2];
pros::Motor& cataRight2 = chassis.right_motors[3];


// used to transfer the catapult's motors to the chassis, and vice versa
// pros::Motor cataLeft1 = chassis.left_motors[2];
// pros::Motor cataLeft2 = chassis.left_motors[3];
// pros::Motor cataRight1 = chassis.right_motors[2];
// pros::Motor cataRight2 = chassis.right_motors[3];

pros::Motor_Group cata ({
    // 5, -10
    // -5, 10
    // -5, -10
    // 9, -7 correct for right motors
    5, 10, 9, -7
});

// pros::Motor_Group cata ({
//     ,
//     cataLeft2.get_port(),
//     cataRight1.get_port(),
//     cataRight2.get_port()
// });
// std:: << (signed char)cataLeft1.get_port();

bool cata_reset = false;
bool cata_state = false;

// pulling back negative; throwing forward positive
pros::Rotation rotSensor(20);

// 0: catapult enabled; 1: catapult disabled
pros::ADIDigitalOut cata_piston ('B');
// the pistons start in the off position (catapult)
bool piston_state = false;

void catapult() {
    // only allows motor movement when the catapult is enabled (otherwise it risks moving the drivetrain when the catapult controls are used)
    
    if (!piston_state) {
        // runs initialization code
        if (!cata_reset) {
            // resets rotation sensor at the beginning (we assume catapult is in the fired position at the time of program start)
            rotSensor.reset();

            // sets catapult pistons to false (enables the catapult, by default, at the beginning of the program)
            cata_piston.set_value(0);

            // makes the catapult hold its current position if the motors stop turning
            // cata.set_brake_modes(MOTOR_BRAKE_HOLD);
            // chassis.pto_toggle({cataLeft1, cataLeft2}, true);
            // chassis.pto_toggle({cataRight1, cataRight2}, true);
            
            cata_reset = true;
        }

        if (abs(rotSensor.get_angle()/100-305) > 5 || cata_state) {
            cata.move(-127);
        } else { cata.brake(); }

        if (master.get_digital_new_press(DIGITAL_A)) {
            cata_state = !cata_state;
        }
        cout << abs(rotSensor.get_angle()/100-315) << endl;
    }
    
    // handles switching between catapult and drivetrain powering
    /**
     * TODO: not working; should comment out?
    */
    if (master.get_digital_new_press(DIGITAL_X)) {
        piston_state = !piston_state;
        cata_piston.set_value(piston_state);

        // // if piston state is false, catapult is enabled, which means pto should be enabled tooo....?????
        // chassis.pto_toggle({cataLeft1, cataLeft2}, !piston_state);
        // chassis.pto_toggle({cataRight1, cataRight2}, !piston_state);

        // !piston_state; if we're toggling FROM the catapult TO the drivetrain, add the "catapult" motors to the drivetrain
        // piston_state; if we're toggling FROM the drivetrain TO the catapult, remove the "catapult" motors from the drivetrain
    }
}