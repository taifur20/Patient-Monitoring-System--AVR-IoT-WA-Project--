/*
 * File:   MLX90614.c
 * Author: Md. Khairul Alam
 *
 * Created on December 30, 2020, 11:13 PM
 */
#include "MLX90614.h"
#include "drivers/i2c_simple_master.h"
#include "debug_print.h"


uint16_t MLX90614_ReadAmbTemp(void)
{   
    uint8_t temp[3]; 
    uint16_t rawTemperature; 
    i2c_readDataBlock(MLX90614_DEFAULT_ADDRESS, MLX90614_REGISTER_TA, temp, 3);
    
	rawTemperature = temp[1] << 8 | temp[2];
    return rawTemperature;
    //debug_printIoTAppMsg("aa= %d   ba = %d   ca = %d",temp[0], temp[1], temp[2]);
	
}

uint16_t MLX90614_ReadObj_1_Temp(void)
{   
    uint8_t temp[3]; 
    uint16_t rawTemperature;  
    i2c_readDataBlock(MLX90614_DEFAULT_ADDRESS, MLX90614_REGISTER_TOBJ1, temp, 3);
	
    rawTemperature = temp[1] << 8 | temp[2];
    return rawTemperature;
    //debug_printIoTAppMsg("ao = %d   bo = %d   co = %d",temp[0], temp[1], temp[2]);
	
}

uint16_t MLX90614_ReadObj_2_Temp(void)
{   
    uint8_t temp[3]; 
    uint16_t rawTemperature;  
    i2c_readDataBlock(MLX90614_DEFAULT_ADDRESS, MLX90614_REGISTER_TOBJ2, temp, 3);
	
    rawTemperature = temp[1] << 8 | temp[2];
    return rawTemperature;
    //debug_printIoTAppMsg("ao = %d   bo = %d   co = %d",temp[0], temp[1], temp[2]);
	
}

uint16_t MLX90614_ReadMaxTemp(void)
{   
    uint8_t temp[3]; 
    uint16_t rawTemperature; 
    i2c_readDataBlock(MLX90614_DEFAULT_ADDRESS, MLX90614_REGISTER_TOMAX, temp, 3);
    
    rawTemperature = temp[1] << 8 | temp[2];
    return rawTemperature;	
    //debug_printIoTAppMsg("ao = %d   bo = %d   co = %d",temp[0], temp[1], temp[2]);
	
}

uint16_t MLX90614_ReadMinTemp(void)
{   
    uint8_t temp[3]; 
    uint16_t rawTemperature; 
    i2c_readDataBlock(MLX90614_DEFAULT_ADDRESS, MLX90614_REGISTER_TOMIN, temp, 3);
	
    rawTemperature = temp[1] << 8 | temp[2];
    return rawTemperature;
    //debug_printIoTAppMsg("ao = %d   bo = %d   co = %d",temp[0], temp[1], temp[2]);
    
}


uint8_t MLX90614_ReadAddress(void)
{   
    uint8_t temp[3];   
    i2c_readDataBlock(MLX90614_DEFAULT_ADDRESS, MLX90614_REGISTER_ADDRESS, temp, 3);
	
    return temp[2];
    //debug_printIoTAppMsg("addo = %d   bddo = %d   cddo = %d",temp[0], temp[1], temp[2]);
    
}


float MLX90614_ambTempC(void) 
{
  float temp = MLX90614_ReadAmbTemp();
  temp *= .02;
  temp -= 273.15;
  return temp;
}


float MLX90614_obj1TempC(void) 
{
  float temp = MLX90614_ReadObj_1_Temp();
  temp *= .02;
  temp -= 273.15;
  return temp;
}


float MLX90614_obj2TempC(void) 
{
  float temp = MLX90614_ReadObj_2_Temp();
  temp *= .02;
  temp -= 273.15;
  return temp;
}


float MLX90614_ambTempF(void) 
{
  return (MLX90614_ambTempC() * 9/5) + 32;
}


float MLX90614_obj1TempF(void) 
{
  return (MLX90614_obj1TempC() * 9/5) + 32;
}


float MLX90614_obj2TempF(void) 
{
  return (MLX90614_obj2TempC() * 9/5) + 32;
}
