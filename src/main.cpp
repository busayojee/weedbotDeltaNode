#include <Arduino.h>
#include "delta_node.h"

DeltaNode node;

void setup(){ Serial.begin(115200); node.begin(); }
void loop(){  node.spinOnce(); delay(10); }
