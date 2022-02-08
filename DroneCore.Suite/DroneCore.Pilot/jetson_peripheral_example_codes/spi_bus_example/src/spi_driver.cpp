#include "spi_driver.h"


SPIDriver::SPIDriver(const char * devstr, int32_t speed_hz)
{
  spi_mode = SPI_MODE_0;
  device = devstr;
  spi_speed=speed_hz;
  spi_bits = 8;
  spi_delay = 0;  

  /*TODO pass this settings through fcn parameters*/
    //spi_mode |= SPI_LOOP;       //loopback mode
  //spi_mode |= SPI_CPHA;       //clock phase shift
  //spi_mode |= SPI_CPOL;       //clock polarity inversion
  //spi_mode |= SPI_LSB_FIRST;  
  //spi_mode |= SPI_CS_HIGH;
  //spi_mode |= SPI_3WIRE;
  //spi_mode |= SPI_NO_CS;
  //spi_mode |= SPI_READY;
  //spi_mode |= SPI_TX_DUAL;
  //spi_mode |= SPI_TX_QUAD;
}


int SPIDriver::SPIOpen()
{  
  int ret = 0;

  spi_fd = open(device, O_RDWR);
  if (spi_fd < 0)
  {
    perror(device);
    return -1;
  }

	ret = ioctl(spi_fd, SPI_IOC_WR_MODE, &spi_mode);
	if (ret == -1)
		return ret;

	ret = ioctl(spi_fd, SPI_IOC_RD_MODE, &spi_mode);
	if (ret == -1)
		return ret;

	ret = ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &spi_bits);
	if (ret == -1)
		return ret;

	ret = ioctl(spi_fd, SPI_IOC_RD_BITS_PER_WORD, &spi_bits);
	if (ret == -1)
		return ret;

	ret = ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed);
	if (ret == -1)
		return ret;

	ret = ioctl(spi_fd, SPI_IOC_RD_MAX_SPEED_HZ, &spi_speed);
	if (ret == -1)
		return ret;


  return 0;
}
 
int SPIDriver::SPITransfer(uint8_t const *tx_buff, uint8_t const *rx_buff, size_t len)
{
  struct spi_ioc_transfer tr;

  memset(&tr, 0, sizeof(tr));

  tr.tx_buf = (unsigned long)tx_buff;
  tr.rx_buf = (unsigned long)rx_buff;
  tr.len = len;
  tr.delay_usecs = spi_delay;
  tr.speed_hz = spi_speed;
  tr.bits_per_word = spi_bits;	  

  /*if (mode & SPI_TX_QUAD)tr.tx_nbits = 4;
  else if (mode & SPI_TX_DUAL)tr.tx_nbits = 2;

  if (mode & SPI_RX_QUAD)tr.rx_nbits = 4;
  else if (mode & SPI_RX_DUAL)tr.rx_nbits = 2;

  if (!(mode & SPI_LOOP)) {
    if (mode & (SPI_TX_QUAD | SPI_TX_DUAL))tr.rx_buf = 0;
    else if (mode & (SPI_RX_QUAD | SPI_RX_DUAL))tr.tx_buf = 0;
  }*/
  
  int result = ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr);
  if (result < 1)
  {
    perror("failed to set target");
    return -1;
  }
  return 0;
}

/*Start read operation from register (reg) of data length (length)*/
int SPIDriver::SPIRead(uint8_t reg, uint8_t *read_data, size_t length)
{
  uint8_t rx_buffer[length+1];
  uint8_t tx_buffer[length+1];
  //tx = malloc(size);

  tx_buffer[0] = reg;
  memset(&tx_buffer[1],0xFF,length);

  int ret = SPITransfer(&tx_buffer[0],&rx_buffer[0],length+1);

  if(ret==0)
  memcpy(read_data,&rx_buffer[1],length);


  return ret;
}

/*Start write operation to register (reg) of data length (length)*/
int SPIDriver::SPIWrite(uint8_t reg, uint8_t *write_data, size_t length)
{
  uint8_t rx_buffer[length+1];
  uint8_t tx_buffer[length+1];

  tx_buffer[0] = reg;
  memcpy(&tx_buffer[1],write_data,length);

  int ret = SPITransfer(&tx_buffer[0],&rx_buffer[0],length+1);

  return ret;
}

int SPIDriver::SPIClose()
{
  close(spi_fd);
  return 0;
}

SPIDriver::~SPIDriver(){
  close(spi_fd);
}