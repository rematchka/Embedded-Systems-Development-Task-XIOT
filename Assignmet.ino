#include <math.h>
const int B=4275; // B value of the thermistor
const long R0 = 100000; // R0 = 100k
const int pinTempSensor = A5; // Grove - Temperature Sensor connect to A5
const int interruptpin=2;
const int ledpin=13;
unsigned long interval=3000;
unsigned long prevMillis=0;
bool currstate=false;
bool prevsate=false;

void setup() {
  Serial.begin(9600);
  pinMode(ledpin,OUTPUT);
  pinMode(interruptpin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptpin),change_state,CHANGE);
  // put your setup code here, to run once:

}
void change_state()
{
  Serial.print("Pressed\n" );
  
 
 //   Serial.print("LED OFF\n" );
    
   currstate=true;
      // Serial.print("LED ON" );
    
  digitalWrite(ledpin,true);
  }

void loop() {
  // put your main code here, to run repeatedly:
 //  currstate=false;
   if(currstate!=prevsate)
   {
      if(currstate==false)
      {
         Serial.print("LED OFF\n" );
         }
      else {
             Serial.print("LED ON\n" );
        }
       prevsate=currstate;
    }
  
  unsigned long currentMillis=millis();
  if((unsigned long)(currentMillis-prevMillis)>=interval)
  { int a = analogRead(pinTempSensor );
   float R = 1023.0/((float)a)-1.0;
   R = 100000.0*R;
 //convert to temperature via datasheet ;
  float temperature=1.0/(log(R/100000.0)/B+1/298.15)-273.15;
  Serial.print("temperature = ");
  Serial.println(temperature);
  }
currstate=false;
digitalWrite(ledpin,false);
}
