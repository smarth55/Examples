//includes 
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_i2c.h>
#include "ST7735.h"
#include "imgnsnd.h"
#include "I2C.h"
#include "eeprom.h"
#include <math.h>
#include "audio.h"

//globals
#define NUNCHUK_ADDRESS 0xA4
#define ZEROJX 130
#define ZEROJY 135

#define MAXASTEROIDS 20

uint16_t asteroidImg[ASTEROIDSIZE];
uint16_t meter = 258;
uint32_t gameClock = 0;
uint8_t score = 0;
uint8_t randomX = 10; //to 120
uint8_t randomY = 12; //to 148
uint8_t randomDir = 0; //to 3
struct asteroid moveables[MAXASTEROIDS];
struct asteroid asteroid;
struct spaceship player;
uint8_t asteroidCount = 0;
uint8_t collided = 0;
uint8_t freeze = 0;
uint8_t high_score[] = {000};


static __IO uint32_t TimingDelay ;

/* RCC init for all clocks */
void RCC_Init() {
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE );
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 | RCC_APB1Periph_DAC | RCC_APB1Periph_TIM3, ENABLE); 
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
}

//Timer code
void Delay( uint32_t nTime ){
  TimingDelay = nTime ;
  while ( TimingDelay != 0);
}

int menu() {
  eepromRead(high_score, 1, 0);
  
  // load background 
  drawTitle();
  
  // display text 
  displayText("press c to start\0", 15, 92);
  
  displayText("high score\0", 35, 118);
  displayScore(high_score[0], 56, 128);
  
  while(1) {
    // Read nunchuck
    int C,Z;
    uint8_t data[6];
    const uint8_t buf[] = {0};
    I2C_Write(I2C1, buf, 1, NUNCHUK_ADDRESS);
    I2C_Read(I2C1, data, 6, NUNCHUK_ADDRESS);
    
    C = ((data[5] >> 1) & 1);
    Z = (data[5] & 1);
    
    if(!C){
      return;
    }
  }
}

void moveAsteroid() {
  // check direction and move
  int i;
  for (i = 0; i < asteroidCount; i++) {
    checkAudio();
    if (moveables[i].x == 0 && moveables[i].y == 0) {
      Delay(1);
      moveables[i].dir = randomDir;
      if (moveables[i].dir == 0) { //Down
	moveables[i].x = randomX;
	moveables[i].y = 129;
      } else if (moveables[i].dir == 1) {  //Left
	moveables[i].x = 10;
	moveables[i].y = randomY;
      } else if (moveables[i].dir == 2) { // Up
	moveables[i].x = randomX;
	moveables[i].y = 12;
      } else {  // Right
	moveables[i].x = 100;
	moveables[i].y = randomY;
      }
    }
    checkAudio();
    if ((moveables[i].x >= 0+ASTEROIDRADIUS) && (moveables[i].x <= ST7735_width-ASTEROIDRADIUS-1) &&
	(moveables[i].y >= ASTEROIDRADIUS+2) && (moveables[i].y <= ST7735_height-ASTEROIDRADIUS-11)) {
      if (!freeze) {
	if (moveables[i].dir == 0) { //DOWN
	  moveables[i].y -= 1;
	} else if (moveables[i].dir == 1) { //LEFT
	  moveables[i].x += 1;
	} else if (moveables[i].dir == 2) { //UP
	  moveables[i].y += 1;
	} else {                   //RIGHT
	  moveables[i].x -= 1;
	}
      }
      checkAudio();
      drawAsteroid(asteroidImg, moveables[i].x, moveables[i].y);
      // check for collision
      float distance = sqrt((moveables[i].x - player.x)*(moveables[i].x - player.x) + (moveables[i].y - player.y)*(moveables[i].y - player.y));
      if (distance < SHIPRADIUS+ASTEROIDRADIUS) {
	collided = 1;
      }
      checkAudio();
    } else {
      fillBMP(0x0001,moveables[i].x,moveables[i].y,moveables[i].x+20,moveables[i].y+20);
      moveables[i].x = 0;
      moveables[i].y = 0;
    }
    checkAudio();
  }    
}

