#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

//===========================================================================
// 函数: EPWM4_Init (严格按照您的EPWM1代码转换)
//===========================================================================
void EPWM4_Init(Uint16 tbprd, Uint16 phaseshiftvalue , Uint16 duty )
{
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;   // Disable TBCLK within the ePWM
	SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 1;  // ePWM4
	EDIS;

	InitEPwm4Gpio();

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Stop all the TB clocks
	EDIS;

	// Setup Sync
	EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;  // Pass through
	// Allow each timer to be sync'ed
	EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm4Regs.TBPHS.half.TBPHS = 0;
	EPwm4Regs.TBCTR = 0x0000;                  // Clear counter
	EPwm4Regs.TBPRD = tbprd;
	EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;    // Count up
	EPwm4Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;
	EPwm4Regs.TBCTL.bit.CLKDIV=TB_DIV1;

	// Setup shadow register load on ZERO
	EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	// Set Compare values
	EPwm4Regs.CMPA.half.CMPA = duty;    // Set compare A value
	EPwm4Regs.CMPB = duty;              // Set Compare B value

	// Set actions
	EPwm4Regs.AQCTLA.bit.ZRO = AQ_SET;            // Set PWM4A on Zero
	EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR;          // Clear PWM4A on event A, up count
	EPwm4Regs.AQCTLB.bit.ZRO = AQ_CLEAR;            // Set PWM4B on Zero
	EPwm4Regs.AQCTLB.bit.CBU = AQ_SET;          // Clear PWM4B on event B, up count

	EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
	EPwm4Regs.ETSEL.bit.INTEN = 1;  // Enable INT
	EPwm4Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event

    // Active Low PWMs - Setup Deadband
    EPwm4Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;//RED FED are enabled使能双边沿延时
    EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;//B is inverted 极性选择控制（EPWMB翻转）
    EPwm4Regs.DBCTL.bit.IN_MODE = DBA_ALL;//A is source of rising and falling  （EPWMxA是双边沿延时输入源）
    EPwm4Regs.DBRED = 20;  //deadtime
    EPwm4Regs.DBFED = 20;

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;         // Start all the timers synced
	EDIS;
}



//===========================================================================
void EPWM5_Init(Uint16 tbprd, Uint16 phaseshiftvalue , Uint16 duty )
{
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;   // 在 ePWM 内部禁用 TBCLK
	SysCtrlRegs.PCLKCR1.bit.EPWM5ENCLK = 1;  // 使能 EPWM5 时钟
	EDIS;

	InitEPwm5Gpio();

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // 停止所有 TB 时钟
	EDIS;

	// 设置同步
	EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;  // 直通

	// 计算 90 度的相位移值
	//Uint16 phaseShiftValue = (Uint16)(((float)tbprd * 180.0 / 360.0) + 0.5); // 加 0.5 以四舍五入到最接近的整数

	// 设置相位移
	EPwm5Regs.TBCTL.bit.PHSEN = TB_ENABLE;      // 使能相位加载
	EPwm5Regs.TBPHS.half.TBPHS = phaseshiftvalue; // 设置相位移数值
	EPwm5Regs.TBCTL.bit.PHSDIR = 0;

	EPwm5Regs.TBCTR = 0x0000;                  // 清零计数器
	EPwm5Regs.TBPRD = tbprd;
	EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;    // 递增计数模式
	EPwm5Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;
	EPwm5Regs.TBCTL.bit.CLKDIV=TB_DIV1;

	// 在 ZERO 时加载影子寄存器
	EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	// 设置比较值
	EPwm5Regs.CMPA.half.CMPA = duty;    // 设置比较 A 的值
	EPwm5Regs.CMPB = duty;              // 设置比较 B 的值

	// 设置动作
	EPwm5Regs.AQCTLA.bit.ZRO = AQ_SET;            // 在计数器为零时置位 PWM1A
	EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR;          // 在 A 事件上升计数时清除 PWM1A
	EPwm5Regs.AQCTLB.bit.ZRO = AQ_CLEAR;            // 在计数器为零时清除 PWM1B
	EPwm5Regs.AQCTLB.bit.CBU = AQ_SET;          // 在 B 事件上升计数时置位 PWM1B

	EPwm5Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // 在 Zero 事件触发中断
	EPwm5Regs.ETSEL.bit.INTEN = 1;  // 使能中断
	EPwm5Regs.ETPS.bit.INTPRD = ET_1ST;           // 在第一个事件产生中断

    // 有源低电平 PWM——设置死区
    EPwm5Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;// RED/FED 使能，双边沿延时
    EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;// B 端反相（极性选择控制，EPWMB 翻转）
    EPwm5Regs.DBCTL.bit.IN_MODE = DBA_ALL;// A 作为上升沿与下降沿的源（EPWMxA 是双边沿延时输入源）
    EPwm5Regs.DBRED = 10;  // 死区时间
    EPwm5Regs.DBFED = 10;

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;         // 以同步方式启动所有定时器
	EDIS;
}

