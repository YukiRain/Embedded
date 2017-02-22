#include "common.h"
#include "include.h"
#include "SpeedControl.h"
#include "DirectionControl.h"

int32 Right_Speed;
int32 Left_Speed;
void Get_Speed()
{
  Left_Speed = tpm_pulse_get(TPM2);               //获取左侧tpm速度
  Right_Speed = lptmr_pulse_get();                //获取右侧lptmr速度
  
  /*清空计数值*/
  tpm_pulse_clean(TPM2);
  lptmr_pulse_clean();
}

extern uint8 S_Prop;
extern uint8 S_Inte;
extern uint8 S_Diff;
extern uint8 H_Speed;
extern uint8 L_Speed;
uint16 Speed_P_L;
uint16 Speed_P_R;
uint16 Speed_I_L;
uint16 Speed_I_R;
uint16 Motor_Right_Out;
uint16 Motor_Left_Out;

uint8 Set_Speed=0;
void Correct_Speed(uint8 SetSpeed)
{
  uint32 S_Speed_temp;
  int32 SpeedError_L;
  int32 SpeedError_R;       
  S_Speed_temp = Set_Speed * 500;
  /*计算速度误差*/
  SpeedError_L = S_Speed_temp - Left_Speed;
  SpeedError_R = S_Speed_temp - Right_Speed;
  /*速度PI*/
  Speed_P_L = SpeedError_L * S_Prop;
  Speed_P_R = SpeedError_R * S_Prop;
  //积分累加
  Speed_I_L += SpeedError_L * S_Inte;
  Speed_I_R += SpeedError_R * S_Inte;
  //限幅
  if(Speed_I_L > Speed_I_Max)
    Speed_I_L = Speed_I_Max;
  if(Speed_I_R > Speed_I_Max)
    Speed_I_R = Speed_I_Max;
  
  Motor_Right_Out = (Speed_P_R + Speed_I_R);
  Motor_Left_Out = (Speed_P_L + Speed_I_L);
}


void Motor_Out()
{ 
  tpm_pwm_duty(TPM0,TPM_CH0,Motor_Right_Out);
  tpm_pwm_duty(TPM0,TPM_CH1,0);
  tpm_pwm_duty(TPM0,TPM_CH2,Motor_Right_Out);
  tpm_pwm_duty(TPM0,TPM_CH3,0);
  tpm_pwm_duty(TPM1,TPM_CH0,DirectPID());
}