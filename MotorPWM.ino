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
float TotalCounts2;
volatile unsigned long Timer1overflowCounts;
volatile unsigned long sp ;
volatile unsigned int arjunstime ;

//-------------------

//PID parameters
float proportional ;
float integral;
float correction;
float error;

//------------------

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

  // Set up Timer1 to count external pulses on T1 (pin D5)
  //noInterrupts(); // Disable all interrupts

  TCCR1A = 0;     // Clear Timer/Counter Control Register A
  TCCR1B = 0;     // Clear Timer/Counter Control Register B

  TCNT1 = 0;      // Initialize counter value to 0
  TCCR1B |= 0b00000111;   
  OCR1A = 0x00; 
  bitSet(TIMSK1, OCIE1A);
  TIMSK1|= 0b00000001;

  //sei()   ;

  //-----------------------------

  TCCR2B= B01010001; // configure timer2 for PWM on pin 11 


  Serial.begin(9600);
  //bitSet(TIMSK0, OCIE0A); // Enable Timer1 compare interrupt
  //sei();                  // Enable global interrupts
}


void loop()
 {
 if ( arjunstime<50)
 {
  sp=0;
 }
 if (arjunstime >  50 && arjunstime < 200)
 {
  sp=1000;
 
 }
 if (arjunstime >200 && arjunstime <300)
 {
  sp=500;
 }
 if (arjunstime > 300 && arjunstime <400)
 {
  sp=0;
  arjunstime=0;
 }

  // Print the pulse count to the serial monitor
  Serial.print("Pulse Count: "); Serial.print(TotalCounts2);Serial.print(" Pulse Width "); Serial.print(pwmVal);Serial.print(" Timer "); Serial.print(arjunstime);Serial.print(" Error "); Serial.print(error);
 
  Serial.println();


}


ISR(TIMER0_COMPA_vect)
{
  Correction++; // each time an intrupt happens at the given rate, inc the count

if (Correction >=24) // if the count matches for 0.1 second procede further
{
    arjunstime++;
    
    Correction=0; // cler the count
   
    TotalCounts = (Timer1overflowCounts * 65536) + TCNT1 ;
    TotalCounts2=TotalCounts;

    long error = sp - TotalCounts2;

    proportional = error*0.1;

    integral += error*0.01 ;

    correction = proportional + integral*0.01; 



    TCNT1=0;
    TotalCounts=0;
    Timer1overflowCounts=0;
   
    

   if (TotalCounts2 > sp)
   {
    pwmVal=pwmVal+correction;
   }
   
   if (TotalCounts2 < sp)
   {
      pwmVal=pwmVal+correction;
   }

   if(pwmVal >= 254)
   {
    pwmVal=254;
   }

   if(pwmVal <3)
   {

    pwmVal = 3;

   }

  analogWrite(11,pwmVal);
} 
  }

ISR(TIMER1_OVF_vect)
{
  Timer1overflowCounts++; //  ccounter overflows from 65535 to 0,omes here thus this value is Timer1overflowCounts * 65535
}


