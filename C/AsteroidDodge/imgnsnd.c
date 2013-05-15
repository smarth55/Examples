#include <stdlib.h>
#include "ff9/src/ff.h"
#include "bmp.h"
#include "ST7735.h"
#include "imgnsnd.h"
#include "lcdfont.c"
#include "wav.h"
#include "audio.h"

FATFS Fatfs;		/* File system object */
FIL Fil;			/* File object */
struct bmpfile_magic magic;
struct bmpfile_header header;
BITMAPINFOHEADER info;
struct ckhd hd;
struct fmtck fck;
uint32_t  waveid;

uint8_t Audiobuf[AUDIOBUFSIZE];
uint8_t next;
int audioplayerHalf = 0;
int audioplayerWhole = 0;


uint16_t SHIP[] = {0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,0,
                   0,    0,    0,    0, 8558,17047,21342,21308,17014, 8458,    0,    0,    0,0,   //1
                   0,    0, 2115,17048,25471,23423,23359,21407,21343,21343,16982,   32,    0,0,   //2
                   0,   34,19161,21407,25503,65535,23391,23519,65535,21375,21406,17047,    0,0,   //3
                   0,10638,23423,21375,21375,27486,39543,41588,27453,23391,21375,23391, 6442,0,   //4
                   0,19161,23519,65535,23391,59790,64336,64563,59884,29565,65535,21375,14965,0,   //5
                   0,23359,23423,23358,35577,64208,65535,65503,64855,41588,23391,21375,21241,0,   //6
                   0,23390,23359,21439,33498,64239,63487,65535,62775,39542,23390,25407,19194,0,   //7
                   0,17113,23518,65535,21311,55824,64269,64401,57837,27551,65535,23423,14965,0,   //8
                   0,10607,23423,21342,21407,23359,33530,35546,25439,21406,23390,23391, 6441,0,   //9
                   0,    0,19098,23391,23519,63487,23359,27583,65535,21375,21407,16983,    0,0,   //10
                   0,    0,   68,14933,23391,23422,19359,23359,23391,23391,14900,2049,     0,0,   //11
                   0,    0,    0,   32, 8493,14932,21211,19195,12883, 6410,    0,   0,     0,0,
                   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,0};  //12

/* Stop with dying message */
void die (FRESULT rc) { /* FatFs return value */  
  for (;;) ;  
}

/* Color converter*/
uint16_t colorConversion(struct bmppixel p) {
  uint16_t outp;
  outp = ((p.r & 0xf8) << 8) | ((p.g & 0xfc) << 3) | ((p.b & 0xf8) >> 3);
  return(outp);
}

/* Load asteroid */
void loadAsteroid(uint16_t *oBuff) {
  struct bmppixel Buff[ASTEROIDSIZE];
  
  FRESULT rc;				/* Result code */
  DIR dir;				/* Directory object */
  FILINFO fno;			/* File information object */
  UINT bw, br, i;
  
  rc = f_open(&Fil, "asteroid.bmp", FA_READ);
  if (!rc) {
    rc = f_read(&Fil, &magic, sizeof (struct bmpfile_magic), &br);
    rc = f_read(&Fil, &header, sizeof (struct bmpfile_header), &br);
    rc = f_read(&Fil, &info, sizeof (BITMAPINFOHEADER), &br);
    if (info.bitspp == 24 && info.width == 20 && info.height == 20) {
      for (;;) {
	/* Read a chunk of file */
	rc = f_read(&Fil, Buff, ASTEROIDSIZE * 3, &br); 
	if (rc || !br) break;/* Error or end of file */
	for (i = 0; i < ASTEROIDSIZE; i++) {/* do conversion and send to DMA */
	  oBuff[i] = colorConversion(Buff[i]);
	}
      }
    }
    if (rc) die(rc);
    rc = f_close(&Fil);
    if (rc) die(rc);
  }
}

