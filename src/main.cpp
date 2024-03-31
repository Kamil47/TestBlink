/* 
Kompilacia OK, displej nefunguje!?
Displej BW funguje pre uvedený font 9,12,18,24pt
Pre Arduino Uno  Vcc-5V, GND-GND
BUSY-D7, RST-D8, DC-D9, CS-D10, CLK-D13, DIN-D11
Pre Esp32 D1 mini Mosi Din-23, CLK-18, CS-5, DC-17, RST-16, BUSY-26 funguje OK
*/

#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold12pt7b.h> //7 riadkov a cca 27 znakov, celkom 189 znakov pre Bold9, 5x21 znakov Bold12, 4x14 Bold18
#define EPD_SS 5                      // CS SPI chip select 10 ArdUno
#define EPD_DC 17                     // DC SPI Data Control 9
#define EPD_RST 16                    // Reset external 8
#define EPD_BUSY 26                   // ArdUno 7
#define MAX_DISPLAY_BUFFER_SIZE 800   // Max buffer size
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2)/ (EPD::WIDTH / 8) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE / 2) /(EPD::WIDTH / 8))
GxEPD2_BW<GxEPD2_290_T94_V2, MAX_HEIGHT(GxEPD2_290_T94_V2) > display(GxEPD2_290_T94_V2(EPD_SS, EPD_DC, EPD_RST, EPD_BUSY));

void setup()
{
display.init(115200);                   // bitrate for diagnostic
//helloWorld();                           // funkcia
display.hibernate();                    // turns display OFF and set MCU to deep sleep
}
const char HelloWorld[] = "Test displeja BW a GIT";
void helloWorld()                       //funkcia nastavenia displeja
{
display.setRotation(1);                 //pismo        1 vodorovne 2 zvislo
display.setFont(&FreeMonoBold12pt7b);   //font
display.setTextColor(GxEPD_BLACK);      //farba textu

int16_t tbx, tby; uint16_t tbw, tbh;
display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);    //(text, cursor x, cursor y, x1, y1, širka, výška)// center the bounding box by transposition of the origin:
uint16_t x = ((display.width() - tbw) / 2) - tbx;    //Cursor vodorovne v px max 296
uint16_t y = ((display.height() - tbh) / 2) - tby;   //Cursor zvisle v px max 128

display.setFullWindow();                  //nedeje sa nič ak sa odstrani  
display.firstPage();                      //nedeje sa nič ak sa odstrani

do                                        //slucka musi byt inac sa nezobrazi nic
{
display.fillScreen(GxEPD_WHITE);          //farba plochy, pri bielej asi to je jedno
display.setCursor(x, y);                  //kurzor sa presne nastaví, ináč rozhádzané
display.print(HelloWorld);                //vytlači sa obsah za printom asi full refresh?
}
while (display.nextPage());
}
void loop() 
{
    //Test
};



