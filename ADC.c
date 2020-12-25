#include "ADC.h"

void Init_ADC(void)	
{
// enable clock for ADC0
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK ;   

//make mux field in pcr 000 so it's Analog	
	PORTE->PCR[ADC_In] |= PORT_PCR_MUX(0); 

// enable clock for Port E input for ATD	
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK ;  
		
//  12/13(SE/DIFF) bit mode , Bus clock ,Short sample time ,Clk division by 1, high power mode(conversion speed faster) 
	ADC0->CFG1 =  ADC_CFG1_MODE(1)  | ADC_CFG1_ADICLK(0)  | ADC_CFG1_ADLSMP(0) | ADC_CFG1_ADIV(0) |ADC_CFG1_ADLPC(0)  ;
	
// enable interrupt  , single ended mode 
	ADC0->SC1[0]  = ADC_SC1_AIEN (1) |  ADC_SC1_DIFF (0)  ;
  
// enable continous conversion
	ADC0->SC3 |= ADC_SC3_ADCO(1);
	
// software trigger enable by writing in ADCH, selecting voltage reference as externel
	ADC0->SC2  = ADC_SC2_ADTRG (0)  | ADC_SC2_REFSEL(0) ;
	
	
// enable ADC0 interrupt
	NVIC_SetPriority(ADC0_IRQn , 0);
	NVIC_ClearPendingIRQ(ADC0_IRQn);
	NVIC_EnableIRQ(ADC0_IRQn);


// choose channel 0 for analog single ended input and start conversion 
	ADC0->SC1[0] = ADC_SC1_ADCH(0);	
	
//result is placed in ADC0_R0 and COCO flag is set after end of conversion that trigger an interupt

}