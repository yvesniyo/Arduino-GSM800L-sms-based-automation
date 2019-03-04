#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#include <Sim800l.h>
#include <SoftwareSerial.h> //is necesary for the library!! 
Sim800l Sim800l;  //to declare the library



String textSms,numberSms;
uint8_t index1;
uint8_t LED2=5; // use what you need 
bool error;



void setup(){
    lcd.begin(16,2);
    pinMode(LED2,OUTPUT); 
    Serial.begin(9600); // only for debug the results . 
    Sim800l.begin(); // initializate the library. 
    //Sim800l.reset();
    //don't forget to catch the return of the function delAllSms! 
    error=Sim800l.delAllSms(); //clean memory of sms;
    lcd.print("Tangira");
    
}

void loop(){
    textSms=Sim800l.readSms(1); //read the first sms
    String text=Sim800l.readSms(1);     
    Serial.println(text);
    lcd.clear();
    lcd.print("Tegereza");
    lcd.setCursor(1,1);
    if (textSms.indexOf("OK")!=-1) //first we need to know if the messege is correct. NOT an ERROR
        {           
        if (textSms.length() > 7)  // optional you can avoid SMS empty
            {
               
                numberSms=Sim800l.getNumberSms(1);  // Here you have the number
                //for debugin
                Serial.println(numberSms); 
                
                textSms.toUpperCase();  // set all char to mayus ;)

                if (textSms.indexOf("CAN")!=-1){
                    Serial.println("LED TURN ON");
                    digitalWrite(LED2,1);
                    lcd.clear();
                    lcd.print("Tegereza");
                    lcd.setCursor(1,1);                   
                    lcd.print("Riratse");
                }
                else if (textSms.indexOf("ZIMA")!=-1){
                    Serial.println("LED TURN OFF");
                    digitalWrite(LED2,0);
                    lcd.clear();
                    lcd.print("Tegereza");
                    lcd.setCursor(1,1);
                    lcd.print("Itara rirazimye");

                }
                else{
                    Serial.println("Not Compatible ...sorry.. :D");
                }


            Sim800l.delAllSms(); //do only if the message is not empty,in other case is not necesary
             //delete all sms..so when receive a new sms always will be in first position
            } 



        }
    }
 
