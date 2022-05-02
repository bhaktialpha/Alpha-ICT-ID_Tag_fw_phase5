/*
 * User_CRC.h
 *
 *  Created on: 20-Sep-2018
 *      Author: Ajinkya
 */

#ifndef USER_CRC_H_
#define USER_CRC_H_



#endif /* USER_CRC_H_ */
extern void Calculate_CRC_A(uint8_t *pbtData, size_t szLen, uint8_t *pbtCrc);
extern void Calculate_Byte_CRC16(unsigned int Data_Byte);
extern unsigned char Verify_CRC16(unsigned char *Data_Block,unsigned int RESPONSE_LENGTH);
extern void CRC_correct(unsigned char *CRC_StartAdd_receive,unsigned char *CRC_StartAdd_new,unsigned int receive_size);
extern unsigned short int Calculate_Block_CRC16( uint8_t*Data_Block, unsigned int Length);
extern unsigned char Calc_Checksum;
extern unsigned int CRC_index,C1,C2,CRC_size;
extern unsigned char CRC_arr[2],x_CRC,y_CRC,CRC_final;
extern unsigned short int CRC_Initial_Value, Calculated_CRC16;
extern unsigned char F_CRC_Verified;

extern unsigned char Value[3];
extern unsigned char Value1[3];
extern unsigned char d_slave_TX[60],vrfy_crc[60];

extern unsigned char  c_slave[60],y_slave_1[60],d_slave_TX[60],slave_resp[60],n,crc_chk[60],vrfy_crc[60];

extern union
{
	unsigned short int CRC_Value_int;
	unsigned char CRC_Value_char[2];
}CRC_Value;


