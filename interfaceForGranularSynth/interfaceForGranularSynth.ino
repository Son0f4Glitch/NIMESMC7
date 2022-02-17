// ZX Distance and Gesture Sensor
#include <ZX_Sensor.h> // Include Sensor Library
const int ZX_ADDR = 0x10;  // ZX Sensor I2C address
ZX_Sensor zx_sensor = ZX_Sensor(ZX_ADDR);

// LED
int thresholdd = 50;
unsigned long startTime;
int toggle = 1;

int fullRange = 180;

void setup() {
  
   Serial.begin(9600);

// ZX Distance and Gesture Sensor  
  if ( zx_sensor.init() );

// Buttons and LED
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(9, OUTPUT); // Blue
  pinMode(10, OUTPUT); // Green
  pinMode(11, OUTPUT); // Red
  
}


void loop() {
  
//ZX Distance and Gesture Sensor
 if ( zx_sensor.positionAvailable() ) {
    
      uint8_t z_pos = zx_sensor.readZ(); Serial.print("  Z: "); Serial.println(z_pos);

// Buttons
      int rec = analogRead(A1); Serial.print("Record: "); Serial.print(rec);
      int cr = analogRead(A0); Serial.print("  Clear: "); Serial.print(cr);

//Sharp 2Y0A21
      int density = analogRead(A2); Serial.print("  Density: "); Serial.print(density);
      
// LED
    int buttonState = analogRead(A1); 
    int elapsedTime = millis() - startTime;

      if (buttonState < thresholdd) {

        digitalWrite(9, HIGH); 
        startTime = millis();
    
    } else if (elapsedTime >= 2000) {

        toggle = 0;
        digitalWrite(9, LOW);
    
    }  
  }
}
