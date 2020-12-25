#include "dac.h"


void init_DAC0(void){
  //enable_DACO_clock
	SIM->SCGC6|=SIM_SCGC6_DAC0_MASK;
	//enable_PORTE_clock
	SIM->SCGC5|=SIM_SCGC5_PORTE_MASK;
	//configure_pin_20_as_analog_pin
	PORTE->PCR[30]&=~PORT_PCR_MUX_MASK;
	PORTE->PCR[30]|=PORT_PCR_MUX(0);
	//disable_buffer_mode
	DAC0->C1=0;
	DAC0->C2=0;
	//enable_dac&select_vdd_as_reference_voltage
	DAC0->C0=DAC_C0_DACEN_MASK |DAC_C0_DACRFS_MASK|DAC_C0_DACTRGSEL_MASK;
  DAC0->C0&=~DAC_C0_LPEN_MASK;
}

void control_action (float measured_value , float setpoint ,float Kp ,float Ki, float Kd, float* int_value , float* old_error , float dt )
{
	
float error = setpoint - measured_value ;
	
	float proportinal = Kp * error ;
	
	*int_value  =  Ki*(*int_value + error * dt) ; 
	
	float drevative = Kd*(error - *old_error) / dt ;
	
	int output = proportinal + *int_value + drevative ;
	
	
	DAC0->DAT[0].DATL =DAC_DATL_DATA0(output); //write data to register
	
	DAC0->DAT[0].DATH =DAC_DATH_DATA1(output >> 8);
	
	DAC0->C0 |= DAC_C0_DACSWTRG_MASK ;	// change analog value to the new value (software trigger)
	
  *old_error= error ;

}
void delay_ms (int nCount){   /* Wait function */ 
  nCount=nCount+16000000; 
 
  while (nCount--); 
}