/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PCF8574_H
#define __PCF8574_H
/* Includes ------------------------------------------------------------------*/
#include "sys.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
//PCA9685�豸��ַ
#define PCA9685_adrr 0xAA
//��ؼĴ���
#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4
//MODE1�Ĵ���
#define PCA9685_MODE1 0x0
//PRE_SCALE�Ĵ���
#define PCA9685_PRESCALE 0xFE
//0ͨ����ON��OFF�Ĵ���
#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD
/* Exported functions --------------------------------------------------------*/

void PCA9685_Init(void);
void PCA9685_write(unsigned char reg,unsigned char data);
u8 PCA9685_read(unsigned char reg);
void setPWMFreq(u8 freq);
void setPWM(u8 num, u16 on, u16 off);
u16 calculate_PWM(u8 angle);

#endif

/************************ (C) COPYRIGHT JXUST@WangMingcong *****END OF FILE****/







