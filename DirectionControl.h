#ifndef _DIRECTIONCONTROL_H_
#define _DIRECTIONCONTROL_H_
#define Error_Permit  8       //�۲�ͼ��ã�8�����ص��ܽϺõ��ų�����
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