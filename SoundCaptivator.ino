#define SENSOR 0 // define sensor as pin Analog 0 
const int RED = 11; // Configure Pin 11 as red LED output
const int YELLOW = 12; // Configure Pin 12 as yellow LED output
const int BLUE = 13; // Configure Pin 13 as blue LED output
const int sampleWindow = 50;  //define constant of type int as sampleWindow with a value of 50
unsigned int sample; // declare unsigned int sample with value 0

void setup() { 
  Serial.begin(9600); //  
  pinMode (SENSOR, INPUT); // configure pin A0 as input 
  pinMode(BLUE, OUTPUT);  // configure pin 13 as output 
  pinMode(YELLOW, OUTPUT);  // configure pin 12 as output 
  pinMode(RED, OUTPUT);  // configure pin 11 as output 
} 

void loop() { 
unsigned long startMillis= millis();                   // Start of sample window at current time 
float sound = 0;                                       // declare float soundlevel 
unsigned int signalMin = 0;                            // define unsigned int signalMin as minimum value 
unsigned int signalMax = 1024;                         // define unsigned int signalMax as maximum value  
 // collect data for 50 mS by sampling sound frequency
while (millis() - startMillis < sampleWindow) // While current time - statrMillis time is lesser then sample window(50ms)
   { 
     sample = analogRead(SENSOR);                    // get analog values from microphone 
      if (sample < 1024)                                  // Discard Misleading Readings 
      { 
         if (sample > signalMin) 
         { 
            signalMin = sample;                           // save just the min levels 
         } 
         else if (sample < signalMax)               
         { 
            signalMax = sample;                           // save just the max levels 
         }}} 
  sound = signalMin - signalMax;                    // sound amplitude 
  int db = map(sound,20,900,39.5,100);           // calibrate for deciBels 
  Serial.print("Sound level: "); 
  Serial.print(db); 
  Serial.println("dB"); 
    if(db < 40) {  // if sound level is less then 40 Decibels, then light blue is on, lights orange and Red are off. 
      digitalWrite(BLUE, LOW);   
      digitalWrite(YELLOW, HIGH);   
      digitalWrite(RED, HIGH);   
   }   
   else if(db > 40 and db < 90) {  // if sound level is greater then 40 Db and lesser then 90 Decibels, then light blue and orange are on, and Red are off. 
      digitalWrite(BLUE, LOW);   
      digitalWrite(YELLOW, LOW);   
      digitalWrite(RED, HIGH);   
   }   
  else if (db > 90) {  // if sound level is greater then 90 Db, all lights will be on. 
      digitalWrite(BLUE, LOW);   
      digitalWrite(YELLOW, LOW);   
      digitalWrite(RED, LOW);   
   }   
  delay(1000); //
}
