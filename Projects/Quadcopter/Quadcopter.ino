#include <GY953.h>
#include <SPI.h>
#include <Servo.h>
#include <PID_v1.h>

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 700
#define MOTOR_PIN1 9
#define MOTOR_PIN2 11

String inString = "";
String motor1, motor2;
Servo m1, m2;
bool justStarted = true;
int sp1 = 1400, sp2 = 1400, deg, spd1 , spd2, f; //sp2 pin11 motor dor black
int temp=0;
GY953 mag = GY953(10, 2);

double Kp=2, Ki=0.8, Kd=0.8;
// 2 - 0.8 - 0.8
double input, output, setpoint;

PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;
  for(int i = 0 ; i <= maxIndex && found <= index ; i++){
    if(data.charAt(i) == separator || i == maxIndex){
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}


void setup() {
  Serial.begin(115200);
  long unsigned debug_start = millis ();
  Serial.println("started");
  Serial.println("This program will calibrate the ESC.");
  m1.attach(MOTOR_PIN1);
  m2.attach(MOTOR_PIN2);
  Serial.println("Now writing maximum output.");
  Serial.println("Turn on power source, then wait 2 seconds and press any key.");
  m1.writeMicroseconds(MAX_SIGNAL);
  m2.writeMicroseconds(MAX_SIGNAL);
  // Wait for input
  while (!Serial.available());
  Serial.read();
  // Send min output
  Serial.println("Sending minimum output");
  m1.writeMicroseconds(MIN_SIGNAL);
  m2.writeMicroseconds(MIN_SIGNAL);
  delay(2000);
  while (!Serial && ((millis () - debug_start) <= 5000));
  mag.begin();
  Serial.println("calibration");
  
  setpoint = 0;
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-125, 125);
}

void loop() {
  int data[3], data4[3], data5[3], data6[3], data7[3];
  if (mag.update()) {
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
    } else {
      mag.getRPY(data);
      mag.getACC(data4);
      mag.getGYR(data5);
      mag.getMAG(data6);
      mag.getQ(data7);
    }
  }
  
  //setpoint = data[4];
  //input = map(data[1],-9000,9000,100,200);
  input = data[1] / 120;
  myPID.Compute();
  Serial.print("in :   ");
  Serial.print(input);
  Serial.print("      Out :   ");
  Serial.print(output);
  sp1 = 1400 + output;
  sp2 = 1400 - output;
  m1.writeMicroseconds(sp1);
  m2.writeMicroseconds(sp2); 
  Serial.print("       sp1 :   ");
  Serial.print(sp1);
  Serial.print("       sp2 :   ");
  Serial.println(sp2);
}

