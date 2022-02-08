#include <fcntl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>


#define I2C_M_WR        0 


class I2CDriver
{
    private:      

        int i2c_fd;

    public:  

        int I2cOpen(const char * device);

        int I2cGetData(uint8_t address, uint8_t reg, uint8_t * read_buffer, uint8_t length);

        int I2cSetData(uint8_t address, uint8_t reg, uint8_t * buffer, uint8_t length);

        int I2cReadSingle(uint8_t address, uint8_t * buffer, uint8_t length);

        int I2CWriteSingle(uint8_t address, uint8_t * buffer, uint8_t length);

        int I2cClose();

        ~I2CDriver();

};