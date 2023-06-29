#include "input.h"

uint16_t BUTTON_PIN[NO_OF_BUTTONS] = { PIN_BT0, PIN_SW_WAKEUP };
bool Flag_for_button_press[NO_OF_BUTTONS];
uint16_t Counter_button_press[NO_OF_BUTTONS];

//=================HIGH LEVEL FUNCTION=================//
void IN_Init(void){

  for(uint8_t i = 0; i < NO_OF_BUTTONS; i++){
    pinMode(BUTTON_PIN[i], INPUT_PULLUP);
  }
}

void IN_ReadButton(void){
  for (uint8_t i = 0; i < NO_OF_BUTTONS; i++) {
    if (digitalRead(BUTTON_PIN[i]) == BUTTON_IS_PRESSED) {
      if (Counter_button_press[i] < MAX_COUNTER) {
        Counter_button_press[i]++;
      }
    } else {
      Flag_for_button_press[i] = (Counter_button_press[i] > 0) && (Counter_button_press[i] < 10);
      Counter_button_press[i] = 0;
    }
  }
}

bool IN_IsPressed(uint8_t index){
  if(index >= NO_OF_BUTTONS) return 0;

  return Flag_for_button_press[index];
}
bool IN_IsPressed_ms(uint8_t index, uint16_t duration){
	if(index >= NO_OF_BUTTONS) return 0;

	//button is read every 50ms -> counter += 1 every 50ms if button is held
	return Counter_button_press[index] >= (duration / 50);
}

bool IN_IsHeld(uint8_t index){
  if(index >= NO_OF_BUTTONS) return 0;

  return Counter_button_press[index] > 0;
}