void move() {
  int JX, JY, C;
  // read nunchuck
  uint8_t data[6];
  const uint8_t buf[] = {0};
  I2C_Write(I2C1, buf, 1, NUNCHUK_ADDRESS);
  I2C_Read(I2C1, data, 6, NUNCHUK_ADDRESS);
  JX = data[0] - ZEROJX;
  JY = data[1] - ZEROJY;
  C = ((data[5] >> 1) & 1);
  checkAudio();
  // move ship
  if ((player.x >= 0+SHIPRADIUS) && (player.x <= ST7735_width-SHIPRADIUS)) {
    player.x += JX/100;
    if (player.x < 0+SHIPRADIUS) {
      player.x = 0+SHIPRADIUS;
    } else if (player.x > ST7735_width-SHIPRADIUS) {
      player.x = ST7735_width-SHIPRADIUS;
    }
  }
  checkAudio();
  if ((player.y >= 0+SHIPRADIUS+3) && (player.y <= ST7735_height-SHIPRADIUS-10)) {
    player.y += JY/100;
    if (player.y < 0+SHIPRADIUS+3) {
      player.y = 0+SHIPRADIUS+3;
    } else if (player.y > ST7735_height-SHIPRADIUS-10) {
      player.y = ST7735_height-SHIPRADIUS-10;
    }
  }
  drawShip(player.x, player.y);
  checkAudio();
  if (!C && meter > 0) {
    freeze = 1;
    meter -= 1;
    fill(0x0001,(meter/2),157,129,159);
  }
  if (C) freeze = 0;
  moveAsteroid();
  checkAudio();
}

// there are a billion checkAudios in here for shits and giggles (not really)
int game() { 
  int i;
  fill(0x0001,0,0,129,159);
  // load images to memory
  loadAsteroid(asteroidImg);

  //delay 3,2,1,start
  displayText("3\0", 62, 69);
  Delay(1000);
  displayText("2\0",62,69);
  Delay(1000);
  displayText("1\0",62,69);
  Delay(1000);
  displayText("START!\0",47,69);
  Delay(1000);
  fill(0x0001,47,69,83,79);
  asteroidCount = 0;
  gameClock = 1;
  displayText("SCORE\0",0,0);
  //draw meter
  fill(0xf800,0,158,128,160);
  
  // center the ship
  player.x = 59;
  player.y = 74;
  
  asteroid.x = 0;
  asteroid.y = 0;
  
  collided = 0;
  meter = 258;
  
  for (i = 0; i < MAXASTEROIDS; i++) {
    moveables[i] = asteroid;
  }
  loadAudio();
  while(1){
    checkAudio();
    move();
    checkAudio();
    displayText("SCORE\0",0,0);
    checkAudio();
    score = gameClock/1000;
    checkAudio();
    displayScore(score, 110, 0);
    checkAudio();
    asteroidCount = (score / 10)+1;
    if (asteroidCount > MAXASTEROIDS) {
      asteroidCount = MAXASTEROIDS;
    }
    checkAudio();
    if (collided) {
      audioStop();
      return;
    }
    checkAudio();
  }
}

void end() {
  eepromRead(high_score,1,0);
  if (score > high_score[0]) {
    high_score[0] = score;
    eepromWrite(high_score[0],1,0);
  }
  
  fill(0x0001,0,0,129,159);
  //show score
  displayText("press c to return\0", 15, 35);
  displayText("your score\0", 35, 45);
  displayScore(score, 56, 55);
  
  displayText("high score\0", 35, 118);
  displayScore(high_score[0], 56, 128);
  while(1) {
    
    int C,Z;
    // Read nunchuck
    uint8_t data[6];
    const uint8_t buf[] = {0};
    I2C_Write(I2C1, buf, 1, NUNCHUK_ADDRESS);
    I2C_Read(I2C1, data, 6, NUNCHUK_ADDRESS);
    
    C = ((data[5] >> 1) & 1);
    Z = (data[5] & 1);
    
    if(!C){
      return;
    }
  }
}

int main() {
  if ( SysTick_Config ( SystemCoreClock / 1000) )
    while (1);
  
  //init Clocks
  RCC_Init();
  //init SPI
  spiInit(SPI2);
  //init LCD
  ST7735_init();
  //init I2C
  
  I2C_LowLevel_Init(I2C1, 10000, NUNCHUK_ADDRESS);
  
  /* init Nunchuck */
  const uint8_t buf[] = {0xf0, 0x55};
  const uint8_t buf2[] = {0xfb, 0x00};
  I2C_Write(I2C1, buf, 2, NUNCHUK_ADDRESS);
  I2C_Write(I2C1, buf2, 2, NUNCHUK_ADDRESS);
  
  mountSD();
  
  Delay(1000);
  
  /* main loop */
  while(1) {
    gameClock = 0;
    menu();
    
    game();
    
    end();
    
  }
  
  return(0);
}

void SysTick_Handler (void){
  if ( TimingDelay != 0x00)
    TimingDelay--;
  if (gameClock != 0) {
    gameClock++;
  }
  randomX++;
  randomY++;
  randomDir++;
  if (randomX > 118) {
    randomX = 10;
  }
  if (randomY > 139) {
    randomY = 12;
  }
  if (randomDir > 3) {
    randomDir = 0;
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif