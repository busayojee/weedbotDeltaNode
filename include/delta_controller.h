#ifndef WEEDBOT_DELTA_CONTROLLER_H
#define WEEDBOT_DELTA_CONTROLLER_H

#include <ESP32Servo.h>
#include "servo_mapper.h"

class DeltaController {
public:
  void begin(int pin1, int pin2, int pin3,
             ServoCal c1={}, ServoCal c2={}, ServoCal c3={});
  // Blocking smooth move (simple)
  void smoothMove(int a1_deg, int a2_deg, int a3_deg,
                  int steps, int stepDelayMs);

  // Immediate set (no smoothing)
  void writeAngles(int a1_deg, int a2_deg, int a3_deg);

  // Track last commanded (for smoothing/increments)
  int last1() const { return lastAngle1; }
  int last2() const { return lastAngle2; }
  int last3() const { return lastAngle3; }

private:
  Servo s1, s2, s3;
  ServoCal c1, c2, c3;
  int lastAngle1 = 0, lastAngle2 = 0, lastAngle3 = 0;
};

#endif
