#include "i2c_driver.h"


int I2CDriver::I2cOpen(const char * device)
{
  i2c_fd = open(device, O_RDWR);
  if (i2c_fd < 0)
  {
    perror(device);
    return -1;
  }
  return 0;
}
 
 /*Write register (reg) to i2c dev on address (address) and then start read operation for [length] of bytes*/
int I2CDriver::I2cGetData(uint8_t address, uint8_t reg, uint8_t * read_buffer, uint8_t length)
{
  uint8_t regp[] = {reg};
  struct i2c_msg messages[] = {
    { address, I2C_M_WR, 1, regp},
    { address, I2C_M_RD, length, read_buffer},
  };
  struct i2c_rdwr_ioctl_data ioctl_data = { messages, 2 };
  int result = ioctl(i2c_fd, I2C_RDWR, &ioctl_data);
  if (result != 2)
  {
    perror("failed to get variables");
    return -1;
  }
  return 0;
}

 /*Write register (reg) to i2c dev on address (address) and then start write operation for [length] of bytes*/
int I2CDriver::I2cSetData(uint8_t address, uint8_t reg, uint8_t * buffer, uint8_t length)
{
  uint8_t regp[] = {reg};
  struct i2c_msg messages[] = {
    { address, I2C_M_WR, 1, regp},
    { address, I2C_M_WR, length, buffer},
  };
  struct i2c_rdwr_ioctl_data ioctl_data = { messages, 2 };
  int result = ioctl(i2c_fd, I2C_RDWR, &ioctl_data);
  if (result != 2)
  {
    perror("failed to get variables");
    return -1;
  }
  return 0;
}
 
/*Start read operation to i2c dev on address (address) for [length] of bytes*/
int I2CDriver::I2cReadSingle(uint8_t address, uint8_t * buffer, uint8_t length)
{
  struct i2c_msg messages[] = {
    { address, I2C_M_RD, length, buffer },
  };
  struct i2c_rdwr_ioctl_data ioctl_data = { messages, 1 };
  int result = ioctl(i2c_fd, I2C_RDWR, &ioctl_data);
  if (result != 1)
  {
    perror("failed to get variables");
    return -1;
  }
  return 0;
}

/*Start write operation to i2c dev on address (address) for [length] of bytes*/
int I2CDriver::I2CWriteSingle(uint8_t address, uint8_t * buffer, uint8_t length)
{
  struct i2c_msg message = { address, I2C_M_WR , length, buffer };
  struct i2c_rdwr_ioctl_data ioctl_data = { &message, 1 };
  int result = ioctl(i2c_fd, I2C_RDWR, &ioctl_data);
  if (result != 1)
  {
    perror("failed to set target");
    return -1;
  }
  return 0;
}


int I2CDriver::I2cClose()
{
  close(i2c_fd);
  return 0;
}

I2CDriver::~I2CDriver(){
  close(i2c_fd);
}