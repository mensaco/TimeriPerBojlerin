double second = 329670.32967;
long LP = (long) (10 * second);
long HP = (long) (1 * second);

long lowPeriod = LP;
long highPeriod = HP;
bool reset = false;
bool isOn = false;
int pwm = 200;

void onInterrupt(){
  reset = true;
}

void turnOn(){
  digitalWrite(LED_BUILTIN, HIGH);
  analogWrite(PD3, pwm);
  delay(10);
}

void turnOff() {
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  analogWrite(PD3, 0);
  delay(10);
}

void ensureReset(){
  if(reset == true){ // interrupt request
    reset = false; 
    lowPeriod = LP;
    highPeriod = HP;
    turnOff(); 
    isOn = false;
  }
}

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PD3,OUTPUT);
  turnOff();
  reset = false;
  attachInterrupt(digitalPinToInterrupt(2),onInterrupt,RISING); 
}

// the loop function runs over and over again forever
void loop() {  
  if(lowPeriod < 0) {
    lowPeriod = 0;
  }
  ensureReset();  
  
  if(lowPeriod > 0) { // derisa lowPeriod > 0
    isOn = false;
    lowPeriod--;    
  } 
  else {   // lowPeriod == 0 
    
    if(highPeriod > 0) { // lowPeriod == 0 and highPeriod > 0
      if(isOn == false){ 
        isOn = true;
        turnOn();
      }
      highPeriod--;      
    }
    else { // highPeriod == 0 and lowPeriod == 0
      isOn = false;
      turnOff();
    }
  }
     
}
