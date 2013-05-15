#define SHIPSIZE 196
#define ASTEROIDSIZE 400
#define SHIPRADIUS 7
#define ASTEROIDRADIUS 10

struct spaceship {
  uint8_t x;
  uint8_t y;
};

struct asteroid {
  uint8_t x;
  uint8_t y;
  uint8_t dir;
};



void loadAsteroid(uint16_t *oBuff);
void loadShip(uint16_t *oBuff);
void loadAudio();
void checkAudio();
void audioStop();
void drawTitle();
void drawShip(uint8_t x, uint8_t y);
void clearShip(uint8_t x, uint8_t y);
void drawAsteroid(uint16_t oBuff[], uint8_t x, uint8_t y);
void displayText(char c[], uint8_t startx, uint8_t starty);
void displayScore(uint8_t score, uint8_t startx, uint8_t starty);
void fillBMP(uint16_t color, uint8_t x, uint8_t y, uint8_t x2, uint8_t y2);
void fill(uint16_t color, uint8_t x, uint8_t y, uint8_t x2, uint8_t y2);
void mountSD();
