#include<mwc_stepper.h>
#define EN_PIN 3
#define DIR_PIN 2
#define STEP_PIN 5

#define RPM 30
#define PULSE 200
#define ClOCKWISE 1
#define OTHERWISE 0
#define OMDREJNINGER 0.1

MWCSTEPPER nema23(EN_PIN, DIR_PIN, STEP_PIN);

const int switchPin1 = 10; 
const int switchPin2 = 11;

void setup() {

nema23.init();

Serial.begin(9600);
pinMode(switchPin1, INPUT_PULLUP); 
pinMode(switchPin2, INPUT_PULLUP); 


}

void loop() {

int switchState1 = digitalRead(switchPin1); 
int switchState2 = digitalRead(switchPin2); 

if (switchState1 == HIGH) {
  Serial.println("Switch1 is ON");
  
  nema23.set(ClOCKWISE, RPM, PULSE);
  for (size_t i = 0; i < PULSE*OMDREJNINGER; i++){
  nema23.run();
  }
  }

if (switchState2 == HIGH) {
  Serial.println("Switch2 is ON");
  
  nema23.set(OTHERWISE, RPM, PULSE);
  for (size_t i = 0; i < PULSE*OMDREJNINGER; i++){
  nema23.run();
  }
  }

delay(50);


}