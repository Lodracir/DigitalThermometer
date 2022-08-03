/* EEPROM Driver Header */
#include "APP/eeprom.h"

/****************************************************************
 *                                                              *
 *                 Static Prototype Functions                   *
 *                                                              *
 ****************************************************************/

/****************************************************************
 *                      Write Functions                         *
 ****************************************************************/

/** Unsigned Data **/
void    EEPROM_WRITE_U8BIT(SPI_HandleTypeDef *hspi, uint8_t addr, uint8_t data);
void    EEPROM_WRITE_U16BIT(SPI_HandleTypeDef *hspi, uint8_t addr, uint16_t data);
void    EEPROM_WRITE_U32BIT(SPI_HandleTypeDef *hspi, uint8_t addr, uint32_t data);
void    EEPROM_WRITE_U64BIT(SPI_HandleTypeDef *hspi, uint8_t addr, uint64_t data);

/** Signed Data **/
void    EEPROM_WRITE_S8BIT(SPI_HandleTypeDef *hspi, uint8_t addr, int8_t data);
void    EEPROM_WRITE_S16BIT(SPI_HandleTypeDef *hspi, uint8_t addr, int16_t data);
void    EEPROM_WRITE_S32BIT(SPI_HandleTypeDef *hspi, uint8_t addr, int32_t data);
void    EEPROM_WRITE_S64BIT(SPI_HandleTypeDef *hspi, uint8_t addr, int64_t data);

/** Float and Double Data **/
void    EEPROM_WRITE_FloatData(SPI_HandleTypeDef *hspi, uint8_t addr, float data);
void    EEPROM_WRITE_DoubleData(SPI_HandleTypeDef *hspi, uint8_t addr, double data);

/****************************************************************
 *                       Read Functions                         *
 ****************************************************************/

/** Unsigned Data **/
void    EEPROM_READ_U8BIT(SPI_HandleTypeDef *hspi, uint8_t addr, uint8_t *data);
void    EEPROM_READ_U16BIT(SPI_HandleTypeDef *hspi, uint8_t addr,uint16_t *data);
void    EEPROM_READ_U32BIT(SPI_HandleTypeDef *hspi, uint8_t addr,uint32_t *data);
void    EEPROM_READ_U64BIT(SPI_HandleTypeDef *hspi, uint8_t addr,uint64_t *data);

/** Signed Data **/
void    EEPROM_READ_S8BIT(SPI_HandleTypeDef *hspi, uint8_t addr, int8_t *data);
void    EEPROM_READ_S16BIT(SPI_HandleTypeDef *hspi, uint8_t addr, int16_t *data);
void    EEPROM_READ_S32BIT(SPI_HandleTypeDef *hspi, uint8_t addr, int32_t *data);
void    EEPROM_READ_S64BIT(SPI_HandleTypeDef *hspi, uint8_t addr, int64_t *data);

/** Float and Double Data **/
void    EEPROM_READ_FloatData(SPI_HandleTypeDef *hspi, uint8_t addr, float *data);
void    EEPROM_READ_DoubleData(SPI_HandleTypeDef *hspi, uint8_t addr, double *data);

/****************************************************************
 *                                                              *
 *                          Functions                           *
 *                                                              *
 ****************************************************************/

void EEPROM_Init(EEPROM_t *heeprom)
{

    /** Allocate Write Functions **/
    heeprom->write.U8BIT        = EEPROM_WRITE_U8BIT;
    heeprom->write.U16BIT       = EEPROM_WRITE_U16BIT;
    heeprom->write.U32BIT       = EEPROM_WRITE_U32BIT;
    heeprom->write.U64BIT       = EEPROM_WRITE_U64BIT;
    heeprom->write.S8BIT        = EEPROM_WRITE_S8BIT;
    heeprom->write.S16BIT       = EEPROM_WRITE_S16BIT;
    heeprom->write.S32BIT       = EEPROM_WRITE_S32BIT;
    heeprom->write.S64BIT       = EEPROM_WRITE_S64BIT;
    heeprom->write.FloatData    = EEPROM_WRITE_FloatData;
    heeprom->write.DoubleData   = EEPROM_WRITE_DoubleData;

    /** Allocate Read Functions **/
    heeprom->read.U8BIT        = EEPROM_READ_U8BIT;
    heeprom->read.U16BIT       = EEPROM_READ_U16BIT;
    heeprom->read.U32BIT       = EEPROM_READ_U32BIT;
    heeprom->read.U64BIT       = EEPROM_READ_U64BIT;
    heeprom->read.S8BIT        = EEPROM_READ_S8BIT;
    heeprom->read.S16BIT       = EEPROM_READ_S16BIT;
    heeprom->read.S32BIT       = EEPROM_READ_S32BIT;
    heeprom->read.S64BIT       = EEPROM_READ_S64BIT;
    heeprom->read.FloatData    = EEPROM_READ_FloatData;
    heeprom->read.DoubleData   = EEPROM_READ_DoubleData;

}

