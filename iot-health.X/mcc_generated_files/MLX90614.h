#ifndef MLX90614_H
#define MLX90614_H

// MLX90614 Default I2C Address //
#define MLX90614_DEFAULT_ADDRESS  0x5A
// MLX90614 RAM and EEPROM Addresses //
#define MLX90614_REGISTER_TA      0x06
#define MLX90614_REGISTER_TOBJ1	  0x07
#define MLX90614_REGISTER_TOBJ2	  0x08
#define MLX90614_REGISTER_TOMAX   0x20
#define MLX90614_REGISTER_TOMIN   0x21
#define MLX90614_REGISTER_PWMCTRL 0x22
#define MLX90614_REGISTER_TARANGE 0x23
#define MLX90614_REGISTER_KE      0x24
#define MLX90614_REGISTER_CONFIG  0x25
#define MLX90614_REGISTER_ADDRESS 0x2E
#define MLX90614_REGISTER_ID0     0x3C
#define MLX90614_REGISTER_ID1     0x3D
#define MLX90614_REGISTER_ID2     0x3E
#define MLX90614_REGISTER_ID3     0x3F
#define MLX90614_REGISTER_SLEEP   0xFF



uint16_t MLX90614_ReadAmbTemp(void);
uint16_t MLX90614_ReadObj_1_Temp(void);
uint16_t MLX90614_ReadObj_2_Temp(void);
uint16_t MLX90614_ReadObj_2_Temp(void);
uint16_t MLX90614_ReadMaxTemp(void);
uint16_t MLX90614_ReadMinTemp(void);
uint8_t MLX90614_ReadAddress(void);
float MLX90614_ambTempC(void) ;
float MLX90614_obj1TempC(void) ;
float MLX90614_obj2TempC(void) ;
float MLX90614_ambTempF(void) ;
float MLX90614_obj1TempF(void) ;
float MLX90614_obj2TempF(void) ;



#endif /* MLX90614_H */