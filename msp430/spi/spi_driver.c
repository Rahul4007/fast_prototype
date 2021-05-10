/***********************************************************************************
 * @file SPIDriver.c
 * \b Processor: MSP430FR2033
 *
 * \b Complier: TI V18.1.3 LTS
 *
 * \b Company: Apollo Fire Detectors Ltd (c) 2016
 *
 ************************************************************************************
 * <b> File Description: </b>
 *
 * <table>
 * <tr><th> Parameter <th> Descriptions
 * <tr><td> Author <td> R. Sharma
 * <tr><td> Dependencies <td> Dependencies on SPIDriver header, Hardware header
 * </table>
 ************************************************************************************/
/******************************************************************************
 1. Within HardwareProfile_xxxxx.h, add the following #defines:-
 1.1 bit masks for:
 -SPI_STE
 -SPI_SIMO
 -SPI_SOMI
 -SPI_CLK

 1.2 Also define the Function Select register for the eUSCI-SPI peripheral as
 #define  SPI_PORT_SEL0     PxSEL0      // and PxSEL1 if needed


 *****************************************************************************/
#include <stdint.h>
#include <stdlib.h>

/* L O C A L   I N C L U D E S ***********************************************/
//clang-format off
#include "hardware_profile.h"
#include "spi_driver.h"
//clang-format on

/* T Y D E F E F ' s   A N D   D E F I N E S *********************************/

/* P R I V A T E   ( S T A T I C )   D E F I N I T I O N S *******************/

/* P U B L I C  ( G L O B A L )   V A R I A B L E S **************************/

/* P R I V A T E  ( S T A T I C )   V A R I A B L E S ************************/

/* P R I V A T E   ( S T A T I C )   P R O T O T Y P E S *********************/

/******************************************************************************
 * \b Function: void SPI_MasterSetup(void)
 *
 * \b Pre-Condition: None
 *
 * @param            [in] None
 *                   [out] None
 *
 * @return           None
 *
 * \b Input:         None
 *
 * \b Output:        None
 *
 *
 * \b Overview:      When completed, Configured SPI peripheral for master at desire configuration
 *
 ******************************************************************************/
void SPI_MasterSetup(void)
{
    /* enable the primary SPI functions on the I/O pins */
    SPI_PORT_SEL0 |= SPI_MOSI + SPI_MISO + SPI_SCK;
    /* Initialize USCI state machine*********************/
    UCB0CTLW0 |= UCSWRST;
    /* 3-pin, 8-bit SPI master***************************/
    UCB0CTLW0 |= UCMSB + UCCKPL + UCMST + UCSYNC;
    /* SMCLK -- 8Mhz*************************************/
    UCB0CTLW0 |= UCSSEL__SMCLK;
    /* SPI CLK - 1Mhz************************************/
    UCB0BR0 = 0x08U;
    UCB0BR1 = 0x00U;
    /* Initialize USCI state machine ********************/
    UCB0CTLW0 &= ~UCSWRST;
    /* Interrupt Disable*********************************/
    UCB0IE = 0U;
}

/******************************************************************************
 * \b Function: void SPI_SlaveSetup(void)
 *
 * \b Pre-Condition: None
 *
 * @param            [in] None
 *                   [out] None
 *
 * @return           None
 *
 * \b Input:         None
 *
 * \b Output:        None
 *
 *
 * \b Overview:      When completed, Configured SPI peripheral for slave at desire configuration
 *
 ******************************************************************************/
void SPI_SlaveSetup(void)
{
    SPI_PORT_SEL0 |= SPI_SCK + SPI_MOSI + SPI_MISO;
    /* Put state machine in reset */
    UCB0CTLW0 = UCSWRST;
    /* 3-pin, 8-bit SPI slave */
    UCB0CTLW0 |= UCMSB + UCCKPL + UCSYNC;
    /* Initialize USCI state machine */
    UCB0CTLW0 &= ~UCSWRST;
    /* Enable USCI0 RX interrupt */
    UCB0IE |= UCRXIE;
}

/******************************************************************************
 * \b Function: inline void TransmitSPIbyte(uint8_t Value)
 *
 * \b Pre-Condition: None
 *
 * @param            [in] None
 *                   [out] None
 *
 * @return           None
 *
 * \b Input:         None
 *
 * \b Output:        None
 *
 *
 * \b Overview:      when completed, the value updated in SPI TX buffer
 *
 ******************************************************************************/
void TransmitSPIbyte(const uint8_t Value)
{

    /* Update UCB0TXBUFF register */
    UCB0TXBUF = Value;
    while(UCB0STATW & UCBUSY);
}

/******************************************************************************
 * \b Function: inline uint8_t ReceiveSPIbyte(void)
 *
 * \b Pre-Condition: None
 *
 * @param            [in] None
 *                   [out] None
 *
 * @return           Value
 *
 * \b Input:         None
 *
 * \b Output:        None
 *
 *
 * \b Overview:      when completed, the value updated in SPI TX buffer
 *
 ******************************************************************************/
uint8_t ReceiveSPIbyte(void)
{
    uint8_t Value = 0;
    /* Update Variable with UCB0RXBUFF */
    Value = UCB0RXBUF;

    return Value;
}
/*EOF*/
