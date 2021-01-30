/*
 * File:   MAX30102.c
 * Author: Md. Khairul Alam
 *
 * Created on December 29, 2020, 3:30 PM
 */
#include "MAX30102.h"
#include <string.h>
#include <avr/io.h>
#include "drivers/i2c_simple_master.h"
#include "time_service.h"
#include "debug_print.h"



bool MAX30102_begin()
{
  if (MAX30102_getPartID() != MAX30102_EXPECTED_PARTID) {
    return false;
  }
  return true;
}


void MAX30102_enableAlmostFull(void) {
  bitMask(MAX30102_INTENABLE1, MAX30102_INT_A_FULL_MASK, MAX30102_INT_A_FULL_ENABLE);
}

void MAX30102_disableAlmostFull(void) {
  bitMask(MAX30102_INTENABLE1, MAX30102_INT_A_FULL_MASK, MAX30102_INT_A_FULL_DISABLE);
}

void MAX30102_enableDataReady(void) {
  bitMask(MAX30102_INTENABLE1, MAX30102_INT_DATA_RDY_MASK, MAX30102_INT_DATA_RDY_ENABLE);
}

void MAX30102_disableDataReady(void) {
  bitMask(MAX30102_INTENABLE1, MAX30102_INT_DATA_RDY_MASK, MAX30102_INT_DATA_RDY_DISABLE);
}

void MAX30102_enableALCOverflow(void) {
  bitMask(MAX30102_INTENABLE1, MAX30102_INT_ALC_OVF_MASK, MAX30102_INT_ALC_OVF_ENABLE);
}

void MAX30102_disableALCOverflow(void) {
  bitMask(MAX30102_INTENABLE1, MAX30102_INT_ALC_OVF_MASK, MAX30102_INT_ALC_OVF_DISABLE);
}

void MAX30102_enablePROXINT(void) {
  bitMask(MAX30102_INTENABLE1, MAX30102_INT_PROX_INT_MASK, MAX30102_INT_PROX_INT_ENABLE);
}

void MAX30102_disablePROXINT(void) {
  bitMask(MAX30102_INTENABLE1, MAX30102_INT_PROX_INT_MASK, MAX30102_INT_PROX_INT_DISABLE);
}

void MAX30102_enableDieTempReady(void) {
  bitMask(MAX30102_INTENABLE2, MAX30102_INT_DIE_TEMP_RDY_MASK, MAX30102_INT_DIE_TEMP_RDY_ENABLE);
}

void MAX30102_disableDieTempReady(void) {
  bitMask(MAX30102_INTENABLE2, MAX30102_INT_DIE_TEMP_RDY_MASK, MAX30102_INT_DIE_TEMP_RDY_DISABLE);
}

void MAX30102_enableFIFORollover(void) {
  bitMask(MAX30102_FIFOCONFIG, MAX30102_ROLLOVER_MASK, MAX30102_ROLLOVER_ENABLE);
}

void MAX30102_disableFIFORollover(void) {
  bitMask(MAX30102_FIFOCONFIG, MAX30102_ROLLOVER_MASK, MAX30102_ROLLOVER_DISABLE);
}

void MAX30102_setFIFOAlmostFull(uint8_t numberOfSamples) {
  bitMask(MAX30102_FIFOCONFIG, MAX30102_A_FULL_MASK, numberOfSamples);
}

void MAX30102_setFIFOAverage(uint8_t numberOfSamples) {
  bitMask(MAX30102_FIFOCONFIG, MAX30102_SAMPLEAVG_MASK, numberOfSamples);
}

void MAX30102_shutDown(void) {
  bitMask(MAX30102_MODECONFIG, MAX30102_SHUTDOWN_MASK, MAX30102_SHUTDOWN);
}

void MAX30102_wakeUp(void) {
  bitMask(MAX30102_MODECONFIG, MAX30102_SHUTDOWN_MASK, MAX30102_WAKEUP);
}

void MAX30102_setLEDMode(uint8_t mode) {
  bitMask(MAX30102_MODECONFIG, MAX30102_MODE_MASK, mode);
}

void MAX30102_setADCRange(uint8_t adcRange) {
  bitMask(MAX30102_PARTICLECONFIG, MAX30102_ADCRANGE_MASK, adcRange);
}

void MAX30102_setSampleRate(uint8_t sampleRate) {
  bitMask(MAX30102_PARTICLECONFIG, MAX30102_SAMPLERATE_MASK, sampleRate);
}

void MAX30102_setPulseWidth(uint8_t pulseWidth) {
  bitMask(MAX30102_PARTICLECONFIG, MAX30102_PULSEWIDTH_MASK, pulseWidth);
}

