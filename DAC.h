

#ifndef DAC_H_
#define DAC_H_

#include <MKL25Z4.h>



void control_action (float measured_value , float setpoint ,float Kp ,float Ki, float Kd, float* int_value , float* old_error , float dt );
	

void init_DAC0(void);
void delay_ms (int count );

#endif