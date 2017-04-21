

#include <stdint.h>

#define GPIO_C_DIR				0x400DB400
#define GPIO_C_DATA				0x400DB000

#define HWREG(x)                                                              \
	(*((volatile uint32_t *)(x)))

int main(void)
{
    volatile uint32_t ui32LoopCount;
    
    // Set direction output and initial value for PC2 and PC0
    // Greed LED on PC2
    // Red LED on PC0
    HWREG(GPIO_C_DIR) |= 0x05;
    HWREG(GPIO_C_DATA + (0x05 << 2)) = 0;
    
    // Loop forever.
    while(1)
    {
        // Turn on both LED's.
        HWREG(GPIO_C_DATA + (0x05 << 2)) ^= 0x05;
        
        // Delay for a bit
        for(ui32LoopCount = 200000; ui32LoopCount > 0; ui32LoopCount--)
        {
        }
    }
}
