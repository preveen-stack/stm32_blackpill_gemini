#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

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
        uint32_t dr = RTC_DR;
        int h = ((tr >> 20) & 0x3) * 10 + ((tr >> 16) & 0xF);
        int m = ((tr >> 12) & 0x7) * 10 + ((tr >> 8) & 0xF);
        int s = ((tr >> 4) & 0x7) * 10 + (tr & 0xF);
        int y = ((dr >> 20) & 0xF) * 10 + ((dr >> 16) & 0xF);
        int mon = ((dr >> 12) & 0x1) * 10 + ((dr >> 8) & 0xF);
        int d = ((dr >> 4) & 0x3) * 10 + (dr & 0xF);
        printf("[%02d/%02d/20%02d %02d:%02d:%02d] ", d, mon, y, h, m, s);
    } else {
        printf("[%lu ms] ", ms_ticks);
    }

    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\r\n");
}

static uint8_t to_bcd(uint8_t val) {
    return ((val / 10) << 4) | (val % 10);
}

void RTC_SetDateTime(uint8_t y, uint8_t mon, uint8_t d, uint8_t h, uint8_t min, uint8_t s) {
    RTC_WPR = 0xCA;
    RTC_WPR = 0x53;
    RTC_ISR |= (1 << 7); // INIT
    while (!(RTC_ISR & (1 << 6)));

    RTC_TR = (to_bcd(h) << 16) | (to_bcd(min) << 8) | to_bcd(s);
    RTC_DR = (to_bcd(y) << 16) | (to_bcd(mon) << 8) | to_bcd(d);

    RTC_ISR &= ~(1 << 7);
    RTC_WPR = 0xFF;
}

void RTC_Init(void) {
    RCC_APB1ENR |= (1 << 28);
    PWR_CR |= (1 << 8);

    RCC_BDCR |= (1 << 0);
    uint32_t timeout = 0xFFFFF;
    while (!(RCC_BDCR & (1 << 1)) && --timeout);

    uint32_t prediv_a, prediv_s;
    if (RCC_BDCR & (1 << 1)) {
        RCC_BDCR |= (1 << 8);
        prediv_a = 127;
        prediv_s = 255;
    } else {
        RCC_CSR |= (1 << 0);
        while (!(RCC_CSR & (1 << 1)));
        RCC_BDCR &= ~(3 << 8);
        RCC_BDCR |=  (2 << 8);
        prediv_a = 127;
        prediv_s = 249;
    }

    RCC_BDCR |= (1 << 15);
    RTC_WPR = 0xCA;
    RTC_WPR = 0x53;
    RTC_ISR |= (1 << 7);
    while (!(RTC_ISR & (1 << 6)));
    RTC_PRER = (prediv_a << 16) | prediv_s;
    RTC_ISR &= ~(1 << 7);
    RTC_WPR = 0xFF;
    rtc_ready = 1;
}

void USART1_Init_Pins(void) {
    RCC_AHB1ENR |= (1 << 0);
    RCC_APB2ENR |= (1 << 4);
    
    /* PA9 (TX), PA10 (RX) -> AF7 */
    GPIOA_MODER &= ~((3 << (9 * 2)) | (3 << (10 * 2)));
    GPIOA_MODER |=  ((2 << (9 * 2)) | (2 << (10 * 2)));
    GPIOA_AFRH  &= ~((0xF << (1 * 4)) | (0xF << (2 * 4)));
    GPIOA_AFRH  |=  ((7 << (1 * 4)) | (7 << (2 * 4)));
}

void USART1_Init_16MHz(void) {
    USART1_Init_Pins();
    USART1_BRR = (8 << 4) | 11;
    USART1_CR1 = (1 << 13) | (1 << 3) | (1 << 2); // UE, TE, RE
}

void USART1_Init_96MHz(void) {
    USART1_BRR = (52 << 4) | 1;
    USART1_CR1 = (1 << 13) | (1 << 3) | (1 << 2); // UE, TE, RE
}

