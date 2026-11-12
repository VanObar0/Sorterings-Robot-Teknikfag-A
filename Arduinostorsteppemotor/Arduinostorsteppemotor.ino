#include<mwc_stepper.h>
#include <IRremote.h>
//Pins brugt af step motoren
#define EN_PIN 47
#define DIR_PIN 49
#define STEP_PIN 45
#define EN_PIN2 39
#define DIR_PIN2 37
#define STEP_PIN2 35
//RPM = Hastighed, Pulse skal matche step motoren, Omdreninger = gir sig selv
#define RPM 30
#define PULSE 200 
#define ClOCKWISE 1
#define OTHERWISE 0
#define OMDREJNINGER 0.1

#define IR_RECEIVE_PIN 5

//Retningen for at komme tilbage til 0
#define HOMEDIR OTHERWISE

// ikke stepmotor1 er vist bare en variabel så det kan være den bliver skiftet
MWCSTEPPER stepmotor1(EN_PIN, DIR_PIN, STEP_PIN);
MWCSTEPPER stepmotor2(EN_PIN2, DIR_PIN2, STEP_PIN2);

//Definere pins der bliver brugt til knapper: Ikke relævant udenfor test kan fjernes
const int homePin = 53;

const long Pos1 = 200;

long currentPos = 0;


void setup() {
//tilføjer en verdi til variablen
stepmotor1.init();
stepmotor2.init();
//Sætter de pins til knapperne op - til test kan fjernes
Serial.begin(9600); 
pinMode(homePin, INPUT_PULLUP);
IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

}

void loop() {






int homeState = digitalRead(homePin);

if (homeState == LOW){
  currentPos = 0;
  Serial.println(currentPos);
}



if (IrReceiver.decode()) {
  //Serial.print(IrReceiver.decodedIRData.command);
  switch (IrReceiver.decodedIRData.command) {
      case 67:
      Serial.println("Switch2 is ON");
      stepmotor1.set(ClOCKWISE, RPM, PULSE);
      stepmotor2.set(ClOCKWISE, RPM, PULSE);
      for (size_t i = 0; i < PULSE*OMDREJNINGER; i++){
        stepmotor1.run();
        stepmotor2.run();
        }
      currentPos += (PULSE*OMDREJNINGER);
      Serial.println(currentPos);
      break;
      case 68:
      Serial.println("Switch2 is ON");
      stepmotor1.set(OTHERWISE, RPM, PULSE);
      stepmotor2.set(OTHERWISE, RPM, PULSE);
      for (size_t i = 0; i < PULSE*OMDREJNINGER; i++){
        stepmotor1.run();
        stepmotor2.run();
        }
      currentPos -= (PULSE*OMDREJNINGER);
      Serial.println(currentPos);
      break;
      
      case 12:
      // ikke relævant udenfor test
      Serial.println("Switch1 is ON");
       if(currentPos < Pos1){
        stepmotor1.set(ClOCKWISE, RPM, PULSE);
        stepmotor2.set(ClOCKWISE, RPM, PULSE);
        for (size_t i = 0; i < Pos1-currentPos; i++){
          stepmotor1.run();
          stepmotor2.run();
        }
      }else{
        stepmotor1.set(OTHERWISE, RPM, PULSE);
        stepmotor2.set(OTHERWISE, RPM, PULSE);
        for (size_t i = 0; i < currentPos-Pos1; i++){
          stepmotor1.run();
          stepmotor2.run();
        }
      }
      //sætter værdier ind i variablen og for løkken kører den x antal gange rundt
      currentPos = Pos1;
      Serial.println(currentPos);
      break;
      
    }
  IrReceiver.resume(); 
  }
delay(50);
}



