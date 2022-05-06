#include "MCUFRIEND_kbv.h"
#include "bitmap_RGB.h"
MCUFRIEND_kbv tft;

#define BLACK   0x0000
#define WHITE   0xFFFF
uint16_t ID = 0;
static uint8_t aspect = 0;
//////////////////TFT Display page////////////////////
void logo_page() {
  tft.fillScreen(BLACK);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.drawRGBBitmap(45, 166, IGGG_128x64, 128, 64);
  tft.setCursor(45, 240);
  tft.print("CAN BUS READER");
  delay(5000);
  tft.fillScreen(BLACK);
}
void TFT_info_page() {
  tft.setRotation(aspect);
  tft.fillScreen(BLACK);
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.print("Screen Info");
  tft.setTextSize(1);
  tft.setCursor(40, 40);
  tft.print("TFT ID: 0x");
  tft.println(ID, HEX);
  tft.setCursor(40, 60);
  tft.print("Width: ");
  tft.print(tft.width(), DEC);
  tft.setCursor(40, 80);
  tft.print("Height: ");
  tft.print(tft.height(), DEC);
  //delay(5000);
  //tft.fillScreen(BLACK);
}
void can_page() {
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.print("CAN BUS MSG");

  tft.setTextSize(1);
  tft.setCursor(0, 30);
  tft.print("ID");
  tft.setCursor(50, 30);
  tft.print("Size");
  tft.setCursor(150, 30);
  tft.print("data");
}
void TFT_can_page(uint32_t can_id, uint8_t dlc, uint8_t data[], int order) {
  int seq = 45 + order * 10;
  tft.setCursor(0, seq);
  tft.fillRect(0, seq, 240, 10, BLACK);

  tft.setCursor(0, seq);
  tft.print("0x");
  tft.print(can_id, HEX);
  tft.setCursor(60, seq);
  tft.print(dlc, DEC);
  tft.setCursor(100, seq);
  for (int i = 0 ; i < dlc; i++) {
    tft.print(data[i], HEX);
    tft.print(" ");
  }
}

void tft_init(){
  tft.reset();
  ID = tft.readID();
  tft.begin(ID);
  logo_page();
  //TFT_info_page();
  can_page();
}
