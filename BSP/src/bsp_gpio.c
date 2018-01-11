#include "bsp_gpio.h"
#include "includes.h"

/**************�������.c�ļ�*****************************/
unsigned char gpio[4][4];
unsigned char g_ucKeyValues = KEY_NUL;      // ��ǰ����ֵ,ȫ��
unsigned char g_ucKeyContinu = 0;           // ���������ı�־
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
    { GPIOC, GPIO_Pin_12 },   { GPIOD, GPIO_Pin_2 },
};

void gpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    unsigned char i;
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE );    // ��ʱ��

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




u8 gpioStatusUpdate(void)
{
    unsigned char i = 0;
    unsigned char j = 0;
    unsigned char ucTime = 0;
    static unsigned char isReleaseKey = 1;
    if (g_ucKeyValues != KEY_NUL)
    {
        return 0;
    }
    for(i = 0; i < 4; i++)             //i������ڣ������õ͵�ƽ
    {
        GPIO_ResetBits(gpio_output[i].GPIO_x, gpio_output[i].GPIO_pin);
        for(j = 0; j < 2; j++)            //j������ڣ���������ʱ��ͨ����Ϊ�͵�ƽ
        {
            if(!GPIO_ReadInputDataBit(gpio_input[j].GPIO_x, gpio_input[j].GPIO_pin))
            {
                delayMs(1);
                while(!GPIO_ReadInputDataBit(gpio_input[j].GPIO_x, gpio_input[j].GPIO_pin))
                {
                    delayMs(10);
                    if (g_ucKeyContinu == 1)        // �����ǳ�ʱ����
                    {
                        if (ucTime++ == 20)         // �������������,20ms�˳�,���Ͻ�����ʱ10ms,��210ms����һ�ΰ���
                        {
                            ucTime = 0;
                            g_ucKeyContinu = 0;     // ����ģʽ����,�ɿ�֮��ֱ���˳�
                            break;
                        }
                    }
                    else
                    {
                        if (ucTime++ == 200)
                        {
                            // ����,����һֱ�����͵����,��Ϊ�Ǵ������,��Ϊû�а�������
                            ucTime = 0;
                            break;
                        }
                    }
                }
                GPIO_SetBits(gpio_output[i].GPIO_x, gpio_output[i].GPIO_pin);
                g_ucKeyValues = (i + 1) * 10 + (j + 1);
                TIM_Cmd(GENERAL_TIM3, ENABLE); // ���30��û�а���,���˳�����������ʾ��ǰ��������״̬
                time_0 = 0;
                return 0;
            }
        }
        GPIO_SetBits(gpio_output[i].GPIO_x, gpio_output[i].GPIO_pin);
    }
    return 1;
}
