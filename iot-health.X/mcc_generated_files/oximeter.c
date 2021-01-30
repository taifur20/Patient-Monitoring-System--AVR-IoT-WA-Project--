// For pulse oximeter
// Registers
#define MAX30100_INT_STATUS1     0x00  // Which interrupts are tripped
#define MAX30100_INT_STATUS2     0x01  // Which interrupts are tripped
#define MAX30100_INT_ENABLE1     0x02  // Which interrupts are active
#define MAX30100_INT_ENABLE2    0x03  // Which interrupts are active

#define MAX30100_FIFO_WR_PTR    0x04  // Where data is being written
#define MAX30100_OVRFLOW_CTR    0x05  // Number of lost samples
#define MAX30100_FIFO_RD_PTR    0x06  // Where to read from
#define MAX30100_FIFO_DATA      0x07 // Ouput data buffer

#define MAX30100_FIFO_CONFIG    0x08
#define MAX30100_MODE_CONFIG    0x09  // Control register
#define MAX30100_SPO2_CONFIG    0x0A  // Oximetry settings
#define MAX30100_LED1_AMP        0x0C
#define MAX30100_LED2_AMP        0x0D
#define MAX30100_PILOT           0x10
#define MAX310100_MLED_CTRL1 	0x11
#define MAX310100_MLED_CTRL2	0x12
#define MAX30100_TEMP_INTG      0x1F  // Temperature value, whole number
#define MAX30100_TEMP_FRAC      0x20  // Temperature value, fraction
#define MAX30100_DIE_TEMP        0x21
#define MAX30100_PROX_INT_TRESH  0x30
#define MAX30100_REV_ID         0xFE  // Part revision
#define MAX30100_PART_ID        0xFF  // Part ID, normally 0x11

#define MAX30100_LED_CONFIG          0x09

#define MAX30100_ADDRESS        0x57  // 8bit address converted to 7bit


typedef enum{ // This is the same for both LEDs
  pw200,    // 200us pulse
  pw400,    // 400us pulse
  pw800,    // 800us pulse
  pw1600    // 1600us pulse
}pulseWidth;

typedef enum{
  sr50,    // 50 samples per second
  sr100,   // 100 samples per second
  sr167,   // 167 samples per second
  sr200,   // 200 samples per second
  sr400,   // 400 samples per second
  sr600,   // 600 samples per second
  sr800,   // 800 samples per second
  sr1000   // 1000 samples per second
}sampleRate;

typedef enum{
  i0,    // No current
  i4,    // 4.4mA
  i8,    // 7.6mA
  i11,   // 11.0mA
  i14,   // 14.2mA
  i17,   // 17.4mA
  i21,   // 20.8mA
  i27,   // 27.1mA
  i31,   // 30.6mA
  i34,   // 33.8mA
  i37,   // 37.0mA
  i40,   // 40.2mA
  i44,   // 43.6mA
  i47,   // 46.8mA
  i50    // 50.0mA
}ledCurrent;


void oximeter_config();
void oximeter_setLEDs(pulseWidth pw, ledCurrent red, ledCurrent ir);
void oximeter_setSPO2(sampleRate sr);
int oximeter_getNumSamp(void);
void oximeter_readSensor(unsigned int *data_ir, unsigned int *data_red);
void oximeter_shutdown(void);
void oximeter_reset(void);
void oximeter_startup(void);
int oximeter_getRevID(void);
int oximeter_getPartID(void);



void oximeter_config()
{
  i2c_write1ByteRegister(MAX30100_ADDRESS, MAX30100_INT_ENABLE1, 0xc0); 
  i2c_write1ByteRegister(MAX30100_ADDRESS, MAX30100_INT_ENABLE2, 0x00); 
  i2c_write1ByteRegister(MAX30100_ADDRESS, MAX30100_FIFO_WR_PTR, 0x00); 
  i2c_write1ByteRegister(MAX30100_ADDRESS, MAX30100_OVRFLOW_CTR, 0x00); 
  i2c_write1ByteRegister(MAX30100_ADDRESS, MAX30100_FIFO_RD_PTR, 0x00); 
  i2c_write1ByteRegister(MAX30100_ADDRESS, MAX30100_FIFO_CONFIG, 0x00); 
  i2c_write1ByteRegister(MAX30100_ADDRESS, MAX30100_MODE_CONFIG, 0x03); 
  i2c_write1ByteRegister(MAX30100_ADDRESS, MAX30100_SPO2_CONFIG, 0x07); 
  i2c_write1ByteRegister(MAX30100_ADDRESS, MAX30100_LED1_AMP , 0x24); 
  i2c_write1ByteRegister(MAX30100_ADDRESS, MAX30100_LED2_AMP, 0x24); 
}

