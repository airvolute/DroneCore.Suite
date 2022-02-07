#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>


static uint32_t spi_mode;
static uint8_t spi_bits;
static uint32_t spi_speed;
static uint16_t spi_delay;

class SPIDriver
{
    private:     

        int spi_fd;  
        const char * device;  

    public:  

        int SPITransfer(uint8_t const *tx_buff, uint8_t const *rx_buff, size_t len);

        int SPIOpen();

        int SPIRead(uint8_t reg, uint8_t *read_data, size_t length);

        int SPIWrite(uint8_t reg, uint8_t *write_data, size_t length);

        int SPIClose();

        SPIDriver(const char * devstr, int32_t speed_hz);

        ~SPIDriver();

};