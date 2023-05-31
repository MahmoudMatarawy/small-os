/*
 * button.h
 *
 * Created: 5/30/2023 2:38:48 AM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_


#include "button_types.h"

void BUTTON_mainTask(void);
en_btnState_t BUTTON_init(en_btnId_t en_btnId);
en_btnState_t BUTTON_getState(en_btnId_t en_btnId);


#endif /* BUTTON_H_ */