void oximeter_setLEDs(pulseWidth pw, ledCurrent red, ledCurrent ir){
  uint8_t reg = i2c_read1ByteRegister(MAX30100_ADDRESS, MAX30100_SPO2_CONFIG);
  reg = reg & 0xFC; // Set LED_PW to 00
  i2c_write1ByteRegister(MAX30100_ADDRESS, MAX30100_SPO2_CONFIG, reg | pw);     // Mask LED_PW
  //i2c_write1ByteRegister(MAX30100_ADDRESS, MAX30100_LED_CONFIG, (red<<4) | ir); // write LED configs
  i2c_write1ByteRegister(MAX30100_ADDRESS, MAX30100_LED_CONFIG, 0x44);
}

void oximeter_setSPO2(sampleRate sr){
  uint8_t reg = i2c_read1ByteRegister(MAX30100_ADDRESS, MAX30100_SPO2_CONFIG);
  reg = reg & 0xE3; // Set SPO2_SR to 000
  i2c_write1ByteRegister(MAX30100_ADDRESS, MAX30100_SPO2_CONFIG, reg | (sr<<2)); // Mask SPO2_SR
  reg = i2c_read1ByteRegister(MAX30100_ADDRESS, MAX30100_MODE_CONFIG);
  reg = reg & 0xf8; // Set Mode to 000
  i2c_write1ByteRegister(MAX30100_ADDRESS, MAX30100_SPO2_CONFIG, reg | 0x03); // Mask MODE
}

int oximeter_getNumSamp(void){
    uint8_t wrPtr = i2c_read1ByteRegister(MAX30100_ADDRESS, MAX30100_FIFO_WR_PTR);
    uint8_t rdPtr = i2c_read1ByteRegister(MAX30100_ADDRESS, MAX30100_FIFO_RD_PTR);
    return (abs( 16 + wrPtr - rdPtr ) % 16);
}

void oximeter_readSensor(unsigned int *data_ir, unsigned int *data_red){
  uint8_t temp[6] = {0};  // Temporary buffer for read values
  i2c_readDataBlock(MAX30100_ADDRESS, MAX30100_FIFO_DATA, &temp[0], 6);  // Read four times from the FIFO
  //temp[0] = 0x11; temp[1] = 0x22; temp[2] = 0x33; temp[4] = 0x44; temp[5] = 0x55;temp[6] = 0x66;
  *data_ir =  (long)((long)((long)temp[0]&0x03)<<16) | (long)temp[1]<<8 | (long)temp[2];    // Combine values to get the actual number
  *data_red = (long)((long)((long)temp[3] & 0x03)<<16) |(long)temp[4]<<8 | (long)temp[5];   // Combine values to get the actual number
}

void oximeter_shutdown(void){
  uint8_t reg = i2c_read1ByteRegister(MAX30100_ADDRESS, MAX30100_MODE_CONFIG);  // Get the current register
  i2c_write1ByteRegister(MAX30100_ADDRESS, MAX30100_MODE_CONFIG, reg | 0x80);   
}

void oximeter_reset(void){
  uint8_t reg = i2c_read1ByteRegister(MAX30100_ADDRESS, MAX30100_MODE_CONFIG);  // Get the current register
  i2c_write1ByteRegister(MAX30100_ADDRESS, MAX30100_MODE_CONFIG, reg | 0x40);   // mask the RESET bit
}

void oximeter_startup(void){
  uint8_t reg = i2c_read1ByteRegister(MAX30100_ADDRESS, MAX30100_MODE_CONFIG);  // Get the current register
  i2c_write1ByteRegister(MAX30100_ADDRESS, MAX30100_MODE_CONFIG, reg & 0x7F);   // mask the SHDN bit
}

int oximeter_getRevID(void){
  return i2c_read1ByteRegister(MAX30100_ADDRESS, MAX30100_REV_ID);
}

int oximeter_getPartID(void){
  return i2c_read1ByteRegister(MAX30100_ADDRESS, MAX30100_PART_ID);
}

