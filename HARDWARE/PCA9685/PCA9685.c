/**
  ******************************************************************************
  * @file    	PCA9685.c
  * @author  	MC_Wang
  * @version 	V1.0
  * @date    	2021��3��27��
  * @brief   	STM32ͨ��ģ��IICЭ����PCA9685ͨѶ
 @verbatim
 ===============================================================================
                        ##### How to use this driver #####
 ===============================================================================
    [..]
      (#)ʹ��setPWMFreq(u8 freq)������ʼ��PCA9685;
			(++)u8 freq:���ö����PWMƵ�ʣ�����ʹ��u8����(0~255)
			��PCA9685�����������ԼΪ1.6KHz��Ƶ�ʣ����Ҫ���ø���Ƶ�ʣ���Ҫ���β����ͺ�PCA9685_write(unsigned char reg,unsigned char data)
			����Ȥ�����Լ����ԣ����������u8���ͣ����50Hz����freq = 50;����
	  (#)ʹ��PCA9685_write(unsigned char reg,unsigned char data)��ѡ�е�PCA9685��XX�Ĵ���дXX����
			(++)unsigned char reg��PCA9685�Ĵ�����ַ
			(++)unsigned char data:��ѡ�е�PCA9685��ĳ�Ĵ���д�������
	  (#)ʹ��u8 PCA9685_read(unsigned char reg)��ѡ�е�PCA9685��XX�Ĵ�����ȡXX����
			(++)unsigned char reg��PCA9685�Ĵ�����ַ
			(++)����ֵΪPCA9685ĳ�Ĵ���������
	  (#)����PCA9685ĳͨ����ռ�ձȣ���ʹ��setPWM(u8 num, u16 on, u16 off)
	  (#)������ĽǶ�ת����LEDx_OFF��ֵ����ʹ��calculate_PWM(u8 angle)
 @endverbatim
  *
  ******************************************************************************
  * @attention
  * <h2><center>&copy; COPYRIGHT 2021 JXUST@WangMingcong</center></h2>
	******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "PCA9685.h"
#include "IIC.h"
#include "delay.h"
#include "math.h"
#include "usart.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/** @defgroup PCA9685_Private_Functions
  * @{
  */
/** @defgroup PCA9685 Initialization and Configuration
 *  @brief   Initialization and Configuration
 *
 @verbatim
 ===============================================================================
                 ##### PCA9685��ʼ��������PCA9685��PWMƵ�� #####
 ===============================================================================

 @endverbatim
  * @{
  */



/**
  * @brief  ��ѡ�е�PCA9685��XX�Ĵ���дXX����
  * @note   ��ѡ��PCA9685��STM32��ͨ��IIC��PCA9685дPCA9685�豸��ַ,��PCA9685_adrr��0x80
						��ͨ���βν�����д�뵽PCA9685�Ĵ�����
  * @param  unsigned char reg
  *            @arg �Ĵ�����ַ
  * @param  unsigned char data
  *            @arg ��Ĵ���д�������
  * @date   2021��3��27��
  * @retval None
  */


void PCA9685_Init()
{
    IIC_Init();
    PCA9685_write(PCA9685_MODE1,0x0);
    setPWMFreq(50);
}
void PCA9685_write(unsigned char reg,unsigned char data)
{
    IIC_Start();
    IIC_Send_Byte(PCA9685_adrr);
    IIC_Wait_Ack();
    IIC_Send_Byte(reg);
    IIC_Wait_Ack();
    IIC_Send_Byte(data);
    IIC_Wait_Ack();
    IIC_Stop();
}
/**
  * @brief  ��ѡ�е�PCA9685��XX�Ĵ�����ȡXX����
  * @note   ��ѡ��PCA9685��STM32��ͨ��IIC��PCA9685дPCA9685�豸��ַ,��PCA9685_adrr��0x80
						��ͨ���βζ�ȡPCA9685�Ĵ����е�����
  * @param  unsigned char reg
  *            @arg PCA9685�Ĵ�����ַ
  * @date   2021��3��27��
  * @retval  ��ȡ���Ĵ����е�����
  */
