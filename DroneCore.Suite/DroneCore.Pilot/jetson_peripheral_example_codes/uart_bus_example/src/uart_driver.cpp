#include "uart_driver.h"
/*
LINK TO FORUM: SERIAL INTERRUPTS "C": https://stackoverflow.com/questions/15119412/setting-serial-port-interruption-in-linux

read this forum https://raspberrypi.stackexchange.com/questions/57906/uart-interrupt-in-raspberry-pi-with-c-or-c
*/

UartDriver::UartDriver()
{
 
}

int UartDriver::InitSerialPort(const char* port)
{
    serial_port = open(port, O_RDWR);

    if (serial_port < 0){
        //std::cout << "Error while opening port! " << "errno = " << errno << std::endl;    
        return 1;
    }
    struct termios tty;
    memset(&tty, 0, sizeof tty);
    tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
    tty.c_cflag |= CS8; // 8 bits per byte (most common)
    tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
    tty.c_lflag &= ~ICANON;
    //tty.c_lflag |= ICANON  | ISIG;
    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes
    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    tty.c_cc[VTIME] = 1;    // Maximum waiting time for received data (1 = 0,1s) 
    //tty.c_cc[VMIN] = 110;  //Minimum received message length   
    cfsetispeed(&tty, B230400);
    cfsetospeed(&tty, B230400);
    // Save tty settings, also checking for error
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        //std::cout << "Error while saving port settings! " << "errno = " << errno << std::endl;       
        return 1;
    }
    return 0;
}

int UartDriver::WriteData(char *tx_buff, int length)
{
    int res = write(serial_port, tx_buff, length);
    return res;
}

int UartDriver::ReadData(char *rx_buff)
{
    int num_bytes = read(serial_port, rx_buff, sizeof(rx_buff));
    return num_bytes;
}


int UartDriver::DeinitSerialPort()
{
   close(serial_port); 
   return 0;
}


