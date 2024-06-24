//PWM
///timer 0 as timer
// timer 1 as counter
//frequency counter

boolean ledState = false;          //determines current state of led
volatile int Correction;
int x = 0;
const int buttonPin = 2;  // the number of the pushbutton pin
int buttonState = 0;  // variable for reading the pushbutton status


//----------------
int pwmVal = 0 ;

//-------------------
volatile unsigned long TotalCounts;
unsigned long TotalCounts2;
volatile unsigned long Timer1overflowCounts;

//-------------------

void setup() {
  
  pinMode(11, OUTPUT);
  //TCCR1A = 0;                      //Reset Timer1 control Registor A

  bitSet(TCCR0A, WGM01);            //set ctc mode

  bitClear(TCCR0B, CS00);         //Set prescaler to 256
  bitClear (TCCR0B, CS01);        //frequency=   122.6(practical)|| 62.5(theoretical)
  bitSet(TCCR0B, CS02);           //time period ( 8.2 ms )

   //Reset Timer1
  TCNT0 = 0;

  OCR0A = 0xFE;   //for X SEC

  TIMSK0 |= (1<<OCIE0A);
  //-----------------------------

  pinMode (13,OUTPUT);
  pinMode(5,INPUT); // reat external pin 5 on chip T1
  //pinMode(5,HIGH);
  // Set up Timer1 to count external pulses on T1 (pin D5)
  //noInterrupts(); // Disable all interrupts

  TCCR1A = 0;     // Clear Timer/Counter Control Register A
  TCCR1B = 0;     // Clear Timer/Counter Control Register B

  TCNT1 = 0;      // Initialize counter value to 0
  TCCR1B |= 0b00000111;   
  OCR1A = 0x00; 
  bitSet(TIMSK1, OCIE1A);
  
  TIMSK1|= 0b00000001;//
  //sei()   ;

  //-----------------------------

  TCCR2B= B01010001; // configure timer2 for PWM on pin 11 


  Serial.begin(9600);
  //bitSet(TIMSK0, OCIE0A); // Enable Timer1 compare interrupt
  //sei();                  // Enable global interrupts
}


void loop() {
  // put your main code here, to run repeatedly:
   //TotalCounts = TCNT1 ;
  // pwmVal=pwmVal+5;
  
  // if (pwmVal>=255)
  // {
  //   pwmVal=0;
  // }
  pwmVal = 50;

  analogWrite(11,pwmVal);
  // Print the pulse count to the serial monitor
  Serial.print("Pulse Count: "); Serial.print(TotalCounts2);
 
  Serial.println();


}


ISR(TIMER0_COMPA_vect)
{
  Correction++; // each time an intrupt happens at the given rate, inc the count
if (Correction >=244) // if the count matches for 1 second procede further
{
    Correction=0; // cler the count
    // if (ledState)                // check if ledstate is true then convert to false
    // {
    //   ledState = false;
    // }
    // else                         // if ledstate is false then this make it true
    // {
    //   ledState = true;
    // }
    //digitalWrite(LED, ledState); //Set LED pin state as per ledState 
    TotalCounts = (Timer1overflowCounts * 65536) + TCNT1 ;
    TotalCounts2=TotalCounts;
    TCNT1=0;
    TotalCounts=0;
    Timer1overflowCounts=0;
}

    
  }

ISR(TIMER1_OVF_vect)
{
  Timer1overflowCounts++; // counter overflows from 65535 to 0, comes here thus this value is Timer1overflowCounts * 65535
}


