#include "sigmadata.h"

sigmaData::sigmaData(std::string fileSizes,std::string fileBuffer,std::string device)
{
    cargarNumBytesFiles(fileSizes);
    cargarBufferFiles(fileBuffer);
    m_device = device;

}

sigmaData::~sigmaData()
{
    //dtor
}

void sigmaData::cargarNumBytesFiles(std::string numBytes)
{
   fileNumBytes.open(numBytes.c_str());
}

void sigmaData::cargarBufferFiles(std::string bufferFile)
{
    fileBuffer.open(bufferFile.c_str());
}

int sigmaData::cantidadBytes(void)
{
    char datos[50];
    memset(datos,0,50);
    fileNumBytes.getline(datos,50,',');

    if(datos[0]!=0){
        return atoi (datos);
    }
    return 0;
}

unsigned int sigmaData::leerBuffer(unsigned int numBytes)
{
    char datos[100];
    unsigned int index = 0;
    unsigned int aux = 0;
    unsigned int auxLen = 0;
    unsigned int indexRaw = 0;
    memset(rawBuffer,0,40960);
    unsigned int offsetAddr = 0;

    char hex[5];
    while(indexRaw<numBytes)
    {
        memset(datos,0,100);
        fileBuffer.getline(datos,100);
        offsetAddr++;
        auxLen = (unsigned)strlen(datos);
        aux = 0;
        while(auxLen>aux)
        {
            if((datos[aux]!=' ') && (datos[aux]!=',') && (datos[aux]!=9) && (datos[aux]!='/') && (datos[aux]!=13))
            {
                hex[0]=datos[aux];
                hex[1]=datos[aux+1];
                hex[2]=datos[aux+2];
                hex[3]=datos[aux+3];
                hex[4]=' ';
                rawBuffer[indexRaw]=strtol(hex,NULL,0);
                aux+=4;
                indexRaw++;
            }
            if(datos[aux]=='/')
            {
                aux = auxLen;
            }
            aux++;
        }
        index++;
    }
#ifdef __DEBUG__
    for(int i = 0; i< numBytes;i++)
    {
        printf("%d,",rawBuffer[i]);
    }
    printf("\n");
#endif // __DEBUG__
    return offsetAddr;

}

unsigned int sigmaData::leerPartBuffer(void)
{
    char datos[100];
    unsigned int index = 0;
    unsigned int aux = 0;
    unsigned int auxLen = 0;
    unsigned int indexRaw = 0;
    memset(rawBuffer,0,40960);

    char hex[5];
    //while(indexRaw<numBytes)
    //{
        memset(datos,0,100);
        fileBuffer.getline(datos,100);
        auxLen = (unsigned)strlen(datos);
        aux = 0;
        while(auxLen>aux)
        {
            if((datos[aux]!=' ') && (datos[aux]!=',') && (datos[aux]!=9) && (datos[aux]!='/') && (datos[aux]!=13))
            {
                hex[0]=datos[aux];
                hex[1]=datos[aux+1];
                hex[2]=datos[aux+2];
                hex[3]=datos[aux+3];
                hex[4]=' ';
                rawBuffer[indexRaw]=strtol(hex,NULL,0);
                aux+=4;
                indexRaw++;
            }
            if(datos[aux]=='/')
            {
                aux = auxLen;
            }
            aux++;
        }
        index++;
    //}
#ifdef __DEBUG__
    //for(int i = 0; i< numBytes;i++)
    for(int i = 0; i< index;i++)
    {
        printf("%d,",rawBuffer[i]);
    }
    printf("\n");
#endif // __DEBUG__
    return indexRaw;
}

void sigmaData::cargarPrograma(void)
{
    unsigned int bytes;
    unsigned int offset;
    unsigned int leido;
    dsp = new i2cDsp(m_device);
    dsp->openPort();
    bytes = cantidadBytes();
    while(bytes)
    {
        if(bytes < 8190)
        {
            leerBuffer(bytes);
            if(!dsp->sendBlock(DSP_addr,rawBuffer,bytes))
            {
                printf("Error de Escritura en la cadena de %d bytes\n",bytes);
            }
        }
        else
        {
            leerBuffer(2);
            offset = rawBuffer[0] * 0x100 + rawBuffer[1];
            bytes-=2;
            //printf("bytes a leer: %d, direccion: %d\n",bytes,offset);
            while(bytes > 0)
            {
                leido=leerPartBuffer();
                bytes-=leido;
                if(!dsp->sendBlock(DSP_addr,offset,rawBuffer,leido))
                {
                    printf("Error de Escritura en la cadena de %d bytes\n",bytes);
                }
                offset++;
            }
        }
        //leerBuffer(bytes);
        //if(!dsp->sendBlock(DSP_addr,rawBuffer,bytes))
        //{
        //    printf("Error de Escritura en la cadena de %d bytes\n",bytes);
        //}
        //usleep(1000);
        #ifdef __DEBUG__
        printf("Bytes: %d\n",bytes);
        
        //dsp->closePort();
        
        #endif // __DEBUG__
        bytes = cantidadBytes();
    }
    dsp->closePort();
}

