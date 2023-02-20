#include <Wire.h>
#include <Adafruit_AMG88xx.h>
#include <NewPing.h>

#include <SoftwareSerial.h>
int tx = 10;
int rx = 11;

SoftwareSerial bluetooth(tx, rx);

#define trig 7
#define echo 6
#define max 400

NewPing sonar(trig, echo, max);

Adafruit_AMG88xx amg;

float pixels[AMG88xx_PIXEL_ARRAY_SIZE];

void setup() {
    Serial.begin(9600);
    pinMode(13, OUTPUT);
    bluetooth.begin(9600);

    bool status;
    
    // default settings
    status = amg.begin();
    if (!status) {
        Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
        while (1);
    }
    
    Serial.println("-- Pixels Test --");

    delay(100);
}


void loop() { 

    amg.readPixels(pixels);

    int x = 0;

    for(int i=1; i<=AMG88xx_PIXEL_ARRAY_SIZE; i++){
      x += pixels[i-1];
    }

    if (x > 1700 && x < 2500) {
          Serial.println("Human!");
          int uS = sonar.ping(); 
          bluetooth.write(uS / US_ROUNDTRIP_CM); 
          delay(99);
    } 
 }




