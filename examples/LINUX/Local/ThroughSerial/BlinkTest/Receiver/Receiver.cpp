
// For printf used below
#include <stdio.h>
// PJON library
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

 // Include only ThroughSerial
#include <PJONThroughSerial.h>

void receiver_function(uint8_t *payload, uint16_t length, const PJON_Packet_Info &packet_info) {
  /* Make use of the payload before sending something, the buffer where payload points to is
     overwritten when a new message is dispatched */
  printf("BLINK... \n");
  fflush(stdout);
};


int main() {
  printf("PJON instantiation... \n");
  PJONThroughSerial bus(44);
  bus.set_receiver(receiver_function);
  uint32_t baud_rate = 9600;
  printf("Opening serial... \n");
  int s = serialOpen("/dev/ttyUSB0", baud_rate);
  if(int(s) < 0) printf("Serial open fail!");
  printf("Setting serial... \n");
  bus.strategy.set_serial(s);
  bus.strategy.set_baud_rate(baud_rate);

  printf("Opening bus... \n");
  bus.begin();
  printf("Attempting to roll bus... \n");
  bus.update();
  printf("Attempting to receive from bus... \n");
  bus.receive();
  printf("Success! \n");

  while(true) {
    bus.update();
    bus.receive();
  }

  return 0;
};
