#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <array>
#include <map>


class UartDriver
{
    private:
    
        int serial_port;      


    public:   
        UartDriver();

        int WriteData(char *tx_buff, int length);

        int ReadData(char *rx_buff);

        int InitSerialPort(const char* port);

        int DeinitSerialPort();

};