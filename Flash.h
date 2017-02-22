#ifndef _FLASH_H_
#define _FLASH_H_

#include "common.h"
#include "include.h"

#define Save_Sector 255
/*�ٶȴ�С��ַ*/
#define H_Speed_Offset 8 
#define L_Speed_Offset 16

/*�ٶȿ���PID��ַ*/
#define S_Prop_Offset 24
#define S_Inte_Offset 32
#define S_Diff_Offset 40

/*�������*/
#define H_Direction_Offset 48
#define L_Direction_Offset 56

/*�������PID��ַ*/
#define D_Prop_Offset 64
#define D_Inte_Offset 72
#define D_Diff_Offset 80

/*���������Ʋ���*/
#define Camera_Bin_Sector 253
#define Camera_Bin_Offset 0


void Save_Camera(uint8 Camera_Bin);
void Save_Parameter(uint8 *Parameter);
#endif