#include "i2c_driver.h" 
#include <iostream>
 


I2CDriver i2c1_driver;

const char * device = "/dev/i2c-1";
const uint8_t slave_address = 0x40; /*7bit address without last r/w bit*/

int main(int argc, char **argv)
{
  if(i2c1_driver.I2cOpen(device) != 0 )
  {
      //Handle error
      std::cout<<"I2COpen error happens: "<<std::endl;
  };
  

  uint8_t bufferR[2];
  uint8_t bufferW[2];
  bufferW[0]=0x03;
  bufferW[1]=0x04;

  /*Read data from i2c dev*/
  if(i2c1_driver.I2cGetData(slave_address,0x01,bufferR,2) != 0) 
  {
        //handle error
        std::cout<<"I2CGetData error happens: "<<std::endl;
  }else
  {
        std::cout<<"I2CGetData OK: "<<std::endl;
        std::cout<<"Read buff: "<<bufferR[0]<<bufferR[1]<<std::endl;
  }
  

  usleep(200);

  /*Write data from i2c dev*/
  if(i2c1_driver.I2cSetData(slave_address,0x02,bufferW,2) != 0) 
  {
        //handle error
        std::cout<<"I2CSetData error happens: "<<std::endl;
  }else
  {
        std::cout<<"I2CSetData OK: "<<std::endl;
  }

 
  i2c1_driver.I2cClose();


  return 0;
}
