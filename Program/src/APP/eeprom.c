/* EEPROM Driver Header */
#include "APP/eeprom.h"

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

/** Unsigned Data **/
void    EEPROM_WRITE_8BIT(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint8_t data);
void    EEPROM_WRITE_16BIT(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint16_t data);
void    EEPROM_WRITE_32BIT(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint32_t data);
void    EEPROM_WRITE_64BIT(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint64_t data);

/** Float and Double Data **/
void    EEPROM_WRITE_FloatData(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, float data);
void    EEPROM_WRITE_DoubleData(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, double data);

/****************************************************************
 *                       Read Functions                         *
 ****************************************************************/

/** Unsigned Data **/
void    EEPROM_READ_8BIT(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint8_t *data);
void    EEPROM_READ_16BIT(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr,uint16_t *data);
void    EEPROM_READ_32BIT(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr,uint32_t *data);
void    EEPROM_READ_64BIT(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr,uint64_t *data);

/** Float and Double Data **/
void    EEPROM_READ_FloatData(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, float *data);
void    EEPROM_READ_DoubleData(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, double *data);

/****************************************************************
 *                                                              *
 *                          Functions                           *
 *                                                              *
 ****************************************************************/

void EEPROM_Init(EEPROM_t *heeprom)
{

    /** Allocate Write Functions **/
    heeprom->write.D8BIT        = EEPROM_WRITE_8BIT;
    heeprom->write.D16BIT       = EEPROM_WRITE_16BIT;
    heeprom->write.D32BIT       = EEPROM_WRITE_32BIT;
    heeprom->write.D64BIT       = EEPROM_WRITE_64BIT;
    heeprom->write.FloatData    = EEPROM_WRITE_FloatData;
    heeprom->write.DoubleData   = EEPROM_WRITE_DoubleData;

    /** Allocate Read Functions **/
    heeprom->read.D8BIT        = EEPROM_READ_8BIT;
    heeprom->read.D16BIT       = EEPROM_READ_16BIT;
    heeprom->read.D32BIT       = EEPROM_READ_32BIT;
    heeprom->read.D64BIT       = EEPROM_READ_64BIT;
    heeprom->read.FloatData    = EEPROM_READ_FloatData;
    heeprom->read.DoubleData   = EEPROM_READ_DoubleData;

}

void EEPROM_DeInit(EEPROM_t *heeprom)
{

    /** Deallocate Write Functions **/
    heeprom->write.D8BIT        = NULL;
    heeprom->write.D16BIT       = NULL;
    heeprom->write.D32BIT       = NULL;
    heeprom->write.D64BIT       = NULL;
    heeprom->write.FloatData    = NULL;
    heeprom->write.DoubleData   = NULL;

    /** Deallocate Read Functions **/
    heeprom->read.D8BIT        = NULL;
    heeprom->read.D16BIT       = NULL;
    heeprom->read.D32BIT       = NULL;
    heeprom->read.D64BIT       = NULL;
    heeprom->read.FloatData    = NULL;
    heeprom->read.DoubleData   = NULL;

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
void EEPROM_WRITE_8BIT(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint8_t data)
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
    HAL_I2C_Mem_Write(hi2c, MemAddr, addr, 1, &data, 1, 100);

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_WRITE_16BIT(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint16_t data)
{

    /** Local Variables **/
    uint8_t TransmitBuffer[2] = { 0x00 , 0x00 };

    /** Store data to buffer **/
    TransmitBuffer[0] = (uint8_t)(data >> 8);
    TransmitBuffer[1] = (uint8_t)data;

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
    HAL_I2C_Mem_Write(hi2c, MemAddr, addr, 1, &TransmitBuffer[0], 1, 100);

    /** Write second byte to next address **/
    addr += 1;
    HAL_I2C_Mem_Write(hi2c, MemAddr, addr, 1, &TransmitBuffer[1], 1, 100);

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_WRITE_32BIT(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint32_t data)
{

    /** Local Variables **/
    uint8_t TransmitBuffer[4] = { 0x00, 0x00, 0x00, 0x00 };
    int itr = 0, Bits2Move = (32 - 8);

    /** Stora Data to buffer **/
    for(itr = 0; itr < 4; itr++)
    {
        TransmitBuffer[itr] = (uint8_t)(data >> Bits2Move);
        Bits2Move -= 8;
        if(Bits2Move == 0 )
        {
            TransmitBuffer[itr] = (uint8_t)(data);
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
        HAL_I2C_Mem_Write(hi2c, MemAddr, addr, 1, &TransmitBuffer[itr], 1, 100);
        addr++;
    }

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_WRITE_64BIT(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint64_t data)
{

    /** Local Variables **/
    uint8_t TransmitBuffer[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    int itr = 0, Bits2Move = (64 - 8);

    /** Stora Data to buffer **/
    for(itr = 0; itr < 8; itr++)
    {
        TransmitBuffer[itr] = (uint8_t)(data >> Bits2Move);
        Bits2Move -= 8;
        if(Bits2Move == 0 )
        {
            TransmitBuffer[itr] = (uint8_t)(data);
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
        HAL_I2C_Mem_Write(hi2c, MemAddr, addr, 1, &TransmitBuffer[itr], 1, 100);
        addr++;
    }

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_WRITE_FloatData(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, float data)
{

    /** Local Variables **/
    uint32_t    tempData = (uint32_t)data;
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
        HAL_I2C_Mem_Write(hi2c, MemAddr, addr, 1, &TransmitBuffer[itr], 1, 100);
        addr++;
    }

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_WRITE_DoubleData(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, double data)
{

    /** Local Variables **/
    uint64_t    tempData = (uint64_t)data;
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
        HAL_I2C_Mem_Write(hi2c, MemAddr, addr, 1, &TransmitBuffer[itr], 1, 100);
        addr++;
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
void EEPROM_READ_8BIT(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint8_t *data)
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
    HAL_I2C_Mem_Read(hi2c, MemAddr, addr, 1, data, 1, 100);

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_READ_16BIT(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr,uint16_t *data)
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
    HAL_I2C_Mem_Read(hi2c, MemAddr, addr, 1, &ReceiveBuffer[0], 1, 100);

    /** Read second data from EEPROM **/
    addr += 1;
    HAL_I2C_Mem_Read(hi2c, MemAddr, addr, 1, &ReceiveBuffer[1], 1, 100);

    /** Store received buffer data **/
    (*data) = (ReceiveBuffer[0] << 8) + ReceiveBuffer[1];

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_READ_32BIT(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint32_t *data)
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
        HAL_I2C_Mem_Read(hi2c, MemAddr, addr, 1, &ReceiveBuffer[itr], 1, 100);
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
void EEPROM_READ_64BIT(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr,uint64_t *data)
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
        HAL_I2C_Mem_Read(hi2c, MemAddr, addr, 1, &ReceiveBuffer[itr], 1, 100);
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
void EEPROM_READ_FloatData(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, float *data)
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
        HAL_I2C_Mem_Read(hi2c, MemAddr, addr, 1, &ReceiveBuffer[itr], 1, 100);
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
void EEPROM_READ_DoubleData(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, double *data)
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
        HAL_I2C_Mem_Read(hi2c, MemAddr, addr, 1, &ReceiveBuffer[itr], 1, 100);
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