void SystemClock_Config_96MHz(void) {
    RCC_CR |= (1 << 16);
    uint32_t timeout = 0xFFFF;
    while (!(RCC_CR & (1 << 17)) && --timeout);
    int use_hse = (RCC_CR & (1 << 17));
    FLASH_ACR = (1 << 8) | (1 << 9) | (1 << 10) | 3;
    uint32_t pllm = use_hse ? 25 : 16;
    uint32_t plln = 192;
    uint32_t pllp = 0;
    RCC_PLLCFGR = (pllm << 0) | (plln << 6) | (pllp << 16) | (use_hse ? (1 << 22) : (0 << 22));
    RCC_CR |= (1 << 24);
    while (!(RCC_CR & (1 << 25)));
    RCC_CFGR |= (0 << 4) | (4 << 10) | (0 << 13);
    RCC_CFGR |= (2 << 0);
    while ((RCC_CFGR & (3 << 2)) != (2 << 2));
}

void uart_putc(char c) {
    while (!(USART1_SR & (1 << 7)));
    USART1_DR = c;
}

int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        uart_putc(ptr[i]);
    }
    return len;
}

char rx_buffer[32];
int rx_index = 0;

void Process_UART(void) {
    while (USART1_SR & (1 << 5)) { // RXNE
        char c = USART1_DR;
        /* Echo back for debugging */
        uart_putc(c); 
        
        if (c == '\r' || c == '\n') {
            rx_buffer[rx_index] = '\0';
            if (rx_index == 15 && rx_buffer[0] == 'T') {
                /* Format: TYYYYMMDDHHMMSS */
                int y, mon, d, h, m, s;
                char tmp[5];
                
                tmp[0] = rx_buffer[1]; tmp[1] = rx_buffer[2]; tmp[2] = rx_buffer[3]; tmp[3] = rx_buffer[4]; tmp[4] = '\0';
                y = atoi(tmp) - 2000;
                tmp[0] = rx_buffer[5]; tmp[1] = rx_buffer[6]; tmp[2] = '\0';
                mon = atoi(tmp);
                tmp[0] = rx_buffer[7]; tmp[1] = rx_buffer[8]; tmp[2] = '\0';
                d = atoi(tmp);
                tmp[0] = rx_buffer[9]; tmp[1] = rx_buffer[10]; tmp[2] = '\0';
                h = atoi(tmp);
                tmp[0] = rx_buffer[11]; tmp[1] = rx_buffer[12]; tmp[2] = '\0';
                m = atoi(tmp);
                tmp[0] = rx_buffer[13]; tmp[1] = rx_buffer[14]; tmp[2] = '\0';
                s = atoi(tmp);

                RTC_SetDateTime(y, mon, d, h, m, s);
                Logger_Log("RTC Sync Successful!");
            }
            rx_index = 0;
        } else if (rx_index < 31) {
            rx_buffer[rx_index++] = c;
        }
    }
}

int main(void) {
    USART1_Init_16MHz();
    printf("\r\n--- STM32F411 RTC Sync Ready ---\r\n");
    
    SystemClock_Config_96MHz();
    USART1_Init_96MHz();

    STK_LOAD = 96000000 / 1000 - 1;
    STK_VAL = 0;
    STK_CTRL = 0x07;

    RTC_Init();
    Logger_Log("System online. Send TYYYYMMDDHHMMSS to sync time.");

    RCC_AHB1ENR |= (1 << 2);
    GPIOC_MODER &= ~(3 << (13 * 2));
    GPIOC_MODER |=  (1 << (13 * 2));

    uint32_t last_blink = 0;
    while (1) {
        Process_UART();
        
        if ((ms_ticks - last_blink) >= 1000) {
            GPIOC_ODR ^= (1 << 13);
            Logger_Log("Heartbeat");
            last_blink = ms_ticks;
        }
    }
}
