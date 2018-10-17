// demo: CAN-BUS Shield, send data
// loovee@seeed.cc

#include <mcp_can.h>
#include <SPI.h>
#include <SoftwareSerialParity.h>

//SoftwareSerialParity MCUserial(3, 5); // RX, TX
//SoftwareSerialParity EPSserial(4, 6); // RX, TX
const int SPI_CS_PIN = 10;   // the cs pin of the version after v1.1 is default to D9   // v0.9b and v1.0 is default D10
MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

unsigned long int lastSend = 500;
uint8_t countSinceLastSend = 0;
unsigned char data[3] = {0, 0, 0};

byte countEPSsinceLastSend = 0;
byte countMCUsinceLastSend = 0;
byte EPSbyteBuf[8];
bool EPSbyteLocation = false;
byte EPSbyteOffset = 0;
byte MCUbyteBuf[8];
bool MCUbyteLocation = false;
byte MCUbyteOffset = 0;

byte tempoffset;

void sendTHECan(byte id, unsigned char* data) {
  //  CAN.sendMsgBuf(id, 0, 3, stmp);
}
void sendESPdata();
void sendMCUdata();
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
 // if (CAN_MSGAVAIL == CAN.checkReceive())  printCanId();         // check if data coming

  while (Serial.available()) {   //   while (MCUserial.available()) {
   MCUSerialIsAvail();
  }
  
//  while (EPSserial.available()) {
//    Serial.println("EPSSerial is avail");
//    tempoffset = EPSbyteOffset;
//    if (tempoffset == 5) tempoffset = 0;
//    if (tempoffset > 0) tempoffset++;
//    EPSbyteBuf[tempoffset] = EPSserial.read();
//    EPSbyteOffset = tempoffset;
//    if (EPSbyteLocation == false) EPSbyteLocation = true;
//    else EPSbyteLocation = false;
//    countEPSsinceLastSend++;
//  }

//  if (millis() > lastSend) {
//    if (countMCUsinceLastSend > 0) sendMCUdata();
//    if (countEPSsinceLastSend > 0) sendESPdata();
//    lastSend = millis() + 166;
//  }
  


} //END LOOP


void sendMCUdata() {
  tempoffset = MCUbyteOffset;
  if (EPSbyteLocation == true) {
    if (tempoffset == 5) tempoffset = 0;
    else if (tempoffset == 0) tempoffset = 4;
    else tempoffset--;
  }
  data[0] = MCUbyteBuf[tempoffset];
  data[1] = MCUbyteBuf[tempoffset + 1];
  data[2] = countMCUsinceLastSend;

  CAN.sendMsgBuf(0x200, 0, 3, data);
  countMCUsinceLastSend = 0;
}

void sendESPdata() {
  tempoffset = EPSbyteOffset;
  if (EPSbyteLocation == true) {
    if (tempoffset == 5) tempoffset = 0;
    else if (tempoffset == 0) tempoffset = 4;
    else tempoffset--;
  }
  data[0] = EPSbyteBuf[tempoffset];
  data[1] = EPSbyteBuf[tempoffset + 1];
  data[2] = countEPSsinceLastSend;
  CAN.sendMsgBuf(0x201, 0, 3, data);
  countEPSsinceLastSend = 0;
}

void printCanId(){
    Serial.print("can is avail");
    Serial.println(CAN.getCanId());
}

void MCUSerialIsAvail(){
   MCUbyteBuf[MCUbyteOffset] = Serial.read();
   MCUbyteOffset++;
   if(MCUbyteOffset == 8){
      CAN.sendMsgBuf(0x200, 0, 8, MCUbyteBuf);
      MCUbyteOffset = 0;
   }
}

//old MCUSerialIsAvail
   //    Serial.println("MCUSerial is avail");
//    tempoffset = MCUbyteOffset;
//    if (tempoffset == 5) tempoffset = 0;
//    else tempoffset++;
//    MCUbyteBuf[tempoffset] = Serial.read();   //     MCUbyteBuf[tempoffset] = MCUserial.read();
//    MCUbyteOffset = tempoffset;
//    if (MCUbyteLocation == false) MCUbyteLocation = true;
//    else MCUbyteLocation = false;
//    countMCUsinceLastSend++;


//    CAN.sendMsgBuf(0x200, 0, 2, stmp);
//    delay(100);                       // send data per 100ms
