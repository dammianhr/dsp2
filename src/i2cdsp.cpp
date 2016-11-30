#include "i2cdsp.h"

i2cDsp::i2cDsp()
{
    //ctor
}

i2cDsp::~i2cDsp()
{
    //dtor
}

i2cDsp::i2cDsp(std::string device)
{
    m_device = device;
}

int i2cDsp::openPort()
{
    if ((m_handler = open(m_device.c_str(), O_RDWR)) < 0) {
        printf("Failed to open I2C device.");
    }
    return 1;
}

int i2cDsp::sendBlock(unsigned char address, unsigned char* bloque, unsigned int largo)
{

    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[1];

    messages[0].addr  = address;
    messages[0].flags = 0;
    messages[0].len   = largo;
    messages[0].buf   = bloque;

    packets.msgs  = messages;
    packets.nmsgs = 1;
    if(ioctl(m_handler, I2C_RDWR, &packets) < 0) {
        printf("Failed to writing block data.");
    }

    return 1;
}
int i2cDsp::sendBlock(unsigned char devaddress, unsigned int direccionMemoria, unsigned char* datos, unsigned int largoDatos)
{
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[1];

    unsigned char rawDatos[100];
    rawDatos[0]=(direccionMemoria & 0xff00) >> 8;
    rawDatos[1]=(direccionMemoria & 0x00ff);

    memcpy(rawDatos+2,datos,largoDatos);

    messages[0].addr  = devaddress;
    messages[0].flags = 0;
    messages[0].len   = largoDatos+2;
    messages[0].buf   = rawDatos;

    packets.msgs  = messages;
    packets.nmsgs = 1;
    if(ioctl(m_handler, I2C_RDWR, &packets) < 0) {
        printf("Failed to writing long block data.");
    }

    return 1;

}

void i2cDsp::closePort()
{
    close(m_handler);
}
