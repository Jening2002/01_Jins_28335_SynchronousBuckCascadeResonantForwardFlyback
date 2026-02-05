/*
 * 		math.c
 *
 * 		 Modified on: 2025-4-10
 *      Author: Jin
 */



#include "math.h"
#include "main.h"
#include "epwm.h"

PID Vout;//调频电压环
PID Phase_Vout;//调频电压环

Uint16 dbtime_now = 75;
//******************************************************************************************
//滑动取均值
//功能：计算最近两次PID结果的平均值
//******************************************************************************************
float Sliding_average_fre(float value)
{
    float average2;

    Window_data_fre[1] = Window_data_fre[0];
    Window_data_fre[0] = value;
    average2 = (Window_data_fre[0]+Window_data_fre[1])/2;
    return average2;
}
float Sliding_average_phs(float value)
{
    float average2;

    Window_data_phs[1] = Window_data_phs[0];
    Window_data_phs[0] = value;
    average2 = (Window_data_phs[0]+Window_data_phs[1])/2;
    return average2;
}
//******************************************************************************************
//限幅函数
//功能：将输出限幅在最大值和最小值内
//******************************************************************************************
float Function_Constrain(float Input, float Max, float Min)
{
    if(Input > Max)
    {
        return Max;
    }
    else if(Input < Min)
    {
        return Min;
    }
    else
    {
        return Input;
    }
}

float AVG_Nomaxmin(Uint16 a[]) // 去掉最大最小值后的10个元素的平均值
{
    Uint16 max = a[0];
    Uint16 min = a[0];
    Uint16 sum = 0;
    Uint16 i;
    // 一次性遍历，同时找最大、最小并求和
    for (i = 0; i < 10; i++)
    {
        if (a[i] > max)
        	max = a[i];
        if (a[i] < min)
        	min = a[i];
        sum += a[i];
    }

    // 直接计算并返回平均值，避免额外变量
    return (float)(sum - max - min) / 8.0;
}


//******************************************************************************************
//同步整流驱动信号查表函数
//功能：根据频率自动调节同步整流驱动的占空比（死区时间）
//这里预留了两个函数，第一个是开环上电后实测的谐振电流与励磁电流相等时刻对应的死区时间，测量多组数据后拟合而成的曲线关系（未完成），后一个是保守估计，按照原边管子的导通时间的百分比确定副边导通时间
//lookup传入的是频率，secdb传入的是fscount
//******************************************************************************************
Uint16 lookup_table(Uint16 fsw_now)
{
    dbtime_now = 0.125*150000/fsw_now;//对应45度移相角
    if(dbtime_now<30)
    {
    	dbtime_now=30;
    }
    //保守起见，设置死区最小为30，严谨起见需要计算谐振时间
    return dbtime_now;
}

Uint16 SecDbtime_table(Uint16 fscount_now)
{
    dbtime_now = 0.125*fscount_now;//对应45度移相角
    if(dbtime_now<30)
    {
    	dbtime_now=30;
    }
    //保守起见，设置死区最小为30，严谨起见需要计算谐振时间
    return dbtime_now;

}



//******************************************************************************************
//调频电压环初始化函数
//功能：将MPPT的变量进行初始化(步长等)
//******************************************************************************************
void Init_VoltageLoop(void)
{
    Vout.Kp = 0.01;
    Vout.Ki = 0.01;
    Vout.Kd = 0.0;
    Vout.Target = Voltage_Target;
    Vout.Error = 0.0;
    Vout.Error_Old = 0.0;
    Vout.Error_Old_Old = 0.0;
    Vout.Error_Sum = 0.0;
    Vout.Output = 0.0;
}

//******************************************************************************************
//调频电压闭环函数
//功能：输出电压PID闭环
//******************************************************************************************
void Voltage_Loop(void)
{
    //计算误差
    Vout.Error = (float)(ADC_A1_Vout) - Vout.Target;
    //计算PID输出,此为PID增量表达式，Vou.Output为频率增量
    Vout.Output = Vout.Kp * (Vout.Error - Vout.Error_Old)
                           + Vout.Ki * Vout.Error
						   + Vout.Kd * (Vout.Error - 2.0 * Vout.Error_Old + Vout.Error_Old_Old);

    Vout.Output = Function_Constrain(Vout.Output,0.5,-0.5);//输出限幅
    Control_frequency = Control_frequency + Vout.Output;//确定频率
    Control_frequency = Function_Constrain(Control_frequency,Control_frequency_Max,Control_frequency_Min);//输出限幅

    //误差随时间传递
    Vout.Error_Old_Old = Vout.Error_Old;
    Vout.Error_Old = Vout.Error;
    Control_fswcount=(Uint16)(150000.0/Control_frequency);
    //更改开关频率
    EPWM4_SetFrequency(Control_fswcount);
    EPWM5_SetFrequency(Control_fswcount);
    EPWM6_SetFrequency(Control_fswcount);

    avg_frequency = Sliding_average_fre(Control_frequency);
    //Control_frequency =avg_frequency;
}




