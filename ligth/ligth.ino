#define BLYNK_TEMPLATE_ID "TMPL6l8l0Rp1Y"
#define BLYNK_TEMPLATE_NAME "MQ2"
#define BLYNK_AUTH_TOKEN "BIGPpTT1to-rCRLwEntgMoAcsyQFq4kL"

#include <WiFi.h>
#include <SPI.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define BLYNK_PRINT Serial
BlynkTimer timer;
//---------------------------------------
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "DESKTOP-LAPTOP 8363";
char pass[] = "123456789";
//---------------------------------------
#define cbAS 4
#define led1 22
#define led2 15
#define led3 16
#define led4 17
#define led5 18
int value;
//---------------------------------------
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  pinMode(cbAS, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  //--------------------------------------------------
}

void sendUptime()
{
  value = 100-map(analogRead(cbAS), 0, 4095, 0, 100);

  // Bật đèn khi ánh sáng dưới 20% và tắt đèn khi ánh sáng trên 20%
  if (value > 20)
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }
  else
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
  }

  // Hiển thị cường độ ánh sáng trên Blynk
  Blynk.virtualWrite(V0, value);

  // Hiển thị trạng thái đèn trên Blynk
  if (value < 20)
  {
    Blynk.virtualWrite(V1, led1);
    Blynk.virtualWrite(V2, led2);
    Blynk.virtualWrite(V3, led3);
    Blynk.virtualWrite(V4, led4);
    Blynk.virtualWrite(V5, led5);
  }
  else
  {
    Blynk.virtualWrite(V1, led1);
    Blynk.virtualWrite(V2, led2);
    Blynk.virtualWrite(V3, led3);
    Blynk.virtualWrite(V4, led4);
    Blynk.virtualWrite(V5, led5); 
  }

  Serial.println(value);
}

void loop()
{
  Blynk.run();
  timer.run();
}
