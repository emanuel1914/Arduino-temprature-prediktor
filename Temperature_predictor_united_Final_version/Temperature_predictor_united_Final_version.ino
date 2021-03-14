#include <LiquidCrystal.h>              //include LiquidCrystal för att LCD 16x2 ska fungera  

#include <SoftwareSerial.h>   // include SoftwareSerial så Bluetooth kan läsa och skicka data ifrån digital pins som inte är 0 och 1


#include <OneWire.h> // Gör så tempratursensor (och andra Dallas komponenter) kan användas
#include <DallasTemperature.h> //Gör så tempratursensoren kan användas
LiquidCrystal lcd (12, 11, 5, 4, 3, 2);  //Digitals pins som lcd är inkopplad i

SoftwareSerial hc06(6,7);    //Pins som Bluetooth är kopplad i.

#define ONE_WIRE_BUS 8 // Vilken pin tempratursensorerna skickar data till
float tempervatten; 
float temperluft; 
float area; 
float varmekoeffictient; 
float avgedevarme; 
float tid; 
float villjadvarme;
float massa;
float varmekonstant = 4.18*1000;
float energi;
float h;
int once=0;
float q;
OneWire oneWire(ONE_WIRE_BUS); 
float temp1;
float temp2;
float timed;
String cmd="";
float sensor_val=0;
DallasTemperature sensors(&oneWire);
float tempwant;
float myTime;
int fixed = 0;
 int cled =1;
int donen= 0;
int ma = 0;
void setup() 
{
Serial.begin(9600);  // Startar Serial monitor i arduino 
  hc06.begin(9600); // Startar Bluetoht modueln


}

void loop() {
  // put your main code here, to run repeatedly:








 if( donen == 0) { //ser till att detta gör endast en gång

  for (int allvariblesdone = 0; allvariblesdone!=3;)  {  //slutar efter alla tre medelande har skickas
     
     while(hc06.available()>0){
    cmd+=(char)hc06.read();
  } //säker efter bluetoht konection 

  if(cmd!=""){
    Serial.print("Command recieved : ");
    Serial.println(cmd);
     
      if (allvariblesdone == 0) {
     massa=cmd.toFloat(); //Enda sätten att konverterar värdet till ett numerisk värde.
 allvariblesdone = 1;
Serial.println(massa);
     }  
    else if (allvariblesdone ==1) {
     area=cmd.toFloat();
 allvariblesdone = 2;
     Serial.print("Command recieved : ");

Serial.println(area);
     } 
     
    else if (allvariblesdone == 2) {
     tempwant=cmd.toFloat();
     Serial.print("Command recieved : ");

Serial.println(tempwant);
allvariblesdone = 3;
     }  //Varje if/else if tar värdet skickat och spara det till en varsin variabale och sedan ökar allvariblesdone med ett så nästa värdet skickas till else if sattsen under tills värdet når 3 och loopen slutar 
     
     cmd=""; //reset cmd värdet 
  }
  delay(100);  //delay så den kan läsa datan ordentligt 
  }

  


  
   myTime = millis();  // sparar tiden programet tar att gör beräkningara 


for (int slut = 0; slut == 0;) {
 sensors.requestTemperatures(); //Begär värdet ifrån tempratur sensorerna 
 

 temp1=sensors.getTempCByIndex(0);  //sätter temp1 till värdet av tempratursensor i vatten
  Serial.println(temp1);
 delay(10000);  
    sensors.requestTemperatures();

 temp2=sensors.getTempCByIndex(0);  
 Serial.println(temp2);
float temperluft=sensors.getTempCByIndex(1); // Sätter temperluft till värdet av tempratursensor som mätter  tempraturen i luften
Serial.println(temperluft);

// kollar skillnaden i tempraturer i vattnet i ett 10 sekund intevall 
 if(temp1-temp2 >= 0 ) {

 

float tempdiff = temp1 - temp2; // beräknar tempratur skillnaden
  
 avgedevarme = (massa)*(0.1)*(tempdiff)*(varmekonstant); //Beräknar hur mycket energi som avgedes på 1 sekund 
  Serial.println(tempdiff);

 

 
 h=((avgedevarme)/((area)*(temp2-temperluft))); // Beräknar värdet av h genom detta 
 
energi =(massa)*(varmekonstant)*((temp2-temperluft)); // Beräknar hur mycket energi skillnad det är mellan luften och vattnet 


 

slut = 1;}
//Denna loop körs endast en gång
}

for (float z; temp2 > tempwant;) {
 if( cled==1) {
    sensors.requestTemperatures();
 temperluft=sensors.getTempCByIndex(1);  
cled =2;
 // Fixar en bug där temperluften värde blev noll av någon anledning 
 
 }
 
 
 




   
avgedevarme = ((area)*((temp2-temperluft))*(h)); //beräknar ur mycket energi som ges bort av vatten till luften per sekund
 
 

   energi= (energi)-(avgedevarme);  //Beräknar hur mycket energi vatten har efter en sekund 

     temp2 =  (energi/(massa*varmekonstant)) +(temperluft); //Beräkna vattens nya tempratur 

     tid++;  //Ökar tiden detta tar med en sekund 
     Serial.print("tid ");
 Serial.println(tid);

 
  Serial.print("temp ");

 Serial.println(temp2);}


}
 

 donen=1;
 if (ma == 0) {
int tid2 = tid-(myTime*0.001); //Tar bort tiden det tog för programet att göra detta ifrån tiden det kommer ta att få vatten att bli rätt tempratur 
Serial.println(tid2);
  hc06.println(tid2); //Skickar detta till appen

ma=1;

 }



}
