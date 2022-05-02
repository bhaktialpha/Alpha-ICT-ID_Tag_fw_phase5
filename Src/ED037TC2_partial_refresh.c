///*
// * ED037TC2_partial_refresh.c
// *
// *  Created on: Apr 7, 2022
// *      Author: bhakti.deshpande
// */
//
//
//#define __ED037TC2_C__
///*************************************************************************************
// * Copyright (C) 2019 E Ink Holdings Inc. (Ryan Liu, Eric CH Huang) All Rights Reserved *
// *************************************************************************************/
//
//#include "ED037TC2.h"
//#include "delay.h"
//#include "LUT.h"
//#include "User_UART.h"
//#include "Global.c"
////typedef uint16_t eink_coordinate;
//FLG flags;
//extern unsigned int Counter_Response_Time;
//
////==============================================================================
//void check_busy_high(void) /* If BUSYN=0 then waiting */
//{
//	while(!(BUSYN))
//	{
//		if(flags.F_Response_timeout_done == 1)  /* Check for 7 second timeout */
//		{
//			break;        						/* Exit while loop after 7 second timeout */
//		}
//	}
//	flags.Start_Response_time_flag = 0;
//	flags.F_Response_timeout_done = 0;
//	Counter_Response_Time = 0; 					/* Reset counter */
//}
//
//void check_busy_low(void) /* If BUSYN=1 then waiting */
//{
//	while(BUSYN)
//	{
//		if(flags.F_Response_timeout_done == 1)
//		{
//			break;       /* Exit while loop after 7 second timeout */
//		}
//	}
//	flags.Start_Response_time_flag = 0;
//	flags.F_Response_timeout_done = 0;
//	Counter_Response_Time = 0;
//}
//
////*****************************************************************************
///**
// * @fn void EPD_Init(void)
// * @brief This function initialize 9 bit SPI driver.
// * @author Bhakti Deshpande
// */
////***************************************************************************************************************************
//
//void spi_9b_init(void)
//{
//	SCL_L;
//	SDA_H;
//	CSB_H;
//	//BS_H;
//	HAL_Delay(10);  // 5+(1+1)*6+3 = 20 us
//}
////*****************************************************************************
///**
// * @fn void EPD_Init(void)
// * @brief This function initialize the E paper display.
// * @author Bhakti Deshpande
// */
////***************************************************************************************************************************
//
//void EPD_Init(void)
//{
//	spi_9b_init();
//	RSTN_L; // Reset
//	for(int b=0;b<1;b++);		//HAL_Delay(1);
//	RSTN_H;
//	for(int b=0;b<1;b++);		//HAL_Delay(1);
//
//	spi_9b_send_9b(PON);
//	flags.Start_Response_time_flag = 1;    /* Start 7 second timeout */
//	check_busy_high();
//
//	spi_9b_send_9b(PWR_EPD);
//	spi_9b_send(1,0x03);
//	spi_9b_send(1,0x07);
//	spi_9b_send(1,0x0D);
//	spi_9b_send(1,0x0D);
//	spi_9b_send(1,0x00);
//
//	spi_9b_send_9b(BTST);
//	spi_9b_send(1,0x57);
//	spi_9b_send(1,0x63);
//	spi_9b_send(1,0x31);
//
//	spi_9b_send_9b(TCON);
//	spi_9b_send(1,0x04);
//
//	spi_9b_send_9b(PSR);
//	spi_9b_send(1,0x7F);
//	spi_9b_send_9b(PFS);
//	spi_9b_send(1,0x00);
//
//	spi_9b_send_9b(OSC);
//	spi_9b_send(1,0x3C);
//
//	spi_9b_send_9b(TRES);
//	spi_9b_send(1,0x01);
//	spi_9b_send(1,0x18);
//	spi_9b_send(1,0x01);
//	spi_9b_send(1,0xE0);
//
//	spi_9b_send_9b(CDI);
//	spi_9b_send(1,0x37);
//
//	spi_9b_send_9b(SET_STG);
//	spi_9b_send(1,0x0F);
//
//	spi_9b_send_9b(TSGS);
//	spi_9b_send(1,0x00);
//	spi_9b_send(1,0x00);
//	spi_9b_send(1,0x00);
//	spi_9b_send(1,0x00);
//	spi_9b_send_9b(CMD);
//	spi_9b_send(1,0x60);
//	spi_9b_send(1,0xA5);
//	spi_9b_send_9b(CMD);
//	spi_9b_send(1,0x89);
//	spi_9b_send(1,0xA5);
//	spi_9b_send_9b(CMD);
//	spi_9b_send(1,0xA1);
//	spi_9b_send(1,0x00);
//	spi_9b_send_9b(CMD);
//	spi_9b_send(1,0x73);
//	spi_9b_send(1,0x05);
//	spi_9b_send_9b(CMD);
//	spi_9b_send(1,0x7E);
//	spi_9b_send(1,0x31);
//	spi_9b_send_9b(CMD);
//	spi_9b_send(1,0xB8);
//	spi_9b_send(1,0x80);
//	spi_9b_send_9b(CMD);
//	spi_9b_send(1,0x92);
//	spi_9b_send(1,0x08);
//	spi_9b_send_9b(CMD);
//	spi_9b_send(1,0x87);
//	spi_9b_send(1,0x11);
//	spi_9b_send_9b(CMD);
//	spi_9b_send(1,0x88);
//	spi_9b_send(1,0x02);
//	spi_9b_send_9b(CMD);
//	spi_9b_send(1,0xA8);
//	spi_9b_send(1,0x3A);
//
//	spi_9b_send_9b(PON);
//	flags.Start_Response_time_flag = 1;    /* Start 7 second timeout */
//	check_busy_high();
//	spi_9b_send_9b(AMV);
//	spi_9b_send(1,0x11);
//	flags.Start_Response_time_flag = 1;    /* Start 7 second timeout */
//	check_busy_high();
//
//	spi_9b_send_9b(VV);
//	spi_9b_send_9b(VDCS);
//	spi_9b_send(1,0x17);
//
//	spi_9b_send_9b(POF);
//	//flags.Start_Response_time_flag = 1;    /* Start 7 second timeout */
//	//check_busy_low();
//	byte_counter = MAX_IMG_SIZE;
//}
//
//
////load waveform
//
//void EPD_Load_LUTC(unsigned int LUT, unsigned char const *LUT_Value)
//{
//	int i;
//	spi_9b_send_9b(LUT);
//	for(i=0;i<60;i++)
//	{
//		spi_9b_send(DCX_DATA,*LUT_Value);
//		LUT_Value++;
//	}
//}
//
//void EPD_Load_LUT(unsigned int LUT, unsigned char const *LUT_Value)
//{
//	int i;
//	spi_9b_send_9b(LUT);
//	for(i=0;i<42;i++)
//	{
//		spi_9b_send(DCX_DATA,*LUT_Value);
//		LUT_Value++;
//	}
//}
//void Upload_Temperature_LUT(void)
//{
//
//	EPD_Load_LUTC(LUT_VCOM,lut_vcom);
//	EPD_Load_LUT(LUT_WW,lut_ww);
//	EPD_Load_LUTC(LUT_R,lut_r);
//	EPD_Load_LUT(LUT_W,lut_w);
//	EPD_Load_LUT(LUT_B,lut_b);
//}
////*****************************************************************************
///**
// * @fn void EPD_Display_White(void)
// * @brief This function sends 16800 0xFF bytes to display and makes E-Ink display white.
// * @author Bhakti Deshpande
// */
////***************************************************************************************************************************
//
//void EPD_Display_White(void)
//{
//	unsigned int i;
//	spi_9b_send_9b(PON);
//	flags.Start_Response_time_flag = 1;    /* Start 7 second timeout */
//	check_busy_high();
//
//	spi_9b_send_9b(DTM1);
//	for(i=0;i<byte_counter;i++)
//	{
//		spi_9b_send(1,0xFF);
//	}
//
//	spi_9b_send_9b(DTM2);
//	for(i=0;i<byte_counter;i++)
//	{
//		spi_9b_send(1,0xFF);
//	}
//	Upload_Temperature_LUT();
//	spi_9b_send_9b(DRF);
//	//check_busy_high();
//	for(int b=0;b<1;b++);
//	spi_9b_send_9b(POF);
//	flags.Start_Response_time_flag = 1;    /* Start 7 second timeout */
//	check_busy_low();
//}
//
////*****************************************************************************
///**
// * @f void EPD_Display_Black1(void)
// * @brief This function sends 16800 0x00 bytes to display and makes E-Ink display black.
// * @author Bhakti Deshpande
// */
////***************************************************************************************************************************
//
//void EPD_Display_Black1(void)
//{
//	unsigned int i;
//	spi_9b_send_9b(PON);
//	flags.Start_Response_time_flag = 1;    /* Start 7 second timeout */
//	check_busy_high();
//
//	spi_9b_send_9b(DTM1);
//	for(i=0;i<byte_counter;i++)
//	{
//		spi_9b_send(1,0x00);
//	}
//
//	spi_9b_send_9b(DTM2);
//	for(i=0;i<byte_counter;i++)
//	{
//		spi_9b_send(1,0xFF);
//	}
//	Upload_Temperature_LUT();
//	spi_9b_send_9b(DRF);
//	//check_busy_high();
//	for(int b=0;b<100;b++);
//	spi_9b_send_9b(POF);
//	flags.Start_Response_time_flag = 1;    /* Start 7 second timeout */
//	check_busy_low();
//}
//
//
////==============================================================================
////3-wire SPI transmission Protocol
////==============================================================================
////*****************************************************************************
///**
// * @fn void EPD_Init(void)
// * @brief This function send passed command to display.
// * @parameter command address
// * @author Bhakti Deshpande
// */
////***************************************************************************************************************************
//
//
//void spi_9b_send_9b(unsigned int dat)
//{
//	if((dat&DATA_MASK)==DATA_MASK)
//		spi_9b_send(DCX_DATA,(unsigned char)dat);
//	else
//		spi_9b_send(DCX_CMD,(unsigned char)dat);
//}
//
////==============================================================================
////3-wire SPI transmission Protocol
////==============================================================================
////*****************************************************************************
///**
// * @fn void EPD_Init(void)
// * @brief This function sends the 9 bit data to display.
// * @parameter command address/data
// * @parameter data value
// * @author Bhakti Deshpande
// */
////***************************************************************************************************************************
//
//void spi_9b_send(unsigned int dcx,unsigned char dat)
//{
//	unsigned char i;
//
//	CSB_L;
//
//	for(int b=0;b<1;b++);		 // HAL_Delay(1);
//	if(dcx) SDA_H; 			 // 1 for DCX_DATA
//	else SDA_L; 				 // 0 for DCX_CMD
//	SCL_H;
//	for(int b=0;b<1;b++);	     // HAL_Delay(1);
//	SCL_L;
//	for(int b=0;b<1;b++);	     // HAL_Delay(1);
//	for(i=0;i<8;i++)
//	{
//		if(dat & 0x80)
//		{SDA_H;}
//		else
//		{SDA_L;}
//		for(int b=0;b<1;b++);	// HAL_Delay(1);
//		SCL_H;
//		for(int b=0;b<1;b++);	// HAL_Delay(1);
//		SCL_L;
//		dat=dat<<1;
//	}
//	SDA_L;
//	for(int b=0;b<1;b++);		// HAL_Delay(1);
//
//	CSB_H;
//
//	for(int b=0;b<1;b++);		// HAL_Delay(1);
//}
//
//void EPD_Display_KW(const unsigned char *img_kw, unsigned int size)
//{
//
//	unsigned int i;
//	spi_9b_send_9b(PON);
//	flags.Start_Response_time_flag = 1;    /* Start 7 second timeout */
//	check_busy_high();
//
//	spi_9b_send_9b(DTM2);
//
//	//#if(CHECK_DISPLAY_FLAG == 1)
//	//	  img_kw=img_kw+0;
//	//#else
//	//	  img_kw=img_kw+3;
//	//#endif
//
//	for(i=0;i<byte_counter;i++)
//	{
//		spi_9b_send(1,*img_kw);
//		img_kw++;
//	}
////	spi_9b_send_9b(DTM2);
////	for(i=0;i<byte_counter;i++)
////	{
////		spi_9b_send(1,0xFF);
////	}
//	Upload_Temperature_LUT();
//
//	spi_9b_send_9b(DRF);
//	//check_busy_high();
//	for(int b=0;b<1;b++);
//	spi_9b_send_9b(POF);
//	flags.Start_Response_time_flag = 1;    /* Start 7 second timeout */
//	check_busy_low();
//
//}
//
//
///**
// * int Eink_Partial_Display_Update(eink_coordinate x, eink_coordinate y, eink_coordinate w, eink_coordinate l,const unsigned char *img_kw )
//{
// * \brief update and refresh specified part of display.
// *
// * \param x Starting X coordinate.
// * \param y Starting Y coordinate.
// * \param width Width of image.
// * \param height Height of image.
// */
//
//int Eink_Partial_Display_Update(eink_coordinate x, eink_coordinate y, eink_coordinate w, eink_coordinate l,const unsigned char *img_kw )
//{
//
//	int x0=0,x1=0,y0=0,y1=0,w0=0,w1=0,l0=0,l1=0;
//
//	x0 = (x >> 8);
//	x1 =  (x & 0xff);
//	y0 = (y >> 8);
//	y1 =  (y & 0xff);
//	w0 = (w >> 8);
//	w1 =  (w & 0xff);
//	l0 = (l >> 8);
//	l1 =  (l & 0xff);
//	unsigned int i;
//	spi_9b_send_9b(PON);
//	flags.Start_Response_time_flag = 1;    /* Start 7 second timeout */
//	check_busy_high();
//
//	// spi_9b_send_9b(DTM1);
//	spi_9b_send_9b(PDTM2);
//
//	spi_9b_send(1,x0);  //X	update window x_start
//	spi_9b_send(1,x1);
//	spi_9b_send(1,y0);  //Y	update window y_start
//	spi_9b_send(1,y1);
//	spi_9b_send(1,w0);  //W	update window width = 256 (0x0100)
//	spi_9b_send(1,w1);
//	spi_9b_send(1,l0);  //L	update window length = 256 (0x0100)
//	spi_9b_send(1,l1);
//
//	byte_counter = (w*l)/8; //256*256/8;
//	for(i=0;i<byte_counter;i++)
//	{
//		spi_9b_send(1,*img_kw);
//		img_kw++;
//	}
//	Upload_Temperature_LUT();
//	CSB_L;
//	spi_9b_send_9b(PON);
//	flags.Start_busyline_timer=1;
//	check_busy_high();
//	CSB_H;
//	CSB_L;
//	spi_9b_send_9b(PDRF);
//	spi_9b_send(1,x0);  //X	update window x_start
//	spi_9b_send(1,x1);
//	spi_9b_send(1,y0);  //Y	update window y_start
//	spi_9b_send(1,y1);
//	spi_9b_send(1,w0);  //W	update window width
//	spi_9b_send(1,w1);
//	spi_9b_send(1,l0);  //L	update window length
//	spi_9b_send(1,l1);
//	CSB_H;
//	flags.Start_busyline_timer=1;
//	flags.Busy_pin_error_flag = 0;
//	check_busy_high();
//	if(flags.Busy_pin_error_flag == 1)
//	{
//		return ERROR;
//	}
//	else
//	{
//		return SUCCESS;
//	}
//
//	CSB_L;
//	spi_9b_send_9b(POF);
//	CSB_H;
//
//
//}
///**
// * int Eink_Partial_Display_Refresh(eink_coordinate x, eink_coordinate y, eink_coordinate w, eink_coordinate l)
// *
// * \brief refresh specified part of display.
// *
// * \param x Starting X coordinate.
// * \param y Starting Y coordinate.
// * \param width Width of image.
// * \param height Height of image.
// */
//
//int Eink_Partial_Display_Refresh(eink_coordinate x, eink_coordinate y, eink_coordinate w, eink_coordinate l)
//{
//	Upload_Temperature_LUT();
//
//	int x0=0,x1=0,y0=0,y1=0,w0=0,w1=0,l0=0,l1=0;
//
//	x0 = (x >> 8);
//	x1 =  (x & 0xff);
//	y0 = (y >> 8);
//	y1 =  (y & 0xff);
//	w0 = (w >> 8);
//	w1 =  (w & 0xff);
//	l0 = (l >> 8);
//	l1 =  (l & 0xff);
//
//	CSB_L;
//	spi_9b_send_9b(PON);
//	flags.Start_busyline_timer=1;
//	check_busy_high();
//	CSB_H;
//
//	CSB_L;
//	spi_9b_send_9b(PDRF);
//	//spi_9b_send(1,0x80);
//	spi_9b_send(1,x0);  //X	update window x_start
//	spi_9b_send(1,x1);
//	spi_9b_send(1,y0);  //Y	update window y_start
//	spi_9b_send(1,y1);
//	spi_9b_send(1,w0);  //W	update window width = 256 (0x0100)
//	spi_9b_send(1,w1);
//	spi_9b_send(1,l0);  //L	update window length = 256 (0x0100)
//	spi_9b_send(1,l1);
//	CSB_H;
//	flags.Start_busyline_timer=1;
//	flags.Busy_pin_error_flag = 0;
//	check_busy_high();
//	if(flags.Busy_pin_error_flag == 1)
//	{
//		return ERROR;
//	}
//	else
//	{
//		return SUCCESS;
//	}
//
//	CSB_L;
//	spi_9b_send_9b(POF);
//	CSB_H;
//
//}
//
//
//
//void EPD_Partial_white_Display_KW(const unsigned char *img_kw, unsigned int size)
//{
//
//
//
//	unsigned int i;
//	spi_9b_send_9b(PON);
//	flags.Start_Response_time_flag = 1; /* Start 7 second timeout */
//	check_busy_high();
//
//	// spi_9b_send_9b(DTM1);
//	spi_9b_send_9b(PDTM1);
//
//	spi_9b_send_9b(0x00);
//	spi_9b_send(1,0x00);
//	spi_9b_send(1,0x28);
//	spi_9b_send(1,0x00);
//	spi_9b_send(1,0xF0);
//	spi_9b_send(1,0x00);
//	spi_9b_send(1,0x38);
//	spi_9b_send(1,0x00);
//	spi_9b_send(1,0x20);
//
//	for(i=0;i<224;i++)
//	{
//		spi_9b_send(1,0xFF);
//		img_kw++;
//	}
//	//spi_9b_send_9b(DTM2);
//	spi_9b_send_9b(PDTM2);
//	spi_9b_send(1,0x00);
//	spi_9b_send(1,0x28);
//	spi_9b_send(1,0x00);
//	spi_9b_send(1,0xF0);
//	spi_9b_send(1,0x00);
//	spi_9b_send(1,0x38);
//	spi_9b_send(1,0x00);
//	spi_9b_send(1,0x20);
//	for(i=0;i<224;i++)
//	{
//		spi_9b_send(1,0xFF);
//	}
//	// Upload_Temperature_LUT();
//
//
//	// spi_9b_send_9b(DRF);
//	spi_9b_send_9b(PDRF);
//
//	spi_9b_send(1,0x00);
//	spi_9b_send(1,0x28);
//	spi_9b_send(1,0x00);
//	spi_9b_send(1,0xF0);
//	spi_9b_send(1,0x00);
//	spi_9b_send(1,0x38);
//	spi_9b_send(1,0x00);
//	spi_9b_send(1,0x20);
//	//check_busy_high();
//	for(int b=0;b<1;b++);
//	spi_9b_send_9b(POF);
//	flags.Start_Response_time_flag = 1; /* Start 7 second timeout */
//	check_busy_low();
//
//
//
//}