/* Load spaceship */
void loadShip(uint16_t *oBuff) {
  struct bmppixel Buff[SHIPSIZE];
  
  FRESULT rc;				/* Result code */
  DIR dir;				/* Directory object */
  FILINFO fno;			/* File information object */
  UINT bw, br, i;
  
  rc = f_open(&Fil, "spaceship.bmp", FA_READ);
  if (!rc) {
    rc = f_read(&Fil, &magic, sizeof (struct bmpfile_magic), &br);
    rc = f_read(&Fil, &header, sizeof (struct bmpfile_header), &br);
    rc = f_read(&Fil, &info, sizeof (BITMAPINFOHEADER), &br);
    if (info.bitspp == 24 && info.width == 12 && info.height == 12) {
      for (;;) {
	/* Read a chunk of file */
	rc = f_read(&Fil, Buff, SHIPSIZE * 3, &br); 
	if (rc || !br) break;/* Error or end of file */
	for (i = 0; i < SHIPSIZE; i++) {/* do conversion and send to DMA */
	  oBuff[i] = colorConversion(Buff[i]);
	}
      }
    }
    if (rc) die(rc);
    rc = f_close(&Fil);
    if (rc) die(rc);
  }
}

void loadAudio() {
  FRESULT rc;				/* Result code */
  DIR dir;				/* Directory object */
  FILINFO fno;			/* File information object */
  UINT bw, br, i;
  
  rc = f_open(&Fil, "rock.wav", FA_READ);
  if (!rc) {
    //read headers
    f_read(&Fil, &hd, sizeof(struct ckhd), &br); //RIFF
    f_read(&Fil, &waveid, sizeof(waveid), &br);  //WAVEID
    f_read(&Fil, &hd, sizeof(struct ckhd), &br); //FMT HD
    f_read(&Fil, &fck, sizeof(fck), &br);        //FMT
    while (1) {
      f_read(&Fil, &hd, sizeof(struct ckhd), &br);
      if (hd.ckID == 'atad') {
	break;
      }
    }
    audioplayerInit(fck.nSamplesPerSec);
    rc = f_read(&Fil, Audiobuf, 100, &br);
    audioplayerStart();
  } else {
    if (rc) die(rc);
    rc = f_close(&Fil);
    if (rc) die(rc); 
  }
}

void checkAudio() {
  UINT br;
  next = (hd.cksize > AUDIOBUFSIZE/2) ? AUDIOBUFSIZE/2 : hd.cksize;
  if (audioplayerHalf) {
    if (next < AUDIOBUFSIZE/2)
      bzero(Audiobuf , AUDIOBUFSIZE/2);
    f_read(&Fil, Audiobuf , next, &br);
    hd.cksize -= br;
    audioplayerHalf = 0;
  }
  if (audioplayerWhole) {
    f_read(&Fil, Audiobuf + next , next, &br);
    hd.cksize -= br;
    audioplayerWhole = 0;
  }
  if (!hd.cksize) {
    //disable player
    audioplayerStop();
    f_close(&Fil);
  }
}

void audioStop() {
  audioplayerStop();
  f_close(&Fil);
}

//draw background
void drawTitle() {
  struct bmppixel Buff[128];
  uint16_t oBuff[128];
  
  FRESULT rc;				/* Result code */
  DIR dir;				/* Directory object */
  FILINFO fno;			/* File information object */
  UINT bw, br, i;
  
  rc = f_open(&Fil, "title.bmp", FA_READ);
  if (!rc) {
    rc = f_read(&Fil, &magic, sizeof (struct bmpfile_magic), &br);
    rc = f_read(&Fil, &header, sizeof (struct bmpfile_header), &br);
    rc = f_read(&Fil, &info, sizeof (BITMAPINFOHEADER), &br);
    if (info.bitspp == 24 || info.width == 128 || info.height == 160) {
    ST7735_setAddrWindow(0, 0, 127, 159, MADCTLBMP);
      for (;;) {
	/* Read a chunk of file */
	rc = f_read(&Fil, Buff, 384, &br); //384
	if (rc || !br) break;/* Error or end of file */
	for (i = 0; i < 128; i++) {/* do conversion and send to DMA */
	  oBuff[i] = colorConversion(Buff[i]);
	}
	ST7735_pushColor(oBuff , 128);	  
      }
    }
    if (rc) die(rc);
    rc = f_close(&Fil);
    if (rc) die(rc);
  }
}

