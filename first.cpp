// #include <Arduino.h>
// #include <micro_ros_platformio.h>
// #include <rcl/rcl.h>
// #include <rclc/rclc.h>
// #include <rclc/executor.h>
// #include <std_msgs/msg/float32_multi_array.h>
// #include <rcl/error_handling.h>
// #include <std_msgs/msg/float32.h>
// #include <std_msgs/msg/string.h>

// // --- Configurable ---
// const char * serial_dev = "/dev/ttyUSB0"; 
// const size_t RING_BUFFER_SIZE = 512;
// // ----------------------

// // micro-ROS objects
// rcl_publisher_t publisher;
// rcl_subscription_t subscriber;
// std_msgs__msg__Float32 sub_msg;
// rclc_support_t support;
// rcl_allocator_t allocator;
// rcl_node_t node;
// rclc_executor_t executor;
// rcl_publisher_t debug_pub;
// std_msgs__msg__String debug_msg;

// // Callback: called when a new std_msgs/Float32 arrives
// void subscription_callback(const void * msgin)
// {
//   const auto *in = (const std_msgs__msg__Float32 *)msgin;
//   Serial.print("Received value: ");
//   Serial.println(in->data, 4);
//   char buf[64];
//   int len = snprintf(buf, sizeof(buf),
//                      "Received: %.4f", in->data);
//   debug_msg.data.data = (char *)buf;
//   debug_msg.data.size = len;
//   debug_msg.data.capacity = sizeof(buf);
//   rcl_publish(&debug_pub, &debug_msg, NULL);
// }

// void setup() {
//   Serial.begin(115200);
//   while (!Serial) { delay(10); }
//   Serial.println("ESP32 micro-ROS Serial Echo");
//   set_microros_serial_transports(Serial);
//   delay(2000);

//   allocator = rcl_get_default_allocator();
//   rclc_support_init(&support, 0, NULL, &allocator);

//   // Node
//   rclc_node_init_default(&node, "esp32_listener", "", &support);

//   // Subscriber on "/esp32_value" topic, type Float32
//   rclc_subscription_init_default(
//     &subscriber,
//     &node,
//     ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
//     "esp32_value"
//   );

//   rclc_executor_init(&executor, &support.context, 1, &allocator);
//   rclc_executor_add_subscription(
//     &executor,
//     &subscriber,
//     &sub_msg,
//     subscription_callback,
//     ON_NEW_DATA
//   );
//     rclc_publisher_init_default(
//     &debug_pub,
//     &node,
//     ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String),
//     "esp32_debug"
//   );
// }

// void loop() {
//   rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
//   delay(10);
// }


// // #include <Arduino.h>
// // #include <micro_ros_platformio.h>
// // #include <rcl/rcl.h>
// // #include <rclc/rclc.h>
// // #include <rclc/executor.h>
// // #include <std_msgs/msg/float32_multi_array.h>
// // #include <std_msgs/msg/string.h>
// // #include <ESP32Servo.h>


// // const int SERVO_PIN_1 = 18;
// // const int SERVO_PIN_2 = 19;
// // const int SERVO_PIN_3 = 21;

// // Servo servo1, servo2, servo3;

// // // micro-ROS objects
// // rcl_subscription_t subscriber;
// // std_msgs__msg__Float32MultiArray sub_msg;
// // rclc_support_t support;
// // rcl_allocator_t allocator;
// // rcl_node_t node;
// // rclc_executor_t executor;
// // rcl_publisher_t debug_pub;
// // std_msgs__msg__String debug_msg;

// // void joint_callback(const void * msgin) {
  
// //   const auto * msg = (const std_msgs__msg__Float32MultiArray *)msgin;
// //   char buf[64];
// //   int len = snprintf(buf, sizeof(buf),
// //                      "Got: %.1f,%.1f,%.1f",
// //                      msg->data.data[0],
// //                      msg->data.data[1],
// //                      msg->data.data[2]);
// //   debug_msg.data.data = (char *)buf;
// //   debug_msg.data.size = len;
// //   debug_msg.data.capacity = sizeof(buf);
// //   rcl_publish(&debug_pub, &debug_msg, NULL);

// //   // if (msg->data.size < 3) {
// //   //   return;
// //   // }
// //   float angles[3];
// //   for (size_t i = 0; i < 3; i++) {
// //     angles[i] = msg->data.data[i];  
// //   }
// //   servo1.write((int)angles[0]);
// //   servo2.write((int)angles[1]);
// //   servo3.write((int)angles[2]);
  

// // }

// // void setup() {
// //   Serial.begin(115200);
// //   while (!Serial) { delay(10); }
// //   Serial.println("ESP32 delta controller starting...");
// //   servo1.attach(SERVO_PIN_1, 500, 2500);
// //   servo2.attach(SERVO_PIN_2, 500, 2500);
// //   servo3.attach(SERVO_PIN_3, 500, 2500);
// //   set_microros_serial_transports(Serial);
// //   delay(2000);  

