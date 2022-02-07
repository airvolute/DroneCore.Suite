
#include "uart_driver.h" 



int main(int argc, char **argv)
{
    UartDriver uart_driver;
    int status= 0;

    char tx[] = {'L','O','O','P','B','A','C','K'};
    char rx[8];
    
    /*Simple loopback example with interconnection between tx<->rx of THS1 port on DroneCore.Pilot GPS(Jetson) connector*/

    status=uart_driver.InitSerialPort("/dev/ttyTHS1");

    uart_driver.WriteData(&tx[0],8);
    std::cout<<"Writed data: "<<tx<<std::endl;

    uart_driver.ReadData(&rx[0]);
    std::cout<<"Received data:: "<<rx<<std::endl; 

    uart_driver.DeinitSerialPort();
    return 0;
}
