#include "bsp_gpio.h"
#include "includes.h"

unsigned char gpio[4][4];
unsigned char g_ucKeyValues = KEY_NUL;      // 当前按键值,全局
unsigned char g_ucKeyContinu = 0;           // 连续按键的标志
struct io_port
{
    GPIO_TypeDef *GPIO_x;
    unsigned short GPIO_pin;
};

static struct io_port gpio_output[4] =
{
    { GPIOC, GPIO_Pin_8 },   { GPIOC, GPIO_Pin_9 },
};
static struct io_port gpio_input[4] =
{
    { GPIOC, GPIO_Pin_6 }, { GPIOC, GPIO_Pin_7 },
    { GPIOC, GPIO_Pin_12 },{ GPIOD, GPIO_Pin_2 },
};

// gpio初始化
void gpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    unsigned char i;
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE );    // 打开时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

}


// gpio状态读取与更新

u8 gpioStatusUpdate(void)
{
    unsigned char i = 0;
    unsigned char j = 0;
    unsigned char ucTime = 0;
    static unsigned char isReleaseKey = 1;

    GPIO_ReadInputDataBit(gpio_input[0].GPIO_x, gpio_input[0].GPIO_pin);

    GPIO_ReadInputDataBit(gpio_input[0].GPIO_x, gpio_input[0].GPIO_pin);

    GPIO_ReadInputDataBit(gpio_input[0].GPIO_x, gpio_input[0].GPIO_pin);

    GPIO_ReadInputDataBit(gpio_input[0].GPIO_x, gpio_input[0].GPIO_pin);

    for(i = 0; i < 4; i++)             //i是输出口，依次置低电平
    {
        GPIO_ResetBits(gpio_output[i].GPIO_x, gpio_output[i].GPIO_pin);
        for(j = 0; j < 2; j++)            //j是输入口，当键按下时导通被置为低电平
        {
            if(!GPIO_ReadInputDataBit(gpio_input[j].GPIO_x, gpio_input[j].GPIO_pin))
            {
                delayMs(1);
                while(!GPIO_ReadInputDataBit(gpio_input[j].GPIO_x, gpio_input[j].GPIO_pin))
                {
                    delayMs(10);

                }
                GPIO_SetBits(gpio_output[i].GPIO_x, gpio_output[i].GPIO_pin);
                g_ucKeyValues = (i + 1) * 10 + (j + 1);
                TIM_Cmd(GENERAL_TIM3, ENABLE); // 如果30秒没有按键,则退出到主界面显示当前发卡机的状态
                time_0 = 0;
                return 0;
            }
        }
        GPIO_SetBits(gpio_output[i].GPIO_x, gpio_output[i].GPIO_pin);
    }
    return 1;
}
