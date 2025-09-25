// #include <Arduino.h>
// #include <WiFi.h>
// #include <micro_ros_platformio.h>
// #include <rcl/rcl.h>
// #include <rclc/rclc.h>
// #include <rclc/executor.h>
// #include <geometry_msgs/msg/point.h>
// #include <std_msgs/msg/float32.h>
// #include <ESP32Servo.h>

// const char* WIFI_SSID    = "iPhone (6)";
// const char* WIFI_PASS    = "busayoalabi";
// IPAddress  AGENT_IP(172, 20, 10, 6);
// const uint16_t AGENT_PORT = 8888;
// WiFiServer httpServer(80);

// // Servo pins
// const int SERVO_PIN1 = 18;
// const int SERVO_PIN2 = 19;
// const int SERVO_PIN3 = 21;
// // Motor driver pins (H-bridge inputs)
// const int MOTOR_PIN1 = 26;
// const int MOTOR_PIN2 = 27;

// Servo servo1, servo2, servo3;

// // Last commanded angles for smoothing
// int lastAngle1 = 0;
// int lastAngle2 = 0;
// int lastAngle3 = 0;
// const int SMOOTH_STEPS = 20;    // more steps = smoother
// const int STEP_DELAY_MS = 15;   // delay between steps

// // micro-ROS objects
// rclc_support_t support;
// rcl_allocator_t allocator;
// rcl_node_t node;
// rcl_subscription_t pointSub;
// rcl_subscription_t spinSub;
// rcl_publisher_t digPub;
// rclc_executor_t executor;

// // Message buffers
// geometry_msgs__msg__Point pointMsg;
// std_msgs__msg__Float32 spinMsg;
// geometry_msgs__msg__Point digMsg;
// rcl_publisher_t sweepPub;
// std_msgs__msg__Float32 sweepMsg;

// // Smoothly move servos from last angles to new ones
// void smoothMove(int target1, int target2, int target3) {
//   for (int i = 1; i <= SMOOTH_STEPS; ++i) {
//     int a1 = lastAngle1 + (target1 - lastAngle1) * i / SMOOTH_STEPS;
//     int a2 = lastAngle2 + (target2 - lastAngle2) * i / SMOOTH_STEPS;
//     int a3 = lastAngle3 + (target3 - lastAngle3) * i / SMOOTH_STEPS;
//     servo1.write(a1);
//     servo2.write(a2);
//     servo3.write(a3);
//     delay(STEP_DELAY_MS);
//   }
//   lastAngle1 = target1;
//   lastAngle2 = target2;
//   lastAngle3 = target3;
// }

// // Callback for joint angles
// void point_callback(const void* msgin) {
//   auto *pt = (const geometry_msgs__msg__Point *)msgin;
//   int target1 = int(pt->x + 0.5);
//   int target2 = int(pt->y + 0.5);
//   int target3 = int(pt->z + 0.5);
//   Serial.printf("→ New angles: %d, %d, %d\n", target1, target2, target3);
//   smoothMove(target1, target2, target3);
// }

// // Callback for spinner command: 1.0=forward, 2.0=reverse, 0.0=stop
// void spin_callback(const void* msgin) {
//   auto *sm = (const std_msgs__msg__Float32 *)msgin;
//   float cmd = sm->data;
//   if (cmd == 1.0f) {
//     delay(100);
//     digitalWrite(MOTOR_PIN1, HIGH);
//     digitalWrite(MOTOR_PIN2, LOW);
//     Serial.println(">> Spinner FORWARD");
//   } else if (cmd == 2.0f) {
//     delay(100);
//     digitalWrite(MOTOR_PIN1, LOW);
//     digitalWrite(MOTOR_PIN2, HIGH);
//     Serial.println(">> Spinner REVERSE");
//   } else {
//     digitalWrite(MOTOR_PIN1, LOW);
//     digitalWrite(MOTOR_PIN2, LOW);
//     Serial.println("<< Spinner STOP");
//   }
// }

// void setup() {
//   Serial.begin(115200);
//   while (!Serial) delay(10);
//   Serial.println("ESP32 delta controller with smooth motion starting...");

//   servo1.attach(SERVO_PIN1, 500, 2500);
//   servo2.attach(SERVO_PIN2, 500, 2500);
//   servo3.attach(SERVO_PIN3, 500, 2500);

