#ifndef PINOUT_H
#define PINOUT_H

#include "AsyncTaskLib.h"
#include <LiquidCrystal.h>
#include <LiquidMenu.h>
#include <Keypad.h>
#include "StateMachineLib.h"
#include "DHT.h"

// Definiciones de los leds
#define LED_RED 7
#define LED_GREEN 6
#define LED_BLUE 9

//Definiciones de los pines
#define PIN_LUZ A0
#define PIN_MAG A1
#define PIN_DHT 10
#define BOTON 38

#define DHTTYPE DHT11

DHT dht(PIN_DHT, DHTTYPE);

//Definición del Keypad
#define ROWS 4  //four rows
#define COLS 4  //four columns
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { 22, 24, 26, 28 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 30, 32, 34, 36 };  //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//Definición del LCD
LiquidCrystal lcd(12, 11,5, 4, 3, 2);

// Create new StateMachine
StateMachine stateMachine(6, 13);

// State Alias
enum State
{
  Inicio = 0,
  Config = 1,
  MonitoreoAmbiental = 2,
  MonitorEventos = 3,
  Alarma = 4,
  Bloqueado = 5
};

// Input Alias
enum Input
{
  TimeOut3 = 0,
  TimeOut4 = 1,
  TimeOut7 = 2,
  TimeOut10 = 3,
  ClaveCorrecta = 4,
  Boton = 5,
  SistemaBloqueado = 6,
  TempLuz = 7,
  Hall = 8,
  Unknown = 9
};

Input input = Unknown;

int tempHigh = 40;
int tempLow = 0;
int luzHigh = 300;
int luzLow = 100;
int hallValue = 1000;

int valueLuz;
int valuemag;
int valuetem;
int valuehum;

int currentMelody;

void readluz(void);
void readmag(void);
void readtem(void);
void readhum(void);
void printLTH(void);
void printM(void);

bool checkAuthorization();

void ejecutarMenu();

void tempLuzMayor();
void hallMayor();

void playCurrentMelody();

AsyncTask TaskEjecutarMenu(100, true, []() { ejecutarMenu(); });

AsyncTask TaskLuz(100, false, readluz);
AsyncTask TaskTem(250, false, readtem);
AsyncTask TaskHum(220, false, readhum);
AsyncTask TaskMonitoreoAmbiental(500, false, printLTH);

AsyncTask TaskMag(150, false, readmag);
AsyncTask TaskMonitorEventos(500, false, printM);

AsyncTask TaskEjecutarBuzzer(200, false, []() { playCurrentMelody(); });

AsyncTask TaskSecurity(100, false, []() { checkAuthorization(); });
AsyncTask TaskTimeOut3(3000, false, []() { input = Input::TimeOut3; });
AsyncTask TaskTimeOut4(4000, false, []() { input = Input::TimeOut4; });
AsyncTask TaskTimeOut7(7000, false, []() { input = Input::TimeOut7; });
AsyncTask TaskTimeOut10(10000, false, []() { input = Input::TimeOut10; });
AsyncTask TaskBoton(1000, false, []() { input = Input::Boton; });
AsyncTask TaskTempLuz(100, false, [](){ input = Input::TempLuz; });
AsyncTask TaskHall(100, false, [](){ input = Input::Hall; });
AsyncTask TaskLedBLUE(800, false, [](){ digitalWrite(LED_BLUE, HIGH);});
AsyncTask TaskLedBLUELOW(800, false, [](){ digitalWrite(LED_BLUE, 0);});
AsyncTask TaskLedRED(50, false, [](){ digitalWrite(LED_RED, HIGH);});
AsyncTask TaskLedREDLOW(1000, false, [](){ digitalWrite(LED_RED, 0);});

#endif //PINOUT_H