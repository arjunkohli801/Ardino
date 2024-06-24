//Stepper Countrol 
// motor least count is 0.9* per pulse at half step step setting

#define LED1 10
#define LED2 9
volatile unsigned long TotalCounts;

void setup() {
  
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT); // Anti-clockwise
  pinMode(9, OUTPUT);// Clockwise 
 
  Serial.begin(9600);
  //bitSet(TIMSK0, OCIE0A); // Enable Timer1 compare interrupt
  //sei();                  // Enable global interrupts
}


void loop()
 {
    for( int j = 0; j <= 400; j++) 
    {

    delay(1);
    digitalWrite(LED1, HIGH);

    delay (1);
    digitalWrite(LED1, LOW);

    }


  delay (1000);


    for( int j = 0; j <= 400; j++) 
    {

    delay(1);
    digitalWrite(LED2, HIGH);

    delay (1);
    digitalWrite(LED2, LOW);

    }
    

  delay (1000);
 
}


