#ifndef MAX30102_H
#define MAX30102_H

#define MAX30102_IIC_ADDRESS  0x57 //I2C Address

// MAX30102 Commands
// Interrupt configuration (pg 13, 14)
//#define MAX30102_INT_A_FULL_MASK 		   (byte)~0b10000000
static const uint8_t MAX30102_INT_A_FULL_MASK = (uint8_t)~0b10000000;
#define MAX30102_INT_A_FULL_ENABLE 		   0x80
#define MAX30102_INT_A_FULL_DISABLE		   0x00

//#define MAX30102_INT_DATA_RDY_MASK 		   (byte)~0b01000000
static const uint8_t MAX30102_INT_DATA_RDY_MASK = (uint8_t)~0b01000000;
#define MAX30102_INT_DATA_RDY_ENABLE 	   0x40
#define MAX30102_INT_DATA_RDY_DISABLE 	   0x00

//#define MAX30102_INT_ALC_OVF_MASK 		   (byte)~0b00100000
static const uint8_t MAX30102_INT_ALC_OVF_MASK = (uint8_t)~0b00100000;
#define MAX30102_INT_ALC_OVF_ENABLE 	   0x20
#define MAX30102_INT_ALC_OVF_DISABLE 	   0x00

//#define MAX30102_INT_PROX_INT_MASK 		   (byte)~0b00010000
static const uint8_t MAX30102_INT_PROX_INT_MASK = (uint8_t)~0b00010000;
#define MAX30102_INT_PROX_INT_ENABLE 	   0x10
#define MAX30102_INT_PROX_INT_DISABLE 	   0x00

//#define MAX30102_INT_DIE_TEMP_RDY_MASK 	   (byte)~0b00000010
static const uint8_t MAX30102_INT_DIE_TEMP_RDY_MASK = (uint8_t)~0b00000010;
#define MAX30102_INT_DIE_TEMP_RDY_ENABLE   0x02
#define MAX30102_INT_DIE_TEMP_RDY_DISABLE  0x00


// Mode configuration commands (page 19)
#define MAX30102_SHUTDOWN_MASK      0x7F
#define MAX30102_SHUTDOWN    		0x80
#define MAX30102_WAKEUP  			0x00

#define MAX30102_RESET_MASK  		0xBF
#define MAX30102_RESET  			0x40

#define MAX30102_MODE_MASK  		0xF8
#define MAX30102_MODE_REDONLY   	0x02
#define MAX30102_MODE_REDIRONLY  	0x03
#define MAX30102_MODE_MULTILED  	0x07


// Particle sensing configuration commands (pgs 19-20)
#define MAX30102_ADCRANGE_MASK  	0x9F
#define MAX30102_ADCRANGE_2048    	0x00
#define MAX30102_ADCRANGE_4096  	0x20
#define MAX30102_ADCRANGE_8192  	0x40
#define MAX30102_ADCRANGE_16384  	0x60

#define MAX30102_SAMPLERATE_MASK    0xE3
#define MAX30102_SAMPLERATE_50  	0x00
#define MAX30102_SAMPLERATE_100  	0x04
#define MAX30102_SAMPLERATE_200  	0x08
#define MAX30102_SAMPLERATE_400  	0x0C
#define MAX30102_SAMPLERATE_800   	0x10
#define MAX30102_SAMPLERATE_1000    0x14
#define MAX30102_SAMPLERATE_1600    0x18
#define MAX30102_SAMPLERATE_3200    0x1C

#define MAX30102_PULSEWIDTH_MASK    0xFC
#define MAX30102_PULSEWIDTH_69  	0x00
#define MAX30102_PULSEWIDTH_118  	0x01
#define MAX30102_PULSEWIDTH_215  	0x02
#define MAX30102_PULSEWIDTH_411  	0x03


// Configuration Registers
#define MAX30102_FIFOCONFIG  		0x08
#define MAX30102_MODECONFIG  		0x09
#define MAX30102_PARTICLECONFIG  	0x0A    // Note, sometimes listed as "SPO2" config in datasheet (pg. 11)
#define MAX30102_LED1_PULSEAMP  	0x0C
#define MAX30102_LED2_PULSEAMP  	0x0D
#define MAX30102_MULTILEDCONFIG1    0x11
#define MAX30102_MULTILEDCONFIG2    0x12

// FIFO Registers
#define MAX30102_FIFOWRITEPTR    	0x04
#define MAX30102_FIFOOVERFLOW   	0x05
#define MAX30102_FIFOREADPTR    	0x06
#define MAX30102_FIFODATA   		0x07

// Status Registers
#define MAX30102_INTSTAT1   		0x00
#define MAX30102_INTSTAT2   		0x01
#define MAX30102_INTENABLE1 		0x02
#define MAX30102_INTENABLE2 		0x03

// Die Temperature Registers
#define MAX30102_DIETEMPINT  		0x1F
#define MAX30102_DIETEMPFRAC    	0x20
#define MAX30102_DIETEMPCONFIG  	0x21

// Part ID Registers
#define MAX30102_REVISIONID  		0xFE
#define MAX30102_PARTID  			0xFF 

// Proximity Function Registers
#define MAX30102_PROXINTTHRESH  	0x30

//Multi-LED Mode configuration (pg 22)
#define MAX30102_SLOT1_MASK  		0xF8
#define MAX30102_SLOT2_MASK  		0x8F
#define MAX30102_SLOT3_MASK  		0xF8
#define MAX30102_SLOT4_MASK  		0x8F

