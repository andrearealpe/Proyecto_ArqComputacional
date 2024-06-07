#ifndef MENU_H
#define MENU_H

#include "pinout.h"
#include <LiquidMenu.h>

LiquidScreen screen;

LiquidLine temp_high(0, 0, "TEMP_HIGH ", tempHigh);
LiquidLine temp_low(0, 1, "TEMP_LOW ", tempLow);
LiquidScreen screen1(temp_high,temp_low);
LiquidLine luz_high(0, 0, "LUZ_HIGH ", luzHigh);
LiquidLine luz_low(0, 1, "LUZ_LOW ", luzLow);
LiquidScreen screen2(luz_high,luz_low);
LiquidLine hall(0, 0, "HALL ", hallValue);
LiquidLine reset(0, 1, "RESET ");
LiquidScreen screen3(hall,reset);

LiquidMenu menu(lcd);

void sensor_up() {
	int focusedLine = menu.get_focusedLine();
	if(focusedLine == 0){
		tempHigh += 5;
	} else if (focusedLine == 1){
		tempLow += 5;
	} else if (focusedLine == 2){
		luzHigh += 5;
	} else if (focusedLine == 3){
		luzLow += 5;
	} else if (focusedLine == 4){
		hallValue += 5;
	}
	menu.update();
}

void sensor_down() {
	int focusedLine = menu.get_focusedLine();
	if(focusedLine == 0){
		tempHigh -= 5;
	} else if (focusedLine == 1){
		tempLow -= 5;
	} else if (focusedLine == 2){
		luzHigh -= 5;
	} else if (focusedLine == 3){
		luzLow -= 5;
	} else if (focusedLine == 4){
		hallValue -= 5;
	}
	menu.update();
}

void sensor_reset(){
	tempHigh = 40;
	tempLow = 0;
 	luzHigh = 300;
	luzLow = 100;
	hallValue = 1000;
	menu.update();
}

void setupMenu() {
	lcd.clear();
	// Function to attach functions to LiquidLine objects.
	temp_high.attach_function(1, sensor_up);
	temp_high.attach_function(2, sensor_down);
	temp_low.attach_function(1, sensor_up);
	temp_low.attach_function(2, sensor_down);
	luz_high.attach_function(1, sensor_up);
	luz_high.attach_function(2, sensor_down);
	luz_low.attach_function(1, sensor_up);
	luz_low.attach_function(2, sensor_down);
	hall.attach_function(1, sensor_up);
	hall.attach_function(2, sensor_down);
	reset.attach_function(1, sensor_reset);
	reset.attach_function(2, sensor_reset);

	menu.add_screen(screen1);
	menu.add_screen(screen2);
	menu.add_screen(screen3);

	menu.update();
	TaskEjecutarMenu.Start();
}

void ejecutarMenu() {
  char key = keypad.getKey();
	int focusedLine = menu.get_focusedLine();

  if (key){
    Serial.println(key);
		switch (key){
			case 'A':
				Serial.println(F("RIGHT button pressed"));
				menu.next_screen();
				break;
			case 'B':
				Serial.println(F("LEFT button pressed"));
				menu.previous_screen();
			case 'C':
				Serial.println(F("UP button pressed"));
				menu.call_function(1);
				break;
			case 'D':
				Serial.println(F("DOWN button pressed"));
				menu.call_function(2);
				break;
			case '*':
				Serial.println(F("ENTER button pressed"));
				menu.switch_focus();
				if(focusedLine == 5){
					menu.switch_focus();
				}
				break;
			default:
				Serial.println(key);
				break;
		}
  }

}

#endif