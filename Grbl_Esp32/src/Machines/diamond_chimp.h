#pragma once
// clang-format off

/*
    diamond_chimp.h
    
    Pin assignments for the ESP32 Plotter Controller RevA (Diamond Chimp)
    https://github.com/MarkJB/ESP32_Plotter_Controller

    2021    - Mark Benson
    
    Grbl_ESP32 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Grbl is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Grbl_ESP32.  If not, see <http://www.gnu.org/licenses/>.
*/

#define CUSTOM_CODE_FILENAME    "../Custom/CoreXY.cpp"
#define USE_KINEMATICS      // there are kinematic equations for this machine
#define USE_FWD_KINEMATICS  // report in cartesian
#define USE_MACHINE_INIT    // There is some custom initialization for this machine
#define USE_CUSTOM_HOMING

// Select a version to match your PCB

#define MACHINE_NAME    "ESP32_Plotter_Controller_RevA_DIAMOND_CHIMP"
#define X_LIMIT_PIN     GPIO_NUM_34
#define Y_LIMIT_PIN     GPIO_NUM_35

#define TRINAMIC_RUN_MODE           TrinamicMode :: CoolStep
// To use conventional switches uncomment the follow and comment
// out the 'StallGuard' option.
//#define TRINAMIC_HOMING_MODE        TrinamicMode :: CoolStep
// To use TMC2130 StallGuard for sensorless homing, uncomment the
// following and put jumpers on X & Y Limit connectors (J7 & J9)
#define TRINAMIC_HOMING_MODE        TrinamicMode :: StallGuard

#define X_STEP_PIN              GPIO_NUM_25
#define X_DIRECTION_PIN         GPIO_NUM_26
#define X_TRINAMIC_DRIVER       2130        // Which Driver Type?
#define X_CS_PIN                GPIO_NUM_17  //chip select
#define X_RSENSE                TMC2130_RSENSE_DEFAULT

#define Y_STEP_PIN              GPIO_NUM_32
#define Y_DIRECTION_PIN         GPIO_NUM_33
#define Y_TRINAMIC_DRIVER       2130        // Which Driver Type?
#define Y_CS_PIN                GPIO_NUM_16  //chip select
#define Y_RSENSE                TMC2130_RSENSE_DEFAULT

#define STEPPERS_DISABLE_PIN GPIO_NUM_2

// Spindle = soleniod or servo

// Solenoid
#define SPINDLE_TYPE SpindleType::RELAY
#define SPINDLE_OUTPUT_PIN GPIO_NUM_27
#define INVERT_SPINDLE_PWM

// Laser
//#define SPINDLE_TYPE SpindleType::LASER
#define LASER_OUTPUT_PIN GPIO_NUM_27

// Servo
//#define Z_SERVO_PIN                   GPIO_NUM_27 // comment this out if PWM spindle/laser control.
#define Z_SERVO_CAL_MIN               1.0   // calibration factor for the minimum PWM duty
#define Z_SERVO_CAL_MAX               1.0   // calibration factor for the maximum PWM duty
#define DEFAULT_Z_MAX_TRAVEL          5.0   // Range of travel is 5mm
#define DEFAULT_Z_HOMING_MPOS         5.0   // MPos will be set to 5mm after homing