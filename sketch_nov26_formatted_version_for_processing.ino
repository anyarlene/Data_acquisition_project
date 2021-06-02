#include <SoftwareSerial.h>

#define trigPin 13//for the FIRST distance module 
#define echoPin 12 
#define trigPin2 10//for the SECOND  distance module 
#define echoPin2 9

#define trigPin 13//for the distance module
#define echoPin 12

int firstTime=0;//we need to declare firstTime outside the loop 
long Distance,auxDistance,gap=0;
long Distance2,auxDistance2,gap2=0;
int counter=0;

void setup()
{
  Serial.begin(9600);//Start our Serial coms for serial monitor in our pc

delay(500);//Waiting for chip initialization

delay(200);//wait for 200ms
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
pinMode(trigPin2, OUTPUT); 
pinMode(echoPin2, INPUT); 

}
void loop() 
{ 
Distance=measureDistance(trigPin,echoPin);//measure distance1 and store
Distance2=measureDistance(trigPin2,echoPin2);//measure distance2 and store
gap=abs(Distance-auxDistance);// calculate the difference between now and last reading
gap2=abs(Distance2-auxDistance2);// calculate the difference between now and last reading

if(firstTime==0){//necesary for stability of the system
auxDistance=Distance;
auxDistance2=Distance2;
gap=0;
gap2=0;
//to avoid first loop malfuntcion
firstTime++; 
delay(2000);
}


 if(gap>20 and gap2<20 ){ //if distance variation is 20cm
firstTime=0;              //avoiding errors
counter=counter+1;
Serial.print("IN");
Serial.print(":");
Serial.println((String)counter);
delay(1000); 
} 
 if(gap2>20 and gap<20){ //if distance variation is 20cm
firstTime=0;            //avoiding errors
counter=counter-1;
Serial.print("OUT");
Serial.print(":");
Serial.println((String)counter);
delay(1000); 
} 
//Serial.println("\\\\\\\\\\\\\\\\\\\\\\");
//Serial.print(" New Distace:");
//Serial.print(Distance);
//Serial.print("   Old Distance: ");
//Serial.print(auxDistance);
//Serial.print("   GAP ");
//Serial.println(gap);

//Serial.print("New Distace2:");
//Serial.print(Distance);
//Serial.print("  Old Distance2: ");
//Serial.print(auxDistance);
//Serial.print("  GAP2 ");
//Serial.println(gap);
//Serial.println("\\\\\\\\\\\\\\\\\\\\\\");

//delay(300); 
auxDistance=Distance;//store the value for the if() in the next loop
auxDistance2=Distance2;//store the value for the if() in the next loop

}

long measureDistance(int trigger,int echo){
   long duration, distance;
  
  digitalWrite(trigger, LOW);  //PULSE ___|---|___
  delayMicroseconds(2); 
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigger, LOW);
  
  duration = pulseIn(echo, HIGH);
  distance = (duration/2) / 29.1;
//   Serial.println("distance:");
//   Serial.println(distance);
  return distance;

}