// //   allocator = rcl_get_default_allocator();
// //   rclc_support_init(&support, 0, NULL, &allocator);

// //   rclc_node_init_default(&node, "esp32_delta", "", &support);

// //   rclc_subscription_init_default(
// //     &subscriber,
// //     &node,
// //     ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32MultiArray),
// //     "joint_angles"
// //   );

// //   rclc_executor_init(&executor, &support.context, 1, &allocator);
// //   rclc_executor_add_subscription(
// //     &executor,
// //     &subscriber,
// //     &sub_msg,
// //     joint_callback,
// //     ON_NEW_DATA
// //   );
// //     rclc_publisher_init_default(
// //     &debug_pub,
// //     &node,
// //     ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String),
// //     "esp32_debug"
// //   );
// // }

// // void loop() {

// //   rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
// //   delay(10);
// // }

// // #include <Arduino.h>
// // #include <micro_ros_platformio.h>
// // #include <rcl/rcl.h>
// // #include <rclc/rclc.h>
// // #include <rclc/executor.h>
// // #include <std_msgs/msg/string.h>
// // #include <ESP32Servo.h>

// // // pins
// // const int PIN1 = 18, PIN2 = 19, PIN3 = 21;
// // Servo s1, s2, s3;

// // // micro-ROS objects
// // rcl_subscription_t  sub;
// // std_msgs__msg__String sub_str;
// // rcl_publisher_t     dbg_pub;
// // std_msgs__msg__String dbg_str;
// // rclc_support_t      support;
// // rcl_allocator_t     alloc;
// // rcl_node_t          node;
// // rclc_executor_t     exe;

// // void cb(const void * msgin) {
// //   Serial.println(">> CB FIRED!");
// //   const auto * m = (const std_msgs__msg__String*)msgin;
// //   static char buf[64];
// //   memcpy(buf, m->data.data, m->data.size);
// //   buf[m->data.size] = 0;

// //   // parse three floats
// //   float a[3] = {0,0,0};
// //   char *tok = strtok(buf, ",");
// //   for (int i=0; i<3 && tok; ++i) {
// //     a[i] = atof(tok);
// //     tok = strtok(NULL, ",");
// //   }

// //   // drive servos
// //   s1.write((int)a[0]);
// //   s2.write((int)a[1]);
// //   s3.write((int)a[2]);

// //   // publish a debug string
// //   int L = snprintf(buf, sizeof(buf),
// //                    "A=%.1f,%.1f,%.1f", a[0],a[1],a[2]);
// //   dbg_str.data.data     = buf;
// //   dbg_str.data.size     = L;
// //   dbg_str.data.capacity = sizeof(buf);
// //   rcl_publish(&dbg_pub, &dbg_str, nullptr);
// // }

// // void setup() {
// //   Serial.begin(115200);
// //   while(!Serial) delay(10);
// //   Serial.println("ESP32 delta controller starting...");

// //   // attach servos
// //   s1.attach(PIN1, 500, 2500);
// //   s2.attach(PIN2, 500, 2500);
// //   s3.attach(PIN3, 500, 2500);
// //   delay(500);

// //   // micro-ROS over USB-CDC
// //   set_microros_serial_transports(Serial);
// //   delay(2000);
// //   Serial.println(">> micro-ROS transport ready");

// //   // init support & node
// //   std_msgs__msg__String__init(&sub_str);
// //   std_msgs__msg__String__init(&dbg_str);
// //   alloc = rcl_get_default_allocator();
// //   rclc_support_init(&support, 0, NULL, &alloc);
// //   rclc_node_init_default(&node, "esp32_delta", "", &support);

// //   // subscription & publisher
// //   rclc_subscription_init_default(
// //     &sub, &node,
// //     ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String),
// //     "joint_angles_str"
// //   );
// //   rclc_publisher_init_default(
// //     &dbg_pub, &node,
// //     ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String),
// //     "esp32_debug"
// //   );
// //   Serial.println(">> created node, sub & pub");

// //   // executor
// //   rclc_executor_init(&exe, &support.context, 1, &alloc);
// //   rclc_executor_add_subscription(&exe, &sub, &sub_str, cb, ON_NEW_DATA);
// //   Serial.println(">> micro-ROS setup complete");
// // }

// // void loop() {
// //   rclc_executor_spin_some(&exe, RCL_MS_TO_NS(100));
// //   delay(10);
// // }

// // // const char* WIFI_SSID   = "Wifinity Home Network";
// // const char* WIFI_PASS   = "hole3last1spend";
// // const char* AGENT_IP    = "192.168.64.4"; 