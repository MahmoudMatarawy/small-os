/*
 * small os.c
 *
 * Created: 5/28/2023 1:58:00 PM
 * Author : Mahmoud Sarhan
 */ 

#define F_CPU 8000000UL

#include "APP/app.h"


int main(void)
{
	APP_init();
	APP_start();
	
}