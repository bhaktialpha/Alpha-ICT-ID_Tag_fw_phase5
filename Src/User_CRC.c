/*
 * User_CRC.c
 *
 *  Created on: 20-Sep-2018
 *      Author: Radhika
 */
#include "string.h"
#include "stdint.h"

void Calculate_Byte_CRC16(unsigned int Data_Byte);
void CRC_correct(unsigned char *CRC_StartAdd_receive,unsigned char *CRC_StartAdd_new,unsigned int receive_size);
unsigned short int Calculate_Block_CRC16( uint8_t *Data_Block, unsigned int Length);

#define FEEDBACK                       0xA001         /* standard crc - 16 feedback tapping */

unsigned char Calc_Checksum;
unsigned int CRC_index=0,C1=0,C2=0,CRC_size;
unsigned char CRC_arr[2],x_CRC,y_CRC,CRC_final;
unsigned short int CRC_Initial_Value, Calculated_CRC16;

//unsigned char Value[3];
//unsigned char Value1[3];
//unsigned char d_slave_TX[60],vrfy_crc[60];

struct CRC_arry
{
unsigned char *CRC_receive;
unsigned char *CRC_new;
unsigned char *CRC_StartAdd_receive;
unsigned char *CRC_StartAdd_new;
unsigned int receive_size;
}CRC_C1;

//unsigned char  c_slave[60],y_slave_1[60],d_slave_TX[60],slave_resp[60],n,crc_chk[60],vrfy_crc[60];
//unsigned short int CRC_Value;
union
{
	 short int CRC_Value_int;
	 char CRC_Value_char[2];
}CRC_Value;


/**************************************************

* Function name : unsigned char Verify_CRC16(char *Data_Block)
* \Returns : 16 bit CRC for given Data_Block.
* \arg1 : Data Block for which 16 bit CRC is to be calculated.
* \Created by : Vrushali Kulkarni
* \Date Created : 21/04/2009
* \Description : Calculates 16 bit CRC for a given Data Block.
* \Notes : calls Calculate_Byte_CRC16(char Data_Byte).
**************************************************/
unsigned char ByteNibble(char c)
{
	char d;
	d = c;
	if (d >= (char) 65) d -= 7;
	d -= 48;
	return(d);
}

unsigned short Convert_To_Int(unsigned char *s)
{
	unsigned short i;

	i = (4096 * ByteNibble(*s)) + (256 * ByteNibble(*(s + 1))) + (16 * ByteNibble(*(s + 2))) + ByteNibble(*(s + 3));
	return i;
}

char AscNibble(char h)
{
	char x;
	x = h + (char) 48;
	if (h >= (char) 10)
		x += (char) 7;
	return((char) x);
}


void Convert_To_Hex(unsigned char c, unsigned char *s)
{
	s[0] = AscNibble(c / 16);
	s[1] = AscNibble(c % 16);
	s[2] = 0;
}

void Calculate_Byte_CRC16(unsigned int Data_Byte)
{
	unsigned char Index;

	CRC_Initial_Value = (CRC_Initial_Value) ^ (Data_Byte);

	for (Index = 8; Index; Index--)
	{
		if ( (CRC_Initial_Value) & 0x0001)
		{
			(CRC_Initial_Value) = ( (CRC_Initial_Value) >> 1) ^ FEEDBACK;
		}
		else
		{
			(CRC_Initial_Value) = ( (CRC_Initial_Value) >> 1);
		}
	}
}
/**************************************************

* Function name : unsigned short int Calculate_Block_CRC16(unsigned char *Data_Block, unsigned int Length)
* \Returns : 16 bit CRC for given Data_Block.
* \arg1 : Data Block for which 16 bit CRC is to be calculated.
* \arg2 : Length of Data Block.
* \Created by : Vrushali Kulkarni
* \Date Created : 21/04/2009
* \Description : Calculates 16 bit CRC for a given Data Block.
* \Notes : calls Calculate_Byte_CRC16(char Data_Byte).
**************************************************/

unsigned short int Calculate_Block_CRC16( uint8_t *Data_Block, unsigned int Length)
{
	unsigned int Count;

	CRC_Initial_Value = 0xFFFF;            // initialise CRC for block calculation

	for (Count = 0; Count < Length; Count++ )
	{
		Calculate_Byte_CRC16(*(Data_Block + Count));   // update CRC with current data
	}
	return(CRC_Initial_Value);
}


/*void CRC_correct(unsigned char *CRC_StartAdd_receive,unsigned char *CRC_StartAdd_new,unsigned int receive_size)
{

unsigned int m;
	CRC_C1.CRC_receive = CRC_StartAdd_receive;
	CRC_C1.CRC_new = CRC_StartAdd_new;
	CRC_index=0;
	for(CRC_size=0;CRC_size < receive_size;CRC_size++)
	{
	for(m=0;m<2;m++)
	{
		CRC_arr[m]= *CRC_C1.CRC_receive;
		CRC_C1.CRC_receive++;
	}
		if(CRC_arr[0] >0x40)
		{
			C1=CRC_arr[0]-0x57;
		}
		else
		{
		C1=CRC_arr[0]-0x30;
		}
			x_CRC= C1<<4;

			if(CRC_arr[1] >0x40)
					{
						C2= CRC_arr[1]- 0x57;
					}
			else
				 {
					 C2=CRC_arr[1]-0x30;
			   }
			CRC_final = x_CRC | 	C2;
			CRC_C1.CRC_new[CRC_index] = CRC_final;
		  CRC_index++;
	}

}*/

