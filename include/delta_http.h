#ifndef WEEDBOT_DELTA_HTTP_H
#define WEEDBOT_DELTA_HTTP_H
#include <WiFi.h>

// Minimal HTTP interface to communicate with the vision host. The vision host sends the command to start or stop the robot's movement and also the x, y position of a weed in space for the end effectore to go to: /command?cmd={0|1}  /point?x=..&y=..
class DeltaHttp {
public:
  void begin(uint16_t port) { server = WiFiServer(port); server.begin(); }
  template <typename OnCommand, typename OnPoint>
  void poll(OnCommand onCommand, OnPoint onPoint) {
    WiFiClient client = server.available();
    if (!client) return;

    String req = client.readStringUntil('\r');
    client.readStringUntil('\n');

    if (req.startsWith("GET /command?cmd=")) {
      int eq = req.indexOf('='), sp = req.indexOf(' ', eq);
      int cmd = req.substring(eq+1, sp).toInt();
      onCommand(cmd);
      client.println("HTTP/1.1 200 OK\r\nConnection: close\r\n\r\nOK");
    } else if (req.startsWith("GET /point?")) {
      int q = req.indexOf('?'), sp = req.indexOf(' ', q);
      String params = req.substring(q+1, sp);
      int amp = params.indexOf('&');
      float x = params.substring(2, amp).toFloat();
      float y = params.substring(amp+3).toFloat();
      onPoint(x, y);
      client.println("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n");
      client.printf("x=%.1f,y=%.1f\r\n", x, y);
    } else {
      client.println("HTTP/1.1 404 Not Found\r\nConnection: close\r\n\r\n");
    }
    client.stop();
  }
private:
  WiFiServer server;
};

#endif
