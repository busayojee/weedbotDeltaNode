#ifndef WEEDBOT_DELTA_NODE_H
#define WEEDBOT_DELTA_NODE_H

#include <micro_ros_platformio.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <geometry_msgs/msg/point.h>
#include <std_msgs/msg/float32.h>

#include "delta_controller.h"
#include "spinner.h"
#include "delta_http.h"

class DeltaNode {
public:
  void begin();       // WiFi, micro-ROS, subs/pubs, hardware attach
  void spinOnce();    // executor and HTTP polling

private:
  // ROS
  rclc_support_t support{};
  rcl_allocator_t allocator{};
  rcl_node_t node{};
  rcl_subscription_t subAngles{};
  rcl_subscription_t subSpin{};
  rcl_publisher_t    pubDig{};
  rcl_publisher_t    pubSweep{};
  rclc_executor_t    executor{};
  geometry_msgs__msg__Point anglesMsg{};
  std_msgs__msg__Float32    spinMsg{};
  geometry_msgs__msg__Point digMsg{};
  std_msgs__msg__Float32    sweepMsg{};

  // HW
  DeltaController delta;
  Spinner spinner;
  DeltaHttp http;

  // callbacks
  static DeltaNode* self;
  static void anglesCb(const void* msgin);
  static void spinCb(const void* msgin);
  void onAngles(const geometry_msgs__msg__Point* pt);
  void onSpin(const std_msgs__msg__Float32* sm);
};

#endif
