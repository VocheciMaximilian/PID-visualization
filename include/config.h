#ifndef CONFIG_H
#define CONFIG_H
// pid default
#define PID_KP 3.0f
#define PID_KI 0.0f
#define PID_KD 0.4f
#define PID_INTEGRAL_MIN -1.0f
#define PID_INTEGRAL_MAX 1.0f
#define PID_OUTPUT_MIN -0.95f
#define PID_OUTPUT_MAX 0.95f
#define PID_HAS_PREVIOUS false
#define PID_PREVIOUS_ERROR 0.0f
#define PID_INTEGRAL 0.0f
#define TIME_STEP 1e-6f
// motor default
#define MOTOR_MIN_SPEED -20.0f
#define MOTOR_MAX_SPEED 20.0f
#define MOTOR_ACCEL_RATE 8.0f
#define MOTOR_BRAKE_RATE 12.0f
#define MOTOR_DRAG 0.8f
#define MOTOR_INTIAL_RPM 0.0f
#define MOTOR_INITIAL_LEFT_SPEED 0.0f
#define MOTOR_INITIAL_RIGHT_SPEED 0.0f

#define MOTOR_INPUT_MIN -1.0f
#define MOTOR_INPUT_MAX 1.0f
#define MOTOR_INPUT_NEUTRAL 0.0f
#define MOTOR_TWO_WHEELS 2.0f
// steering default
#define STEERING_MAX_ANGLE 0.6f
#define STEERING_RATE 3.0f
#define STEERING_INTIAL_ANGLE 0.0f

#endif
