#include "DSP2833x_Device.h"	// DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"	//  DSP2833x  Examples  Include  File
#include "leds.h"
#include "timer.h"
#include "epwm.h"

/*******************************************************************************
	2025.11.20
	金琛
	由于YH28335开发板的epwm1A2a2b损坏，因此输出端口改为4和5和6
*******************************************************************************/

Uint16 fsw=250;	//开关频率，k Hz

//设定周期计时器值
Uint16 EPWM4_tbprd=600;	//EPWM4对应Buck高边开关管Q2
Uint16 EPWM5_tbprd=600;	//EPWM5对应副边Buck开关管Q4
Uint16 EPWM6_tbprd=600;	//EPWM6对应谐振级开关管Q1

//设定移相值
Uint16 EPWM4_PSV=0; //EPWM4A-GPIO6
Uint16 EPWM5_PSV=0; //EPWM5A-GPIO8
Uint16 EPWM6_PSV=0; //EPWM6A-GPIO10

// 千分比 + 四舍五入
Uint16 EPWM4_duty = 498;
Uint16 EPWM5_duty = 400;
Uint16 EPWM6_duty = 235;




void main()
{
	InitSysCtrl();
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
	//LED_Init();
	/*原边驱动*/
	EPWM4_Init(EPWM4_tbprd,EPWM4_PSV,EPWM4_duty);	//EPWM4对应Buck高边开关管Q2
	EPWM5_Init(EPWM5_tbprd,EPWM5_PSV,EPWM5_duty);	//EPWM5对应Buck低边开关管Q3
	EPWM6_Init(EPWM6_tbprd,EPWM6_PSV,EPWM6_duty);	//EPWM6对应谐振级开关管Q1
}
