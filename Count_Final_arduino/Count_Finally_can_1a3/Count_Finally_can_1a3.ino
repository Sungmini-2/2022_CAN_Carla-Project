// demo: CAN-BUS Shield, receive data with check mode
// send data coming to fast, such as less than 10ms, you can use this way
// loovee, 2014-6-13

#include <SPI.h>

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "HIGHT_core.h"
#include "HIGHT_core.c"


#define CAN_2515
// #define CAN_2518FD

// Set SPI CS Pin according to your hardware

#if defined(SEEED_WIO_TERMINAL) && defined(CAN_2518FD)
// For Wio Terminal w/ MCP2518FD RPi Hat：
// Channel 0 SPI_CS Pin: BCM 8
// Channel 1 SPI_CS Pin: BCM 7
// Interupt Pin: BCM25
const int SPI_CS_PIN  = BCM8;
const int CAN_INT_PIN = BCM25;
#else

// For Arduino MCP2515 Hat:
// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 10;
const int CAN_INT_PIN = 2;
#endif


#ifdef CAN_2518FD
#include "mcp2518fd_can.h"
mcp2518fd CAN(SPI_CS_PIN); // Set CS pin
#endif

#ifdef CAN_2515
#include "mcp2515_can.h"
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
#endif

const int LED        = 8;
boolean ledON        = 1;
unsigned char perstep[8] = {00, 00, 00, 00, 00, 00, 00, 00};
void setup() {
    SERIAL_PORT_MONITOR.begin(115200); 
    pinMode(LED, OUTPUT);
    while (CAN_OK != CAN.begin(CAN_500KBPS)) {             // init can bus : baudrate = 500k
        SERIAL_PORT_MONITOR.println("CAN init fail, retry...");
        delay(100);
    }
    SERIAL_PORT_MONITOR.println("CAN init ok!");
    //CAN.sendMsgBuf(0x44, 0, 8, perstep); // perID to Raspberrypi
    //SERIAL_PORT_MONITOR.println("Send one"); //send check
    pinMode(8, OUTPUT); // setting pin number of LED
    digitalWrite(8, HIGH); //LED on
    delay(1000);
    digitalWrite(8, LOW); //LED off
    delay(1000);
 
}
int Cnt=0;
int result_1;
int result;
int parity;
int check;
int sum;
int point_1;
int point_2;

int keynum = 0;
int cnt = 0;