void MAX30102_setPulseAmplitudeRed(uint8_t amplitude) {
  i2c_write1ByteRegister(MAX30102_IIC_ADDRESS, MAX30102_LED1_PULSEAMP, amplitude);
}

void MAX30102_setPulseAmplitudeIR(uint8_t amplitude) {
  i2c_write1ByteRegister(MAX30102_IIC_ADDRESS, MAX30102_LED2_PULSEAMP, amplitude);
}

void MAX30102_disableAllSlots(void) {
  i2c_write1ByteRegister(MAX30102_IIC_ADDRESS, MAX30102_MULTILEDCONFIG1, 0);
  i2c_write1ByteRegister(MAX30102_IIC_ADDRESS, MAX30102_MULTILEDCONFIG2, 0);
}

uint8_t MAX30102_getWritePointer(void) {
  return (i2c_read1ByteRegister(MAX30102_IIC_ADDRESS, MAX30102_FIFOWRITEPTR));
}

uint8_t MAX30102_getReadPointer(void) {
  return (i2c_read1ByteRegister(MAX30102_IIC_ADDRESS, MAX30102_FIFOREADPTR));
}

uint8_t MAX30102_getPartID(void) {
  return i2c_read1ByteRegister(MAX30102_IIC_ADDRESS, MAX30102_PARTID);
}

uint8_t MAX30102_getRevisionID(void) {
  return i2c_read1ByteRegister(MAX30102_IIC_ADDRESS, MAX30102_REVISIONID);
}

void MAX30102_resetFIFO(void) {
  i2c_write1ByteRegister(MAX30102_IIC_ADDRESS, MAX30102_FIFOWRITEPTR, 0);
  i2c_write1ByteRegister(MAX30102_IIC_ADDRESS, MAX30102_FIFOOVERFLOW, 0);
  i2c_write1ByteRegister(MAX30102_IIC_ADDRESS, MAX30102_FIFOREADPTR, 0);
}

void MAX30102_softReset(void) {
  bitMask(MAX30102_MODECONFIG, MAX30102_RESET_MASK, MAX30102_RESET);

  uint8_t timeCount = 0;
  while (timeCount <= 100)
  {
    uint8_t response = i2c_read1ByteRegister(MAX30102_IIC_ADDRESS, MAX30102_MODECONFIG);
    if ((response & MAX30102_RESET) == 0) break; //We're done!
    DELAY_milliseconds(1); //Let's not over burden the I2C bus
	timeCount++;
  }
}


void MAX30102_enableSlot(uint8_t slotNumber, uint8_t device) {

  switch (slotNumber) {
    case (1):
      bitMask(MAX30102_MULTILEDCONFIG1, MAX30102_SLOT1_MASK, device);
      break;
    case (2):
      bitMask(MAX30102_MULTILEDCONFIG1, MAX30102_SLOT2_MASK, device << 4);
      break;
    case (3):
      bitMask(MAX30102_MULTILEDCONFIG2, MAX30102_SLOT3_MASK, device);
      break;
    case (4):
      bitMask(MAX30102_MULTILEDCONFIG2, MAX30102_SLOT4_MASK, device << 4);
      break;
    default:
      break;
  }
}

float MAX30102_readTemperatureC(void) {
  
  i2c_write1ByteRegister(MAX30102_IIC_ADDRESS, MAX30102_DIETEMPCONFIG, 0x01);

  uint8_t count = 0;
  while (count <= 100)
  {
	uint8_t response = i2c_read1ByteRegister(MAX30102_IIC_ADDRESS, MAX30102_INTSTAT2);
    if ((response & MAX30102_INT_DIE_TEMP_RDY_ENABLE) > 0) break; 
    DELAY_milliseconds(1); 
    count++;
  }

  int8_t tempInt = i2c_read1ByteRegister(MAX30102_IIC_ADDRESS, MAX30102_DIETEMPINT);
  uint8_t tempFrac = i2c_read1ByteRegister(MAX30102_IIC_ADDRESS, MAX30102_DIETEMPFRAC);

  return (float)tempInt + ((float)tempFrac * 0.0625);
}

float MAX30102_readTemperatureF(void) {
  float temp = MAX30102_readTemperatureC();

  if (temp != -999.0) temp = temp * 1.8 + 32.0;

  return (temp);
}


