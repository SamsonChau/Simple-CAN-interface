#include <esp_now.h>
#include <WiFi.h>

#define serial_debug true
// REPLACE WITH THE MAC Address of your receiver
uint8_t receiverAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
//uint8_t receiverAddress[] = {0x78, 0xE3, 0x6D, 0x10, 0x57, 0x60};

bool sent;

uint8_t id;
uint8_t Rx_buffer[8];

typedef struct struct_message {
  uint8_t msg_id;
  uint8_t msg_data[8];
} esp_msg;

esp_msg robot_read;
esp_msg send_robot;

// Callback when data is sent
void sent_callback(const uint8_t *macaddr, esp_now_send_status_t status) {
  status = ESP_NOW_SEND_SUCCESS;
  if (status == 0) {
    sent = true;
  }
  else {
    sent = false;
  }
  if (serial_debug) {
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(sent ? "Message send Sucess" : "Messagesent Fail");
  }
}

// Callback when data is received
void receive_callback(const uint8_t * macaddr, const uint8_t *msg_data, int len) {
  memcpy(&robot_read, msg_data, sizeof(robot_read));
  id = robot_read.msg_id;
  for (int i =0; i<8 ;i++){
    Rx_buffer[i] = robot_read.msg_data[i];
  }
  if (serial_debug) {
    Serial.print("Msgs received: ");
  }
}
void setup() {
  if (serial_debug) {
    Serial.begin(115200);
    Serial.println(WiFi.macAddress());
  }
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_MODE_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    if (serial_debug) {
      Serial.println("Error initializing ESP-NOW");
    }
    return;
  }
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(sent_callback);
  
  // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  
  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    if (serial_debug) {
      Serial.println("Failed to add peer");
    }
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(receive_callback);
}

void loop() {
  send_robot.msg_id = 0x01;
  uint8_t Tx_buffer[] = {0x78, 0xE3, 0x6D, 0x10, 0x57, 0x60, 0x00, send_robot.msg_id};
  memcpy(send_robot.msg_data, Tx_buffer, 8);
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(receiverAddress, (uint8_t *) &send_robot, sizeof(send_robot));
   
  if (result == ESP_OK) {
    if (serial_debug) {
      Serial.println("Sent with success");
    }
  }
  else {
    if (serial_debug) {
      Serial.println("Error sending the data");
    }
  }
  delay(1000);
}


/*
  void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);
  }

  void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("My MAC address is:");
  Serial.print(WiFi.macAddress());

  delay(1000);
  }
*/
