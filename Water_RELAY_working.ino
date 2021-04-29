

#include "Wire.h" // This library allows you to communicate with I2C devices.


// constants won't change
const int RELAY_PIN = 3;  // the Arduino pin, which connects to the IN pin of relay
//Liquid Level Sensor
const int read = A1;
int value;



int red_light_pin= 11;
int green_light_pin = 10;
int blue_light_pin = 9;
//FOR TEMP AND HUMIDITY SENSOR

#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

//Vars for the accellerometer/gyro module /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data
char tmp_str[7]; // temporary variable used in convert function
char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// the setup function runs once when you press reset or power the board
void setup() {
   Serial.begin(9600);
   dht.begin(); // initialize the sensor
// initialize digital pin 9 as an output.
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);


// Tx/Rx lines for accellerometer/gyroscope

Wire.begin();
Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
Wire.write(0x6B); // PWR_MGMT_1 register
Wire.write(0); // set to zero (wakes up the MPU-6050)
Wire.endTransmission(true);

}


// the loop function runs over and over again forever
void loop() {
  RGB_color(255, 255, 255); // WHITE
  delay(3000);

   // read humidity
  float humi  = dht.readHumidity();
  // read temperature as Celsius
  float tempC = dht.readTemperature();
  // read temperature as Fahrenheit
  float tempF = dht.readTemperature(true);
 value = analogRead(read);
int watersensor = A1;

 

 // check if any reads failed
  if (isnan(humi) || isnan(tempC) || isnan(tempF)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {



    int thermistor = analogRead(A0);
    int liquid = analogRead(A1);
    int photoSensor = analogRead(A3);
  
    

//Output all values into one string so it can be parsed via node red
//Look into binning data later if you get the time
String p1=",";
String p2="=";
String A = "Humidity";
String B = "TempC";
String C = "TempF";
String D = "Thermistor";
String E = "LiquidLevel";
String F = "Photoresistor";
String G = "GyroX";
String H = "GyroY";
String I = "AccellX";
String J = "AccellY";



//Serial.println( A + p2 + humi + p1 + B + p2 +tempC + p1 + C + p2 +tempF + p1 + D + p2 + thermistor + p1 + E + p2 + liquid + p1 + F + p2 + photoSensor + p1 + G + p2 + gyro_x + p1 + H + p2 + gyro_y + p1 + I + p2 + accelerometer_x + p1 + J + p2 + accelerometer_y + p1);
Serial.println(humi + p1 + tempC + p1 + tempF + p1 + thermistor + p1 + liquid + p1 +  photoSensor + p1 +   gyro_x + p1  + gyro_y + p1 +  accelerometer_x + p1 +  accelerometer_y + p1);
delay(1000);

  
  }
  if (value > 40){
  digitalWrite(RELAY_PIN, LOW);

  }

  if (value < 150){
  digitalWrite(RELAY_PIN, HIGH);
  }
  



 Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
  
  // print out data
  //Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
  //Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y));
  //Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accelerometer_z));
  // the following equation was taken from the documentation [MPU-6000/MPU-6050 Register Map and Description, p.30]
  //Serial.print(" | tmp = "); Serial.print(temperature/340.00+36.53);
  //Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
  //Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
  //Serial.print(" | gZ = "); Serial.print(convert_int16_to_str(gyro_z));
  //Serial.println();

  
  
}



void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