void MAX30102_sensorConfiguration(uint8_t ledBrightness, uint8_t sampleAverage, uint8_t ledMode, uint32_t sampleRate, uint32_t pulseWidth, uint32_t adcRange)
{
  MAX30102_softReset();
  //MAX30102_setFIFOAverage(sampleAverage);
  if (sampleAverage == 1) MAX30102_setFIFOAverage(MAX30102_SAMPLEAVG_1); //No averaging per FIFO record
  else if (sampleAverage == 2) MAX30102_setFIFOAverage(MAX30102_SAMPLEAVG_2);
  else if (sampleAverage == 4) MAX30102_setFIFOAverage(MAX30102_SAMPLEAVG_4);
  else if (sampleAverage == 8) MAX30102_setFIFOAverage(MAX30102_SAMPLEAVG_8);
  else if (sampleAverage == 16) MAX30102_setFIFOAverage(MAX30102_SAMPLEAVG_16);
  else if (sampleAverage == 32) MAX30102_setFIFOAverage(MAX30102_SAMPLEAVG_32);
  else MAX30102_setFIFOAverage(MAX30102_SAMPLEAVG_4);
  
  //MAX30102_setADCRange(adcRange);
  if(adcRange < 4096) MAX30102_setADCRange(MAX30102_ADCRANGE_2048); //7.81pA per LSB
  else if(adcRange < 8192) MAX30102_setADCRange(MAX30102_ADCRANGE_4096); //15.63pA per LSB
  else if(adcRange < 16384) MAX30102_setADCRange(MAX30102_ADCRANGE_8192); //31.25pA per LSB
  else if(adcRange == 16384) MAX30102_setADCRange(MAX30102_ADCRANGE_16384); //62.5pA per LSB
  else MAX30102_setADCRange(MAX30102_ADCRANGE_2048);
  
  //MAX30102_setSampleRate(sampleRate);
  if (sampleRate < 100) MAX30102_setSampleRate(MAX30102_SAMPLERATE_50); //Take 50 samples per second
  else if (sampleRate < 200) MAX30102_setSampleRate(MAX30102_SAMPLERATE_100);
  else if (sampleRate < 400) MAX30102_setSampleRate(MAX30102_SAMPLERATE_200);
  else if (sampleRate < 800) MAX30102_setSampleRate(MAX30102_SAMPLERATE_400);
  else if (sampleRate < 1000) MAX30102_setSampleRate(MAX30102_SAMPLERATE_800);
  else if (sampleRate < 1600) MAX30102_setSampleRate(MAX30102_SAMPLERATE_1000);
  else if (sampleRate < 3200) MAX30102_setSampleRate(MAX30102_SAMPLERATE_1600);
  else if (sampleRate == 3200) MAX30102_setSampleRate(MAX30102_SAMPLERATE_3200);
  else MAX30102_setSampleRate(MAX30102_SAMPLERATE_50);
  
  //MAX30102_setPulseWidth(pulseWidth);
  if (pulseWidth < 118) MAX30102_setPulseWidth(MAX30102_PULSEWIDTH_69); //Page 26, Gets us 15 bit resolution
  else if (pulseWidth < 215) MAX30102_setPulseWidth(MAX30102_PULSEWIDTH_118); //16 bit resolution
  else if (pulseWidth < 411) MAX30102_setPulseWidth(MAX30102_PULSEWIDTH_215); //17 bit resolution
  else if (pulseWidth == 411) MAX30102_setPulseWidth(MAX30102_PULSEWIDTH_411); //18 bit resolution
  else MAX30102_setPulseWidth(MAX30102_PULSEWIDTH_69);
  
  //Default is 0x1F which gets us 6.4mA
  //ledBrightness = 0x02, 0.4mA - Presence detection of ~4 inch
  //ledBrightness = 0x1F, 6.4mA - Presence detection of ~8 inch
  //ledBrightness = 0x7F, 25.4mA - Presence detection of ~8 inch
  //ledBrightness = 0xFF, 50.0mA - Presence detection of ~12 inch
  MAX30102_setPulseAmplitudeRed(ledBrightness);
  MAX30102_setPulseAmplitudeIR(ledBrightness);
  
  MAX30102_enableSlot(1, SLOT_RED_LED);
  if (ledMode > 1) MAX30102_enableSlot(2, SLOT_IR_LED);

  //MAX30102_setLEDMode(ledMode);
  if (ledMode == 3) MAX30102_setLEDMode(MAX30102_MODE_MULTILED); //Watch all three LED channels
  else if (ledMode == 2) MAX30102_setLEDMode(MAX30102_MODE_REDIRONLY); //Red and IR
  else MAX30102_setLEDMode(MAX30102_MODE_REDONLY); //Red only
  activeLEDs = ledMode; 

  MAX30102_enableFIFORollover(); 
  MAX30102_resetFIFO(); 
}


uint32_t MAX30102_getRed(void)
{
  MAX30102_getNewData();
  return (senseBuf.red[senseBuf.head]);
}

