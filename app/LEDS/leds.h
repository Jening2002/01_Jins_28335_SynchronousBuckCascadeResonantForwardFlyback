/*
 * leds.h
 *
 *  Created on: 2025年7月29日
 *      Author: Jin
 */

#ifndef _LEDS_H_
#define _LEDS_H_



#include  "DSP2833x_Device.h"	//  DSP2833x  头文件
#include  "DSP2833x_Examples.h"	//  DSP2833x  例子相关头文件




//#define  LED14_OFF	(GpioDataRegs.GPCSET.bit.GPIO68=1)
//#define  LED14_ON	(GpioDataRegs.GPCCLEAR.bit.GPIO68=1)
//#define  LED14_TOGGLE	(GpioDataRegs.GPCTOGGLE.bit.GPIO68=1)
//

//#define  LED13_OFF	(GpioDataRegs.GPCSET.bit.GPIO67=1)
//#define  LED13_ON	(GpioDataRegs.GPCCLEAR.bit.GPIO67=1)
//#define  LED13_TOGGLE	(GpioDataRegs.GPCTOGGLE.bit.GPIO67=1)
//

//#define  LED12_OFF	(GpioDataRegs.GPCSET.bit.GPIO66=1)
//#define  LED12_ON	(GpioDataRegs.GPCCLEAR.bit.GPIO66=1)
//#define  LED12_TOGGLE	(GpioDataRegs.GPCTOGGLE.bit.GPIO66=1)
//

//#define  LED11_OFF	(GpioDataRegs.GPCSET.bit.GPIO65=1)
//#define  LED11_ON	(GpioDataRegs.GPCCLEAR.bit.GPIO65=1)
//#define  LED11_TOGGLE	(GpioDataRegs.GPCTOGGLE.bit.GPIO65=1)
//

//#define  LED10_OFF	(GpioDataRegs.GPCSET.bit.GPIO64=1)
//#define  LED10_ON	(GpioDataRegs.GPCCLEAR.bit.GPIO64=1)
//#define  LED10_TOGGLE	(GpioDataRegs.GPCTOGGLE.bit.GPIO64=1)
//

//#define  LED9_OFF	(GpioDataRegs.GPBSET.bit.GPIO61=1)
//#define  LED9_ON	(GpioDataRegs.GPBCLEAR.bit.GPIO61=1)
//#define  LED9_TOGGLE	(GpioDataRegs.GPBTOGGLE.bit.GPIO61=1)
//
//#define  LED8_OFF	(GpioDataRegs.GPBSET.bit.GPIO60=1)
//#define  LED8_ON	(GpioDataRegs.GPBCLEAR.bit.GPIO60=1)
//#define  LED8_TOGGLE	(GpioDataRegs.GPBTOGGLE.bit.GPIO60=1)




//下面为研旭开发板代码
// ==================== LED对GPIO映射 ======================
// LED2 --> GPIO3
// LED3 --> GPIO4
// LED4 --> GPIO0
// LED5 --> GPIO1
// LED6 --> GPIO2
// ==========================================================

// LED2 控制宏（GPIO3）
#define  LED2_ON       (GpioDataRegs.GPACLEAR.bit.GPIO3 = 1)
#define  LED2_OFF      (GpioDataRegs.GPASET.bit.GPIO3   = 1)
#define  LED2_TOGGLE   (GpioDataRegs.GPATOGGLE.bit.GPIO3 = 1)

// LED3 控制宏（GPIO4）
#define  LED3_ON       (GpioDataRegs.GPACLEAR.bit.GPIO4 = 1)
#define  LED3_OFF      (GpioDataRegs.GPASET.bit.GPIO4   = 1)
#define  LED3_TOGGLE   (GpioDataRegs.GPATOGGLE.bit.GPIO4 = 1)

// LED4 控制宏（GPIO0）
#define  LED4_ON       (GpioDataRegs.GPACLEAR.bit.GPIO0 = 1)
#define  LED4_OFF      (GpioDataRegs.GPASET.bit.GPIO0   = 1)
#define  LED4_TOGGLE   (GpioDataRegs.GPATOGGLE.bit.GPIO0 = 1)

// LED5 控制宏（GPIO1）
#define  LED5_ON       (GpioDataRegs.GPACLEAR.bit.GPIO1 = 1)
#define  LED5_OFF      (GpioDataRegs.GPASET.bit.GPIO1   = 1)
#define  LED5_TOGGLE   (GpioDataRegs.GPATOGGLE.bit.GPIO1 = 1)

// LED6 控制宏（GPIO2）
#define  LED6_ON       (GpioDataRegs.GPACLEAR.bit.GPIO2 = 1)
#define  LED6_OFF      (GpioDataRegs.GPASET.bit.GPIO2   = 1)
#define  LED6_TOGGLE   (GpioDataRegs.GPATOGGLE.bit.GPIO2 = 1)

// 初始化函数声明
void LED_Init(void);

#endif /* _LEDS_H_ */

