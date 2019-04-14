#include<Servo.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);
Servo gateEnter;
Servo gateExit;
////////////
int gateEnterpin=3;
int gateExitpin=5;
int ledpins[]={1,2,3,4,5};//will be modified
int flamepin=1;
int spotssensors[]={A2,A3,A4,A5};
int entersensor=A0;
int exitsensor=A1;
int CounterSpots;
int entergateangle;
int exitgateangle;
int detectionvalueGates;
int detectionvalueSpots;
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
   pinMode(ledpins[i],OUTPUT);  
 
}
 pinMode(ledpins[4],OUTPUT); 
 CounterSpots=0;  
 entergateangle=1;
 exitgateangle=1;
 detectionvalueGates=1010;
 detectionvalueSpots=1010;
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("HELLO PARKING");
 delay(2000);
}



void loop() {
  
CounterSpots=0;
if(!carDetection(entersensor,detectionvalueGates))
{
  gateEnter.write(0);
}
if(!carDetection(exitsensor,detectionvalueGates))
{
  gateExit.write(0);
  
}
  lcd.clear();  
  lcd.setCursor(0,0); 
  String AvailableSpots=""; 
  for(int i=0;i<4;i++)
  {
    int sensorvalue=analogRead(spotssensors[i]);    
    if(carDetection(spotssensors[i],detectionvalueSpots))
    {
      CounterSpots++;
      digitalWrite(ledpins[i],HIGH);     
      
    }
    else{      
           digitalWrite(ledpins[i],LOW);   
           AvailableSpots+=String(i+1)+",";   
      }     
  }

  if(CounterSpots<4)
  {
    
    lcd.print("Available spots");
    lcd.setCursor(1,0);    
    lcd.print(AvailableSpots);
    
  }
  else{   
     lcd.print("Parking is FULL");    
    } 

   if(carDetection(entersensor,detectionvalueGates)&&CounterSpots<4)
   {
        openEnterGate();
   } 
    
    if(carDetection(exitsensor,detectionvalueGates)&&CounterSpots<4)
   {
      
     openExitGate();
  
   } 
}



void openEnterGate()
{
    for(entergateangle;entergateangle<=90;entergateangle+=10)
    {
      gateEnter.write(entergateangle);                
      delay(100);
      if(carDetection(exitsensor,detectionvalueGates))
      {
        openBoth();        
      }
      
    }     
     
 } 

void openExitGate()
{
  
 for(exitgateangle;exitgateangle<=90;exitgateangle+=10)
    {
        gateExit.write(exitgateangle);               
        delay(100);
     if(carDetection(entersensor,detectionvalueGates))
      {
        openBoth();        
      }     
    }    
   
}

void openBoth()
{  

while(exitgateangle<90||entergateangle<90)
{
  if(exitgateangle<90)
  {
    exitgateangle+=10;
    gateExit.write(exitgateangle); 
  }
   if(entergateangle<90)
  {
    entergateangle+=10;
    gateEnter.write(exitgateangle); 
  } 
  
}  
  
}

bool carDetection(int sensor,int detectvalue)
{
 return (analogRead(sensor)<detectvalue); 
}


bool checkFlame()
{
 return (digitalRead(flamepin));    
}

void flameLogic()
{  
//ba3deen b2a ;
  
}
