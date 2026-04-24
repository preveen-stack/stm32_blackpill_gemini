#include <stdint.h>
#include <stdio.h>

/* Register base addresses */
#define RCC_BASE        0x40023800
#define GPIOA_BASE      0x40020000
#define GPIOC_BASE      0x40020800
#define USART1_BASE     0x40011000
#define FLASH_R_BASE    0x40023C00

/* Register offsets */
#define RCC_CR          (*(volatile uint32_t *)(RCC_BASE + 0x00))
#define RCC_PLLCFGR     (*(volatile uint32_t *)(RCC_BASE + 0x04))
#define RCC_CFGR        (*(volatile uint32_t *)(RCC_BASE + 0x08))
#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x44))

#define GPIOA_MODER     (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_AFRH      (*(volatile uint32_t *)(GPIOA_BASE + 0x24))

#define GPIOC_MODER     (*(volatile uint32_t *)(GPIOC_BASE + 0x00))
#define GPIOC_ODR       (*(volatile uint32_t *)(GPIOC_BASE + 0x14))

#define USART1_SR       (*(volatile uint32_t *)(USART1_BASE + 0x00))
#define USART1_DR       (*(volatile uint32_t *)(USART1_BASE + 0x04))
#define USART1_BRR      (*(volatile uint32_t *)(USART1_BASE + 0x08))
#define USART1_CR1      (*(volatile uint32_t *)(USART1_BASE + 0x0C))

#define FLASH_ACR       (*(volatile uint32_t *)(FLASH_R_BASE + 0x00))

/* Bit definitions */
#define RCC_CR_HSION    (1 << 0)
#define RCC_CR_HSIRDY   (1 << 1)
#define RCC_CR_HSEON    (1 << 16)
#define RCC_CR_HSERDY   (1 << 17)
#define RCC_CR_PLLON    (1 << 24)
#define RCC_CR_PLLRDY   (1 << 25)

#define RCC_PLLCFGR_PLLSRC_HSE (1 << 22)
#define RCC_PLLCFGR_PLLSRC_HSI (0 << 22)

#define RCC_CFGR_SW_PLL (2 << 0)
#define RCC_CFGR_SWS_PLL (2 << 2)

#define USART1EN       (1 << 4)
#define GPIOAEN        (1 << 0)
#define GPIOCEN        (1 << 2)
#define PIN13          (1 << 13)

void delay(uint32_t count) {
    for (volatile uint32_t i = 0; i < count; i++);
}

void SystemClock_Config(void) {
    /* 1. Enable HSE and wait for it to be ready (or timeout and use HSI) */
    RCC_CR |= RCC_CR_HSEON;
    uint32_t timeout = 5000;
    while (!(RCC_CR & RCC_CR_HSERDY) && --timeout);

    int use_hse = (RCC_CR & RCC_CR_HSERDY);

    /* 2. Configure Flash Latency for 96MHz (3 Wait States) */
    FLASH_ACR = (1 << 8) | (1 << 9) | (1 << 10) | 3;

    /* 3. Configure PLL: 
       If HSE (25MHz): M=25, N=192, P=2 -> 96MHz
       If HSI (16MHz): M=16, N=192, P=2 -> 96MHz
    */
    uint32_t pllm = use_hse ? 25 : 16;
    uint32_t plln = 192;
    uint32_t pllp = 0; // PLLP = 2 (coded as 00)
    
    RCC_PLLCFGR = (pllm << 0) | (plln << 6) | (pllp << 16) | 
                  (use_hse ? RCC_PLLCFGR_PLLSRC_HSE : RCC_PLLCFGR_PLLSRC_HSI);

    /* 4. Enable PLL and wait */
    RCC_CR |= RCC_CR_PLLON;
    while (!(RCC_CR & RCC_CR_PLLRDY));

    /* 5. Configure Bus Prescalers: HCLK = SYSCLK, PCLK1 = SYSCLK/2, PCLK2 = SYSCLK/1 */
    RCC_CFGR |= (0 << 4) | (4 << 10) | (0 << 13); // AHB=1, APB1=2, APB2=1

    /* 6. Select PLL as System Clock */
    RCC_CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC_CFGR & (3 << 2)) != RCC_CFGR_SWS_PLL);
}

void USART1_Init(void) {
    /* Enable GPIOA and USART1 clocks */
    RCC_AHB1ENR |= GPIOAEN;
    RCC_APB2ENR |= USART1EN;

    /* Configure PA9 as AF7 (USART1 TX) */
    GPIOA_MODER &= ~(3 << (9 * 2));
    GPIOA_MODER |=  (2 << (9 * 2)); // Alternate Function
    GPIOA_AFRH  &= ~(0xF << (1 * 4)); // Clear AF for PA9
    GPIOA_AFRH  |=  (7 << (1 * 4));   // AF7

    /* Configure Baud Rate: 96MHz / (16 * 115200) = 52.083
       BRR = 52 (DIV_Mantissa) and 1 (DIV_Fraction: 0.083 * 16 = 1.3 -> 1)
    */
    USART1_BRR = (52 << 4) | 1;

    /* Enable USART and TX */
    USART1_CR1 = (1 << 13) | (1 << 3); // UE=1, TE=1
}

int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        while (!(USART1_SR & (1 << 7))); // Wait for TXE
        USART1_DR = ptr[i];
    }
    return len;
}

int main(void) {
    SystemClock_Config();
    USART1_Init();

    /* Enable GPIOC clock and configure PC13 as output */
    RCC_AHB1ENR |= GPIOCEN;
    GPIOC_MODER &= ~(3 << (13 * 2));
    GPIOC_MODER |=  (1 << (13 * 2));

    printf("\r\n--- STM32F411 Blackpill Booting ---\r\n");
    printf("System Clock: 96MHz\r\n");
    printf("Clock Source: %s\r\n", (RCC_CR & RCC_CR_HSERDY) ? "HSE (25MHz)" : "HSI (16MHz)");

    uint32_t count = 0;
    while (1) {
        GPIOC_ODR |= PIN13;  /* OFF */
        delay(4000000);      /* Slower delay because of 96MHz clock */
        GPIOC_ODR &= ~PIN13; /* ON */
        delay(4000000);
        
        printf("Blink count: %lu\r\n", ++count);
    }

    return 0;
}
