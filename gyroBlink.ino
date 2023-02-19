#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "BluetoothSerial.h"

// ---------------------------------------------------------------------
// Bluetooth
// ---------------------------------------------------------------------
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

#define VRX_PIN  32 // Arduino pin connected to VRX pin
#define VRY_PIN  33 // Arduino pin connected to VRY pin

BluetoothSerial SerialBT;

int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis
float prev_a_69 = 0.0f;
float prev_a_68 = 0.0f;

// MPU
Adafruit_MPU6050 mpu68;
Adafruit_MPU6050 mpu69;

void setup(void) {
  pinMode(2, OUTPUT);
  pinMode(17, OUTPUT);
  
    Serial.begin(115200);
    SerialBT.begin("ESP32test"); //Bluetooth device name
    Serial.println("The device started, now you can pair it with bluetooth!");



    

    // Try to initialize!
    if (!mpu68.begin(0x68)) {
        Serial.println("Failed to find MPU6050-68 chip");
        while (1) {
          delay(10);
        }
    }

    if (!mpu69.begin(0x69)) {
        Serial.println("Failed to find MPU6050-69 chip");
        while (1) {
          delay(10);
        }
    }

    // set accelerometer range to +-8G
    mpu68.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu69.setAccelerometerRange(MPU6050_RANGE_8_G);

    // set gyro range to +- 500 deg/s
    mpu68.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu69.setGyroRange(MPU6050_RANGE_500_DEG);

    // set filter bandwidth to 21 Hz
    mpu68.setFilterBandwidth(MPU6050_BAND_21_HZ);
    mpu69.setFilterBandwidth(MPU6050_BAND_21_HZ);

    delay(100);
}

void loop() {
    /* Get new sensor events with the readings */
    sensors_event_t a68, a69, g68, g69, temp68, temp69;
    mpu68.getEvent(&a68, &g68, &temp68);
    mpu69.getEvent(&a69, &g69, &temp69);

//
//    if (Serial.available()) {
//    SerialBT.write(Serial.read());
//    }
//    
//    if (SerialBT.available()) {
//      Serial.write(SerialBT.read());
//    }

  String stick_one = "0";
  String stick_two = "0";
  bool is_movement = false;

  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
  String joy_stick_mode = "s";
  if(xValue < 200){
    joy_stick_mode = "h";
  } else if(yValue < 200){        //output2 goes high in region 2
      joy_stick_mode = "c";
  } else if(xValue > 3800){
      joy_stick_mode = "p";
  } else if(yValue > 3800){        //output4 goes high in region 4
      joy_stick_mode = "t";
  }
  
  if (prev_a_68 < -10 && a68.acceleration.x > -10) {
    is_movement = true;
    digitalWrite(2, HIGH);
    stick_one = joy_stick_mode;
  } else {
    digitalWrite(2, LOW);
  }

  if (prev_a_69 < -10 && a69.acceleration.x > -10) {
    is_movement = true;
    digitalWrite(17, HIGH);
    stick_two = "t";
  } else {
    digitalWrite(17, LOW);
  }

  if (is_movement) {
    String output_packet = stick_two;
    output_packet += stick_one;
    SerialBT.println(output_packet);
    Serial.println(output_packet);
  }

  prev_a_69 = a69.acceleration.x;
  prev_a_68 = a68.acceleration.x;
  
}
