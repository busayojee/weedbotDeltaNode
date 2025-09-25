#include "servo_mapper.h"
int angleToMicros(float deg, const ServoCal& c) {
  float clamped = constrain(deg + c.offset_deg, c.min_deg, c.max_deg);
  float t = (clamped - c.min_deg) / (c.max_deg - c.min_deg);
  return c.min_us + int(t * (c.max_us - c.min_us));
}
