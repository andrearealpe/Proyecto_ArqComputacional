#include "pinout.h"
#include "StateMachine.h"
#include "StateMachineLib.h"
#include <LiquidCrystal.h>

bool systemAuthorized = false;
int oldValue = LOW;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(BOTON, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  dht.begin();
  setupStateMachine();
}

void loop()
{
  inputBoton();
  TaskLuz.Update();
  TaskTem.Update();
  TaskHum.Update();
  TaskMag.Update();
  TaskTempLuz.Update();
  TaskHall.Update();
  TaskMonitoreoAmbiental.Update();
  TaskMonitorEventos.Update();
  TaskSecurity.Update();
  TaskTimeOut7.Update();
  TaskTimeOut3.Update();
  TaskTimeOut4.Update();
  TaskTimeOut10.Update();
  TaskLedBLUELOW.Update();
  TaskLedREDLOW.Update();
  TaskLedBLUE.Update();
  TaskLedRED.Update();
  TaskEjecutarBuzzer.Update();
  TaskEjecutarMenu.Update();
  TaskBoton.Update();
  
  stateMachine.Update();
}


void inputBoton()
{
  Input currentInput = Unknown;
  int newValue = digitalRead(BOTON);

  if(newValue != oldValue)
  {
    oldValue = newValue;
    if(newValue == HIGH)
    {
      currentInput = Boton;
      Serial.println("El botón fue presionado.");
      
    }
    delay(100);
  }
  input = currentInput;
}
