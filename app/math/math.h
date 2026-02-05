/*
 * 		math.h
 *
 * 		 Modified on: 2025-4-10
 *      Author: Jin
 */

#ifndef APP_MATH_XIANER_MATH_H_
#define APP_MATH_XIANER_MATH_H_


#include "DSP2833x_Device.h"


extern Uint16 dbtime_now;
float Function_Constrain(float Input, float Max, float Min);
float AVG_Nomaxmin(Uint16 a[]);//去掉最大最小值后的n个元素的平均值
Uint16 lookup_table(Uint16 fsw_now);
Uint16 SecDbtime_table(Uint16 fscount_now);

typedef struct
{
    float Kp;
    float Ki;
    float Kd;
    float Target;
    float Error;
    float Error_Old;
    float Error_Old_Old;
    float Error_Sum;
    float Output;
    float OutputMax;
    float OutputMin;
}PID;

extern PID Vout;//调频电压环


void Init_VoltageLoop(void);
void Voltage_Loop(void);//电压环

#endif /* APP_MATH_XIANER_MATH_H_ */
