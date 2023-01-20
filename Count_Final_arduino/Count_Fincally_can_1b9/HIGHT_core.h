#ifndef HIGHT_CORE_H_
#define HIGHT_CORE_H_

#include <avr/pgmspace.h> 
#include <stdio.h>

#define BYTE    unsigned char       
#define WORD    unsigned short int  
#define DWORD   unsigned long       

void    HIGHT_Key(BYTE    *pbUserKey, BYTE    *pdwRoundKey);
void    HIGHT_Enc(BYTE    *pdwRoundKey,BYTE    *pbData);
void    HIGHT_Dec(BYTE    *pdwRoundKey,BYTE    *pbData);

#endif /* HIGHT_CORE_H_ */
