// The delta servos configurations. Note this uses the DS

#ifndef WEEDBOT_SERVO_MAPPER_H
#define WEEDBOT_SERVO_MAPPER_H
#include <Arduino.h>

struct ServoCal{
    float offset_deg = 0.0f; 
    float min_deg = 0.0f;
    float max_deg = 180.0f;
    int   min_us  = 500;
    int   max_us  = 2500;
};

int angleToMicros(float angle_deg, const ServoCal& cal);

#endif