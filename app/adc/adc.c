/*
 * adc.c
 *
 *  Created on: 2026年2月5日
 *      Author: Jin
 */


#include "adc.h"    // ADC模块头文件
#include "main.h"   // 主头文件
#include "math.h"   // 数学库
#include "leds.h"   // LED控制头文件


void ADC_Init(void)
{
    // 允许访问受保护的寄存器
	EALLOW;
	// 设置ADC中断服务程序入口地址
	PieVectTable.ADCINT = &adc_isr;
	EDIS;  // 禁止访问受保护的寄存器

	InitAdc();  // 初始化ADC模块

	// 中断配置
	PieCtrlRegs.PIEIER1.bit.INTx6 = 1;  // 使能PIE组1的第6个中断(ADC中断)
	IER |= M_INT1;                      // 使能CPU级中断1(INT1)

	EALLOW;  // 允许访问受保护的寄存器

	/* ADC工作模式配置 */
	AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;   // 设置采样窗口大小(顺序采样方式)
	AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;  // 设置ADC内核时钟分频系数
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;         // 设置排序器模式: 1=级联模式(16通道)
	AdcRegs.ADCTRL1.bit.CONT_RUN = 1;         // 设置连续运行模式

	// 设置最大转换通道数(配置了5个通道但只启用了3个)
	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0x4;

	// 配置通道选择序列
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;  // 第1个转换: ADCINA0	对应Iout输出电流
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;  // 第2个转换: ADCINA1	对应Vout输出电压
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2;  // 第3个转换: ADCINA2	对应Vin输入电压

	// 启动SEQ1
	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;  // 使能EPWM模块SOCA触发信号
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0x1;  // 使能SEQ1中断
	EDIS;  // 禁止访问受保护的寄存器
}

// ADC中断服务函数
__interrupt void adc_isr(void)
{

    static Uint16 countLED=0;  // LED闪烁计数器
    countLED++;
    if(countLED==5000)  // 达到计数阈值
    {
    	countLED=0;
       LED9_TOGGLE;  // 切换LED9状态
    }

    // 读取ADC结果并存入数组(右移4位将12位结果对齐)
    A0_Iout[ConversionCount] = AdcRegs.ADCRESULT0>>4;  // 通道0结果(电流输出)
    A1_Vout[ConversionCount] = AdcRegs.ADCRESULT1>>4;  // 通道1结果(电压输出)
    A2_Vin[ConversionCount] = AdcRegs.ADCRESULT2>>4;    // 通道2结果(电压输入)


    // 循环更新数组索引(0-9)
    if(ConversionCount == 9)
    {
        ConversionCount = 0;
    }
    else
    {
        ConversionCount++;
    }

    // 对采样值进行去极值平均滤波
    ADC_A0_Iout = AVG_Nomaxmin(A0_Iout);  // 电流输出平均值
    ADC_A1_Vout = AVG_Nomaxmin(A1_Vout);  // 电压输出平均值
    ADC_A2_Vin = AVG_Nomaxmin(A2_Vin);    // 电压输入平均值


    /* 实际值计算(带滤波)
     * 一阶低通滤波算法
	滤波结果=a*本次采样值+（1-a）*上次滤波结果
	a取值为0~1之间
	就是将新的采样值与上次的滤波结果计算一个加权平均值。
	a的取值决定了算法的灵敏度，a越大，新采集的值占的权重越大，算法越灵敏，但平顺性差；相反，a越小，新采集的值占的权重越小，灵敏度差，但平顺性好

	优点：对周期性干扰具有良好的抑制作用，适用于波动频率较高的场合
	缺点：相位滞后,灵敏度低
     * */

    // 输出电流计算(含滤波系数0.01新值+0.99旧值)
    //Real_Iout = (float)((ADC_A0_Iout)*0.00771)*0.01 + Real_Iout_old*0.99;//未校正，但是已经按照电路图计算好


    // 输入电压计算(两种方式:理论计算和线性校正，当前使用校正公式)	Vin不采取滤波算法，因为需要实时监测，如果输入过压需要及时切断
    //Real_Vin = (float)(ADC_A2_Vin)*0.05703;	//  Real_Vin = ((float)(ADC_A2_Vin)*3.0/4096.0*(Rl_Vin+Rh_Vin)/Rl_Vin)*3.3/4.7;  // 理论计算(已注释),3.3,4.7分别为运放输入端串接电阻和反馈电阻
    Real_Vin = (float)(ADC_A2_Vin)*0.0548+1.2278;// 线性校正公式 y=0.0548x + 1.2278

    // 输出电压计算(两种方式:理论计算和线性校正，当前使用校正公式)	Vout不采取滤波算法，因为需要实时监测，如果输出过压需要及时切断
    //Real_Vout = (float)(ADC_A1_Vout)*0.006912;	//  Real_Vout = ((float)(ADC_A1_Vout)*3.0/4096.0*(Rl_Vout+Rh_Vout)/Rl_Vout)*3.3/4.7;  // 理论计算(已注释),3.3,4.7分别为运放输入端串接电阻和反馈电阻
    Real_Vout = (float)(ADC_A1_Vout)*0.0075-0.0382;	// 线性校正公式 y=0.0075x -0.0382
    Real_Iout = (float)Real_Vout/2.0;

    // 更新旧值用于下次滤波计算
    Real_Iout_old = Real_Iout;
    Real_Vout_old = Real_Vout;
    Real_Vin_old = Real_Vin;

    // 清除中断标志
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;       // 复位SEQ1
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;     // 清除SEQ1中断标志
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;  // 应答PIE组1中断

    return;
}



