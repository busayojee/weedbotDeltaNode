// End effector motor spinner
#ifndef WEEDBOT_SPINNER_H
#define WEEDBOT_SPINNER_H
#include <Arduino.h>

class Spinner {
public:
  void begin(int in1, int in2) {
    pinMode(in1, OUTPUT); pinMode(in2, OUTPUT);
    _in1 = in1; _in2 = in2; stop();
  }
  // 1.0 = forward, 2.0 = reverse, 0.0 = stop
  void cmd(float v) {
    if (v == 1.0f) { forward(); }
    else if (v == 2.0f) { reverse(); }
    else { stop(); }
  }
  void forward(){ digitalWrite(_in1,HIGH); digitalWrite(_in2,LOW); }
  void reverse(){ digitalWrite(_in1,LOW);  digitalWrite(_in2,HIGH); }
  void stop()   { digitalWrite(_in1,LOW);  digitalWrite(_in2,LOW);  }
private:
  int _in1=-1, _in2=-1;
};

#endif
