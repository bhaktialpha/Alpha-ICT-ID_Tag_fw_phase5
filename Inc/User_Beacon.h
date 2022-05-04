/*
 * User_Beacon.h
 *
 *  Created on: Jan 29, 2020
 *      Author: bhakti.deshpande
 */

#ifndef USER_BEACON_H_
#define USER_BEACON_H_

void Send_BLE_Commands(void);
void Check_Response( uint8_t* Rx_strng, unsigned int size);
void Send_BLE_Commands(void);
void Command_Response(uint8_t* Tx_string,char* Rx_string);
void Check_Get_Response(uint8_t* Rx_strng, unsigned int size);
void Check_Device_Connection(void);
void EPD_Display_Black1(void);

uint8_t BLE_Command_1[] = 	"D\r\n";
uint8_t BLE_Command_2[] = 	"&,3481F4971FE7\r\n";
//uint8_t BLE_Command_3[] = 	"&C\r\n";
uint8_t BLE_Command_4[] = 	"IB,FF,";
uint8_t BLE_Command_5[] =  "SN,INTERACT_TAG\r\n";
uint8_t BLE_Command_6[] = 	"IA,FF,";
///uint8_t BLE_Command_7[] = 	"&C\r\n";



uint8_t BM71_Command_0[] = "R,1\r\n";
uint8_t BM71_Command_11[] =  "$";
uint8_t BM71_Command_1[] =  "$$$";
uint8_t BM71_Command_2[] =  "SC,0\r\n";
uint8_t BM71_Command_3[] =  "D\r\n";
uint8_t BM71_Command_4[] =  "S-,ALPHA_ID_TAG\r\n";
uint8_t BM71_Command_5[] =  "SO,1\r\n";
//uint8_t BM71_Command_6[] =  "SP,123456\r\n";//"SF,1\r\n";//"SP,0000\r\n";
uint8_t BM71_Command_6[] =  "Y,1\r\n";
uint8_t BM71_Command_7[] =  "SC,2\r\n";//"SA,0\r\n";
uint8_t BM71_Command_8[] =  "SC,1\r\n";
uint8_t BM71_Command_9[] =  "STB,0640\r\n";
uint8_t BM71_Command_10[] =  "NB,Z\r\n";
uint8_t BM71_Command_14[] = "A\r\n"; //12start adv
uint8_t BM71_Command_77[] =  "SF,2\r\n";

/*
uint8_t*  BLE_Command[25]=
{
	"$",//0
	"$$$", //1
	"SC,0\r\n", //2//0
    "STA,00A0,0003,00A0\r\n",//3,0003,0601\r\n",   320-500ms //640-3.3mA//20-3.2mA //3e80-10s//5sec- 1f40//500ms-0320 //1sec-0640 //10240ms-4000                   //1
	"R,1\r\n",//4
	"SO,1\r\n", //5
	"SO,0\r\n", //6
	"IB,Z\r\n",  //7            //clear beacon
	"IB,03,AAFE\r\n",//8
	//"IB,16,AAFE10D802676F6F2E676C2F357347303868\r\n",   //6
	"IB,16,AAFE10D8027777772e616c7068612d6963742e696e2f\r\n",//9
	//"NB,FF,4C000215AD11CF40063F11E5BE3E0002A5D5C51B000C000DC5\r\n",
	//"IB,FF,CD000000\r\n",
	"IB,01,03\r\n",//10
	"IB,01,16\r\n",  //11   set url
	"A\r\n", //12start adv
	"R,1\r\n",//13
	"PZ\r\n",//14-4
	"PS,0000fff000001000800000805f9b34fb\r\n",//15-9
	"PC,0000fff400001000800000805f9b34fb,1A,9B\r\n",//16 -15
	"SS,C0\r\n",//17-7
	"K,1\r\n",
	"O,0\r\n"
//	"PS,010203040506070809000A0B0C0D0E0F\r\n",//15-37
//	"PC,11223344556677889900AABBCCDDEEFF,1A,05\r\n"//16-43

};//,command_array1[25];
*/

uint8_t BLE_Response_0[] = "CMD> ";
uint8_t BLE_Response_1[] = "AOK\r\nCMD> ";
uint8_t BLE_Response_2[] = "%DISCONNECT%> ";
uint8_t BLE_Response_3[] = "SECURED";
uint8_t BLE_Response_4[] = "Rebooting";
uint8_t BLE_Response_5[] = "%CONNECT,";
uint8_t BLE_Response_6[] = "BTA";
//uint8_t BLE_Response_3[] = "Rebooting";

/*char*  BLE_Response[25]=
{
	"CMD> ",   //0
    "AOK\r\nCMD> ", //1
	"Err\r\nCMD> ", //2
	"Rebooting", //3
	"END\r\n",//4
	"%DISCONNECT%",
	"%CONNECT,",
	//"Rebooting\r\n%REBOOT%"

},command_array[25];*/

#endif /* USER_BEACON_H_ */
