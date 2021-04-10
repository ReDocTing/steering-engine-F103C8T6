#include "sys.h"
#include "delay.h"
#include "config.h"
#include "usart.h"
#include "PCA9685.h"
#include "IIC.h"

int main()
{
    uart_init(115200);
    delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    PCA9685_Init();
    while(1) {
        setPWM(0x0,0,calculate_PWM(0));
        setPWM(0x1,0,calculate_PWM(0));
        setPWM(0x2,0,calculate_PWM(0));
        setPWM(0x3,0,calculate_PWM(0));
        setPWM(0x4,0,calculate_PWM(0));
        setPWM(0x5,0,calculate_PWM(0));
        setPWM(0x6,0,calculate_PWM(0));
        setPWM(0x7,0,calculate_PWM(0));
        setPWM(0x8,0,calculate_PWM(0));
        setPWM(0x9,0,calculate_PWM(0));
        setPWM(0xA,0,calculate_PWM(0));
        setPWM(0xB,0,calculate_PWM(0));
        setPWM(0xC,0,calculate_PWM(0));
        setPWM(0xD,0,calculate_PWM(0));
        setPWM(0xE,0,calculate_PWM(0));
        setPWM(0xF,0,calculate_PWM(0));
        delay_ms(10);
        setPWM(0x0,0,calculate_PWM(180));
        setPWM(0x1,0,calculate_PWM(180));
        setPWM(0x2,0,calculate_PWM(180));
        setPWM(0x3,0,calculate_PWM(180));
        setPWM(0x4,0,calculate_PWM(180));
        setPWM(0x5,0,calculate_PWM(180));
        setPWM(0x6,0,calculate_PWM(180));
        setPWM(0x7,0,calculate_PWM(180));
        setPWM(0x8,0,calculate_PWM(180));
        setPWM(0x9,0,calculate_PWM(180));
        setPWM(0xA,0,calculate_PWM(180));
        setPWM(0xB,0,calculate_PWM(180));
        setPWM(0xC,0,calculate_PWM(180));
        setPWM(0xD,0,calculate_PWM(180));
        setPWM(0xE,0,calculate_PWM(180));
        setPWM(0xF,0,calculate_PWM(180));
        delay_ms(10);
    }
}
