#define LOW 0
#define HIGH 1

#define LCD_C LOW
#define LCD_D HIGH

#define ST7735_width 128
#define ST7735_height 160

#define ST7735_CASET 0x2A
#define ST7735_RASET 0x2B
#define ST7735_MADCTL 0x36
#define ST7735_RAMWR 0x2C
#define ST7735_RAMRD 0x2E
#define ST7735_COLMOD 0x3A

#define MADCTLGRAPHICS 0x6
#define MADCTLBMP 0x2


void ST7735_setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t madctl);
void ST7735_pushColor(uint16_t *color , int cnt);
void ST7735_backLight(uint8_t on);
void ST7735_init();
static void LcdWrite(char dc, const char *data, int nbytes);
static void LcdWrite16(char dc, const uint16_t *data, int cnt);
static void ST7735_writeCmd(uint8_t c);
