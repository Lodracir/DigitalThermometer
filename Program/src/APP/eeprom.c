/* EEPROM Driver Header */
#include "APP/eeprom.h"
#include "MCU_Drivers/DRV_I2C1.h"

/**
 *  Local Variables
 **/
static uint8_t MemAddr = (0x50 << 1); // 0b 0101 0000 -> 0x50

/****************************************************************
 *                                                              *
 *                 Static Prototype Functions                   *
 *                                                              *
 ****************************************************************/

/****************************************************************
 *                      Write Functions                         *
 ****************************************************************/

static void    WRITE_8BIT(MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint8_t *data);
static void    WRITE_16BIT(MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint16_t *data);
static void    WRITE_32BIT(MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint32_t *data);
static void    WRITE_64BIT(MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint64_t *data);
static void    WRITE_FLOAT(MEM_BLOCKADDR_t AddrBlock, uint8_t addr, float *data);
static void    WRITE_DOUBLE(MEM_BLOCKADDR_t AddrBlock, uint8_t addr, double *data);

/** Write Function **/
static void EEPROM_WriteData( MEM_BLOCKADDR_t AddrBlock, uint8_t addr, void* pData, Data_Type_t DataType );

/****************************************************************
 *                       Read Functions                         *
 ****************************************************************/

void    READ_8BIT(MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint8_t *data);
void    READ_16BIT(MEM_BLOCKADDR_t AddrBlock, uint8_t addr,uint16_t *data);
void    READ_32BIT(MEM_BLOCKADDR_t AddrBlock, uint8_t addr,uint32_t *data);
void    READ_64BIT(MEM_BLOCKADDR_t AddrBlock, uint8_t addr,uint64_t *data);
void    READ_FLOAT(MEM_BLOCKADDR_t AddrBlock, uint8_t addr, float *data);
void    READ_DOUBLE(MEM_BLOCKADDR_t AddrBlock, uint8_t addr, double *data);

/** Read Function **/
static void EEPROM_ReadData( MEM_BLOCKADDR_t AddrBlock, uint8_t addr, void* pData, Data_Type_t DataType );

/****************************************************************
 *                                                              *
 *                          Functions                           *
 *                                                              *
 ****************************************************************/

void EEPROM_Init(EEPROM_t *heeprom)
{

    /** Allocate Functions **/
    heeprom->WriteData  = EEPROM_WriteData;
    heeprom->ReadData   = EEPROM_ReadData;

}

void EEPROM_DeInit(EEPROM_t *heeprom)
{

    /** Deallocate Functions **/
    heeprom->WriteData  = NULL;
    heeprom->ReadData   = NULL;

}

/****************************************************************
 *                                                              *
 *                     Static Functions                         *
 *                                                              *
 ****************************************************************/

