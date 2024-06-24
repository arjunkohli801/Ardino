// Counter using Timer 1 as counter
// counting external pulses
// LEO 10.06.2024
// working 10.06.2024 

#define LED 13
boolean ledState = false;
volatile unsigned int TotalCounts= 0;
volatile unsigned int Timer1overflowCounts;


void setup() 
{
  Serial.begin(9600); // Initialize serial communication for debugging
  pinMode (13,OUTPUT);
  pinMode(5,INPUT); // reat external pin 5 on chip T1
  //pinMode(5,HIGH);

//---------------------------------------------------------
  // Set up Timer1 to count external pulses on T1 (pin D5)
  //noInterrupts(); // Disable all interrupts

  TCCR1A = 0;     // Clear Timer/Counter Control Register A
  TCCR1B = 0;     // Clear Timer/Counter Control Register B

  TCNT1 = 0;      // Initialize counter value to 0
  TCCR1B |= 0b00000111;   
  OCR1A = 0x00; 
  bitSet(TIMSK1, OCIE1A);
  
  TIMSK1|= 0b00000001;//
  sei()   ;


//---------------------------------------------------------



 

}

void loop() {
  // Read the current value of the timer counter

  TotalCounts = TCNT1 ;
 

  // Print the pulse count to the serial monitor
  Serial.print("Pulse Count: "); Serial.print(TCNT1);Serial.print("    Timer overflow Count: ");Serial.print(Timer1overflowCounts);
 
  Serial.println();

  


}

ISR (TIMER1_COMPA_vect)
  {
    Timer1overflowCounts=Timer1overflowCounts+1;

    //--------------------------------------

    if (ledState)                // check if ledstate is true then convert to false
    {
      ledState = false;
    }
    else                         // if ledstate is false then this make it true
    {
      ledState = true;
    }
    digitalWrite(LED, ledState); //Set LED pin state as per ledState 


    //---------------------------------------
  }