void drawShip(uint8_t x, uint8_t y){
  ST7735_setAddrWindow(x-SHIPRADIUS, y-SHIPRADIUS, x+SHIPRADIUS-1, y+SHIPRADIUS-1, MADCTLBMP);
  ST7735_pushColor(SHIP , SHIPSIZE);
}
  
//draw asteroid
void drawAsteroid(uint16_t oBuff[], uint8_t x, uint8_t y){
  ST7735_setAddrWindow(x-ASTEROIDRADIUS, y-ASTEROIDRADIUS, x+ASTEROIDRADIUS-1, y+ASTEROIDRADIUS-1, MADCTLBMP);
  ST7735_pushColor(oBuff , ASTEROIDSIZE);
}

//draw text
void displayText(char c[], uint8_t startx, uint8_t starty) {
  uint8_t x,y,i;
  uint16_t white[] = {0xffff};
  uint16_t black[] = {0x0};
  for (i = 0; c[i] != '\0'; i++) {
    if (startx+6 > ST7735_width) {
      startx = 0;
      starty += 10;
    }
    uint8_t letter[] = {ASCII[c[i]*5], ASCII[(c[i]*5)+1], ASCII[(c[i]*5)+2], ASCII[(c[i]*5)+3], ASCII[(c[i]*5)+4], 0};
    ST7735_setAddrWindow(startx, starty, startx+5, starty+9, MADCTLGRAPHICS);
    for (y=0; y < 10; y++) {
      for (x=0; x < 6; x++) {
	if (((letter[x]&(1 << y)) >> y) == 1) {
	  ST7735_pushColor(white ,1);
	} else {
	  ST7735_pushColor(black ,1);
	}
      }
    }
    startx += 6;    
  }
}

// display score
void displayScore(uint8_t score, uint8_t startx, uint8_t starty) {
  char s[] = {0,0,0,'\0'};
  s[0] = (score / 100) + 48;
  score %= 100;
  s[1] = (score / 10) + 48;
  score %= 10;
  s[2] = (score / 1) + 48;
  displayText(s, startx, starty);
}

void fillBMP(uint16_t color, uint8_t x, uint8_t y, uint8_t x2, uint8_t y2) {
  uint8_t i,j;
  ST7735_setAddrWindow(x-ASTEROIDRADIUS, y-ASTEROIDRADIUS, x+ASTEROIDRADIUS, y+ASTEROIDRADIUS, MADCTLBMP);
  for (i = 0; i < y2-y; i++) {
    for (j = 0; j < x2-x; j++) {
      ST7735_pushColor(&color ,1);
    }
  }
}

//fill 
void fill(uint16_t color, uint8_t x, uint8_t y, uint8_t x2, uint8_t y2) {
  uint8_t i,j;
  ST7735_setAddrWindow(x, y, x2, y2, MADCTLGRAPHICS);
  for (i = 0; i < y2-y; i++) {
    for (j = 0; j < x2-x; j++) {
      ST7735_pushColor(&color ,1);
    }
  }
}

void mountSD(){
  f_mount(0, &Fatfs);  /* Register volume work area (never fails) */
}

/*---------------------------------------------------------*/
/* User Provided Timer Function for FatFs module           */
/*---------------------------------------------------------*/

DWORD get_fattime (void)
{
	return	  ((DWORD)(2012 - 1980) << 25)	/* Year = 2012 */
			| ((DWORD)1 << 21)				/* Month = 1 */
			| ((DWORD)1 << 16)				/* Day_m = 1*/
			| ((DWORD)0 << 11)				/* Hour = 0 */
			| ((DWORD)0 << 5)				/* Min = 0 */
			| ((DWORD)0 >> 1);				/* Sec = 0 */
}
