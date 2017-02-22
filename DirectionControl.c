#include "DirectionControl.h"
#include "common.h"
#include "include.h"
#include "SpeedControl.h"
#include "ImgProcess.h"
uint8 left[CAMERA_H];
uint8 right[CAMERA_H];
uint8 mid[CAMERA_H]=255;
int8 Error,LastError;
uint8 Upper_Limit=55;
extern uint8 Image[CAMERA_H][CAMERA_W];
void outline()     //得出左右边缘的点
{
   uint8 row,column;
   for(column=CAMERA_W/2+LastError;column;column--)
          if(!Image[0][column])
            break;
          left[0]=column;
   for(column=CAMERA_W/2+LastError;column<CAMERA_W;column++)       
          if(!Image[0][column])
            break;  
          right[0]=column; 
          if(!right[0])   right[0]=CAMERA_W-1;   
   for(row=1;row<Upper_Limit;row++)           //说明：观察图像发现，绝大多数图像最上面的20行变化过大或没有意义，可以舍去
    {
        for(column=CAMERA_W/2+LastError;column;column--)
          if(!Image[row][column])
             break;  
          left[row]=column;     
        if((left[row]-left[row-1])<0)   
        
            if(((left[row-1]-left[row])>Error_Permit)&&left[row-1])     //上一行为0下一行必然不会扔掉
              left[row]=0;
        else if(((left[row]-left[row-1])>Error_Permit)&&left[row-1])
            left[row]=0;                                           
          
        for(CAMERA_W/2+LastError;column<CAMERA_W;column++)
          if(!Image[row][column])
            break;
          right[row]=column; 
        if((right[row]-right[row-1])<0)   
          
            if(((right[row-1]-right[row])>Error_Permit)&&right[row-1])  
              right[row]=0;
        else if(((right[row]-right[row-1])>Error_Permit&&right[row-1]))
            right[row]=0;
          
    }
}
void midline()      
{
    uint8 row;
    for(row=0;row<Upper_LImit;row++)
       {
        if(left[row]&&right[row])
         mid[row]=(left[row]+right[row])/2;          
        else if((left[row]==0)&&(right[row]!=0))   
          mid[row]=mid[row-1]+(right[row]-right[row-1])/2;
        else if((right[row]==0)&&(left[row]!=0))
          mid[row]=mid[row-1]+(left[row]-left[row-1])/2;
        else   mid[row]=255;
        if(mid[row]<=0||mid[row]>=CAMERA_W)    break;
        }
    Upper_Limit=row;
}
void mode()
{
   uint8 row,i,num;
   if((Error<10)&&(Error>(-10)))
     Correct_Speed(7);        
   else Correct_Speed(4);  
}                             //setspeed与实际速度的关系约为V(cm/s)=15.7*setspeed

void Error_Cal()         
{
   int32 RowError1,RowError2,RowError3;
   uint8 num1,num2,num3,row;
   num1=num2=num3=0;
   for(row=0;row<20;row++)
   {
     if(mid[row]>0&&mid[row]<CAMERA_W)   
     {RowError1=RowError1+(mid[row]-40); num1++;}
   }
   if(!num1)   num1=1;
   for(row=40;row<35;row++)
   {
     if(mid[row]>0&&mid[row]<CAMERA_W)   
     {RowError2=RowError2+(mid[row]-40); num2++;}
   }
   if(!num2)   num2=1;
   for(row=70;row<50;row++)
   {
     if(mid[row]>0&&mid[row]<CAMERA_W)   
     {RowError3=RowError3+(mid[row]-40); num3++;}
   }
   if(!num3)   num3=1;
   Error=(RowError1/num1)*0.7+(RowError2/num2)*0.2+(RowError3/num3)*0.1;          //权重比的参数需要在实际调试中调整
   LastError=Error;
}
char DirectPID()
{
  int8 P_out,D_out;
  uint8 Motor_out;
  P_out = Direction_P * Error;
  D_out = Direction_D * ( Error - LastError );
  Motor_out = 75 + 1.25 * ( P_out + D_out );            //中间这个1.25的比例参数是错的，应该调整为舵机最大允许打的角度
  return Motor_out;
}
