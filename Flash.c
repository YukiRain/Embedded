#include "common.h"
#include "include.h"
#include "Flash.h"

void Save_Camera(uint8 Camera_Bin)
{
  SPILCD_ShowStr(80,160,"Saving....",BLUE,GRED);
  flash_erase_sector(Camera_Bin_Sector);
  flash_write(Camera_Bin_Sector,Camera_Bin_Offset,(Camera_Bin|0x00000000));
}

void Save_Parameter(uint8 *Parameter)
{
  SPILCD_ShowStr(80,160,"Saving....",BLUE,GRED);
  flash_erase_sector(Save_Sector);
  flash_write(Save_Sector,H_Speed_Offset,(Parameter[0])&0xFFFFFFFF);
  flash_write(Save_Sector,L_Speed_Offset,(Parameter[1]|0x00000000));
  flash_write(Save_Sector,S_Prop_Offset,(Parameter[2]|0x00000000));
  flash_write(Save_Sector,S_Inte_Offset,(Parameter[3]|0x00000000));
  flash_write(Save_Sector,S_Diff_Offset,(Parameter[4]|0x00000000));
  flash_write(Save_Sector,H_Direction_Offset,(Parameter[5]|0x00000000));
  flash_write(Save_Sector,L_Direction_Offset,(Parameter[6]|0x00000000));
  flash_write(Save_Sector,D_Prop_Offset,(Parameter[7])|0x00000000);
  flash_write(Save_Sector,D_Inte_Offset,(Parameter[8]|0x00000000));
  flash_write(Save_Sector,D_Diff_Offset,(Parameter[9]|0x00000000));
}