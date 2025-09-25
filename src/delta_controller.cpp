#include "delta_controller.h"

void DeltaController::begin(int p1,int p2,int p3, ServoCal C1,ServoCal C2,ServoCal C3){
  c1=C1; c2=C2; c3=C3;
  s1.attach(p1, c1.min_us, c1.max_us);
  s2.attach(p2, c2.min_us, c2.max_us);
  s3.attach(p3, c3.min_us, c3.max_us);
  writeAngles(0,0,0);
}

void DeltaController::writeAngles(int a1,int a2,int a3){
  s1.writeMicroseconds(angleToMicros(a1,c1));
  s2.writeMicroseconds(angleToMicros(a2,c2));
  s3.writeMicroseconds(angleToMicros(a3,c3));
  lastAngle1=a1; lastAngle2=a2; lastAngle3=a3;
}

void DeltaController::smoothMove(int t1,int t2,int t3,int steps,int delayMs){
  for(int i=1;i<=steps;++i){
    int a1 = lastAngle1 + (t1-lastAngle1)*i/steps;
    int a2 = lastAngle2 + (t2-lastAngle2)*i/steps;
    int a3 = lastAngle3 + (t3-lastAngle3)*i/steps;
    writeAngles(a1,a2,a3);
    delay(delayMs);
  }
}
