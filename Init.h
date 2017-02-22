#ifndef _INIT_H_
#define _INIT_H_

/***变量初始化***/
  uint8 Run_Flag;       //行驶启动标志
//控制变量初始化
  uint8 H_Speed;
  uint8 L_Speed;
  uint8 Speed_Prop;
  uint8 Speed_Inte;
  uint8 Speed_Diff;
  uint8 H_Dir;
  uint8 L_Dir;
  uint8 Dir_Prop;
  uint8 Dir_Inte;
  uint8 Dir_Diff;
  uint8 Parameter[10];
//摄像头初始化
  uint8 Camera_Bin;
  uint8 imgbuff[CAMERA_SIZE];
  uint8 Image[CAMERA_H][CAMERA_W];

//路线参量初始化
  /*now empty*/
/*****************/

void Read_Flash_Config(void);
void Module_Init(void);
void Interrupt_Init(void);
#endif