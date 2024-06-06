#include "pinout.h"

void printLTH (void){

  lcd.setCursor(0, 1);
  lcd.print("Luz:");
  TaskLuz.Start();

  lcd.setCursor(0, 0);
  lcd.print("Tem:");
  TaskTem.Start();

  lcd.setCursor(9, 0);
  lcd.print("Hum:");
  TaskHum.Start();

  tempLuzMayor();
};

void printM (void){
  lcd.setCursor(0, 0);
  lcd.print("Hall: ");
  TaskMag.Start();

  void hallMayor();
}

void readluz (void){
  valueLuz = analogRead(PIN_LUZ);
  lcd.setCursor(5, 1);
  lcd.print(valueLuz);//escribe luz
};
void readmag (void){
  valuemag = analogRead(PIN_MAG);
  lcd.setCursor(6, 0);
  lcd.print(valuemag);//escribe mag
};
void readtem (void){
  valuetem = analogRead(PIN_TEM);
  lcd.setCursor(5, 0);
  lcd.print(valuetem);//escribe temperatura
};
void readhum (void){
  valuehum = analogRead(PIN_HUM);
  lcd.setCursor(14, 0);
  lcd.print(valuehum);// escribe humedad
};

void tempLuzMayor(){
  if (valuetem > tempHigh){
    Serial.print("La temperatura supero los: ");
    Serial.println(tempHigh);
    TaskTempLuz.Start();
  } else if (valueLuz > luzHigh){
    Serial.print("La luz supero los: ");
    Serial.println(luzHigh);
    TaskTempLuz.Start();
  }
}
void hallMayor(){
  if (valuemag > hallValue){
    Serial.print("El Hall supero los: ");
    Serial.println(hallValue);
    TaskHall.Start();
  }
}

