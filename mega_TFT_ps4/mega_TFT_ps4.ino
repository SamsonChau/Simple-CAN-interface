#include "CAN_ID.h"
#include "page.h"
#include <SPI.h>
#include <mcp2515.h>

MCP2515 mcp2515(7);
struct can_frame canMsg;
int  CANID[35];

void setup()
{
  Serial.begin(115200);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
  tft_init();
}

void loop(void)
{
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    for(int i =0; i < sizeof(CANID); i ++){
      if (canMsg.can_id == CANID[i] && CANID[i] != NULL ){
         TFT_can_page(canMsg.can_id, canMsg.can_dlc, canMsg.data, i);
         CANID[i]=canMsg.can_id;
      }
      else if(canMsg.can_id != CANID[i] && CANID[i] == NULL){
          TFT_can_page(canMsg.can_id, canMsg.can_dlc, canMsg.data, i);
          CANID[i]=canMsg.can_id;
      }
      else{
         
      }
    }
    
  }
  delay(100);
}
