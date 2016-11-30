#ifndef SIGMADATA_H
#define SIGMADATA_H
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>     /* atoi */
#include "i2cdsp.h"

#define __DEBUG__
#define DSP_addr 0x3b


class sigmaData
{
    public:
        sigmaData(std::string fileSizes,std::string fileBuffer,std::string device);
        virtual ~sigmaData();
        void cargarPrograma(void);

    protected:
    private:
        void cargarNumBytesFiles(std::string numBytes);
        void cargarBufferFiles(std::string bufferFile);
        int cantidadBytes(void);
        unsigned int leerBuffer(unsigned int numBytes);
        unsigned int leerPartBuffer(void);

        std::ifstream fileNumBytes;
        std::ifstream fileBuffer;
        std::string m_device;
        unsigned char rawBuffer[40960];
        i2cDsp *dsp;

};

#endif // SIGMADATA_H
