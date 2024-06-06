#ifndef SEGURIDAD_H
#define SEGURIDAD_H

#include "pinout.h"

const char clave[5] = "12345";
char pass[5];
int c=0;

bool checkAuthorization()
{
  lcd.print("Ingrese contra:");
  int nIntentos = 0;
  while (nIntentos < 3){
    lcd.setCursor(c, 1);
    char key = keypad.getKey();
    if (key) {
      pass[c++] = key;
      lcd.print("*");
      if (c == 5) {
        lcd.clear();
        pass[c] = '\0';
          if (strcmp(pass, clave)==0) {
            lcd.print("Contra correcta");
            Serial.println(":)");
            digitalWrite(LED_GREEN, HIGH);
            memset(pass, 0, sizeof(pass));
            input = Input::ClaveCorrecta;
            delay(1000);
            digitalWrite(LED_GREEN, LOW);
            return true;
          } else {  
            nIntentos++;
            if (nIntentos == 3){
              lcd.print("Sistema Bloqueado");
              Serial.println(":(");
              memset(pass, 0, sizeof(pass));
              lcd.clear();
              input = Input::SistemaBloqueado;
              return false;
            }
            lcd.print("Contra incorrecta");
            digitalWrite(LED_BLUE, HIGH);
            delay(1000);
            memset(pass, 0, sizeof(pass));
            lcd.clear();
            digitalWrite(LED_BLUE, LOW);
            lcd.print("Ingrese contra:");
          }
          c=0;
          digitalWrite(LED_GREEN, LOW);
      }
    }   
  }
}
#endif 