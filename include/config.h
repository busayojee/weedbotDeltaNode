#ifndef WEEDBOT_DELTA_CONFIG_H
#define WEEDBOT_DELTA_CONFIG_H

#include <Arduino.h>
#include <IPAddress.h>

// WiFi + micro-ROS agent (declarations only; defs live in src/config.cpp)
extern const char* WIFI_SSID;
extern const char* WIFI_PASS;
extern const IPAddress AGENT_IP;
extern const uint16_t AGENT_PORT;

// Pins
constexpr int SERVO_PIN1 = 18;
constexpr int SERVO_PIN2 = 19;
constexpr int SERVO_PIN3 = 21;

constexpr int MOTOR_PIN1 = 26; // H-bridge IN1
constexpr int MOTOR_PIN2 = 27; // H-bridge IN2

// Motion smoothing
constexpr int SMOOTH_STEPS   = 20;
constexpr int STEP_DELAY_MS  = 15;

// HTTP to communicate with the vision host
constexpr uint16_t HTTP_PORT = 80;

#endif