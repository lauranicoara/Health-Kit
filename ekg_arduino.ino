// Connect LO+ to PD7 pin
#define LO_MINUS PD6
// Connect LO- to PD6 pin
#define LO_PLUS PD7
// Connect output to A0 pin
#define OUTPUT_ECG A0

// Flags for LO+ and LO- interrupts
volatile bool flag_lo_m = 0;
volatile bool flag_lo_p = 0;

// Pin Change Interrupt 2
ISR(PCINT2_vect) {
  if ((PIND & (1 << LO_MINUS)) == 0) {
     flag_lo_m = 1;
  } else if ((PIND & (1 << LO_MINUS)) != 0) {
    flag_lo_m = 0;
  }
  
  if ((PIND & (1 << LO_PLUS)) == 0) {
     flag_lo_p = 1;
  } else if ((PIND & (1 << LO_PLUS)) != 0) {
    flag_lo_p = 0;
  }
}

void setup_interrupts() {
  cli();
 
  // Set pins as input
  DDRD &= ~(1 << LO_MINUS) & ~(1 << LO_PLUS);
 
  // Activate the interrupt vector for Pin Change Interrupt 2
  PCICR |= (1 << PCIE2);
   
  // Set the mask to activate interrupts on the required pins
  PCMSK2 |= (1 << PCINT22) | (1 << PCINT23);
 
  sei();
}

void setup() {
  // initialize the serial communication
  Serial.begin(9600);
  setup_interrupts();
}

void readECG() {
  // Only when both flags are set, read the analog value
  if (flag_lo_m == 1 && flag_lo_p == 1) {
    Serial.println(analogRead(OUTPUT_ECG));
  }
}

void loop() {
  readECG();
  delay(19);
}
