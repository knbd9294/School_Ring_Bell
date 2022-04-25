//Libraries
#include <SoftwareSerial.h>
#include <Wire.h>//https://www.arduino.cc/en/reference/wire
#include <DS3231.h>//https://github.com/NorthernWidget/DS3231

//Variables
const int relay=12;
//---------------Objects------------------------
/*Init the DS3231 using the hardware interface*/
DS3231  rtc(SDA, SCL);

//-----------------------------Connections--------------------------------

//------------------------------------------------------------------------


void setup() 
{
  //Init Serial USB
  Serial.begin(9600);
  // Initialise l'object rtc
  rtc.begin();
  // Initialize the relay pin and putting it at Low
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
}

void loop() 
{
  
  if(licenceIsValid())
  {
    //verification de la licence, si valide la routine, si non ne rien faire....
    //listening to set Weekly Rings
    routine();
    Serial.println("la routine.... ");
  }
  else
  {//do nothing
    Serial.println("votre licence est expiree, contactez nous au +237 695 061 600 ");
    //try to set new Incomming License
  }
}

void routine(){//sonne toutes les fin de periodes et pauses

  const Time  t = rtc.getTime();
  int jour=t.dow;
  int h = t.hour;
  int mn = t.min;
  int s =  t.sec;
  //test............
     //independament du jour de semaine..
     // bloc de code temporaire pour tester..
    if(h==12 && mn==0 && s==0)
    {
      Serial.print("je sonne oh, test...");
      sonne(4,1);
    }  
    //fin test...
  /*------------------------------verification du jour de la semaine-----------------------------------------------------*/
  if(jour==1 || jour==2 || jour==4 || jour==5 || jour==6)//lundi, mardi, jeudi et vendredi jour==6 cest pr le test
  {
    if((h==8 && mn==25 && s==0) || (h==9 && mn==20 && s==0) || (h==11 && mn==25 && s==0) || (h==12 && mn==20 && s==0) || (h==14 && mn==35 && s==0) || (h==15 && mn==30 && s==0))
    {//toutes les periodes de la journee....
      Serial.print("fin de l'heure il est: ");
      Serial.println(rtc.getTimeStr());
      sonne(1,1);//sonne 1e fois pendant 1s a chaque fin de periode....
    }
    else if((h==7 && mn== 30 && s==0) || (h==10 && mn== 15 && s==0) || (h==10 && mn== 30 && s==0) || (h==13 && mn== 15 && s==0) || (h==13 && mn== 40 && s==0))
    {//les heures de pauses.....
      Serial.print("c'est la pause...");
      Serial.println(rtc.getTimeStr());
      sonne(2,5);//soone 1e fois pendant 3s a chaque debut et fin de pause....
    }
  }
  else if(jour==3)//mercredi
  {
    if((h==8 && mn==25 && s==0) || (h==9 && mn==20 && s==0) || (h==11 && mn==25 && s==0) || (h==12 && mn==20 && s==0) || (h==13 && mn==15 && s==0))
    {//toutes les periodes de la journee....
      Serial.print("fin de l'heure il est: ");
      Serial.println(rtc.getTimeStr());
      sonne(1,1);//sonne 1e fois pendant 1s a chaque fin de periode....
    }
    else if((h==7 && mn== 30 && s==0) || (h==10 && mn== 15 && s==0) || (h==10 && mn== 30 && s==0))
    {//les heures de pauses.....
      Serial.print("c'est la pause...");
      Serial.println(rtc.getTimeStr());
      sonne(2,5);//soone 1e fois pendant 3s a chaque debut et fin de pause....
    }
  }
  else//le weekend
  {//les jours non pris en charge samedi et dimanche
    //mode veille prolonguee....
  }
  /*------------------------------------------------------------------------------------------------------------------------*/
}

String getExpiredDate(){
  return expDate;// Get the expiring date in format (DD/MM/YY) from EEPROM or sd Card
}

bool setExpiredDate(String expDateToSet){ //expiredDateSettle
  String expDate = expDateToSet; // Set the expiring date in format (DD/MM/YY)--> 23 janvier 2022 read from EEPROM or sd Card
  //String expDate = "23.01.2022"; // Set the expiring date in format (DD/MM/YY)--> 23 janvier 2022 read from EEPROM or sd Card
  return true //if settle successfully;
}

bool licenceIsValid(){
  const String expDate=getExpiredDate();
  const String today = rtc.getDateStr();
  const int dateDiff = today.compareTo(expDate);
  if(dateDiff < 0)
  {
    Serial.print("case 1 : ");Serial.print(dateDiff, DEC);
    Serial.println("....everything is normal.....");
    return true; 
  }
  else if(dateDiff == 0)
  {
    Serial.print("case 2 : ");Serial.print(dateDiff, DEC);
    Serial.println("the licence has just expire...");
    return false;
  }
  else
  {
    Serial.print("case 3 : ");Serial.print(dateDiff, DEC);
    Serial.println("the licence has just expire...");
    return false;
  }
}

bool setWeeklyRingDate(){ 
  //set Weekly Ring date on SD Card or EEPROM eg: use routine
  return true //if settle successfully;
}

bool getWeeklyRingDate(){ 
  //get Weekly Ring date on SD Card or EEPROM eg: use routine
  return true // if succesfully got it;
}

void printMessageOnScreen(String message, date startDate, date endDate){
  //print Message on Screen between dateInterval = endDate-startDate
}





bool setPeriodIntervalRing(time interval){
}

bool setBreakIntervalRing(time interval){
  
}
