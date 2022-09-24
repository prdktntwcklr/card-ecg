#include "ADuC706x.h"

#define INT_OSC         (32768UL)
#define PLL_CLK         (10240000UL)
#define SLCLK           INT_OSC
#define ECLK            PLL_CLK

#define TICK_RATE_HZ    (100UL)

void IRQHandler(void) __attribute__((interrupt));

int main(void)
{
    /* perform power settings */
    POWKEY1 = 0x1;
    POWCON0 = CLK_10240_KHZ | CORE_POWER_ON | PERIPH_POWER_ON | PLL_POWER_ON;
    POWKEY2 = 0xF4;	

    /* set up timer0 */
    T0LD  = ECLK/TICK_RATE_HZ;
    T0CON = T0_10MHZ | T0_DIV_1 | T0_ENABLED | T0_DOWN | T0_PERIODIC;

    /* TODO: enable interrupt - not yet working */
    // IRQEN = TIMER0_BIT;	

    GP1DAT |= (1 << 29); /* Configure P1.5 as an output */
    GP1DAT |= (1 << 21); /* turn P1.5 on */
    
    while(1)
    {
        static int count = 0;

        if(T0VAL == 0)
        {
            if(++count == 10)
            {
                GP1DAT ^= (1 << 21); /* toggle P1.5 */
                count = 0;
            }

            T0LD  = ECLK/TICK_RATE_HZ;
        }
    }

    return 0;
}

// void IRQHandler(void)
// {
//     static int count = 0;

//     uint32_t irq = IRQSTA;

//     if(irq & TIMER0_BIT)
//     {
//         if(++count == 10)
//         {
//             GP1DAT ^= (1 << 21); /* toggle P1.5 */
//             count = 0;
//         }

//         T0CLRI = 0;
//     }
// }
