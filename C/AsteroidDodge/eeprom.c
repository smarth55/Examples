#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_spi.h>
#include "eeprom.h"
#include "spi.h"

#define WIP(x) ((x) & 1)

enum eepromCMD { cmdREAD = 0x03, cmdWRITE = 0x02,
                 cmdWREN = 0x06, cmdWRDI = 0x04,
                 cmdRDSR = 0x05, cmdWRSR = 0x01 };

void eepromInit() {
  //Init spi and eeprom pins
  spiInit(SPI2);
}

void eepromWriteEnable() {
  uint8_t cmd = cmdWREN;
  while (WIP(eepromReadStatus()));
  GPIO_WriteBit(GPIOC , GPIO_Pin_10 , 0);
  spiReadWrite(SPI2 , 0, &cmd, 1, SPI_SLOW);
  GPIO_WriteBit(GPIOC , GPIO_Pin_10 , 1);
}

void eepromWriteDisable() {
  uint8_t cmd = cmdWRDI;
  while (WIP(eepromReadStatus()));
  GPIO_WriteBit(GPIOC , GPIO_Pin_10 , 0);
  spiReadWrite(SPI2 , 0, &cmd, 1, SPI_SLOW);
  GPIO_WriteBit(GPIOC , GPIO_Pin_10 , 1);
}

uint8_t eepromReadStatus() {
  uint8_t cmd[] = {cmdRDSR , 0xff};
  uint8_t res[2];
  GPIO_WriteBit(GPIOC , GPIO_Pin_10 , 0);
  spiReadWrite(SPI2 , res, cmd, 2, SPI_SLOW);
  GPIO_WriteBit(GPIOC , GPIO_Pin_10 , 1);
  return res[1];
}

void eepromWriteStatus(uint8_t status) {
  uint8_t cmd[] = {cmdWRSR, status};
  while (WIP(eepromReadStatus()));
  GPIO_WriteBit(GPIOC , GPIO_Pin_10 , 0);
  spiReadWrite(SPI2 , 0, cmd, 2, SPI_SLOW);
  GPIO_WriteBit(GPIOC , GPIO_Pin_10 , 1);
}

//spi writing (SPIx , read buffer , write buffer , count , SPEED)
int eepromWrite(uint8_t *buf, uint8_t cnt, uint16_t offset) {
  int i;
  uint8_t cmd = cmdWRITE;
  for(i = 0; i < cnt; i++) {
    eepromWriteEnable();
    //we're writing one byte at a time for now.
    GPIO_WriteBit(GPIOC , GPIO_Pin_10 , 0);
    
    spiReadWrite(SPI2 , 0, &cmd, 1, SPI_SLOW);  //set write bit    
    spiReadWrite16(SPI2 , 0, &offset, 1, SPI_SLOW);  //address
    spiReadWrite(SPI2 , 0, buf+i, 1, SPI_SLOW);  //write data
    
    GPIO_WriteBit(GPIOC , GPIO_Pin_10 , 1);

    eepromWriteDisable();
    offset++;
    //Delay(10);
  }
  
  return 0;
  
}

int eepromRead(uint8_t *buf, uint8_t cnt, uint16_t offset) {
  uint8_t cmd = cmdREAD;
 
  while (WIP(eepromReadStatus()));
  
  GPIO_WriteBit(GPIOC , GPIO_Pin_10 , 0);
  
  spiReadWrite(SPI2 , 0, &cmd, 1, SPI_SLOW);
  spiReadWrite16(SPI2 , 0, &offset, 1, SPI_SLOW);
  spiReadWrite(SPI2 , buf, 0, cnt, SPI_SLOW);
  
  GPIO_WriteBit(GPIOC , GPIO_Pin_10 , 1);
  return 0;
  
}
