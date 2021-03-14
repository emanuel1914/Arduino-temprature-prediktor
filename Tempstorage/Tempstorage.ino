


#include <OneWire.h> // Gör så tempratursensor (och andra Dallas komponenter) kan användas
#include <DallasTemperature.h> //Gör så tempratursensoren kan 
#define ONE_WIRE_BUS 8 // Vilken pin tempratursensorerna skickar data till
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);

float temparray[100]; //En array
float tempwant = 27;
 float temp1 = 1000;
 int i=-1;
 int tid = 0;  //Tiden 
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);  // Startar Serial monitor i arduino 

}

void loop() {
  // put your main code here, to run repeatedly:

for(temp1 >tempwant; i++; tid = tid + 2)  {   //Detta körs till tempraturen av vattnet är lika stor som tempraturen som man vill vattnet ska vara och detta tjeckas i 2 minuts intervaller 
sensors.requestTemperatures(); //Begär värdet ifrån tempratur sensorerna 
 temp1=sensors.getTempCByIndex(0);  //sätter temp1 till värdet av tempratursensor i vatten
 float temp2=sensors.getTempCByIndex(1);  //sätter temp1 till värdet av tempratursensor i vatten

temparray[i]=temp1; //sätter den nuvarande tid till ett värdet av tempraturen på array

Serial.print(tid);
Serial.println(" minuter");
Serial.println(temparray[i]);
Serial.println(temp2);

  delay(120000); //delay på 2 minuter
}

}
