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

long currentPos = 0;

long currentPosX = 0;
long currentPosY = 0;

const long Pos1 = 200;
const long Pos2 = 300;
const long Pos3 = 100;




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
//sætter positionerne til 0
int homeState = digitalRead(homePin);

if (homeState == LOW){
  currentPosX = 0;
  currentPosY = 0;
  Serial.println(currentPosX);
  Serial.println(currentPosY);
}


//IR fjernbetjening til test
if (IrReceiver.decode()) {
  //Serial.print(IrReceiver.decodedIRData.command);
  switch (IrReceiver.decodedIRData.command) {
      case 12:
      gotopos(400,400, "en");
      break;
      case 24:
      gotopos(300,200, "to" );
      break;
      case 22:
      gotopos(0,0, "tre");
      break;
    }
  IrReceiver.resume(); 
  }
delay(50);
}

//funktion til at bevæge stepper motorene til en position. POSX er stepper motor 1 og POSY er stepper moto 2
void gotopos(int POSX, int POSY, const char* tekst){
  Serial.print(tekst);
  //x step motor
  //if statementet tjekker efter om positionen af motoren er større eller mindre end den position den skal bevæge sig hen mod. Hvis den er mindre skal den bevæge sig med uret ellers skal den bevæge sig mod uret
  if(currentPosX < POSX){
    stepmotor1.set(ClOCKWISE, RPM, PULSE);
    for (size_t i = 0; i < POSX-currentPosX; i++){
      stepmotor1.run();
    }
  }else{
    stepmotor1.set(OTHERWISE, RPM, PULSE);
    for (size_t i = 0; i < currentPosX-POSX; i++){
      stepmotor1.run();
    }
  }
  //y step motor
  //samme som ved den første if statment bare for motor y
  if(currentPosY < POSY){
    stepmotor2.set(ClOCKWISE, RPM, PULSE);
    for (size_t i = 0; i < POSY-currentPosY; i++){
      stepmotor2.run();
    }
  }else{
    stepmotor2.set(OTHERWISE, RPM, PULSE);
    for (size_t i = 0; i < currentPosY-POSY; i++){
      stepmotor2.run();
    }
  }
  //ændre positionen til den nye og logger positionen
  currentPosX = POSX;
  currentPosY = POSY;
  Serial.print(currentPosX);
  Serial.print(currentPosY);
}


