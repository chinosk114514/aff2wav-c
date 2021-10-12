#ifndef AFF2WAV_C_DECLARE_H
#define AFF2WAV_C_DECLARE_H
#include <string.h> // For size_t definition
#include <stdint.h>

typedef struct {
    long timing;
    int type;
} MIXERDATA;

typedef struct wave_header
{
    uint8_t  riff[4]; // 'R I F F'
    uint32_t size;
    uint8_t  waveFlag[4];//' W A V E'
    uint8_t  fmt[4];//'F M T'
    uint32_t fmtLen; /* 16 for PCM */
    uint16_t tag;/* PCM = 1*/
    uint16_t channels;
    uint32_t sampFreq;
    uint32_t byteRate;
    uint16_t blockAlign;/* = NumChannels * BitsPerSample/8 */
    uint16_t bitSamp;
    uint8_t  dataFlag[4];//'D A T A'
    uint32_t length;/* data size */
} wave_header_t;

typedef struct wave_file
{
    wave_header_t header;
    uint32_t *data;
}wave_file_t;

// Module
MIXERDATA* analyzeOSU(char* affContent, size_t contentLength, size_t* output_mixerDataLength);
MIXERDATA* analyzeAff(char* affContent, size_t contentLength, size_t* output_mixerDataLength);
struct wave_file read_wav_file(char *file_path);

// Util
short validateShort(short x, short y);
short makeWord(unsigned char low, unsigned char high);
float bits2time(int bitCount);
const unsigned char* getData(int dataType);
int getDataLen(int dataType);
int getTiming(const void* a, const void* b);
char* getMiddleText(char* text, char* beginWith, char* endWith);
unsigned char* mixKeysound(MIXERDATA* mixerData, size_t mixerDataLength, size_t* output_keysoundDataLength, int offset);
void* packWav(unsigned char* keysoundData, size_t keysoundDataLength, size_t* output_wavDataLength);
char* splittext(char* text, char* split, int retcount);

// Const data
extern const int AUDIOTAP_LEN;
extern const int AUDIOARC_LEN;
extern const unsigned char WAVHEADER[];
extern const unsigned char AUDIOTAP[];
extern const unsigned char AUDIOARC[];
extern const int ARC;
extern const int OSU;

#endif
