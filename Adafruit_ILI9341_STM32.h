/*
See rights and use declaration in License.h
This library has been modified for the Maple Mini
*/

#ifndef _ADAFRUIT_ILI9341H_
#define _ADAFRUIT_ILI9341H_

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <SPI.h>



#ifndef swap
  #define swap(a, b) { int16_t t = a; a = b; b = t; }
#endif

#define ILI9341_TFTWIDTH  240
#define ILI9341_TFTHEIGHT 320

#define ILI9341_NOP     0x00
#define ILI9341_SWRESET 0x01
#define ILI9341_RDDID   0x04
#define ILI9341_RDDST   0x09

#define ILI9341_SLPIN   0x10
#define ILI9341_SLPOUT  0x11
#define ILI9341_PTLON   0x12
#define ILI9341_NORON   0x13

#define ILI9341_RDMODE  0x0A
#define ILI9341_RDMADCTL  0x0B
#define ILI9341_RDPIXFMT  0x0C
#define ILI9341_RDIMGFMT  0x0A
#define ILI9341_RDSELFDIAG  0x0F

#define ILI9341_INVOFF  0x20
#define ILI9341_INVON   0x21
#define ILI9341_GAMMASET 0x26
#define ILI9341_DISPOFF 0x28
#define ILI9341_DISPON  0x29

#define ILI9341_CASET   0x2A
#define ILI9341_PASET   0x2B
#define ILI9341_RAMWR   0x2C
#define ILI9341_RAMRD   0x2E

#define ILI9341_PTLAR   0x30
#define ILI9341_MADCTL  0x36
#define ILI9341_PIXFMT  0x3A

#define ILI9341_FRMCTR1 0xB1
#define ILI9341_FRMCTR2 0xB2
#define ILI9341_FRMCTR3 0xB3
#define ILI9341_INVCTR  0xB4
#define ILI9341_DFUNCTR 0xB6

#define ILI9341_PWCTR1  0xC0
#define ILI9341_PWCTR2  0xC1
#define ILI9341_PWCTR3  0xC2
#define ILI9341_PWCTR4  0xC3
#define ILI9341_PWCTR5  0xC4
#define ILI9341_VMCTR1  0xC5
#define ILI9341_VMCTR2  0xC7

#define ILI9341_RDID1   0xDA
#define ILI9341_RDID2   0xDB
#define ILI9341_RDID3   0xDC
#define ILI9341_RDID4   0xDD

#define ILI9341_GMCTRP1 0xE0
#define ILI9341_GMCTRN1 0xE1
/*
#define ILI9341_PWCTR6  0xFC

*/



#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

class Adafruit_ILI9341_STM32 : public Adafruit_GFX {

 public:

  Adafruit_ILI9341_STM32(int8_t _CS, int8_t _DC, int8_t _RST = -1);

  void     begin(SPIClass & spi, uint32_t freq=48000000);
  void     begin(void) { begin(SPI); }
  void     setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1),
           pushColor(uint16_t color),
           pushColors(void * colorBuffer, uint16_t nr_pixels, uint8_t async=0),
           fillScreen(uint16_t color),
		       drawLine(int16_t x0, int16_t y0,int16_t x1, int16_t y1, uint16_t color),
           drawPixel(int16_t x, int16_t y, uint16_t color),
           drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color),
           drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color),
           fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color),
           setRotation(uint8_t r),
           invertDisplay(boolean i);
  uint16_t color565(uint8_t r, uint8_t g, uint8_t b);

  /* These are not for current use, 8-bit protocol only! */
  uint16_t readPixel(int16_t x, int16_t y);
  uint16_t readPixels(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t *buf);
  uint16_t readPixelsRGB24(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t *buf);
   void drawImage(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t *img);
  uint8_t  readcommand8(uint8_t reg, uint8_t index = 0);
  /*
  uint16_t readcommand16(uint8_t);
  uint32_t readcommand32(uint8_t);
  */

#define DMA_ON_LIMIT 250 // do DMA only for more data than this
#define SAFE_FREQ  24000000ul // 24MHz for reading

#define writePixel drawPixel

#define dc_command() ( *dcport  =(uint32_t)dcpinmask<<16 ) // 0
#define dc_data()    ( *dcport  =(uint32_t)dcpinmask )     // 1
#define cs_clear()   ( *csport  =(uint32_t)cspinmask<<16 )
#define cs_set()     ( *csport  =(uint32_t)cspinmask )
#define clk_clear()  ( *clkport =(uint32_t)clkpinmask<<16 )
#define clk_set()    ( *clkport =(uint32_t)clkpinmask )
#define mosi_clear() ( *mosiport=(uint32_t)misopinmask<<16 )
#define mosi_set()   ( *mosiport=(uint32_t)misopinmask )
#define miso_in()    ( (*misoport)&misopinmask )

  inline uint8_t spiread(void)  { return mSPI.transfer(0x00); }
  inline uint8_t readdata(void) { return mSPI.transfer(0x00); }
  inline void    writedata(uint8_t c)   { mSPI.write(c); }
  inline void    spiwrite(uint16_t c)   { mSPI.write(c); }
  inline void    spiwrite16(uint16_t c) { mSPI.write16(c); } // 8 bit mode

  void  writecommand(uint8_t c),
        commandList(uint8_t *addr);

 private:
  uint32_t _freq, _safe_freq;
  SPIClass & mSPI = SPI;

  volatile uint32_t *csport, *dcport;
  int8_t  _cs, _dc, _rst;
  uint16_t  cspinmask, dcpinmask;
  uint16_t lineBuffer[ILI9341_TFTHEIGHT]; // DMA buffer. 16bit color data per pixel
};


#endif
