#include <TFT_eSPI.h>
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>

// wifi账号密码
const char *ssid = "ca****";
const char *password = "30****";
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.aliyun.com");
TFT_eSPI tft;

void setup() {
  // 波特率设置，用于监视串口
  Serial.begin(115200);
  // 连wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("连接中");
  }
  tft.begin();
  // 设置屏幕方向
  tft.setRotation(1);
  // 设置时区为东8区
  timeClient.begin();
  timeClient.setTimeOffset(28800);
}

void loop() {
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime((time_t *)&epochTime);
  int currentYear = ptm->tm_year + 1900;
  int currentMonth = ptm->tm_mon + 1;
  int currentMonthDay = ptm->tm_mday;
  int currentWeekDay = ptm->tm_wday;
  int currentHour = ptm->tm_hour;
  int currentMin = ptm->tm_min;
  // 串口打印获取到的时间
  Serial.println(timeClient.getFormattedTime());
  // 设置屏幕颜色，如果不重置黑色，像素点会一直堆积
  tft.fillScreen(TFT_BLACK);
  // 设置光标位置，字号，颜色
  tft.setCursor(6, 45);
  tft.setTextSize(5);
  tft.setTextColor(TFT_YELLOW);
  tft.println(String(currentHour) + ":" + String(currentMin));
  // 一分钟后再校正时间
  delay(60000);
}