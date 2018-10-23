#include <mcp_can.h>
#include <SPI.h>

const int SPI_CS_PIN = 10;   // the cs pin of the version after v1.1 is default to D9   // v0.9b and v1.0 is default D10
uint32_t OPcanId = 0x199;

uint8_t len = 8;
uint8_t buf[8];


MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin






void setup()
{
  Serial.begin(9600,SERIAL_8E1);
//  MCUserial.begin(9600, EVEN);
//  EPSserial.begin(9600, EVEN);
  while (CAN_OK != CAN.begin(CAN_500KBPS))              // init can bus : baudrate = 500k
  {
    // Serial.println("CAN BUS Shield init fail");
    // Serial.println(" Init CAN BUS Shield again");
    delay(100);
  }
  // Serial.println("CAN BUS Shield init ok!");
  // SET MASK and FILTER!!!
  //init_Mask(unsigned char num, unsigned char ext, unsigned char ulData);
  //init_Filt(unsigned char num, unsigned char ext, unsigned char ulData);
  // init_Filt(unsigned char num, unsigned char ext, unsigned char ulData);
  //0x199 = B110011001  = DEC 409
  //0000 0000 0000 0000 0000 0000 0000 0000
  //0000 0000 0000 0000 0000 0000 0000 0000
  //                          001 1001 1001
  //   0 0110 0110 01 << 18 over
  //0000 0110 0110 0100 0000 0000 0000 0000
  //uint32_t maskandfilter = 0b00000110011001000000000000000000;
  OPcanId << 18;
  init_Mask(0,0,OPcanId);
  init_Filt(0,0,OPcanId);


}

void loop()
{
  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    if (CAN.getCanId() == OPcanId){
      CAN.readMsgBuf(len, buf);
      uint8_t tempbyte = buf[0];
      tempbyte >> 5;
      if(tempbyte == 1 || tempbyte == 0){
        for(uint8_t i =0;i>4;i++){
          Serial.write(buf[i]);
        }

      }

    }
    // CAN.readMsgBuf(unsigned char len, unsigned char buf);
     // printCanId();
  }



}
