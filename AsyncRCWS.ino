//input pins
#define EDOWNsw 5
#define EUPsw 4
#define AZACWsw 3
#define AZCWsw 2

//output pins
#define EDOWN 9
#define EUP 8
#define AZACW 7
#define AZCC 6


unsigned long previousMillisAZCC = 0;
unsigned long previousMillisAZACW = 0;
unsigned long previousMillisEUP = 0;
unsigned long previousMillisEDOWN = 0;

const long intervalAZ = 1; // Interval for AZ motor
const long intervalE = 1; // Interval for E motor


int AZstateCC = 1;
int AZstateACW = 1;
int EstateCC = 1;
int EstateACW = 1;

void setup() {
  // put your setup code here, to run once:

  //OUTPUT PINS
  pinMode(9, OUTPUT); // UP
  pinMode(8, OUTPUT); // DOWN 
  pinMode(7, OUTPUT); // Anti-clockwise
  pinMode(6, OUTPUT);  // Clockwise 

  // //INPUT PINS
  // pinMode(5, INPUT); // UP
  // pinMode(4, INPUT); // DOWN 
  // pinMode(3, INPUT); // Anti-clockwise
  // pinMode(2, INPUT); // Clockwise 

  pinMode(5, INPUT_PULLUP);// UP
  pinMode(4, INPUT_PULLUP);// DOWN 
  pinMode(3, INPUT_PULLUP);// Anti-clockwise
  pinMode(2, INPUT_PULLUP);//Clockwise

  digitalWrite(AZCC, LOW);
  digitalWrite(AZACW, LOW);
  digitalWrite(EUP, LOW);
  digitalWrite(EDOWN, LOW);
 
  Serial.begin(9600);

}


void loop() {

unsigned long currentMillis = millis();

  // put your main code here, to run repeatedly:
 AZstateCC = digitalRead(AZCWsw);
 AZstateACW = digitalRead(AZACWsw);
 EstateCC = digitalRead(EUPsw);
 EstateACW = digitalRead(EDOWNsw);


//AZ clockwise
  if(AZstateCC == LOW) 
  {
    //digitalWrite(AZCC, LOW);
      if (currentMillis - previousMillisAZCC >= intervalAZ) 
      {
      previousMillisAZCC = currentMillis;
      digitalWrite(AZCC, !digitalRead(AZCC));
    }
  }
  else {
    digitalWrite(AZCC, LOW);
  }



//AZ Anti clockwise 
   if(AZstateACW == LOW) 
  {
     if (currentMillis - previousMillisAZACW >= intervalAZ) 
     {
      previousMillisAZACW = currentMillis;
      digitalWrite(AZACW, !digitalRead(AZACW));
    }
  }
  else{
    digitalWrite(AZACW, LOW);
  }

//ELEVATION  UP 
   if(EstateCC == LOW) 
  {
 if (currentMillis - previousMillisEUP >= intervalE) 
    {
      previousMillisEUP = currentMillis;
      digitalWrite(EUP, !digitalRead(EUP));
    }
  }
  else{
    digitalWrite(EUP, LOW);
  }

//ELEVATION DOWN
  if(EstateACW == LOW ) 
  {
    if (currentMillis - previousMillisEDOWN >= intervalE)
    {
      previousMillisEDOWN = currentMillis;
      digitalWrite(EDOWN, !digitalRead(EDOWN));
    }
  }
  else {
    digitalWrite(EDOWN, LOW);
  }

}