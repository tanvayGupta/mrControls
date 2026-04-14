#include <SPI.h>
#include <mcp_can.h>

#define CAN_CS 10

MCP_CAN CAN(CAN_CS);

// Motor config
#define MOTOR_ID 0x01
#define CAN_PACKET_SET_POS_SPD 6

// Store last commanded angle
float target_angle = 0.0;

void setup() {
  Serial.begin(115200);

  // Initialize CAN (1 Mbps, 8 MHz crystal)
  while (CAN.begin(MCP_ANY, CAN_1000KBPS, MCP_8MHZ) != CAN_OK) {
    Serial.println("CAN init fail");
    delay(500);
  }

  CAN.setMode(MCP_NORMAL);

  Serial.println("CAN Ready");
}


// -------- POSITION + VELOCITY MODE --------
void setPosVel(float pos_deg, int16_t speed_erpm, int16_t acc_erpm_s2) {

  uint32_t can_id = ((uint32_t)CAN_PACKET_SET_POS_SPD << 8) | MOTOR_ID;

  // Convert values
  int32_t pos = (int32_t)(pos_deg * 10000.0);
  int16_t speed = speed_erpm / 10;
  int16_t acc   = acc_erpm_s2 / 10;

  uint8_t data[8];

  // Position (4 bytes)
  data[0] = (pos >> 24) & 0xFF;
  data[1] = (pos >> 16) & 0xFF;
  data[2] = (pos >> 8) & 0xFF;
  data[3] = pos & 0xFF;

  // Speed (2 bytes)
  data[4] = (speed >> 8) & 0xFF;
  data[5] = speed & 0xFF;

  // Acceleration (2 bytes)
  data[6] = (acc >> 8) & 0xFF;
  data[7] = acc & 0xFF;

  byte result = CAN.sendMsgBuf(can_id, 1, 8, data);

  if (result == CAN_OK) {
    Serial.println("CAN Sent OK");
  } else {
    Serial.println("CAN Send FAIL");
  }
}

void loop() {

  // -------- READ SERIAL FROM ROS2 --------
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');

    Serial.print("Received: ");
    Serial.println(cmd);

    if (cmd.startsWith("P")) {
      target_angle = cmd.substring(2).toFloat();
    }
  }

  // -------- CONTINUOUS CONTROL (VERY IMPORTANT) --------
  //It is important to note, that AK60-39 will operate at a maximum of 72-73 rpm, which is 72*14 = 1008 erpm max according to the data sheet when put under 18Nm of torque, therefore I have used 1000erpm.
  //Acceleration is just set to a random-ass high value, because ideally I would like my motor to go to the position immediately
  setPosVel(target_angle, 1000, 30000);  // stronger + smoother

  delay(20);  // ~50 Hz loop
}