uint32_t MAX30102_getIR(void)
{
  MAX30102_getNewData();
  return (senseBuf.IR[senseBuf.head]);
}


uint16_t MAX30102_getNewData(void)
{
  uint8_t readPointer = MAX30102_getReadPointer();
  uint8_t writePointer = MAX30102_getWritePointer();

  int numberOfSamples = 0;

  if (readPointer != writePointer)
  {
    numberOfSamples = writePointer - readPointer;
    if (numberOfSamples < 0) numberOfSamples += 32;

    int bytesNeedToRead = numberOfSamples * activeLEDs * 3;

    while (bytesNeedToRead > 0)
    {
      int toGet = bytesNeedToRead;
      if (toGet > I2C_BUFFER_LENGTH)
      {
        toGet = I2C_BUFFER_LENGTH - (I2C_BUFFER_LENGTH % (activeLEDs * 3)); 
      }

      bytesNeedToRead -= toGet;
      
      while (toGet > 0)
      {
        senseBuf.head++; 
        senseBuf.head %= MAX30102_SENSE_BUF_SIZE; 
		uint32_t tempBuf = 0;
		
		if (activeLEDs > 1)
        {          
		  uint8_t temp[6]; 
		  uint8_t tempex;
		  
		  i2c_readDataBlock(MAX30102_IIC_ADDRESS, MAX30102_FIFODATA, temp, 6); 
		  
		  for(uint8_t i = 0; i < 3; i++){
              tempex = temp[i];
              temp[i] = temp[5-i];
              temp[5-i] = tempex;
            }
		  
          memcpy(&tempBuf, temp, 3*sizeof(temp[0]));
          tempBuf &= 0x3FFFF;
          senseBuf.IR[senseBuf.head] = tempBuf;
          //debug_printIoTAppMsg("ir = %d",senseBuf.IR[senseBuf.head]); 
          memcpy(&tempBuf, temp+3, 3*sizeof(temp[0]));
          tempBuf &= 0x3FFFF;
          senseBuf.red[senseBuf.head] = tempBuf;
          //debug_printIoTAppMsg("red = %d",senseBuf.red[senseBuf.head]);
        }
		else 
		{ 
          uint8_t temp[3];
          uint8_t tempex;

		  i2c_readDataBlock(MAX30102_IIC_ADDRESS, MAX30102_FIFODATA, temp, 3); 
            
          tempex = temp[0];
          temp[0] = temp[2];
          temp[2] = tempex;

          memcpy(&tempBuf, temp, 3*sizeof(temp[0]));
          tempBuf &= 0x3FFFF;
          senseBuf.red[senseBuf.head] = tempBuf;
        }
        
        toGet -= activeLEDs * 3;
      }
    } 
  } 
  return (numberOfSamples); 
}

uint8_t MAX30102_available(void)
{
  int8_t numberOfSamples = senseBuf.head - senseBuf.tail;
  if (numberOfSamples < 0) numberOfSamples += MAX30102_SENSE_BUF_SIZE;

  return (numberOfSamples);
}

void MAX30102_nextSample(void)
{
  if(MAX30102_available()) //Only advance the tail if new data is available
  {
    senseBuf.tail++;
    senseBuf.tail %= MAX30102_SENSE_BUF_SIZE; //Wrap condition
  }
}


void MAX30102_heartrateAndOxygenSaturation(int32_t* SPO2, int8_t* SPO2Valid, int32_t* heartRate, int8_t* heartRateValid)
{
  uint32_t irBuffer[100];
  uint32_t redBuffer[100];
  int32_t bufferLength = 100;

  for (uint8_t i = 0 ; i < bufferLength ; ) {
	  
    int sampleNumber = MAX30102_getNewData(); 
 
    int8_t numberOfSamples = senseBuf.head - senseBuf.tail;
    if (numberOfSamples < 0) {
      numberOfSamples += MAX30102_SENSE_BUF_SIZE;
    }

    while(numberOfSamples--) {
      redBuffer[i] = senseBuf.red[senseBuf.tail];
      irBuffer[i] = senseBuf.IR[senseBuf.tail];

      senseBuf.tail++;
      senseBuf.tail %= MAX30102_SENSE_BUF_SIZE;
      i++;
      if(i == bufferLength) break;
    }
  }
  maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, SPO2, SPO2Valid, heartRate, heartRateValid);
}


void bitMask(uint8_t reg, uint8_t mask, uint8_t thing)
{
  uint8_t originalContents = i2c_read1ByteRegister(MAX30102_IIC_ADDRESS, reg);
  originalContents = originalContents & mask;
  i2c_write1ByteRegister(MAX30102_IIC_ADDRESS, reg, originalContents | thing);
}