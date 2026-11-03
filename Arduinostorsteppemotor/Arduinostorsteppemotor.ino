#include<mwc_stepper.h>
//Pins brugt af step motoren
#define EN_PIN 3
#define DIR_PIN 2
#define STEP_PIN 5
//RPM = Hastighed, Pulse skal matche step motoren, Omdreninger = gir sig selv
#define RPM 30
#define PULSE 200 
#define ClOCKWISE 1
#define OTHERWISE 0
#define OMDREJNINGER 0.1

// ikke nema23 er vist bare en variabel så det kan være den bliver skiftet
MWCSTEPPER nema23(EN_PIN, DIR_PIN, STEP_PIN);

//Definere pins der bliver brugt til knapper: Ikke relævant udenfor test kan fjernes
const int switchPin1 = 10; 
const int switchPin2 = 11;

void setup() {
//tilføjer en verdi til variablen
nema23.init();

//Sætter de pins til knapperne op - til test kan fjernes
Serial.begin(9600);
pinMode(switchPin1, INPUT_PULLUP); 
pinMode(switchPin2, INPUT_PULLUP); 
}

void loop() {
//læser værdien af de pins knappen er sat til(HIGH eller LOW)
int switchState1 = digitalRead(switchPin1); 
int switchState2 = digitalRead(switchPin2); 

//switchstate ==HIGH skal skiftes ud med de rigtige kriterier
if (switchState1 == HIGH) {
  // ikke relævant udenfor test
  Serial.println("Switch1 is ON");
  
  //sætter værdier ind i variablen og for løkken kører den x antal gange rundt
  nema23.set(ClOCKWISE, RPM, PULSE);
  for (size_t i = 0; i < PULSE*OMDREJNINGER; i++){
  nema23.run();
  }
  }

//samme som if statement før bare den anden retning
if (switchState2 == HIGH) {
  Serial.println("Switch2 is ON");
  
  nema23.set(OTHERWISE, RPM, PULSE);
  for (size_t i = 0; i < PULSE*OMDREJNINGER; i++){
  nema23.run();
  }
  }
//delay for at undgå spass
delay(50);


}