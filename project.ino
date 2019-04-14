#include<Servo.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);
Servo gateEnter;
Servo gateExit;
////////////
int gateEnterpin=3;
int gateExitpin=5;
int ledpins[]={,2,3,4,5};
int flame=1;
int spotssensors[]={A2,A3,A4,A5};
int entersensor=A0;
int exitsensor=A1;
int CounterSpots;
////////////////
void setup() {
gateEnter.attach(gateEnterpin);
gateExit.attach(gateExitpin);
pinMode(flame,INPUT);
pinMode(entersensor,INPUT);
pinMode(exitsensor,INPUT);
for(int i=0;i<4;i++)
{
  
   pinMode(spotssensors[i],INPUT);
   pinMode(ledpins[i],OUTPUT);  
 
}
 pinMode(ledpins[4],OUTPUT); 
 CounterSpots=0;  // used places
}

void loop() {
  
  for(int i=0;i<4;i++)
  {
    int sensorvalue=analogRead(spotssensors[i]);
    if(sensorvalue<1010)
    {
      CounterSpots++;
      
    } 
    
  }
//  show number of used "CounterSpots"

  if(checkFlame())
    {
         flameLogic();
    }
  delay(100);

   int entersensorval=analogRead(entersensor);
   if(entersensorval<1010&&CounterSpots<4)
   {

    for(int i=1;i<=90;i*=10)
    {
        gateEnter.write(i);
        if(checkFlame())
          {
               flameLogic();             
              
          }
                
      delay(100);
      
    }      
    
   }
    int exitsensorval=analogRead(exitsensor);   
    if(exitsensorval<1010)
   {

    for(int i=1;i<=90;i*=10)
    {
        gateExit.write(i);               
        delay(100);     
    }  
  
   }
  


for(int i=0;i<4;i++){
  
  if(analogRead(spotssensors[i])<1010){
    digitalWrite(ledpins[i],LOW);
    
    
    }
  else{
      digitalWrite(ledpins[i],HIGH);
    }
  }

  CounterSpots=0;
}



bool checkFlame()
{
 return (digitalRead(flame));    
}

void flameLogic()
{  

  
}