u8 PCA9685_read(unsigned char reg)
{
    u8 res;
    IIC_Start();
    IIC_Send_Byte(PCA9685_adrr);
    IIC_Wait_Ack();
    IIC_Send_Byte(reg);
    IIC_Wait_Ack();
    IIC_Start();
    IIC_Send_Byte(PCA9685_adrr|0X01);
    IIC_Wait_Ack();
    res=IIC_Read_Byte(0);
    IIC_Stop();
    return res;
}

/**
  * @brief  ��ʼ��PCA9685������PWM���Ƶ��
  * @note   1.����PCA9685��MODE1�Ĵ�����ֵ:oldmode == 0x33 = 0011 0011(����λ��ʹ���ڲ�25MHzʱ�ӡ��ڲ���ַ��д����Զ����ӡ�����sleep����Ӧ0x70ͨ��IIC��ַ)
						2.����λPCA9685�ҽ���sleepģʽ
						3.����PCA9685��PRE_SCALE�Ĵ���������PCA9685�����PWMƵ��
						4.�˳�sleepģʽ
  * @param  u8 freq
  *            @arg  ����PCA9685�����PWMƵ�ʣ�0~255��Hz��Ҳ����PPT�е�update_rate
  * @date   2021��3��27��
  * @retval None
  */
void setPWMFreq(u8 freq)
{
    u8 prescale,oldmode,newmode;
    double prescaleval;
    prescaleval = 25000000.0/(4096*freq*0.915);
    prescale = (u8)floor(prescaleval+0.5)-1;//floor()������ȡ������

    oldmode = PCA9685_read(PCA9685_MODE1);
//����ʹ�ã�
    printf("oldmode = %d\r\n",PCA9685_read(PCA9685_MODE1));//oldmode == 0 = 0x00 = 0000 0000
    newmode = (oldmode&0x7F) | 0x10; // ����λ�ҽ���sleepģʽ  newmode == 16 = 0x10 = 0001 0000
    printf("newmode = %d\r\n",newmode);
    PCA9685_write(PCA9685_MODE1, newmode); // go to sleep
    PCA9685_write(PCA9685_PRESCALE, prescale); // set the prescaler
    PCA9685_write(PCA9685_MODE1, oldmode);
    PCA9685_write(PCA9685_MODE1, oldmode | 0xa1); //1010 0001   д�긴λ��D7λ�Զ�����

    printf("oldmode = %d\r\n",PCA9685_read(PCA9685_MODE1));//  oldmode == 33 = 0x21 = 0010 0001
}


/**
  * @brief  ���ø���ͨ����ON��OFF�Ĵ������Ӷ��ﵽ�ı�PCA9685���PWM��ռ�ձ�
  * @note   ��ΪPCA9685��PWM��12λ�ģ����Դ���Ĳ���Ϊu16��16λ�ſ���װ��12λ�����ݣ�
						��16λ�����У�����λû�ã�on��off��ֵ��0~4096 ����
  * @param  u8 num
  *            @arg	ͨ���� (0~15)
  * @param  u16 on
  *            @arg �Ƶ�LEDX_ONʱ����Ϊ�ߵ�ƽ
  * @param  u16 off
  *            @arg ������LEDX_OFFʱ����Ϊ�͵�ƽ
  * @date  	2021��3��27��
  * @retval None
  */
void setPWM(u8 num, u16 on, u16 off)
{
    PCA9685_write(LED0_ON_L+4*num,on);
    PCA9685_write(LED0_ON_H+4*num,on>>8);
    PCA9685_write(LED0_OFF_L+4*num,off);
    PCA9685_write(LED0_OFF_H+4*num,off>>8);
}



/**
  * @brief  ������ĽǶȼ����12λLEDX_OFF��ֵ
  * @author MC_Wang
  * @note   ͨ�����㹫ʽ��������ĽǶȼ����12λLEDX_OFF��ֵ
���㹫ʽ��PWM = 4096*(0.5 + (2.5-0.5)*(u8 angle)/180)/20

  * @param  u8 angle
  *            @arg ����Ƕ�
  * @date  	2021��3��27��
  * @retval 12λLEDX_OFF��ֵ
  */
u16 calculate_PWM(u8 angle)
{
    return (int)(204.8*(0.5+angle*1.0/90));
}

/************************ (C) COPYRIGHT JXUST@WangMingcong *****END OF FILE****/