//===========================================================================
void EPWM6_Init(Uint16 tbprd, Uint16 phaseshiftvalue , Uint16 duty )
{
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;   // 在 ePWM 内部禁用 TBCLK
	SysCtrlRegs.PCLKCR1.bit.EPWM6ENCLK = 1;  // 使能 EPWM6 时钟
	EDIS;

	InitEPwm6Gpio();

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // 停止所有 TB 时钟
	EDIS;

	// 设置同步
	EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;  // 直通

	// 计算 90 度的相位移值
	//Uint16 phaseShiftValue = (Uint16)(((float)tbprd * 180.0 / 360.0) + 0.5); // 加 0.5 以四舍五入到最接近的整数

	// 设置相位移
	EPwm6Regs.TBCTL.bit.PHSEN = TB_ENABLE;      // 使能相位加载
	EPwm6Regs.TBPHS.half.TBPHS = phaseshiftvalue; // 设置相位移数值
	EPwm6Regs.TBCTL.bit.PHSDIR = 0;

	EPwm6Regs.TBCTR = 0x0000;                  // 清零计数器
	EPwm6Regs.TBPRD = tbprd;
	EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;    // 递增计数模式
	EPwm6Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;
	EPwm6Regs.TBCTL.bit.CLKDIV=TB_DIV1;

	// 在 ZERO 时加载影子寄存器
	EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	// 设置比较值
	EPwm6Regs.CMPA.half.CMPA = duty;    // 设置比较 A 的值
	EPwm6Regs.CMPB = duty;              // 设置比较 B 的值

	// 设置动作
	EPwm6Regs.AQCTLA.bit.ZRO = AQ_SET;            // 在计数器为零时置位 PWM1A
	EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR;          // 在 A 事件上升计数时清除 PWM1A
	EPwm6Regs.AQCTLB.bit.ZRO = AQ_CLEAR;            // 在计数器为零时清除 PWM1B
	EPwm6Regs.AQCTLB.bit.CBU = AQ_SET;          // 在 B 事件上升计数时置位 PWM1B

	EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // 在 Zero 事件触发中断
	EPwm6Regs.ETSEL.bit.INTEN = 1;  // 使能中断
	EPwm6Regs.ETPS.bit.INTPRD = ET_1ST;           // 在第一个事件产生中断

    // 有源低电平 PWM——设置死区
    EPwm6Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;// RED/FED 使能，双边沿延时
    EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;// B 端反相（极性选择控制，EPWMB 翻转）
    EPwm6Regs.DBCTL.bit.IN_MODE = DBA_ALL;// A 作为上升沿与下降沿的源（EPWMxA 是双边沿延时输入源）
    EPwm6Regs.DBRED = 20;  // 死区时间
    EPwm6Regs.DBFED = 20;

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;         // 以同步方式启动所有定时器
	EDIS;
}



