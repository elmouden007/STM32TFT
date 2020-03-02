STM32F103C8 - STM32DUION I/O

#define TFT_CS    PA4
#define TFT_RST   PA2
#define TFT_MOSI  PA7
#define TFT_CLK   PA5
#define TFT_MISO  PA6
#define TFT_DC    PA3
#define SD_CS     PA0 // FOR SD CART
#define F_CS      PA* // FOR MIMORY FLASH WINBOARD ANY DIGITAL PIN

TFT ILI9341 I/O                SD CART I/O

1 - VCC 3.3V                      1 - SD_CS
2 - GND                           2 - SD_MOSI
3 - CSS                           3 - SD_MISO
4 - RESET                         4 - SD_SCK
5 - DC/RS                         5 - F_CS.  FOR MIMORY FLASH CHIP
6 - SDI/MOSI
7 - SCK
8 - LED  3.3V OR 5V IS BEST
9 - SDO/MISO

ffmpeg -i  inputvideo.mp4  -vf scale=320:240 -c:v rawvideo -pix_fmt rgb565 output.rgb 

Reaname output to output.raw
