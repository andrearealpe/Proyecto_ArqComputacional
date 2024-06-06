#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "Menu.h"
#include "Seguridad.h"
#include "Buzzer.h"

void inputInicio();
void inputConfig();
void inputMonitoreoAmbiental();
void inputMonitorEventos();
void inputAlarma();
void inputBloqueado();

void outputInicio();
void outputConfig();
void outputMonitoreoAmbiental();
void outputMonitorEventos();
void outputAlarma();
void outputBloqueado();

// Stores last user input
unsigned long stateEnterTime;

// Setup the State Machine
void setupStateMachine()
{
  // Add transitions
//actual
  stateMachine.AddTransition(Inicio, Config, []() { return input == ClaveCorrecta; });
  stateMachine.AddTransition(Inicio, Bloqueado, []() { return input == SistemaBloqueado; });
  stateMachine.AddTransition(Bloqueado, Inicio, []() { return input == TimeOut10; });
  stateMachine.AddTransition(Config, MonitoreoAmbiental, []() { return input == Boton; });
  stateMachine.AddTransition(MonitoreoAmbiental, Config, []() { return input == Boton; });
  stateMachine.AddTransition(MonitoreoAmbiental, MonitorEventos, []() { return input == TimeOut7; });
  stateMachine.AddTransition(MonitoreoAmbiental, Alarma, []() { return input == TempLuz; });
  stateMachine.AddTransition(Alarma, Inicio, []() { return input == Boton; });
  stateMachine.AddTransition(Alarma, MonitoreoAmbiental, []() { return input == TimeOut4; });
  stateMachine.AddTransition(MonitorEventos, Alarma, []() { return input == Hall; });
  stateMachine.AddTransition(MonitorEventos, Config, []() { return input == Boton; });
  stateMachine.AddTransition(MonitorEventos, MonitoreoAmbiental, []() { return input == TimeOut3; });

  // Add actions
  //cuando entra al estado
  stateMachine.SetOnEntering(Inicio, inputInicio);
  stateMachine.SetOnEntering(Config, inputConfig);
  stateMachine.SetOnEntering(MonitoreoAmbiental, inputMonitoreoAmbiental);
  stateMachine.SetOnEntering(MonitorEventos, inputMonitorEventos);
  stateMachine.SetOnEntering(Alarma, inputAlarma);
  stateMachine.SetOnEntering(Bloqueado, inputBloqueado);

  //cuando sale del estado solo sale una sola veaz
  stateMachine.SetOnLeaving(Inicio, []() {outputInicio;});
  stateMachine.SetOnLeaving(Config, []() {outputConfig;});
  stateMachine.SetOnLeaving(MonitoreoAmbiental, []() {outputMonitoreoAmbiental;});
  stateMachine.SetOnLeaving(MonitorEventos, []() {outputMonitorEventos;});
  stateMachine.SetOnLeaving(Alarma, []() {outputAlarma;});
  stateMachine.SetOnLeaving(Bloqueado, []() {outputBloqueado;});

  stateMachine.SetState(Inicio, false, true);
}

// Auxiliar output functions that show the state debug
void inputInicio()
{
  lcd.clear();
  Serial.println("Entered Inicio");
  TaskSecurity.Start();
}

void inputConfig()
{
  lcd.clear();
  Serial.println("Entered Config");
  setupMenu();
}

void inputMonitoreoAmbiental()
{
  lcd.clear();
  Serial.println("Entered MonitoreoAmbiental");
  TaskMonitoreoAmbiental.Start();
  TaskTimeOut7.Start();
}

void inputMonitorEventos()
{
  lcd.clear();
  Serial.println("Entered MonitorEventos");
  TaskMonitorEventos.Start();
  TaskTimeOut3.Start();
}

void inputAlarma()
{
  lcd.clear();
  Serial.println("Entered Alarma");
  lcd.println("Alarma!!!");
  TaskLedBLUE.Start();
  currentMelody = 1;
  setupBuzzer();
  TaskTimeOut4.Start();
}

void inputBloqueado()
{
  lcd.clear();
  Serial.println("Entered SistemaBloqueado");
  currentMelody = 2;
  TaskLedRED.Start();
  setupBuzzer();
  TaskTimeOut10.Start();
}

void outputInicio()
{
  lcd.clear();
}

void outputConfig()
{
  lcd.clear();
}

void outputMonitoreoAmbiental()
{
  lcd.clear();
  TaskMonitoreoAmbiental.Stop();
}

void outputMonitorEventos()
{
  lcd.clear();
  TaskMonitorEventos.Stop();
}

void outputAlarma()
{
  lcd.clear();
  TaskLedBLUELOW.Start();
}

void outputBloqueado()
{
  lcd.clear();
  TaskLedREDLOW.Start();
}

#endif // STATEMACHINE_H