#include "delta_node.h"
#include "config.h"

DeltaNode* DeltaNode::self = nullptr;

void DeltaNode::begin(){
  self = this;

  // WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status()!=WL_CONNECTED) delay(200);

  // micro-ROS
  set_microros_wifi_transports(
    const_cast<char*>(WIFI_SSID),
    const_cast<char*>(WIFI_PASS),
    AGENT_IP, AGENT_PORT);
  allocator = rcl_get_default_allocator();
  rclc_support_init(&support, 0, NULL, &allocator);
  rclc_node_init_default(&node, "esp32_delta", "", &support);

  // pubs / subs
  geometry_msgs__msg__Point__init(&anglesMsg);
  std_msgs__msg__Float32__init(&spinMsg);
  geometry_msgs__msg__Point__init(&digMsg);
  std_msgs__msg__Float32__init(&sweepMsg);

  rclc_subscription_init_default(&subAngles, &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Point), "joint_angles_point");
  rclc_subscription_init_default(&subSpin, &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32), "spinner_cmd");
  rclc_publisher_init_default(&pubDig, &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Point), "dig_target");
  rclc_publisher_init_default(&pubSweep, &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32), "sweep_cmd");

  rclc_executor_init(&executor, &support.context, 2, &allocator);
  rclc_executor_add_subscription(&executor, &subAngles, &anglesMsg, anglesCb, ON_NEW_DATA);
  rclc_executor_add_subscription(&executor, &subSpin,   &spinMsg,   spinCb,   ON_NEW_DATA);

  // hardware
  delta.begin(SERVO_PIN1, SERVO_PIN2, SERVO_PIN3);
  spinner.begin(MOTOR_PIN1, MOTOR_PIN2);

  // HTTP
  http.begin(HTTP_PORT);
}

void DeltaNode::anglesCb(const void* msgin){
  if (!self) return;
  self->onAngles(static_cast<const geometry_msgs__msg__Point*>(msgin));
}
void DeltaNode::spinCb(const void* msgin){
  if (!self) return;
  self->onSpin(static_cast<const std_msgs__msg__Float32*>(msgin));
}

void DeltaNode::onAngles(const geometry_msgs__msg__Point* pt){
  int t1 = int(pt->x + 0.5f);
  int t2 = int(pt->y + 0.5f);
  int t3 = int(pt->z + 0.5f);
  delta.smoothMove(t1,t2,t3, SMOOTH_STEPS, STEP_DELAY_MS);
}

void DeltaNode::onSpin(const std_msgs__msg__Float32* sm){
  spinner.cmd(sm->data);
}

void DeltaNode::spinOnce(){
  rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
  // HTTP → publish sweep/dig
  http.poll(
    /*onCommand*/[this](int cmd){
      sweepMsg.data = cmd;
      rcl_publish(&pubSweep, &sweepMsg, nullptr);
    },
    /*onPoint*/[this](float x, float y){
      digMsg.x = x; digMsg.y = y; digMsg.z = 0.0f;
      rcl_publish(&pubDig, &digMsg, nullptr);
    }
  );
}
