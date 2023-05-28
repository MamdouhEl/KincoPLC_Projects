#include <modbus.h>
#include <modbusDevice.h>
#include <modbusRegBank.h>
#include <modbusSlave.h>
//#include <SoftwareSerial.h>
modbusDevice regBank;
modbusSlave slave;

#define RS485TxEnablePin 22
#define RS485Baud 19200
#define RS485Format SERIAL_8N1

//SoftwareSerial mySerial(2, 3);// RX, TX

int incomingByte = 0; // for incoming serial data
word buffer2[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
int i;
void setup() {
  Serial1.begin(19200); // opens serial port, sets data rate to 9600 bps
  Serial2.begin(9600);
  Serial.begin(9600);
  regBank.setId(1);
  
  slave.setBaud(&Serial1,RS485Baud,RS485Format,RS485TxEnablePin);  
  regBank.add(40001);
  regBank.add(40002);
  regBank.add(40003);
  regBank.add(40004);
  regBank.add(40005);
  regBank.add(40006);
  regBank.add(40007);
  regBank.add(40008);
  regBank.add(40009);
  regBank.add(40010);
  regBank.add(40011);
  regBank.add(40012);
  i = 0;
  slave._device = &regBank;

}

void loop() {
  // send data only when you receive data:
  
    // read the incoming byte:
    //for(int i = 0; i < 12; i++){
      if (Serial2.available() > 0) {
        incomingByte = Serial2.read();
        Serial.println(incomingByte, DEC);
        buffer2[i] = incomingByte;
        i++;
        if(buffer2[0] != 1){
          i = 0;
        }
    }
    //}
    regBank.set(40001,(word)buffer2[0]); //from 0 - 1023
    regBank.set(40002,(word)buffer2[1]); //from 0 - 1023
    regBank.set(40003,(word)buffer2[2]); //from 0 - 1023
    regBank.set(40004,(word)buffer2[3]); //from 0 - 1023
    regBank.set(40005,(word)buffer2[4]); //from 0 - 1023
    regBank.set(40006,(word)buffer2[5]); //from 0 - 1023
    regBank.set(40007,(word)buffer2[6]); //from 0 - 1023
    regBank.set(40008,(word)buffer2[7]); //from 0 - 1023
    regBank.set(40009,(word)buffer2[8]); //from 0 - 1023
    regBank.set(40010,(word)buffer2[9]); //from 0 - 1023
    regBank.set(40011,(word)buffer2[10]); //from 0 - 1023
    regBank.set(40012,(word)buffer2[11]); //from 0 - 1023
    slave.run();
    if(i == 12){
      i = 0;
      
    }
  
}
