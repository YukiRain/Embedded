#ifndef _DIRECTIONCONTROL_H_
#define _DIRECTIONCONTROL_H_
#define Error_Permit  8       //观察图像得，8个像素点能较好的排除噪声
#define Line_Error  1
#define Direction_P    1
#define Direction_I    0
#define Direction_D    1
void outline();
void midline();
void Error_Cal();
char DirectPID();
void mode();

#endif