// Engine Node CAN Test
// 3/13/2024

// Simulating PT readings
#define FAKEDATA1     ((float) 0.00)
#define FAKEDATA2     ((float) 27.00)
#define FAKEDATA3     ((float) 42.00)
#define FAKEDATA4     ((float) 16383.00)

// 20 transmissions total
#define CANIDONE       ((uint8_t)  1)
#define CANIDTWO       ((uint8_t)  2)
#define CANIDTHREE     ((uint8_t)  3)
#define CANIDFOUR      ((uint8_t)  4)
#define CANIDFIVE      ((uint8_t)  5)
#define CANIDSIX       ((uint8_t)  6)
#define CANIDSEVEN     ((uint8_t)  7)
#define CANIDEIGHT     ((uint8_t)  8)
#define CANIDNINE      ((uint8_t)  9)
#define CANIDTEN       ((uint8_t) 10)
#define CANIDELEVEN    ((uint8_t) 11)
#define CANIDTWELVE    ((uint8_t) 12)
#define CANIDTHIRTEEN  ((uint8_t) 13)
#define CANIDFOURTEEN  ((uint8_t) 14)
#define CANIDFIFTEEN   ((uint8_t) 15)
#define CANIDSIXTEEN   ((uint8_t) 16)
#define CANIDSEVENTEEN ((uint8_t) 17)
#define CANIDEIGHTEEN  ((uint8_t) 18)
#define CANIDNINETEEN  ((uint8_t) 19)
#define CANIDTWENTY    ((uint8_t) 20)

#include <FlexCan.h>

void setup() {
  Can0.begin(500000);
  Can0.setTxBufferSize(64);
}

void loop() {
  // This would actually be part of a check - like if the size of the vector within the CAN driver class != 0
  // Then pull that frame in, and look at the id.
  int verifier = CANDriver::readMessage();
  /*
 *   /// CAN 2.0 Engine Node ///
 *   1.)  Receives [3] from Pi Box
 *   2.)  Sends [4] to Pi Box
 *  
 *   3.)  Receives [6] from Propulsion Node
 *   4.)  Sends [7] to Pi Box
 * 
 *   6.)  Receives [8] from Pi Box
 *   5.)  Sends [9] to Propulsion Node
 */

  if(verifier == CANIDTHREE)
  {
    CANDriver::sendSensorData(CANIDFOUR,FAKEDATA1,FAKEDATA2,FAKEDATA3,FAKEDATA4);
    verifier = 0;
  }
  if(verifier == CANIDSIX)
  {
    CANDriver::sendSensorData(CANIDSEVEN,FAKEDATA1,FAKEDATA2,FAKEDATA3,FAKEDATA4);
    verifier = 0;
  }
  if(verifier == CANIDEIGHT)
  {
    CANDriver::sendSensorData(CANIDNINE,FAKEDATA1,FAKEDATA2,FAKEDATA3,FAKEDATA4);
    verifier = 0;
  }


 /* 
  *   /// CAN FD Engine Node /// 
  *   6.)  Receives [13] from Pi Box
  *   7.)  Sends [14] to Pi Box
  * 
  *   8.)  Receives [16] from Propulsion Node
  *   9.)  Sends [17] to Pi Box
  * 
  *   10.) Receives [18] from Pi Box
  *   11.) Sends [19] to Propulsion Node
  */
  /*
  if(verifier == CANIDTHIRTEEN)
  {
    //msg.bF.id.SID   = CANIDFOURTEEN;
    verifier = 0;
  }
  if(verifier == CANIDSIXTEEN)
  {
    //msg.bF.id.SID   = CANIDSEVENTEEN;
    verifier = 0;
  }
  if(verifier == CANIDEIGHTEEN)
  {
    //msg.bF.id.SID   = CANIDNINETEEN;
  }
  */
}