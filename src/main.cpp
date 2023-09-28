#include "main.h"

/////
// For installation, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////

/**
 * GENERAL CHECKLIST:
 * - check that all ports are correct (including catapult ports added to chassis)
*/

/**
 * GENERAL TODO:
 * - if possible, get an IMU for the robot
 * - see if the catapult piston can change between the cata & drivetrain multiple times, instead of just one time (as is implemented now)
*/

/**
 * Miscellaneous Information:
 * 
 * Motor RPMs:
 * - Blue Motors: 600rpm
 * - Green Motors: 200rpm
 * - Red Motors: 100rpm
*/

/**
 * At A Glance:
 * 
 * Motors:
 * - 4 drivetrain (L: {TBD, TBD}; R: {TBD, TBD})
 *   - blue (600rpm)
 *   - 36:1 gear ratio
 *   - (11W * 4 motors = 44W)
 * - 2 pairs of big and small cata motors (L: {TBD, TBD}; R: {TBD, TBD})
 *   - big motors
 *     - <one of the colors of the rainbow> (200rpm)
 *     - 8:1 gear ratio
 *     - (11W * 2 motors = 22W)
 *   - small motors
 *     - <one of the colors of the rainbow> (200rpm)
 *     - 8:1 gear ratio
 *     - (5.5W * 2 motors = 11W)
 * - 1 intake motor (TBD)
 *   - green (200rpm)
 *   - 1:3 gear ratio 
 *   - (11W * 1 motor = 11W)
 * 
 * total: 88W (limit)
 * 
 * 
 * Cwontrils:
 * - L & R joystick (driving; don't need to deal with bc already handled by chassis.tank())
 * - R1 intake, R2 outtake
 * - (XAYB) X cata, (arrow keys) up arrow key switch cata/drivetrain & down arrow key push intake back; (L1/L2) L2 push flaps
 * 
 * analog:
 * - A: left wing PISTON
 * - B: intake bumper
 * - C: right wing PISTON
 * - D: intake PISTON
 * - E: catapult PISTON
*/

// [13,14] [15,17]

// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {
    // original drivetrain ports
    // -9, -10,
    -2, -3,

    // "catapult" ports (temporarily adding bc catapult not working)
    // 4, -5
    -7, 8
  }

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{
    // original drivetrain ports
    // 2, 3,
    9, 10,

    // "catapult" ports (temporarily adding bc catapult not working)
    // 7, -8
    -4, 5
  }

  /**
   * TODO: the robot quite verifiably does NOT have an IMU at this point in time
  */
  // IMU Port
  ,0

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1.667

  /**
   * TODO: (2) remove all tracking wheel comments */

  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);

/**
 * TODO: ensure that (pneumatics) wires are positioned correctly for the pistons, and that the code takes this into account
*/

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  /**
   * TODO: (2) Configure chassis controls
  */
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!
  exit_condition_defaults(); // Set the exit conditions to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  /* ez::as::auton_selector.add_autons({
    Auton("Example Drive\n\nDrive forward and come back.", drive_example),
    Auton("Example Turn\n\nTurn 3 times.", turn_example),
    Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
    Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
    Auton("Swing Example\n\nSwing, drive, swing.", swing_example),
    Auton("Combine all 3 movements", combining_movements),
    Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
  }); */

  // Initialize chassis and auton selector
  chassis.initialize();

  // LCD goofiness

  pros::lcd::initialize();
  
  // ez::as::initialize();
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

  chassis.set_drive_pid(-30, 120);
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  // This is preference to what you like to drive on.
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

  while (true) {
    // (left joystick controls left wheels, right joystick controls right wheels)
    chassis.tank();

    /**
     * Custom Functions
     */
    intake();
    catapult();
    wings();

    /**
     * LCD
     */
    pros::lcd::print(0, "Buttons Bitmap: %d\n", pros::lcd::read_buttons());

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
