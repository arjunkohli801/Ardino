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


int AZstateCC = 1;
int AZstateACW = 1;
int EstateCC = 1;
int EstateACW = 1;

void setup() {
  // put your setup code here, to run once:

  //OUTPUT PINS
  pinMode(9, OUTPUT); // Anti-clockwise
  pinMode(8, OUTPUT); // Clockwise 
  pinMode(7, OUTPUT); // Anti-clockwise
  pinMode(6, OUTPUT);  // Clockwise 

  //INPUT PINS
  pinMode(5, INPUT); // Anti-clockwise
  pinMode(4, INPUT); // Clockwise 
  pinMode(3, INPUT); // Anti-clockwise
  pinMode(2, INPUT); // Clockwise 

  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);

  digitalWrite(AZCC, LOW);
  digitalWrite(AZACW, LOW);
  digitalWrite(EUP, LOW);
  digitalWrite(EDOWN, LOW);

  Serial.begin(9600);

}


void loop() {
  // put your main code here, to run repeatedly:
 AZstateCC = digitalRead(AZCWsw);
 AZstateACW = digitalRead(AZACWsw);
 EstateCC = digitalRead(EUPsw);
 EstateACW = digitalRead(EDOWNsw);


//AZ clockwise
  if(AZstateCC == LOW) 
  {
    //digitalWrite(AZCC, LOW);
    delay(1);
    digitalWrite(AZCC, LOW);

    delay (1);
    digitalWrite(AZCC, HIGH);
  }

  else {
    digitalWrite(AZCC, LOW);
  }

//AZ Anti clockwise 
   if(AZstateACW == LOW ) 
  {
    delay(1);
    digitalWrite(AZACW, LOW);

    delay (1);
    digitalWrite(AZACW, HIGH);

  }
  else{
    digitalWrite(AZACW, LOW);
  }

   if(EstateCC == LOW ) 
  {
    
    delay(5);
    digitalWrite(EUP, LOW);

    delay (5);
    digitalWrite(EUP, HIGH);

  }
  else{
    digitalWrite(EUP, LOW);
  }

  if(EstateACW == LOW ) 
  {
    delay(5);
    digitalWrite(EDOWN, LOW);

    delay (5);
    digitalWrite(EDOWN, HIGH);
  }
  else {
    digitalWrite(EDOWN, LOW);
  }

}