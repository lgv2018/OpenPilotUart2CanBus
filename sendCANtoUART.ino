#include <mcp_can.h>
#include <SPI.h>

const int SPI_CS_PIN = 10;   // the cs pin of the version after v1.1 is default to D9   // v0.9b and v1.0 is default D10
MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin






void setup()
{
  Serial.begin(9600,SERIAL_8E1);
//  MCUserial.begin(9600, EVEN);
//  EPSserial.begin(9600, EVEN);
  while (CAN_OK != CAN.begin(CAN_500KBPS))              // init can bus : baudrate = 500k
  {
    Serial.println("CAN BUS Shield init fail");
    Serial.println(" Init CAN BUS Shield again");
    delay(100);
  }
  Serial.println("CAN BUS Shield init ok!");
}

void loop()
{
  if (CAN_MSGAVAIL == CAN.checkReceive())  printCanId();
}
