#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "HIGHT_core.h"
#include "HIGHT_core.c"

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  BYTE pdwpdwRoundKey[136] = {0,};                                                  // Round keys for encryption or decryption
    BYTE pbUserKey[16] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};     // User secret key
    BYTE pbData[8]    = {0x77,0x66,0x55,0x44,0x33,0x22,0x11,0x00};      
  int i;
  
  HIGHT_Key( pbUserKey, pdwpdwRoundKey );
  HIGHT_Enc( pdwpdwRoundKey, pbData );

  for(i=0;i<8;i++)
    Serial.print(pbData[i],HEX);
  Serial.println("");
  delay(1000);                                                                                                              // delay in between reads for stability
  
  HIGHT_Dec( pdwpdwRoundKey, pbData );
  for(i=0;i<8;i++)
    Serial.print(pbData[i],HEX);
  Serial.println("");
  delay(1000);                                                                                                              // delay in between reads for stability
}
