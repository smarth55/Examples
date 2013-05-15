#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_spi.h>
#include "ST7735.h"
#include "spidma.c"

// add Delay function



#define MADVAL(x) (((x) << 5) | 8)

struct ST7735_cmdBuf {
  uint8_t command; // ST7735 command byte
  uint8_t delay; // ms delay after
  uint8_t len; // length of parameter data
  uint8_t data[16]; // parameter data
};

static const struct ST7735_cmdBuf initializers[] = {
  // SWRESET Software reset
  { 0x01, 150, 0, 0},
  // SLPOUT Leave sleep mode
  { 0x11, 150, 0, 0},
  // FRMCTR1 , FRMCTR2 Frame Rate configuration -- Normal mode, idle
  // frame rate = fosc / (1 x 2 + 40) * (LINE + 2C + 2D)
  { 0xB1, 0, 3, { 0x01, 0x2C, 0x2D }},
  { 0xB2, 0, 3, { 0x01, 0x2C, 0x2D }},
  // FRMCTR3 Frame Rate configureation -- partial mode
  { 0xB3, 0, 6, { 0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D }},
  // INVCTR Display inversion (no inversion)
  { 0xB4, 0, 1, { 0x07 }},
  // PWCTR1 Power control -4.6V, Auto mode
  { 0xC0, 0, 3, { 0xA2, 0x02, 0x84}},
  // PWCTR2 Power control VGH25 2.4C, VGSEL -10, VGH = 3 * AVDD
  { 0xC1, 0, 1, { 0xC5}},
  // PWCTR3 Power control , opamp current smal, boost frequency
  { 0xC2, 0, 2, { 0x0A, 0x00 }},
  // PWCTR4 Power control , BLK/2, opamp current small and medium low
  { 0xC3, 0, 2, { 0x8A, 0x2A}},
  // PWRCTR5 , VMCTR1 Power control
  { 0xC4, 0, 2, { 0x8A, 0xEE}},
  { 0xC5, 0, 1, { 0x0E }},
  // INVOFF Don't invert display
  { 0x20, 0, 0, 0},
  // Memory access directions. row address/col address , bottom to top refesh (10.1.27)
  { ST7735_MADCTL , 0, 1, {MADVAL(MADCTLGRAPHICS)}},
  // Color mode 16 bit (10.1.30
  { ST7735_COLMOD , 0, 1, {0x05}},
  // Column address set 0..127
  { ST7735_CASET , 0, 4, {0x00, 0x00, 0x00, 0x7F }},
  // Row address set 0..159
  { ST7735_RASET , 0, 4, {0x00, 0x00, 0x00, 0x9F }},
  // GMCTRP1 Gamma correction
  { 0xE0, 0, 16, {0x02, 0x1C, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2D, 0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10 }},
  // GMCTRP2 Gamma Polarity corrction
  { 0xE1, 0, 16, {0x03, 0x1d, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D, 0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10 }},
  // DISPON Display on
  { 0x29, 100, 0, 0},
  // NORON Normal on
  { 0x13, 10, 0, 0},
  // End
  { 0, 0, 0, 0}
};

static uint8_t madctlcurrent = MADVAL(MADCTLGRAPHICS);

void ST7735_setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t madctl) {
  madctl = MADVAL(madctl);
  if (madctl != madctlcurrent) {
    ST7735_writeCmd(ST7735_MADCTL);
    LcdWrite(LCD_D , &madctl , 1);
    madctlcurrent = madctl;
  }
  ST7735_writeCmd(ST7735_CASET);
  LcdWrite16(LCD_D , &x0, 1);
  LcdWrite16(LCD_D , &x1, 1);
  
  ST7735_writeCmd(ST7735_RASET);
  LcdWrite16(LCD_D , &y0, 1);
  LcdWrite16(LCD_D , &y1, 1);
  
  ST7735_writeCmd(ST7735_RAMWR);
}

void ST7735_pushColor(uint16_t *color , int cnt) {
  LcdWrite16(LCD_D , color , cnt);
}

void ST7735_backLight(uint8_t on) {
  if (on)
    GPIO_WriteBit(GPIOA ,GPIO_Pin_1 , LOW);
  else
    GPIO_WriteBit(GPIOA ,GPIO_Pin_1 , HIGH);
}

void ST7735_init() {
  GPIO_InitTypeDef GPIO_InitStructure;
  const struct ST7735_cmdBuf *cmd;
  
  // set cs, reset low
  GPIO_WriteBit(GPIOC ,GPIO_Pin_0 , HIGH);
  GPIO_WriteBit(GPIOC ,GPIO_Pin_1 , HIGH);
  Delay(10);
  GPIO_WriteBit(GPIOC ,GPIO_Pin_1 , LOW);
  Delay(10);
  GPIO_WriteBit(GPIOC ,GPIO_Pin_1 , HIGH);
  Delay(10);

  // Send initialization commands to ST7735
  for (cmd = initializers; cmd->command; cmd++) {
    LcdWrite(LCD_C , &(cmd->command), 1);
    if (cmd->len)
      LcdWrite(LCD_D , cmd->data, cmd->len);
    if (cmd->delay)
      Delay(cmd->delay);
  }
}

static void LcdWrite(char dc, const char *data, int nbytes) {
  GPIO_WriteBit(GPIOC ,GPIO_Pin_2 , dc); // dc 1 = data, 0 = control
  GPIO_ResetBits(GPIOC ,GPIO_Pin_0);
  xchng_datablock(SPI2 , 0, data, 0, nbytes);
  GPIO_SetBits(GPIOC ,GPIO_Pin_0);
}

static void LcdWrite16(char dc, const uint16_t *data, int cnt) {
  GPIO_WriteBit(GPIOC ,GPIO_Pin_2 , dc); // dc 1 = data, 0 = control
  GPIO_ResetBits(GPIOC ,GPIO_Pin_0);
  xchng_datablock(SPI2 , 1, data, 0, cnt);
  GPIO_SetBits(GPIOC ,GPIO_Pin_0);
}
static void ST7735_writeCmd(uint8_t c) {
  LcdWrite(LCD_C , &c, 1);
}

