#ifndef _IMGPROCESS_H_
#define _IMGPROCESS_H_

#include "common.h"
#include "include.h"

void img_extract(uint8 *dst, uint8 *src, uint32 srclen);
void vcan_sendimg(uint8 *imgaddr, uint32 imgsize);
void Image_Deal();

#endif