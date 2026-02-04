/*
 * leds.c
 *
 *  Created on: 2025年7月29日
 *      Author: Jin
 */

#include  "leds.h"

//下面为硬汉YH开发板
//void  LED_Init(void)
//{
//
//EALLOW;
//
////LED14 端口配置
//GpioCtrlRegs.GPCMUX1.bit.GPIO68=0;
//GpioCtrlRegs.GPCDIR.bit.GPIO68=1;
//GpioCtrlRegs.GPCPUD.bit.GPIO68=0;
//
////LED13 端口配置
//GpioCtrlRegs.GPCMUX1.bit.GPIO67=0;
//GpioCtrlRegs.GPCDIR.bit.GPIO67=1;
//GpioCtrlRegs.GPCPUD.bit.GPIO67=0;
//
////LED12 端口配置
//GpioCtrlRegs.GPCMUX1.bit.GPIO66=0;
//GpioCtrlRegs.GPCDIR.bit.GPIO66=1;
//GpioCtrlRegs.GPCPUD.bit.GPIO66=0;
//
////LED11 端口配置
//GpioCtrlRegs.GPCMUX1.bit.GPIO65=0;
//GpioCtrlRegs.GPCDIR.bit.GPIO65=1;
//GpioCtrlRegs.GPCPUD.bit.GPIO65=0;
//
////LED10 端口配置
//GpioCtrlRegs.GPCMUX1.bit.GPIO64=0;
//GpioCtrlRegs.GPCDIR.bit.GPIO64=1;
//GpioCtrlRegs.GPCPUD.bit.GPIO64=0;
//
////LED9端口配置
//GpioCtrlRegs.GPBMUX2.bit.GPIO61=0;
//GpioCtrlRegs.GPBDIR.bit.GPIO61=1;
//GpioCtrlRegs.GPBPUD.bit.GPIO61=0;
//
////LED8 端口配置
//GpioCtrlRegs.GPBMUX2.bit.GPIO60=0;
//GpioCtrlRegs.GPBDIR.bit.GPIO60=1;
//GpioCtrlRegs.GPBPUD.bit.GPIO60=0;
//
//GpioDataRegs.GPCSET.bit.GPIO68=1;
//GpioDataRegs.GPCSET.bit.GPIO67=1;
//GpioDataRegs.GPCSET.bit.GPIO66=1;
//GpioDataRegs.GPCSET.bit.GPIO65=1;
//GpioDataRegs.GPCSET.bit.GPIO64=1;
//GpioDataRegs.GPBSET.bit.GPIO61=1;
//GpioDataRegs.GPBSET.bit.GPIO60=1;
//
//
//EDIS;
//}

//下面为研旭开发板代码
void LED_Init(void)
{
    EALLOW;

    // LED2 -> GPIO3
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;  // 配置为 GPIO 功能
    GpioCtrlRegs.GPADIR.bit.GPIO3  = 1;  // 设置为输出
    GpioCtrlRegs.GPAPUD.bit.GPIO3  = 0;  // 使能上拉

    // LED3 -> GPIO4
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO4  = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO4  = 0;

    // LED4 -> GPIO0
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO0  = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO0  = 0;

    // LED5 -> GPIO1
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO1  = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO1  = 0;

    // LED6 -> GPIO2
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO2  = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO2  = 0;

    // 初始化所有 LED 输出为高（通常为熄灭）
    GpioDataRegs.GPASET.bit.GPIO3 = 1;
    GpioDataRegs.GPASET.bit.GPIO4 = 1;
    GpioDataRegs.GPASET.bit.GPIO0 = 1;
    GpioDataRegs.GPASET.bit.GPIO1 = 1;
    GpioDataRegs.GPASET.bit.GPIO2 = 1;

    EDIS;
}

