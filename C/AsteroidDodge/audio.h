#define AUDIOBUFSIZE 100
extern uint8_t Audiobuf[];
extern int audioplayerHalf;
extern int audioplayerWhole;
void audioplayerInit(uint32_t sampleRate);
void audioplayerStart();
void audioplayerStop();
