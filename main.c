#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

/* Register addresses */
#define RCC_BASE        0x40023800
#define FLASH_R_BASE    0x40023C00
#define GPIOA_BASE      0x40020000
#define GPIOC_BASE      0x40020800
#define USART1_BASE     0x40011000
#define PWR_BASE        0x40007000
#define RTC_BASE        0x40002800

/* RCC Registers */
#define RCC_CR          (*(volatile uint32_t *)(RCC_BASE + 0x00))
#define RCC_PLLCFGR     (*(volatile uint32_t *)(RCC_BASE + 0x04))
#define RCC_CFGR        (*(volatile uint32_t *)(RCC_BASE + 0x08))
#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x40))
#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x44))
#define RCC_BDCR        (*(volatile uint32_t *)(RCC_BASE + 0x70))
#define RCC_CSR         (*(volatile uint32_t *)(RCC_BASE + 0x74))

/* PWR Registers */
#define PWR_CR          (*(volatile uint32_t *)(PWR_BASE + 0x00))

/* RTC Registers */
#define RTC_TR          (*(volatile uint32_t *)(RTC_BASE + 0x00))
#define RTC_DR          (*(volatile uint32_t *)(RTC_BASE + 0x04))
#define RTC_CR_REG      (*(volatile uint32_t *)(RTC_BASE + 0x08))
#define RTC_ISR         (*(volatile uint32_t *)(RTC_BASE + 0x0C))
#define RTC_PRER        (*(volatile uint32_t *)(RTC_BASE + 0x10))
#define RTC_WPR         (*(volatile uint32_t *)(RTC_BASE + 0x24))

#define FLASH_ACR       (*(volatile uint32_t *)(FLASH_R_BASE + 0x00))
#define GPIOA_MODER     (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_AFRH      (*(volatile uint32_t *)(GPIOA_BASE + 0x24))
#define GPIOC_MODER     (*(volatile uint32_t *)(GPIOC_BASE + 0x00))
#define GPIOC_ODR       (*(volatile uint32_t *)(GPIOC_BASE + 0x14))
#define USART1_SR       (*(volatile uint32_t *)(USART1_BASE + 0x00))
#define USART1_DR       (*(volatile uint32_t *)(USART1_BASE + 0x04))
#define USART1_BRR      (*(volatile uint32_t *)(USART1_BASE + 0x08))
#define USART1_CR1      (*(volatile uint32_t *)(USART1_BASE + 0x0C))

/* SysTick */
#define STK_CTRL        (*(volatile uint32_t *)0xE000E010)
#define STK_LOAD        (*(volatile uint32_t *)0xE000E014)
#define STK_VAL         (*(volatile uint32_t *)0xE000E018)

volatile uint32_t ms_ticks = 0;
int rtc_ready = 0;

void SysTick_Handler(void) {
    ms_ticks++;
}

void delay_ms(uint32_t ms) {
    uint32_t start = ms_ticks;
    while ((ms_ticks - start) < ms);
}

void Logger_Log(const char *fmt, ...) {
    if (rtc_ready) {
        uint32_t tr = RTC_TR;
        int h = ((tr >> 20) & 0x3) * 10 + ((tr >> 16) & 0xF);
        int m = ((tr >> 12) & 0x7) * 10 + ((tr >> 8) & 0xF);
        int s = ((tr >> 4) & 0x7) * 10 + (tr & 0xF);
        printf("[%02d:%02d:%02d] ", h, m, s);
    } else {
        printf("[%lu ms] ", ms_ticks);
    }

    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\r\n");
}