void EEPROM_DeInit(EEPROM_t *heeprom)
{

    /** Deallocate Write Functions **/
    heeprom->write.U8BIT        = NULL;
    heeprom->write.U16BIT       = NULL;
    heeprom->write.U32BIT       = NULL;
    heeprom->write.U64BIT       = NULL;
    heeprom->write.S8BIT        = NULL;
    heeprom->write.S16BIT       = NULL;
    heeprom->write.S32BIT       = NULL;
    heeprom->write.S64BIT       = NULL;
    heeprom->write.FloatData    = NULL;
    heeprom->write.DoubleData   = NULL;

    /** Deallocate Read Functions **/
    heeprom->read.U8BIT        = NULL;
    heeprom->read.U16BIT       = NULL;
    heeprom->read.U32BIT       = NULL;
    heeprom->read.U64BIT       = NULL;
    heeprom->read.S8BIT        = NULL;
    heeprom->read.S16BIT       = NULL;
    heeprom->read.S32BIT       = NULL;
    heeprom->read.S64BIT       = NULL;
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
void EEPROM_WRITE_U8BIT(SPI_HandleTypeDef *hspi, uint8_t addr, uint8_t data)
{

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_WRITE_U16BIT(SPI_HandleTypeDef *hspi, uint8_t addr, uint16_t data)
{

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_WRITE_U32BIT(SPI_HandleTypeDef *hspi, uint8_t addr, uint32_t data)
{

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_WRITE_U64BIT(SPI_HandleTypeDef *hspi, uint8_t addr, uint64_t data)
{

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_WRITE_S8BIT(SPI_HandleTypeDef *hspi, uint8_t addr, int8_t data)
{

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_WRITE_S16BIT(SPI_HandleTypeDef *hspi, uint8_t addr, int16_t data)
{

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_WRITE_S32BIT(SPI_HandleTypeDef *hspi, uint8_t addr, int32_t data)
{

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_WRITE_S64BIT(SPI_HandleTypeDef *hspi, uint8_t addr, int64_t data)
{

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_WRITE_FloatData(SPI_HandleTypeDef *hspi, uint8_t addr, float data)
{

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_WRITE_DoubleData(SPI_HandleTypeDef *hspi, uint8_t addr, double data)
{

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
void EEPROM_READ_U8BIT(SPI_HandleTypeDef *hspi, uint8_t addr, uint8_t *data)
{

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_READ_U16BIT(SPI_HandleTypeDef *hspi, uint8_t addr,uint16_t *data)
{

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_READ_U32BIT(SPI_HandleTypeDef *hspi, uint8_t addr,uint32_t *data)
{

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_READ_U64BIT(SPI_HandleTypeDef *hspi, uint8_t addr,uint64_t *data)
{

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_READ_S8BIT(SPI_HandleTypeDef *hspi, uint8_t addr, int8_t *data)
{

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_READ_S16BIT(SPI_HandleTypeDef *hspi, uint8_t addr, int16_t *data)
{

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_READ_S32BIT(SPI_HandleTypeDef *hspi, uint8_t addr, int32_t *data)
{

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_READ_S64BIT(SPI_HandleTypeDef *hspi, uint8_t addr, int64_t *data)
{

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_READ_FloatData(SPI_HandleTypeDef *hspi, uint8_t addr, float *data)
{

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void EEPROM_READ_DoubleData(SPI_HandleTypeDef *hspi, uint8_t addr, double *data)
{

}