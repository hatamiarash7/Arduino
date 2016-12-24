/*
 * Quick n dirty example of GY-953.
 * The library use an interrupt handled internally.
 */
#include <GY953.h>
#include <SPI.h>

bool justStarted = true;

GY953 mag = GY953(10, 2);

void setup() {
  Serial.begin(115200);
  long unsigned debug_start = millis ();
  Serial.println("started 1");
  while (!Serial && ((millis () - debug_start) <= 5000));
  mag.begin();
  //mag.changeRefreshRate(200);
  Serial.println("started 2");
}

void loop() {
  if (mag.update()) {
    int data[3], data4[3], data5[3], data6[3], data7[3];
    if (justStarted) {
      justStarted = false;
      byte data2[4];
      byte data3[3];
      memset(data,0,3);
      memset(data2,0,4);
      memset(data3,0,3);
      memset(data4,0,3);
      memset(data5,0,3);
      memset(data6,0,3);
      memset(data7,0,3);
      mag.readAccuracy(data2);
      Serial.print("\nAccuracy  ");
      Serial.print("ACC:");   //0..3 (less...more accurate)
      Serial.print(data2[0]);
      Serial.print(" | GYR:");//0..3 (less...more accurate)
      Serial.print(data2[1]);
      Serial.print(" | MAG:");//0..3 (less...more accurate)
      Serial.print(data2[2]);
      Serial.print(" | Freq:");//3:50Hz - 4:100Hz - 5:200Hz
      Serial.print(data2[3]);

      mag.readRange(data3);
      Serial.print("      Range  ");
      Serial.print("ACC:");   //0---------------+-2g
      Serial.print(data3[0]);
      Serial.print(" | GYR:");//3---------------+-2000dps/s
      Serial.print(data3[1]);
      Serial.print(" | MAG:");//1:---------16bit
      Serial.print(data3[2]);
    } else {
      mag.getRPY(data);
      mag.getACC(data4);
      mag.getGYR(data5);
      mag.getMAG(data6);
      mag.getQ(data7);
      Serial.println();
      Serial.print("RPY   Roll:");
      Serial.print(data[0]);
      Serial.print(" | Pitch:");
      Serial.print(data[1]);
      Serial.print(" | Yaw:");
      Serial.print(data[2]);

      Serial.print(" ACC   Roll:");
      Serial.print(data4[0]);
      Serial.print(" | Pitch:");
      Serial.print(data4[1]);
      Serial.print(" | Yaw:");
      Serial.print(data4[2]);

      Serial.print(" GYR   Roll:");
      Serial.print(data5[0]);
      Serial.print(" | Pitch:");
      Serial.print(data5[1]);
      Serial.print(" | Yaw:");
      Serial.print(data5[2]);

      Serial.print(" MAG   Roll:");
      Serial.print(data6[0]);
      Serial.print(" | Pitch:");
      Serial.print(data6[1]);
      Serial.print(" | Yaw:");
      Serial.print(data6[2]);

      Serial.print(" Q   Roll:");
      Serial.print(data7[0]);
      Serial.print(" | Pitch:");
      Serial.print(data7[1]);
      Serial.print(" | Yaw:");
      Serial.print(data7[2]);

    }

  }

}
