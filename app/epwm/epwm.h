/*
 * epwm.h
 *
 *  Created on: 2021年6月21日
 *      Author: 14472
 */

#ifndef EPWM_H_
#define EPWM_H_

#include "DSP2833x_Device.h"     // DSP2833x 头文件
#include "DSP2833x_Examples.h"   // DSP2833x 例子相关头文件

// 包含函数原型声明或头文件
void EPWM4_Init(Uint16 tbprd, Uint16 phaseshiftvalue , Uint16 duty );
void EPWM5_Init(Uint16 tbprd, Uint16 phaseshiftvalue , Uint16 duty );
void EPWM6_Init(Uint16 tbprd, Uint16 phaseshiftvalue , Uint16 duty );

#endif /* EPWM_H_ */
