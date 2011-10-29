/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <device.h>

void main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
	Volume_ADC_Start();
	UART_Start();
	timer_clock_Start();
	Counter_1_Start();
	LED_Control_Reg_Write(42);
	Volume_ADC_StartConvert();
	uint8 i;
	uint8 setting = 0;
	Counter_1_WritePeriod(75);
    /* CYGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
	
        if ( Volume_ADC_IsEndConversion(Volume_ADC_WAIT_FOR_RESULT) > 0){
			Volume_ADC_StartConvert();
		}
		
		if(Counter_1_ReadCounter() == Counter_1_ReadPeriod() ){
			i = Volume_ADC_GetResult8();
			
			if(setting == 1){
				if(Button_Read() < 1){
					setting = 0;
				}
			}else if(setting == 2){
				if( i < 103 && i > 80){
					LED_Control_Reg_Write(3);
					UART_PutString("VolUp\n");
				}else if( i > 151 && i < 180){
					LED_Control_Reg_Write(129);
					UART_PutString("Voldown\n");
				}else {
					setting = 0;
				}
			}else {
				if( i>128 && i < 134){
					setting = 0;
					LED_Control_Reg_Write(0);
				}
			}
		}
		
			if(Button_Read() > 0 && setting == 0){
				LED_Control_Reg_Write(255);
				UART_PutString("play/pause\n");
				setting =1;
				Counter_1_WriteCounter(0);
			}
			if( i > 180 && setting == 0){
				LED_Control_Reg_Write(142);
				UART_PutString("PreTrack\n");
				UART_PutString("PreTrack\n");
				setting = 3;
				Counter_1_WriteCounter(0);
			}else if( i < 80 && i>0 && setting == 0){
				LED_Control_Reg_Write(42);
				UART_PutString("NextTrack\n");
				//UART_PutString("Voldown\n");
				setting = 3;
				Counter_1_WriteCounter(0);
			}else if( i < 103 && i > 80 && setting == 0){
				setting = 2;
				Counter_1_WriteCounter(0);
			}else if( i > 151 && i < 180 && setting == 0){
				setting = 2;
				Counter_1_WriteCounter(0);
			}			
    }
}

/* [] END OF FILE */
