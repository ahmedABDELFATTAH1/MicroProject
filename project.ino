#include<Servo.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);
Servo gateEnter;
Servo gateExit;
/////////////
int gateEnterpin=3;
int gateExitpin=5;
int flamepin=1;
int spotssensors[]={A2,A3,A4,A5};
int entersensor=A0;
int exitsensor=A1;
int CounterSpots;
int PrevCounterSpots;
int entergateangle;
int exitgateangle;
int prevsoptCount;
int detectionvalueGates;
int detectionvalueSpots;
int timegateopned;
int timegateclosed;
////////////////
void setup() {
gateEnter.attach(gateEnterpin);
gateExit.attach(gateExitpin);
pinMode(flamepin,INPUT);
pinMode(entersensor,INPUT);
pinMode(exitsensor,INPUT);
for(int i=0;i<4;i++)
{  
   pinMode(spotssensors[i],INPUT); 
}
 timegateopned=1000;
 timegateclosed=1000;
 entergateangle=0;
 exitgateangle=90;
 detectionvalueGates=300;
 detectionvalueSpots=500;
 lcd.begin(16,2);
 lcd.clear();
 lcd.setCursor(0,0);
 Serial.begin(9600); 
}

void loop() { 
  prevsoptCount=CounterSpots;
  timegateopned=millis()-timegateopned; 
   timegateclosed=millis()-timegateclosed;      
  CounterSpots=0; // number of parked places
if(!carDetection(entersensor,detectionvalueGates)&&timegateopned>=1000)  // if no car is near to enter gate
{      
      entergateangle=90;
      gateEnter.write(entergateangle);        
  
}

if(!carDetection(exitsensor,detectionvalueGates)&&timegateclosed>=1000)   // if no car is near to exit gate
{       
        exitgateangle=0;
        gateExit.write(exitgateangle);             
  
}
for(int i=0;i<4;i++)
  {    
    if(carDetection(spotssensors[i],detectionvalueSpots))
    {      
      CounterSpots++;        
    }   
  } 
  if(CounterSpots!=prevsoptCount)
  {
    if(CounterSpots==4){   
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Parking is FULL");    
    }
    else{      
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Available Spots");
      
      }   
    
   }
   
  
//  if there is a near car to enter AND there is available place
   if(carDetection(entersensor,detectionvalueGates)&&CounterSpots<4)
   {
    //  digitalWrite(ledspin,HIGH);
        openEnterGate();  // open enter gate
      
   } 
//  if there is a near car to exit gate
    if(carDetection(exitsensor,detectionvalueGates))
   {
     // digitalWrite(ledspin,LOW); 
     openExitGate();  // open exit gate    
   } 
}

// end void loop
bool carDetection(int sensor,int detectvalue)
{
 return (analogRead(sensor)<detectvalue); 
}


void openEnterGate()
{  
    for(entergateangle;entergateangle>0;entergateangle-=10)
    {      
      gateEnter.write(entergateangle);           
      delay(10);   
       if(carDetection(exitsensor,detectionvalueGates))
       {
        openboth();
        }      
    }   
    
        timegateopned=millis();
 } 

void openExitGate()
{ 
 for(exitgateangle;exitgateangle<90;exitgateangle+=10)
    {        
        gateExit.write(exitgateangle);               
        delay(10); 
       if(carDetection(entersensor,detectionvalueGates))
       {
        openboth();
       }         
    } 
    timegateclosed=millis();        
    
}

void openboth()
{
  while(exitgateangle<90&&entergateangle>0)
  {
     gateExit.write(exitgateangle);   
      gateEnter.write(entergateangle);
       exitgateangle+=10;
       entergateangle-=10;   
  } 
    timegateclosed=millis();
    timegateopned=millis();  
}


bool trueFlame()
{
 return (digitalRead(flamepin));    
}

void flameLogic()
{  
gateEnter.write(90);
gateExit.write(0);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("FIRE !!");
lcd.setCursor(1,0);
lcd.print("RUN FOREST RUN");
while(trueFlame())
{     
//   digitalWrite(ledspin,HIGH);  
   delay(200);  
  // digitalWrite(ledspin,LOW); 
   delay(200);
}
 
}
