#pragma once

#define LIO_LCD_SW_RST		0x01
#define LIO_LCD_SLPOUT		0x11
#define LIO_LCD_INVON		0x21
#define LIO_LCD_INVOFF		0x20

#define LIO_LCD_FRMCTRL1	0xB1	//Frame rate=fosc/((RTNA + 20) x (LINE + FPA + BPA)) ** Normal mode frame rate
#define LIO_LCD_FRMCTRL1_RTNA	5
#define LIO_LCD_FRMCTRL1_FPA	58
#define LIO_LCD_FRMCTRL1_BNA	58

#define LIO_LCD_FRMCTRL2	0xB2	//Frame rate=fosc/((RTNA + 20) x (LINE + FPA + BPA)) ** Idle mode frame rate
#define LIO_LCD_FRMCTRL2_RTNA	5
#define LIO_LCD_FRMCTRL2_FPA	58
#define LIO_LCD_FRMCTRL2_BNA	58

#define LIO_LCD_FRMCTRL3	0xB3	//Frame rate=fosc/((RTNA + 20) x (LINE + FPA + BPA))
#define LIO_LCD_FRMCTRL3_RTNAL	5	//Line inversion mode
#define LIO_LCD_FRMCTRL3_FPAL	58
#define LIO_LCD_FRMCTRL3_BNAL	58
#define LIO_LCD_FRMCTRL3_RTNAF	5	//Frame inversion mode
#define LIO_LCD_FRMCTRL3_FPAF	58
#define LIO_LCD_FRMCTRL3_BNAF	58

#define LIO_LCD_INVCTR		0xB4
#define LIO_LCD_INVCTR_LNINV	0x03

#define LIO_LCD_PWRCTR1		0xC0
#define LIO_LCD_PWRCTR1_AVDD_VRHP	0x62	//AVDD = 4.8V, VRHP = 4.6V
#define LIO_LCD_PWRCTR1_VRHN		0x02
#define LIO_LCD_PWRCTR1_MODE_VRH5	0x04	//Mode 2X

#define LIO_LCD_PWRCTR2		0xC1
#define LIO_LCD_PWRCTR2_VGH_VGLSEL	0xC0 

#define LIO_LCD_PWRCTR3		0xC2
#define LIO_LCD_PWRCTR3_APA		0x0D
#define LIO_LCD_PWRCTR3_DCA		0x00

#define LIO_LCD_PWRCTR4		0xC3
#define LIO_LCD_PWRCTR4_APB		0x8D
#define LIO_LCD_PWRCTR4_DCB		0x6A

#define LIO_LCD_PWRCTR5 	0xC4
#define LIO_LCD_PWRCTR5_APC		0x8D
#define LIO_LCD_PWRCTR5_DCC		0xEE

#define LIO_LCD_VMCTR1		0xC5
#define LIO_LCD_VMCTR1_VCOM		0x0E	//VCOM = -0.775

#define LIO_LCD_GMCTRP		0xE0 		//Gamma correction
#define LIO_LCD_GMCTRP_0		0x10
#define LIO_LCD_GMCTRP_1		0x0E
#define LIO_LCD_GMCTRP_2		0x02
#define LIO_LCD_GMCTRP_3		0x03
#define LIO_LCD_GMCTRP_4		0x0E
#define LIO_LCD_GMCTRP_5		0x07
#define LIO_LCD_GMCTRP_6		0x02
#define LIO_LCD_GMCTRP_7		0x07
#define LIO_LCD_GMCTRP_8		0x0A
#define LIO_LCD_GMCTRP_9		0x12
#define LIO_LCD_GMCTRP_A		0x27
#define LIO_LCD_GMCTRP_B		0x37
#define LIO_LCD_GMCTRP_C		0x00
#define LIO_LCD_GMCTRP_D		0x0D
#define LIO_LCD_GMCTRP_E		0x0E
#define LIO_LCD_GMCTRP_F		0x10

#define LIO_LCD_GMCTRN		0xE1
#define LIO_LCD_GMCTRN_0		0x10
#define LIO_LCD_GMCTRN_1		0x0E
#define LIO_LCD_GMCTRN_2		0x03
#define LIO_LCD_GMCTRN_3		0x03
#define LIO_LCD_GMCTRN_4		0x0F
#define LIO_LCD_GMCTRN_5		0x06
#define LIO_LCD_GMCTRN_6		0x02
#define LIO_LCD_GMCTRN_7		0x08
#define LIO_LCD_GMCTRN_8		0x0A
#define LIO_LCD_GMCTRN_9		0x13
#define LIO_LCD_GMCTRN_A		0x26
#define LIO_LCD_GMCTRN_B		0x36
#define LIO_LCD_GMCTRN_C		0x00
#define LIO_LCD_GMCTRN_D		0x0D
#define LIO_LCD_GMCTRN_E		0x0E
#define LIO_LCD_GMCTRN_F		0x10

#define LIO_LCD_COLMOD		0x3A
#define LIO_LCD_COLMOD_IFPF		0x05

#define LIO_LCD_MADCTL		0x36
#define LIO_LCD_MADCTL_CFG		0x78

#define LIO_LCD_DISPON		0x29

#define LIO_LCD_SET_COLUMN	0x2A
#define LIO_LCD_SET_ROW		0x2B
#define LIO_LCD_WR_MEMORY	0x2C