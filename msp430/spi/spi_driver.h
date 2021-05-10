/***********************************************************************************
 * @file SPIDriver.h
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
 * </table>
 ************************************************************************************/

#ifndef SPIDRIVER_H_
#define SPIDRIVER_H_


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
void SPI_MasterSetup(void);

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
void SPI_SlaveSetup(void);

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
void TransmitSPIbyte(const uint8_t Value);

/******************************************************************************
 * \b Function: inline uint8_t ReceiveSPIbyte(void)
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
uint8_t ReceiveSPIbyte(void);

#endif /* HEADER_SPIDRIVER_H_ */

/*EOF*/