void loop() {
    unsigned char len = 0;
     BYTE pbData[8] ;
    BYTE pdwpdwRoundKey[136] = {0,};
    BYTE key [16];
    BYTE key1 [16]={0x88, 0xE3, 0x4F, 0x8F, 0x08, 0x17, 0x79, 0xF1, 0xE9, 0xF3, 0x94, 0x37, 0x0A, 0xD4, 0x05, 0x89};
    BYTE key2 [16]={0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    BYTE key3 [16]={0xA8, 0x73, 0x4F, 0xDF, 0x08, 0x57, 0xC9, 0xF1, 0xE9, 0xF3, 0x94, 0x37, 0x0A, 0xD4, 0x05, 0x89};
    BYTE key4 [16]={0xB8, 0x53, 0x1F, 0xFF, 0x18, 0x67, 0xB9, 0xF1, 0xE9, 0xF3, 0x94, 0x37, 0x0A, 0xD4, 0x05, 0x89}; 
    BYTE key5 [16]={0x28, 0x13, 0x4F, 0x8F, 0x28, 0x07, 0xA9, 0xF1, 0xE9, 0xF3, 0x94, 0x37, 0x0A, 0xD4, 0x05, 0x89};
    

    if (CAN_MSGAVAIL == CAN.checkReceive()) {
      CAN.readMsgBuf(&len, pbData);       // read data,  len: data length, buf: data buf

      int (receive_id)=CAN.getCanId();
     
            
      result_1=486;

      if(486 <= receive_id <506){
        for(int i=1; i<22; i++){
          if(result_1 > 485){
            result_1=receive_id -i;
          }
        }
      }
        
        
        
   
        if(result_1 == 0x1e5) { //ID success!
          
          Cnt=++Cnt;
          SERIAL_PORT_MONITOR.println(Cnt);//number of receive data
          //SERIAL_PORT_MONITOR.println(result_1);

         if(Cnt == 1111){
            keynum+=1;
            SERIAL_PORT_MONITOR.println("keychange!!!!!!!");
            Cnt=0;
            if(keynum == 5){
              keynum = 0;
              }
            
            }
          
          //unsigned long canId = CAN.getCanId();
          digitalWrite(8, HIGH);
          
          point_1=0;
          point_2=0;
          sum=0;

          
          switch(keynum){

          case  0:
          SERIAL_PORT_MONITOR.println("key1");
              
               for (int k = 0; k < 16; k++){
                      key[k] = key1[k];
               }
             break;
               //for (int k = 0; k < 16; k++){
                      //SERIAL_PORT_MONITOR.print(key[k],HEX);
                     // SERIAL_PORT_MONITOR.print("\t");
                   // }
             
              
          case 1:
          SERIAL_PORT_MONITOR.println("key2");
              
              for (int k = 0; k < 16; k++){
                      key[k] = key2[k];
               }
              
               break;
               //for (int k = 0; k < 16; k++){
                     // SERIAL_PORT_MONITOR.print(key[k],HEX);
                      //SERIAL_PORT_MONITOR.print("\t");
                   // }
              
          case 2:
          SERIAL_PORT_MONITOR.println("key3");
              
              for (int k = 0; k < 16; k++){
                      key[k] = key3[k];
               } 
              
              break;
              // for (int k = 0; k < 16; k++){
                     // SERIAL_PORT_MONITOR.print(key[k],HEX);
                     // SERIAL_PORT_MONITOR.print("\t");
                   // }
                   
              
          case 3:
          SERIAL_PORT_MONITOR.println("key4");
              
              for (int k = 0; k < 16; k++){
                      key[k] = key4[k];
               }
              
              break;
               //for (int k = 0; k < 16; k++){
                      //SERIAL_PORT_MONITOR.print(key[k],HEX);
                     //SERIAL_PORT_MONITOR.print("\t");
               //}
            
              
          case 4:
          SERIAL_PORT_MONITOR.println("key5");
              
              for (int k = 0; k < 16; k++){
                      key[k] = key5[k];
               }
              
               break;
               //for (int k = 0; k < 16; k++){
                      //SERIAL_PORT_MONITOR.print(key[k],HEX);
                      //SERIAL_PORT_MONITOR.print("\t");
               
                    //}
                   
          }

          HIGHT_Key(key , pdwpdwRoundKey ); //roundkey
          HIGHT_Dec( pdwpdwRoundKey, pbData ); //decrypt
          

          
        //  for (int i = 0; i < len; i++) { // print the data
           // result=0;
           // result= pbData[i];
            
           // for (int j = 7; j >= 0; j--){ //bit position strange
             // check=0;
             // check=bitRead(result,j);
             // sum+=check;
             // if(i==7){
              //  if(j==1){
               //   point_1=sum;
                  //point_2=check;
               // }
             // }
            //}/  
     //   }
        
        //SERIAL_PORT_MONITOR.println(point_1); // the number of one
        //SERIAL_PORT_MONITOR.println(check); // at bit 63 number       
       // parity=point_1%2;
        //SERIAL_PORT_MONITOR.println(parity); // parity
                 
                  
                  // if(parity==check){
                   // SERIAL_PORT_MONITOR.println("\n-----------------------------");
                    //SERIAL_PORT_MONITOR.print("ID: 00000");
                    //SERIAL_PORT_MONITOR.print(result_1,HEX );
                   // SERIAL_PORT_MONITOR.print("  DLC 8      ");
                  //  parity=0;
                    for (int k = 0; k < len; k++){
                      SERIAL_PORT_MONITOR.print(pbData[k],HEX);
                      SERIAL_PORT_MONITOR.print("\t");
                    }
                      // //SERIAL_PORT_MONITOR.println("..");
                 // }
                  
                //else {
                  //  SERIAL_PORT_MONITOR.println("Error parity!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                  //  keynum+=1;
                   // if(keynum==5){
                    //  keynum=0;
                    //}
              
        
       // SERIAL_PORT_MONITOR.print("Receive Data");
        //SERIAL_PORT_MONITOR.println();    
        //}

       
    }

}

}
//END FILE
