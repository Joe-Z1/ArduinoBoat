#include <PS4BT.h>
#include <usbhub.h>
#include <Servo.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

Servo myservo;
USB Usb;
BTD Btd(&Usb);
PS4BT PS4 (&Btd, PAIR);
const int ServPin = 2;
int Speed = 3;
int Direct = 9;


void setup() {
 Serial.begin(9600);
 myservo.attach(2);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));
  
    pinMode(Speed, OUTPUT);
    pinMode(Direct, OUTPUT);
    
}


void loop() {
 Usb.Task();

 if (PS4.connected()){
  PS4.setLed(Green);

  uint16_t PosX = PS4.getAnalogHat(RightHatX);

  PosX = map (PosX, 0, 250, 0, 180);
  myservo.write(PosX);


  int PosY = PS4.getAnalogHat(LeftHatY);
  PosY = map(PosY,0, 255, 0, 255);

   if(PosY < 10){
    
    digitalWrite(Speed, HIGH);
    digitalWrite(Direct, LOW);
        }
        
      else if(PosY > 240){
       
    digitalWrite(Speed, LOW);
    digitalWrite(Direct, HIGH);
      }
    else {
    digitalWrite(Speed, LOW);
    digitalWrite(Direct, LOW);

  }

}

}
