/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      ɽ��KL26 ƽ̨������
 * @author     ɽ��Ƽ�
 * @version    v5.2
 * @date       2014-10-26
 */

#include "common.h"
#include "include.h"


/*!
 *  @brief      main����
 *  @since      v5.2
 *  @note       TPM PWM �����������(TPM ���� K60 �� FTM)
 */
void main(void)
{
   Module_Init();
   Interrupt_Init();
    //ɽ��ĵ������ģ�飬���� MOS �� ������롣
    //KL26 ��� PWM Ϊ 100% ��ʵ�ʽ��� ����������� 0%
    //KL26 ��� ʹ�ܶ� Ϊ �͵�ƽ��ʵ�ʽ��� ������� ʹ�ܶ˾��� �ߵ�ƽ

    while(1)
    {
        
    }
}