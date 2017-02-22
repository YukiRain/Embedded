#include "common.h"
#include "include.h"
#include "Init.h"
#include "Flash.h"
#include "SpeedControl.h"
#include "DirectionControl.h"

void Module_Init()
{
  
 
 
  
  /*TPMģ���ʼ��*/

  tpm_pwm_init(TPM1,TPM_CH0,50,750);                            //���
  
  tpm_pwm_init(TPM0,TPM_CH0,1000,10);                            //���
  tpm_pwm_init(TPM0,TPM_CH1,1000,20);
  tpm_pwm_init(TPM0,TPM_CH2,1000,30);
  tpm_pwm_init(TPM0,TPM_CH3,1000,40);

  tpm_pulse_init(TPM2,TPM_CLKIN0,TPM_PS_1);
 
  
  /*UART��ʼ��*/

  uart_init(UART0,115200);
  

  
  /*PIT�жϳ�ʼ��*/

  pit_init_ms(PIT0,1);          //ÿ1ms�ж�һ��


  
  /*LPTMR���������ʼ��*/

  lptmr_pulse_init(LPT0_ALT2,0xffff,LPT_Rising);

  DELAY_MS(500);

}

extern uint8 Parameter[10];
void Read_Flash_Config()
{  
  /****���Ʊ�����ȡ****/
   H_Speed=flash_read(Save_Sector,H_Speed_Offset,uint8);
    Parameter[0]=H_Speed;
  L_Speed=flash_read(Save_Sector,L_Speed_Offset,uint8);
    Parameter[1]=L_Speed;
  Speed_Prop=flash_read(Save_Sector,S_Prop_Offset,uint8);
    Parameter[2]=Speed_Prop;
  Speed_Inte=flash_read(Save_Sector,S_Inte_Offset,uint8);
    Parameter[3]=Speed_Inte;
  Speed_Diff=flash_read(Save_Sector,S_Diff_Offset,uint8);
    Parameter[4]=Speed_Diff;
  H_Dir=flash_read(Save_Sector,H_Direction_Offset,uint8);
    Parameter[5]=H_Dir;
  L_Dir=flash_read(Save_Sector,L_Direction_Offset,uint8);
    Parameter[6]=L_Dir;
  Dir_Prop=flash_read(Save_Sector,D_Prop_Offset,uint8);
    Parameter[7]=Dir_Prop;
  Dir_Inte=flash_read(Save_Sector,D_Inte_Offset,uint8);
    Parameter[8]=Dir_Inte;
  Dir_Diff=flash_read(Save_Sector,D_Diff_Offset,uint8);
    Parameter[9]=Dir_Diff;
  /****ӥ�۲�����ȡ****/
  Camera_Bin=flash_read(Save_Sector,Camera_Bin_Offset,uint8);

}


/*********************************************************�жϷ�����*********************************************************/
/*
 *  @brief      PORTA�жϷ�����
 *  @since      v5.0
 */
void PORTA_IRQHandler()
{
    uint8  n = 0;    //���ź�
    uint32 flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //���жϱ�־λ

    n = 6;                                              //���ж�
    if(flag & (1 << n))                                 //PTA6�����ж�
    {
        camera_vsync();
    }
}

/*!
 *  @brief      DMA0�жϷ�����
 *  @since      v5.0
 */
void DMA0_IRQHandler()
{
    camera_dma();
}

/*!
 *  @brief      PIT�жϷ�����
 *  @since      v5.0
 */
uint8 pit_ms_spd;
uint8 pit_ms_cnt;
uint8 Eagle_ms_cnt;
extern uint8 menu_focus;
void PIT_IRQHandler(void)
{
  if(PIT_TFLG(PIT0) == 1 )        //�ж��Ƿ� PIT0 �����ж�
  {
    if(pit_ms_cnt<20)
      pit_ms_cnt++;
    else
    {
      key_IRQHandler();
      pit_ms_cnt=0;
    }
    PIT_Flag_Clear(PIT0);       //���жϱ�־λ
    
    
  }  
}
void PIT_IRQ_Speed(void)
{
  if(PIT_TFLG(PIT0)==1)
  {
      if(pit_ms_spd<20)
         pit_ms_spd++;
      else
      {
         Get_Speed();
         outline();
         midline();
         Error_Cal();
         mode();
         Motor_out();
      }
  }
  PIT_Flag_Clear(PIT0);
}
void Interrupt_Init()
{
  set_vector_handler(PORTA_VECTORn ,PORTA_IRQHandler);
  set_vector_handler(DMA0_VECTORn ,DMA0_IRQHandler);
  set_vector_handler(PIT_VECTORn ,PIT_IRQHandler);
  
  /*k60���������ȼ�*/
  //NVIC_SetPriorityGrouping(2);            //�������ȼ�����,4bit ��ռ���ȼ�,û�������ȼ�
  NVIC_SetPriority(PORTA_IRQn,0);         //�������ȼ�   �г��ж�
  NVIC_SetPriority(DMA0_IRQn,1);          //�������ȼ�   DMA�����ж�
  NVIC_SetPriority(PIT_IRQn,2);          //�������ȼ�   PIT��ʱ���ж�,��ѹͼ��,IIC�������ɼ�

  
  enable_irq(PIT_IRQn);
  enable_irq(PORTA_IRQn);
  
  enable_irq(DMA0_IRQn);
                                             //�����ж�
  
}
