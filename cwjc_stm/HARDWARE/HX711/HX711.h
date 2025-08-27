#ifndef __HX711_H
#define __HX711_H

#include "sys.h"

#define HX711_SCK PCout(14)// PB0
#define HX711_DOUT PCin(15)// PB1


extern void Init_HX711pin(void);
extern u32 HX711_Read(void);
extern void Get_Maopi(void);
extern void Get_Weight(void);

extern u32 HX711_Buffer;
extern float Weight_Maopi;
extern float Weight_Shiwu;
extern u8 Flag_Error;

#endif


