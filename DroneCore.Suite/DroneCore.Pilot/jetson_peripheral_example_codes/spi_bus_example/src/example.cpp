#include "spi_driver.h" 
#include <iostream>

//Simple read operations on DroneCore.Pilot board with XavierNx

#define SPI20
//#define SPI21
//#define SPI22
//#define SPI00
//#define SPI01

#ifdef SPI20
SPIDriver spi20_driver("/dev/spidev2.0",500000);  //ACC
#endif
#ifdef SPI21
SPIDriver spi21_driver("/dev/spidev2.1",500000);  //GYRO
#endif
#ifdef SPI22
SPIDriver spi22_driver("/dev/spidev2.2",500000);  //BARO
#endif
#ifdef SPI00
SPIDriver spi00_driver("/dev/spidev0.0",500000);  //OUT1
#endif
#ifdef SPI01
SPIDriver spi01_driver("/dev/spidev0.1",500000);  //OUT2
#endif


int main(int argc, char **argv)
{
#ifdef SPI20      
  if(spi20_driver.SPIOpen() != 0 )
  {
      std::cout<<"SPI2.0 Open error happens ! "<<std::endl;
  };
#endif  
#ifdef SPI21 
    if(spi21_driver.SPIOpen() != 0 )
  {
      std::cout<<"SPI2.1 Open error happens ! "<<std::endl;
  };
#endif
#ifdef SPI22
    if(spi22_driver.SPIOpen() != 0 )
  {
      std::cout<<"SPI2.2 Open error happens ! "<<std::endl;
  };
#endif  
#ifdef SPI00
    if(spi00_driver.SPIOpen() != 0 )
  {
      std::cout<<"SPI0.0 Open error happens ! "<<std::endl;
  };
#endif  
#ifdef SPI01
    if(spi01_driver.SPIOpen() != 0 )
  {
      std::cout<<"SPI0.1 Open error happens ! "<<std::endl;
  };  
#endif
  uint8_t bufferR[8];
  uint8_t bufferW[8];
  uint8_t ret_val=0;
  memset(&bufferR[0], 0, 8);

   
  bufferW[0]=0x03;
  bufferW[1]=0x04;

#ifdef SPI20
  spi20_driver.SPIRead(0x80,&bufferR[0],1); /*BMI088  SPI interface for ACC is set by rising edge on CS pin, (one "dummy" read operation can do this)*/
  usleep(5000);
  if(spi20_driver.SPIRead(0x80,&bufferR[0],1) != 0)  /*0x80 = Who I am register address*/
  {
        //handle error
        std::cout<<"SPIGetData error happens: "<<std::endl;
  }else
  {
        //CHIP_ID of bmi088 accel part 0x1E
        std::cout<<"SPIGetData OK: "<<std::endl;
        std::cout<<"CHIP_ID: "<<std::hex<<(int)bufferR[0]<<std::endl;
        ret_val=bufferR[0];
  }
  spi20_driver.SPIClose();
 #endif 
 
#ifdef SPI21
  if(spi21_driver.SPIRead(0x80,&bufferR[0],1) != 0) /*0x80 = Who I am register address*/
  {
        //handle error
        std::cout<<"SPIGetData error happens: "<<std::endl;
  }else
  {
        //CHIP_ID of bmi088 gyro part 0x0F
        std::cout<<"SPIGetData OK: "<<std::endl;
        std::cout<<"CHIP_ID: "<<std::hex<<(int)bufferR[0]<<std::endl;
        ret_val=bufferR[0];
  }
  spi21_driver.SPIClose();
#endif
     


#ifdef SPI22
  /*FOR BMP388 one "dummy" byte follows the control command to start read operation !*/
  if(spi22_driver.SPIRead(0x80,&bufferR[0],2) != 0) /*0x80 = Who I am register address*/
  {
        //handle error
        std::cout<<"SPIGetData error happens: "<<std::endl;
  }else
  {
        //CHIP_ID of bmp388 0x50
        std::cout<<"SPIGetData OK: "<<std::endl;
      /std::cout<<"CHIP_ID: "<<std::hex<<(int)bufferR[1]<<std::endl;
        ret_val=bufferR[1];
  }
  spi22_driver.SPIClose();
#endif

#ifdef SPI00
if(spi00_driver.SPIRead(0x00,&bufferR[0],1) != 0)  
  {
        //handle error
        std::cout<<"SPIGetData error happens: "<<std::endl;
  }else
  {        
        std::cout<<"SPIGetData OK: "<<std::endl;
        std::cout<<"Read value: "<<std::hex<<(int)bufferR[0]<<std::endl;
        ret_val=bufferR[0];
  }
  spi00_driver.SPIClose();
#endif


#ifdef SPI01
if(spi01_driver.SPIRead(0x00,&bufferR[0],1) != 0)   
  {
        //handle error
        std::cout<<"SPIGetData error happens: "<<std::endl;
  }else
  {
        std::cout<<"SPIGetData OK: "<<std::endl;
        std::cout<<"Read value: "<<std::hex<<(int)bufferR[0]<<std::endl;
        ret_val=bufferR[0];
  }
  spi01_driver.SPIClose();
#endif


  return ret_val;
}