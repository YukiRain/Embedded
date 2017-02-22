/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       main.c
 * @brief      山外KL26 平台主程序
 * @author     山外科技
 * @version    v5.2
 * @date       2014-10-26
 */

#include "common.h"
#include "include.h"


/*!
 *  @brief      main函数
 *  @since      v5.2
 *  @note       TPM PWM 电机驱动测试(TPM 类似 K60 的 FTM)
 */
void main(void)
{
   Module_Init();
   Interrupt_Init();
    //山外的电机驱动模块，经过 MOS 管 反相隔离。
    //KL26 输出 PWM 为 100% ，实际接入 电机驱动就是 0%
    //KL26 输出 使能端 为 低电平，实际接入 电机驱动 使能端就是 高电平

    while(1)
    {
        
    }
}