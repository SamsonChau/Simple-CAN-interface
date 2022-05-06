#define Motor_1_RevID 0x201
#define Motor_2_RevID 0x202
#define Motor_3_RevID 0x203
#define Motor_4_RevID 0x204
#define Motor_5_RevID 0x205
#define Motor_6_RevID 0x206
#define Motor_7_RevID 0x207
#define Motor_8_RevID 0x208
#define stm_id 0x200
#define cmd_id 0x15
#define odom_id 0x100
#define reset_id 0x000

//////////////TEST CAN Msgs/////////////////////
/*
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

TFT_can_page(canMsg.can_id, canMsg.can_dlc, canMsg.data, 0);

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

TFT_can_page(canMsg.can_id, canMsg.can_dlc, canMsg.data, 1);
delay(1000);

canMsg.can_dlc = 8;
TFT_can_page(canMsg.can_id, canMsg.can_dlc, canMsg.data, 0);
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
TFT_can_page(canMsg.can_id, canMsg.can_dlc, canMsg.data, 30);
*/
