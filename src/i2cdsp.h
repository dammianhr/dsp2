#ifndef I2CDSP_H
#define I2CDSP_H
#include <string>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>

typedef unsigned short ADI_DATA_U16;
typedef unsigned char  ADI_REG_TYPE;

class i2cDsp
{
    public:
        i2cDsp();
        i2cDsp(std::string device);
        int openPort();
        virtual ~i2cDsp();
        int sendBlock(unsigned char address,unsigned char *bloque, unsigned int largo);
        int sendBlock(unsigned char devaddress,unsigned int direccionMemoria, unsigned char *datos, unsigned int largoDatos);
        void closePort();
    protected:
    private:
        int m_handler;
        std::string m_device;
};

#endif // I2CDSP_H
