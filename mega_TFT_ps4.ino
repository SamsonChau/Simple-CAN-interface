#include "MCUFRIEND_kbv.h"
#include "bitmap_RGB.h"
#include <SPI.h>
#include <mcp2515.h>

MCUFRIEND_kbv tft;
MCP2515 mcp2515(10);
struct can_frame canMsg;

#define Motor_1_RevID 0x201
#define Motor_2_RevID 0x202
#define Motor_3_RevID 0x203
#define Motor_4_RevID 0x204
#define Motor_5_RevID 0x205
#define Motor_6_RevID 0x206
#define Motor_7_RevID 0x207
#define Motor_8_RevID 0x208
#define stm_id 0x200
#define cmd_id 0x255
#define odom_id 0x100
#define reset_id 0x000

#define BLACK   0x0000
#define WHITE   0xFFFF

void logo_page() {
  tft.fillScreen(BLACK);
  tft.drawRGBBitmap(45, 166, IGGG_128x64, 128, 64);
  tft.setCursor(45, 240);
  tft.setTextSize(2);
  tft.print("CAN BUS READER");
  delay(5000);
   tft.fillScreen(BLACK);
}

void TFT_info_page() {

  static uint8_t aspect = 0;
  uint16_t ID = tft.readID();
  int width = tft.width();
  int height = tft.height();
  
  tft.setRotation(aspect);
  tft.fillScreen(BLACK);
  tft.setTextColor(WHITE);

  tft.setCursor(0, 0);
  tft.setTextSize(2);
  tft.print("Screen Info");

  tft.setTextSize(1);
  tft.setCursor(40, 40);
  tft.print("ID: 0x");
  tft.println(ID, HEX);

  tft.setCursor(40, 60);
  tft.print("Width: ");
  tft.print(width, DEC);

  tft.setCursor(40, 80);
  tft.print("Height: ");
  tft.print(height, DEC);
  delay(5000);
  tft.fillScreen(BLACK);
}

void TFT_can_page(uint32_t can_id, uint8_t dlc, uint8_t data[],int order) {

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

  int seq = 45 + order*10;
  
  tft.setCursor(0, seq);
  tft.fillRect(0, seq, 240,10, BLACK);
  
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

void setup()
{
  Serial.begin(115200);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  static uint8_t aspect = 0;
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(aspect);
  tft.fillScreen(BLACK);
  tft.setTextColor(WHITE);
  logo_page();
  //TFT_info_page();
}

void loop(void)
{
  canMsg.can_id = 0x200;
  canMsg.data[0] = 0x21;
  canMsg.data[1] = 0x22;
  canMsg.data[2] = 0x23;
  canMsg.data[3] = 0x24;
  canMsg.data[4] = 0x25;
  canMsg.data[5] = 0x26;
  canMsg.data[6] = 0x27;
  canMsg.data[7] = 0x28;
  canMsg.can_dlc = 8;
  
  TFT_can_page(canMsg.can_id, canMsg.can_dlc, canMsg.data,0);

  canMsg.can_id = 0x201;
  canMsg.data[0] = 0x10;
  canMsg.data[1] = 0x11;
  canMsg.data[2] = 0x12;
  canMsg.data[3] = 0x13;
  canMsg.data[4] = 0x14;
  canMsg.data[5] = 0x15;
  canMsg.data[6] = 0x16;
  canMsg.data[7] = 0x17;
  canMsg.can_dlc = 6;
  
  TFT_can_page(canMsg.can_id, canMsg.can_dlc, canMsg.data,1);
  delay(1000);
  
  canMsg.can_dlc = 8;
  TFT_can_page(canMsg.can_id, canMsg.can_dlc, canMsg.data,0);
  
  delay(1000);
  canMsg.can_id = 0x211;
  canMsg.data[0] = 0x00;
  canMsg.data[1] = 0xFF;
  canMsg.data[2] = 0xEF;
  canMsg.data[3] = 0x4F;
  canMsg.data[4] = 0xA2;
  canMsg.data[5] = 0x34;
  canMsg.data[6] = 0x00;
  canMsg.data[7] = 0xFF;
  canMsg.can_dlc = 8;
  TFT_can_page(canMsg.can_id, canMsg.can_dlc, canMsg.data,30);
  
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
  }
  delay(5000);
}
