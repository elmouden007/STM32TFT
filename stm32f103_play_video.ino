#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341_STM32.h"
#include "SdFat.h"

#define TFT_CS   PA4
#define TFT_RST  PA2
#define TFT_MOSI PA7
#define TFT_CLK  PA5
#define TFT_MISO PA6
#define TFT_DC   PA3

#define NLINES 30
uint16_t buf[200*NLINES]; 

#define USE_SDIO 0
const uint8_t SD_CS = PA0;
SdFat sd;SdFile file;int videoNo=0;

Adafruit_ILI9341_STM32 tft = Adafruit_ILI9341_STM32(TFT_CS,TFT_DC, TFT_RST);


// use 18 if your SD card doesn't work

#define SD_SPEED 36
void sdSPI() { SPI.beginTransaction(SD_SCK_MHZ(SD_SPEED)); }
void tftSPI() { SPI.beginTransaction(SPISettings(36000000, MSBFIRST, SPI_MODE3, DATA_SIZE_16BIT)); }

// the callback function below renders decoded JPEG on the tft
bool rendertft(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
  tftSPI();
  if(y>=tft.height()) return 0; // 0 - to stop decoding
  tft.drawImage(x,y, w,h, bitmap);
  return 1; // 1 - to decode next block
}

void setup() {
  Serial.begin(9600);
  Serial.println("ILI9341 Test!"); 
  tft.begin();
   

   
if(!sd.cardBegin(SD_CS, SD_SCK_MHZ(SD_SPEED))) {
    tftSPI(); tft.fillScreen(RED);
    Serial.println("\nSD Card\ninitialization\nfailed.\n");
    while(1);
  }
  if(!sd.fsBegin()) {
    tftSPI(); tft.fillScreen(YELLOW);
    Serial.println("\nFile System\ninitialization\nfailed.\n");
    while(1);
  }
  tftSPI();
  tft.setRotation(3);
  tft.fillScreen(BLACK);
}

void loop() {

showVideo("3008.raw",0,0, 320,240,10,1);  // ok
}

int statMode=0;

void showVideo(char *name, int x, int y, int wd, int ht, int nl, int skipFr)

{
  if(!file.open(name, O_CREAT | O_RDONLY)) {
    tftSPI(); tft.fillScreen(YELLOW);
    sd.errorHalt(F("open failed"));
  }
  file.seekSet(0);

  while(file.available()) {
     for(int i=0;i<ht/nl;i++) {
       int rd = file.read(buf,wd*2*nl);
      tftSPI();
       for(int j=0;j<nl;j++) tft.drawImage(0,i*nl+j+(statMode>0?0:0),tft.width(),1,buf+0
      +j*wd);
 
    }

  }
  file.close();
}
