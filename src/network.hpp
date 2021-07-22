#ifndef NETWORK_HPP 
#define NETWORK_HPP

#include <WiFi.h>
#include <WiFiUdp.h>
#include <WiFiClientSecure.h>

#include <NTPClient.h>

namespace net {

const int CONNECT_WIFI_DELAY_MS = 3000;

void connectToWifi();

void checkConnection();

void reconnect();

void connectToMQTT();

void publishToMQTT(const char jsonPayload[]);

}
#endif