//   pinMode(MOTOR_PIN1, OUTPUT);
//   pinMode(MOTOR_PIN2, OUTPUT);
//   digitalWrite(MOTOR_PIN1, LOW);
//   digitalWrite(MOTOR_PIN2, LOW);

//   Serial.printf("Connecting to Wi-Fi %s...", WIFI_SSID);
//   WiFi.begin(WIFI_SSID, WIFI_PASS);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print('.');
//   }
//   Serial.println("\nWi-Fi connected!");
//   Serial.print("IP: "); Serial.println(WiFi.localIP());

//   httpServer.begin();
//   Serial.println(">> HTTP server started");

//   set_microros_wifi_transports(
//     const_cast<char*>(WIFI_SSID),
//     const_cast<char*>(WIFI_PASS),
//     AGENT_IP, AGENT_PORT
//   );
//   delay(2000);
//   Serial.println(">> micro-ROS over UDP ready");

//   allocator = rcl_get_default_allocator();
//   rclc_support_init(&support, 0, NULL, &allocator);
//   rclc_node_init_default(&node, "esp32_delta", "", &support);

//   geometry_msgs__msg__Point__init(&pointMsg);
//   std_msgs__msg__Float32__init(&spinMsg);
//   geometry_msgs__msg__Point__init(&digMsg);
//    std_msgs__msg__Float32__init(&sweepMsg);


//   rclc_subscription_init_default(&pointSub, &node,
//     ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Point),
//     "joint_angles_point"
//   );
//   rclc_subscription_init_default(&spinSub, &node,
//     ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
//     "spinner_cmd"
//   );
//   rclc_publisher_init_default(&digPub, &node,
//     ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Point),
//     "dig_target"
//   );
//   rclc_publisher_init_default(&sweepPub, &node,
//     ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
//     "sweep_cmd"
//   );
//   rclc_executor_init(&executor, &support.context, 3, &allocator);
//   rclc_executor_add_subscription(&executor, &pointSub, &pointMsg,
//                                  point_callback, ON_NEW_DATA);
//   rclc_executor_add_subscription(&executor, &spinSub, &spinMsg,
//                                  spin_callback, ON_NEW_DATA);

//   Serial.println(">> Setup complete");
// }

// void loop() {
//   WiFiClient client = httpServer.available();
//   if (client) {
//     String req = client.readStringUntil('\r');
//     client.readStringUntil('\n');

//     if (req.startsWith("GET /command?cmd=")) {
//       int eq = req.indexOf('=');
//       int sp = req.indexOf(' ', eq);
//       int cmd = req.substring(eq+1, sp).toInt();

//       sweepMsg.data = cmd;
//       rcl_publish(&sweepPub, &sweepMsg, NULL);

//       // feedback on ESP side
//       if (cmd == 1) {
//         Serial.println(">> SWEEP_CMD = START");
//       } else {
//         Serial.println("<< SWEEP_CMD = STOP");
//       }

//       client.println("HTTP/1.1 200 OK");
//       client.println("Connection: close");
//       client.println();
//       client.printf("Cmd=%d", cmd);
//     }
//     // else {
//     //   client.println("HTTP/1.1 404 Not Found");
//     //   client.println("Connection: close");
//     //   client.println();
//     // }
//     if (req.startsWith("GET /point?")) {
//       int q = req.indexOf('?');
//       int sp = req.indexOf(' ', q);
//       String params = req.substring(q+1, sp);
//       int amp = params.indexOf('&');
//       float x = params.substring(2, amp).toFloat();
//       float y = params.substring(amp+3).toFloat();
//       digMsg.x = x;
//       digMsg.y = y;
//       digMsg.z = 0.0;
//       rcl_publish(&digPub, &digMsg, NULL);
//       client.println("HTTP/1.1 200 OK");
//       client.println("Content-Type: text/plain");
//       client.println("Connection: close");
//       client.println();
//       client.printf("Dig at X=%.1f, Y=%.1f", x, y);
//     } 
//     // else {
//     //   client.println("HTTP/1.1 404 Not Found");
//     //   client.println("Connection: close");
//     //   client.println();
//     // }

//     client.stop();
//   }

//   rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
//   delay(10);
// }
// // 