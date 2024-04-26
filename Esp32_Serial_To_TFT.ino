#include <TFT_eSPI.h>

TFT_eSPI tft;

void setup() {
  // 波特率设置，用于监视串口
  Serial.begin(115200);
  tft.begin();
  // 设置屏幕方向
  tft.setRotation(1);
}

void loop() {
  if (Serial.available() > 0) {
    // 读取一行的数据
    String receivedData = Serial.readStringUntil('\n');

    // 去除首尾空格和换行符
    receivedData.trim();
    Serial.println("Received data: " + receivedData);

    // 设置屏幕颜色，如果不重置黑色，像素点会一直堆积
    tft.fillScreen(TFT_BLACK);

    // 设置光标位置，字号，颜色，打印串口收到的内容
    tft.setCursor(6, 45);
    tft.setTextSize(3);
    tft.setTextColor(TFT_YELLOW);
    tft.println(receivedData);
  }
  delay(2000);    
}
