#include <MKL25Z4.h>
#include "ADC.h"
#include "DAC.h"

 const float Kp=21;
 const float Ki=500;
 const float Kd=1;
 const float setpoint =40;
 float sensor_reading=0;
 float control_signal=0;
 float int_value=0;
 float error_old=0 ;

 const float dt = 10 ;

int main()
	
{
	init_DAC0();
	Init_ADC();
	
	while(1)
	{}
		
	return 0 ;	
	
}