void RTC_Init(void) {
    /* 1. Enable Power Clock and Access to Backup Domain */
    RCC_APB1ENR |= (1 << 28); // PWREN
    PWR_CR |= (1 << 8);       // DBP: Disable Backup Domain protection

    /* 2. Enable LSE and wait for it to be ready */
    RCC_BDCR |= (1 << 0);     // LSEON
    uint32_t timeout = 0xFFFFF;
    while (!(RCC_BDCR & (1 << 1)) && --timeout); // Wait for LSERDY

    uint32_t prediv_a, prediv_s;

    if (RCC_BDCR & (1 << 1)) {
        /* LSE Ready */
        RCC_BDCR |= (1 << 8); // RTCSEL = LSE
        prediv_a = 127;
        prediv_s = 255;
    } else {
        /* LSE Failed, fall back to LSI */
        RCC_CSR |= (1 << 0);  // LSION
        while (!(RCC_CSR & (1 << 1))); // Wait for LSIRDY
        RCC_BDCR &= ~(3 << 8);
        RCC_BDCR |=  (2 << 8); // RTCSEL = LSI
        prediv_a = 127;
        prediv_s = 249; // 32000 / 128 = 250 -> 250-1
    }

    /* 3. Enable RTC Clock */
    RCC_BDCR |= (1 << 15); // RTCEN

    /* 4. Enter Init Mode */
    RTC_WPR = 0xCA;
    RTC_WPR = 0x53;
    RTC_ISR |= (1 << 7); // INIT
    while (!(RTC_ISR & (1 << 6))); // INITF

    /* 5. Set Prescalers */
    RTC_PRER = (prediv_a << 16) | prediv_s;

    /* 6. Exit Init Mode */
    RTC_ISR &= ~(1 << 7);
    RTC_WPR = 0xFF; // Re-enable protection

    rtc_ready = 1;
}

void USART1_Init_16MHz(void) {
    RCC_AHB1ENR |= (1 << 0);
    RCC_APB2ENR |= (1 << 4);
    GPIOA_MODER &= ~(3 << (9 * 2));
    GPIOA_MODER |=  (2 << (9 * 2));
    GPIOA_AFRH  &= ~(0xF << (1 * 4));
    GPIOA_AFRH  |=  (7 << (1 * 4));
    USART1_BRR = (8 << 4) | 11;
    USART1_CR1 = (1 << 13) | (1 << 3);
}

void USART1_Init_96MHz(void) {
    USART1_BRR = (52 << 4) | 1;
    USART1_CR1 = (1 << 13) | (1 << 3);
}

void SystemClock_Config_96MHz(void) {
    RCC_CR |= (1 << 16); // HSEON
    uint32_t timeout = 0xFFFF;
    while (!(RCC_CR & (1 << 17)) && --timeout);
    int use_hse = (RCC_CR & (1 << 17));

    FLASH_ACR = (1 << 8) | (1 << 9) | (1 << 10) | 3;

    uint32_t pllm = use_hse ? 25 : 16;
    uint32_t plln = 192;
    uint32_t pllp = 0;
    RCC_PLLCFGR = (pllm << 0) | (plln << 6) | (pllp << 16) | (use_hse ? (1 << 22) : (0 << 22));

    RCC_CR |= (1 << 24); // PLLON
    while (!(RCC_CR & (1 << 25)));

    RCC_CFGR |= (0 << 4) | (4 << 10) | (0 << 13);
    RCC_CFGR |= (2 << 0);
    while ((RCC_CFGR & (3 << 2)) != (2 << 2));
}

int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        while (!(USART1_SR & (1 << 7)));
        USART1_DR = ptr[i];
    }
    return len;
}

int main(void) {
    USART1_Init_16MHz();
    printf("\r\n--- STM32F411 Blackpill Booting ---\r\n");
    
    SystemClock_Config_96MHz();
    USART1_Init_96MHz();

    STK_LOAD = 96000000 / 1000 - 1;
    STK_VAL = 0;
    STK_CTRL = 0x07;

    Logger_Log("System Clock set to 96MHz.");
    
    RTC_Init();
    Logger_Log("RTC Initialized using %s.", (RCC_BDCR & (1 << 1)) ? "LSE (32.768kHz)" : "LSI (32kHz)");

    RCC_AHB1ENR |= (1 << 2);
    GPIOC_MODER &= ~(3 << (13 * 2));
    GPIOC_MODER |=  (1 << (13 * 2));

    uint32_t count = 0;
    while (1) {
        GPIOC_ODR ^= (1 << 13);
        delay_ms(1000);
        Logger_Log("Blink count: %lu", ++count);
    }
}
