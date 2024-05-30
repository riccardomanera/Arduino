#include <MPU6050_tockn.h>  // libreria giroscopio
#include <Wire.h> //libreria per permettere all'arduino di comunicare e traferire dati 
#include <Servo.h>

MPU6050 mpu6050(Wire); //
Servo servomotore; //dichiarazione servomotore

int posizione = 0;  // posizione iniziale servomotore

void setup() {
   servomotore.attach(11); //pin a cui si collega il servomotore
  Serial.begin(9600); //porta seriale standard
  // servomotore.attach(porta del servomotore);
    while (!Serial) {
    ; // aspettare collegamento porta seriale
  }
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true); // calibrazione giroscopio  
}

unsigned long t1, dt;
float x, y, z;

void loop() {
  mpu6050.update();
  servomotore.write(posizione); 
  dt = millis() - t1;
  if (dt > 200) {
    t1 = millis();
    x = mpu6050.getAngleX();
    y = mpu6050.getAngleY();
    z = mpu6050.getAngleZ();

    Serial.println("=======================================================");
    Serial.print("temperatura: "); Serial.println(mpu6050.getTemp());
    Serial.print("accelerazione X: "); Serial.print(mpu6050.getAccX());
    Serial.print("accelerazione Y : "); Serial.print(mpu6050.getAccY());
    Serial.print("accelerazione Z : "); Serial.println(mpu6050.getAccZ());

    Serial.print("gyroX : "); Serial.print(mpu6050.getGyroX());
    Serial.print("\tgyroY : "); Serial.print(mpu6050.getGyroY());
    Serial.print("\tgyroZ : "); Serial.println(mpu6050.getGyroZ());

    Serial.print("accelerazione angolare X : "); Serial.print(mpu6050.getAccAngleX());
    Serial.print("accelerazione angolare Y : "); Serial.println(mpu6050.getAccAngleY());

    Serial.print("gyroAngleX : "); Serial.print(mpu6050.getGyroAngleX());
    Serial.print("\tgyroAngleY : "); Serial.print(mpu6050.getGyroAngleY());
    Serial.print("\tgyroAngleZ : "); Serial.println(mpu6050.getGyroAngleZ());

    Serial.print("Angolo X: "); Serial.print(mpu6050.getAngleX());
    Serial.print("Angolo Y: "); Serial.print(mpu6050.getAngleY());
    Serial.print("Angolo Z: "); Serial.println(mpu6050.getAngleZ());
    Serial.println("=======================================================\n");


    if (fabs(y)>100.00) {
       posizione=180;
    } else if (fabs(y)<100.00){
      posizione=0;
    }
  }
}