/****************************************************************
 *                      Write Functions                         *
 ****************************************************************/

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void WRITE_8BIT(MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint8_t *data)
{

    /** Set Memory Address according with selected memory block **/
    switch(AddrBlock)
    {
        case MEM_BLOCK_0:
            MemAddr = ( 0x50 << 1 );
            break;

        case MEM_BLOCK_1:
            MemAddr = ( 0x51 << 1);
    }

    /** Write data to a specified address **/
    DRV_I2C1_Mem_WriteByte(MemAddr, addr, data);

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void WRITE_16BIT(MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint16_t *data)
{

    /** Local Variables **/
    uint8_t TransmitBuffer[2] = { 0x00 , 0x00 };

    /** Store data to buffer **/
    TransmitBuffer[0] = (uint8_t)((*data) >> 8);
    TransmitBuffer[1] = (uint8_t)(*data);

    /** Set Memory Address according with selected memory block **/
    switch(AddrBlock)
    {
        case MEM_BLOCK_0:
            MemAddr = ( 0x50 << 1 );
            break;

        case MEM_BLOCK_1:
            MemAddr = ( 0x51 << 1);
    }

    /** Write first byte data to a specified address **/
    DRV_I2C1_Mem_WriteByte(MemAddr, addr, &TransmitBuffer[0]);

    /** Write second byte to next address **/
    addr += 1;
    DRV_I2C1_Mem_WriteByte(MemAddr, addr, &TransmitBuffer[1]);

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void WRITE_32BIT(MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint32_t *data)
{

    /** Local Variables **/
    uint8_t TransmitBuffer[4] = { 0x00, 0x00, 0x00, 0x00 };
    int itr = 0, Bits2Move = (32 - 8);

    /** Stora Data to buffer **/
    for(itr = 0; itr < 4; itr++)
    {
        TransmitBuffer[itr] = (uint8_t)((*data) >> Bits2Move);
        Bits2Move -= 8;
        if(Bits2Move == 0 )
        {
            TransmitBuffer[itr] = (uint8_t)(*data);
        }
    }

    /** Set Memory Address according with selected memory block **/
    switch(AddrBlock)
    {
        case MEM_BLOCK_0:
            MemAddr = ( 0x50 << 1 );
            break;

        case MEM_BLOCK_1:
            MemAddr = ( 0x51 << 1 );
            break;
    }

    for(int itr = 0; itr < 4; itr++)
    {
        /** Transmit data to EEPROM **/
        DRV_I2C1_Mem_WriteByte(MemAddr, addr, &TransmitBuffer[itr]);
        addr++;
    }

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void WRITE_64BIT(MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint64_t *data)
{

    /** Local Variables **/
    uint8_t TransmitBuffer[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    int itr = 0, Bits2Move = (64 - 8);

    /** Stora Data to buffer **/
    for(itr = 0; itr < 8; itr++)
    {
        TransmitBuffer[itr] = (uint8_t)((*data) >> Bits2Move);
        Bits2Move -= 8;
        if(Bits2Move == 0 )
        {
            TransmitBuffer[itr] = (uint8_t)(*data);
        }
    }

    /** Set Memory Address according with selected memory block **/
    switch(AddrBlock)
    {
        case MEM_BLOCK_0:
            MemAddr = ( 0x50 << 1 );
            break;

        case MEM_BLOCK_1:
            MemAddr = ( 0x51 << 1 );
            break;
    }

    for(itr = 0; itr < 8; itr++)
    {
        /** Transmit data to EEPROM **/
        DRV_I2C1_Mem_WriteByte(MemAddr, addr, &TransmitBuffer[itr]);
        addr++;
    }

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void WRITE_FLOAT(MEM_BLOCKADDR_t AddrBlock, uint8_t addr, float *data)
{

    /** Local Variables **/
    uint32_t    tempData = (uint32_t)(*data);
    uint8_t     TransmitBuffer[4] = { 0x00, 0x00, 0x00, 0x00 };
    int itr = 0, Bits2Move = (32 - 8);

    /** Stora Data to buffer **/
    for(itr = 0; itr < 4; itr++)
    {
        TransmitBuffer[itr] = (uint8_t)(tempData >> Bits2Move);
        Bits2Move -= 8;
        if(Bits2Move == 0 )
        {
            TransmitBuffer[itr] = (uint8_t)(tempData);
        }
    }

    /** Set Memory Address according with selected memory block **/
    switch(AddrBlock)
    {
        case MEM_BLOCK_0:
            MemAddr = ( 0x50 << 1 );
            break;

        case MEM_BLOCK_1:
            MemAddr = ( 0x51 << 1 );
            break;
    }

    
    for(int itr = 0; itr < 4; itr++)
    {
        /** Transmit data to EEPROM **/
        DRV_I2C1_Mem_WriteByte(MemAddr, addr, &TransmitBuffer[itr]);
        addr++;
    }

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void WRITE_DOUBLE(MEM_BLOCKADDR_t AddrBlock, uint8_t addr, double *data)
{

    /** Local Variables **/
    uint64_t    tempData = (uint64_t)(*data);
    uint8_t     TransmitBuffer[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    int itr = 0, Bits2Move = (64 - 8);

    /** Stora Data to buffer **/
    for(itr = 0; itr < 8; itr++)
    {
        TransmitBuffer[itr] = (uint8_t)(tempData >> Bits2Move);
        Bits2Move -= 8;
        if(Bits2Move == 0 )
        {
            TransmitBuffer[itr] = (uint8_t)(tempData);
        }
    }

    /** Set Memory Address according with selected memory block **/
    switch(AddrBlock)
    {
        case MEM_BLOCK_0:
            MemAddr = ( 0x50 << 1 );
            break;

        case MEM_BLOCK_1:
            MemAddr = ( 0x51 << 1);
    }

    for(itr = 0; itr < 8; itr++)
    {
        /** Transmit data to EEPROM **/
        DRV_I2C1_Mem_WriteByte(MemAddr, addr, &TransmitBuffer[itr]);
        addr++;
    }

}

static void EEPROM_WriteData( MEM_BLOCKADDR_t AddrBlock, uint8_t addr, void* pData, Data_Type_t DataType )
{

    switch (DataType)
    {

        case D_UINT8:
            WRITE_8BIT(AddrBlock, addr, (uint8_t *)pData);
            break;

        case D_UINT16:
            WRITE_16BIT(AddrBlock, addr, (uint16_t *)pData);
            break;

        case D_UINT32:
            WRITE_32BIT(AddrBlock, addr, (uint32_t *)pData);
            break;

        case D_UINT64:
            WRITE_64BIT(AddrBlock, addr, (uint64_t *)pData);
            break;

        case D_FLOAT:
            WRITE_FLOAT(AddrBlock, addr, (float *)pData);
            break;

        case D_DOUBLE:
            WRITE_DOUBLE(AddrBlock, addr, (double *)pData);
            break;
    }
}

/****************************************************************
 *                       Read Functions                         *
 ****************************************************************/

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void READ_8BIT(MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint8_t *data)
{

    /** Set Memory Address according with selected memory block **/
    switch(AddrBlock)
    {
        case MEM_BLOCK_0:
            MemAddr = ( 0x50 << 1 );
            break;

        case MEM_BLOCK_1:
            MemAddr = ( 0x51 << 1);
    }

    /** Read Data from EEPROM **/
    DRV_I2C1_Mem_ReadByte(MemAddr, addr, data);

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void READ_16BIT(MEM_BLOCKADDR_t AddrBlock, uint8_t addr,uint16_t *data)
{

    /** Local Vriables **/
    uint8_t ReceiveBuffer[2] = { 0x00, 0x00 };
    

    /** Set Memory Address according with selected memory block **/
    switch(AddrBlock)
    {
        case MEM_BLOCK_0:
            MemAddr = ( 0x50 << 1 );
            break;

        case MEM_BLOCK_1:
            MemAddr = ( 0x51 << 1);
    }

    /** Read first data from EEPROM **/
    DRV_I2C1_Mem_ReadByte(MemAddr, addr, &ReceiveBuffer[0]);

    /** Read second data from EEPROM **/
    addr += 1;
    DRV_I2C1_Mem_ReadByte(MemAddr, addr, &ReceiveBuffer[1]);

    /** Store received buffer data **/
    (*data) = (ReceiveBuffer[0] << 8) + ReceiveBuffer[1];

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void READ_32BIT(MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint32_t *data)
{

    /** Local Variables **/
    uint8_t ReceiveBuffer[4] = { 0x00, 0x00, 0x00, 0x00 };
    int itr = 0, Bits2Move = 8;

    /** Set Memory Address according with selected memory block **/
    switch(AddrBlock)
    {
        case MEM_BLOCK_0:
            MemAddr = ( 0x50 << 1 );
            break;

        case MEM_BLOCK_1:
            MemAddr = ( 0x51 << 1);
    }

    /** Read data from EEPROM **/
    for(int itr = 0; itr < 4; itr++)
    {
        DRV_I2C1_Mem_ReadByte(MemAddr, addr, &ReceiveBuffer[itr]);
        addr++;
    }

    /** Store received data and convert it to 32 bits value **/ //0b 0000 0000 0000 0000 0000 0000 0000 0000
    (*data) = (uint32_t)ReceiveBuffer[3];

    for(itr = 2; itr >= 0; itr--)
    {
        (*data) += ( (uint32_t)ReceiveBuffer[itr] << Bits2Move );
        Bits2Move += 8; 
    }

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void READ_64BIT(MEM_BLOCKADDR_t AddrBlock, uint8_t addr,uint64_t *data)
{

    /** Local Variables **/
    uint8_t ReceiveBuffer[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    int itr = 0, Bits2Move = 8;

    /** Set Memory Address according with selected memory block **/
    switch(AddrBlock)
    {
        case MEM_BLOCK_0:
            MemAddr = ( 0x50 << 1 );
            break;

        case MEM_BLOCK_1:
            MemAddr = ( 0x51 << 1);
    }

    /** Read data from EEPROM **/
    for(int itr = 0; itr < 8; itr++)
    {
        DRV_I2C1_Mem_ReadByte(MemAddr, addr, &ReceiveBuffer[itr]);
        addr++;
    }

    /** Store received data and convert it to 32 bits value **/ //0b 0000 0000 0000 0000 0000 0000 0000 0000
    (*data) = (uint64_t)ReceiveBuffer[7];

    for(itr = 6; itr >= 0; itr--)
    {
        (*data) += ( (uint64_t)ReceiveBuffer[itr] << Bits2Move );
        Bits2Move += 8; 
    }

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void READ_FLOAT(MEM_BLOCKADDR_t AddrBlock, uint8_t addr, float *data)
{
    
    /** Local Variables **/
    uint8_t ReceiveBuffer[4] = { 0x00, 0x00, 0x00, 0x00 };
    uint32_t tempValue;
    int itr = 0, Bits2Move = 8;

    /** Set Memory Address according with selected memory block **/
    switch(AddrBlock)
    {
        case MEM_BLOCK_0:
            MemAddr = ( 0x50 << 1 );
            break;

        case MEM_BLOCK_1:
            MemAddr = ( 0x51 << 1);
    }

    /** Read data from EEPROM **/
    for(int itr = 0; itr < 4; itr++)
    {
        DRV_I2C1_Mem_ReadByte(MemAddr, addr, &ReceiveBuffer[itr]);
        addr++;
    }

    /** Store received data and convert it to 32 bits value **/ //0b 0000 0000 0000 0000 0000 0000 0000 0000
    tempValue = (uint32_t)ReceiveBuffer[3];

    for(itr = 2; itr >= 0; itr--)
    {
        tempValue += ( (uint32_t)ReceiveBuffer[itr] << Bits2Move );
        Bits2Move += 8; 
    }

    /** Store temporal value to data **/
    (*data) = (float)tempValue;

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void READ_DOUBLE(MEM_BLOCKADDR_t AddrBlock, uint8_t addr, double *data)
{

    /** Local Variables **/
    uint8_t ReceiveBuffer[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    int itr = 0, Bits2Move = 8;
    uint64_t tempValue;

    /** Set Memory Address according with selected memory block **/
    switch(AddrBlock)
    {
        case MEM_BLOCK_0:
            MemAddr = ( 0x50 << 1 );
            break;

        case MEM_BLOCK_1:
            MemAddr = ( 0x51 << 1);
    }

    /** Read data from EEPROM **/
    for(int itr = 0; itr < 8; itr++)
    {
        DRV_I2C1_Mem_ReadByte(MemAddr, addr, &ReceiveBuffer[itr]);
        addr++;
    }

    /** Store received data and convert it to 32 bits value **/ //0b 0000 0000 0000 0000 0000 0000 0000 0000
    tempValue = (uint64_t)ReceiveBuffer[7];

    for(itr = 6; itr >= 0; itr--)
    {
        tempValue += ( (uint64_t)ReceiveBuffer[itr] << Bits2Move );
        Bits2Move += 8; 
    }

    (*data) = (double)tempValue;

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
static void EEPROM_ReadData( MEM_BLOCKADDR_t AddrBlock, uint8_t addr, void* pData, Data_Type_t DataType )
{
    switch (DataType)
    {
        case D_UINT8:
            READ_8BIT(AddrBlock, addr, (uint8_t *)pData);
            break;

        case D_UINT16:
            READ_16BIT(AddrBlock, addr, (uint16_t *)pData);
            break;

        case D_UINT32:
            READ_32BIT(AddrBlock, addr, (uint32_t *)pData);
            break;

        case D_UINT64:
            READ_64BIT(AddrBlock, addr, (uint64_t *)pData);
            break;

        case D_FLOAT:
            READ_FLOAT(AddrBlock, addr, (float *)pData);
            break;

        case D_DOUBLE:
            READ_DOUBLE(AddrBlock, addr, (double *)pData);
            break;
    }
}