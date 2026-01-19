#include <BleMouse.h>
#include <MPU9250_asukiaaa.h>

#define SDA_PIN 21
#define SCL_PIN 22

BleMouse bleMouse("StupidNiubi", "ESP32", 100);
MPU9250_asukiaaa mySensor;

void setup() {
  Serial.begin(9600);
  Wire.begin(SDA_PIN, SCL_PIN);
  mySensor.setWire(&Wire);
  mySensor.beginAccel();
  mySensor.beginGyro();

  bleMouse.begin();
  Serial.println("Started");
}

void loop() {
  if (!bleMouse.isConnected()) return;

  mySensor.accelUpdate();
  mySensor.gyroUpdate();
  Serial.print(String(millis()) + " "+ "-->"+" ");

  float aX = mySensor.accelX();
  float aY = mySensor.accelY();
  float aZ = mySensor.accelZ();
  float gZ = mySensor.gyroZ();
  Serial.print(String(aX)+" ");
  Serial.print(String(aY)+" ");
  Serial.print(String(aZ)+" ");
  Serial.print(String(gZ) + "");
  //Serial.print(String(gZ)+" ");
  if (abs(aX) > 0.4 || abs(aY) > 0.4) {
    int Cx = constrain(aX * 15, -10, 10);
    int Cy = constrain(-aY * 15, -10, 10);
    bleMouse.move(Cx, Cy);
    delay(20);
  }

  if (aZ < -1.5) {
    bleMouse.press(MOUSE_LEFT);
    delay(100);
    bleMouse.release(MOUSE_LEFT);
  }

  if (gZ > 100) {
    bleMouse.press(MOUSE_RIGHT);
    delay(100);
    bleMouse.release(MOUSE_RIGHT);
  }

 Serial.println("\n");

}