#define SLOT_NONE   				0x00
#define SLOT_RED_LED    			0x01
#define SLOT_IR_LED  				0x02
#define SLOT_GREEN_LED  			0x03
#define SLOT_NONE_PILOT  			0x04
#define SLOT_RED_PILOT  			0x05
#define SLOT_IR_PILOT   			0x06
#define SLOT_GREEN_PILOT    		0x07

//#define MAX30102_SAMPLEAVG_MASK 	 (byte)~0b11100000
static const uint8_t MAX30102_SAMPLEAVG_MASK = (uint8_t)~0b11100000;
#define MAX30102_SAMPLEAVG_1    	 0x00
#define MAX30102_SAMPLEAVG_2    	 0x20
#define MAX30102_SAMPLEAVG_4    	 0x40
#define MAX30102_SAMPLEAVG_8    	 0x60
#define MAX30102_SAMPLEAVG_16   	 0x80
#define MAX30102_SAMPLEAVG_32   	 0xA0

#define MAX30102_ROLLOVER_MASK  	 0xEF
#define MAX30102_ROLLOVER_ENABLE     0x10
#define MAX30102_ROLLOVER_DISABLE    0x00

#define MAX30102_A_FULL_MASK    	 0xF0
#define MAX30102_EXPECTED_PARTID     0x15


#define MAX30102_SENSE_BUF_SIZE 32

#define I2C_BUFFER_LENGTH 32


//Configuration Options 
//FIFO Configuration(Register address 0x08)
//sampleAverage(Table 3. Sample Averaging)
#define SAMPLEAVG_1     0
#define SAMPLEAVG_2     1
#define SAMPLEAVG_4     2
#define SAMPLEAVG_8     3
#define SAMPLEAVG_16    4
#define SAMPLEAVG_32    5

//Mode configuration(Register address 0x09)
//ledMode(Table 4. Mode Control)
#define MODE_REDONLY    2
#define MODE_RED_IR     3
#define MODE_MULTILED   7

//Particle sensing configuration(Register address 0x0A)
//adcRange(Table 5. SpO2 ADC Range Control)
#define ADCRANGE_2048   0
#define ADCRANGE_4096   1
#define ADCRANGE_8192   2
#define ADCRANGE_16384  3
//sampleRate(Table 6. SpO2 Sample Rate Control)
#define SAMPLERATE_50   0 
#define SAMPLERATE_100  1
#define SAMPLERATE_200  2
#define SAMPLERATE_400  3
#define SAMPLERATE_800  4
#define SAMPLERATE_1000 5
#define SAMPLERATE_1600 6
#define SAMPLERATE_3200 7
//pulseWidth(Table 7. LED Pulse Width Control)
#define PULSEWIDTH_69   0 
#define PULSEWIDTH_118  1
#define PULSEWIDTH_215  2
#define PULSEWIDTH_411  3

//Multi-LED Mode Control Registers(Register address 0x011)
//#define SLOT_NONE       0
//#define SLOT_RED_LED    1
//#define SLOT_IR_LED     2

bool MAX30102_begin();
void MAX30102_enableAlmostFull(void);
void MAX30102_disableAlmostFull(void);
void MAX30102_enableDataReady(void);
void MAX30102_disableDataReady(void);
void MAX30102_enableALCOverflow(void); 
void MAX30102_disableALCOverflow(void);
void MAX30102_enablePROXINT(void);
void MAX30102_disablePROXINT(void);
void MAX30102_enableDieTempReady(void);
void MAX30102_disableDieTempReady(void);
void MAX30102_enableFIFORollover(void);
void MAX30102_disableFIFORollover(void);
void MAX30102_setFIFOAlmostFull(uint8_t numberOfSamples);
void MAX30102_setFIFOAverage(uint8_t numberOfSamples);
void MAX30102_shutDown(void);
void MAX30102_wakeUp(void);
void MAX30102_setLEDMode(uint8_t mode);
void MAX30102_setADCRange(uint8_t adcRange);
void MAX30102_setSampleRate(uint8_t sampleRate);
void MAX30102_setPulseWidth(uint8_t pulseWidth);
void MAX30102_setPulseAmplitudeRed(uint8_t amplitude);
void MAX30102_setPulseAmplitudeIR(uint8_t amplitude);
void MAX30102_disableAllSlots(void);
uint8_t MAX30102_getWritePointer(void);
uint8_t MAX30102_getReadPointer(void);
uint8_t MAX30102_getPartID(void);
uint8_t MAX30102_getRevisionID(void);
void MAX30102_resetFIFO(void);
void MAX30102_softReset(void);
void MAX30102_enableSlot(uint8_t slotNumber, uint8_t device);
float MAX30102_readTemperatureC(void);
float MAX30102_readTemperatureF(void);
void MAX30102_sensorConfiguration(uint8_t ledBrightness, uint8_t sampleAverage, uint8_t ledMode, uint32_t sampleRate, uint32_t pulseWidth, uint32_t adcRange);
uint32_t MAX30102_getRed(void);
uint32_t MAX30102_getIR(void);
uint16_t MAX30102_getNewData(void);
void bitMask(uint8_t reg, uint8_t mask, uint8_t thing);
uint8_t MAX30102_available(void);
void MAX30102_nextSample(void);

void MAX30102_heartrateAndOxygenSaturation(int32_t* SPO2, int8_t* SPO2Valid, int32_t* heartRate, int8_t* heartRateValid);



#endif /* MAX30102_H */

