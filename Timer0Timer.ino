// timer0 as timer
//led will flash every 1 second in the interrupt routine 
//LEO 10-6-2024
// tested working

#define LED 13
boolean ledState = false;          //determines current state of led
volatile int Correction;
int x = 0;
const int buttonPin = 2;  // the number of the pushbutton pin
int buttonState = 0;  // variable for reading the pushbutton status

void setup() {
  pinMode(LED, OUTPUT);
  //TCCR1A = 0;                      //Reset Timer1 control Registor A
                                                    
  bitSet(TCCR0A, WGM01);            //set ctc mode


  //bitSet(TCCR0B, CS00);           //Set prescaler to 1024
 // bitClear (TCCR0B, CS01);        //frequency= 30.53(practical)||15625(theoretical)
 // bitSet(TCCR0B, CS02);           //time period ( 32.80 ms )

  bitClear(TCCR0B, CS00);         //Set prescaler to 256
  bitClear (TCCR0B, CS01);        //frequency=   122.6(practical)|| 62.5(theoretical)
  bitSet(TCCR0B, CS02);           //time period ( 8.2 ms )

  // bitSet(TCCR0B, CS00);           //Set prescaler to 64
  // bitSet(TCCR0B, CS01);          //frequency= 490.2 (practical)|| 250 (theoretical)
  // bitClear(TCCR0B, CS02);        //time period ( 2.040 ms )

 // bitClear(TCCR0B, CS00);           //Set prescaler to 8
  //bitSet(TCCR0B, CS01);          //frequency= 3.9KHz (practical)|| 2 (theoretical)
  //bitClear(TCCR0B, CS02);        //time period ( 256.0 um )

  // To generte 1 second
  // 1000/2.040 = 490.196078 times
  // 1000/8.2 = 121.95 times
 // 1000/32.8 = 30.4878049






  //Reset Timer1
  TCNT0 = 0;

  OCR0A = 0xFE;   //for X SEC

  TIMSK0 |= (1<<OCIE0A);

  Serial.begin(9600);
  //bitSet(TIMSK0, OCIE0A); // Enable Timer1 compare interrupt
  sei();                  // Enable global interrupts
}

void loop() {
  // put your main code here, to run repeatedly:
  

}

ISR(TIMER0_COMPA_vect)
{

Correction++; // each time an intrupt happens at the given rate, inc the count
if (Correction >=121) // if the count matches for 1 second procede further
{
    Correction=0; // cler the count
    if (ledState)                // check if ledstate is true then convert to false
    {
      ledState = false;
    }
    else                         // if ledstate is false then this make it true
    {
      ledState = true;
    }
    digitalWrite(LED, ledState); //Set LED pin state as per ledState 
}


}