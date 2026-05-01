#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

/* Register addresses */
#define RCC_BASE        0x40023800
#define FLASH_R_BASE    0x40023C00
#define GPIOA_BASE      0x40020000
#define GPIOB_BASE      0x40020400
#define GPIOC_BASE      0x40020800
#define USART1_BASE     0x40011000
#define PWR_BASE        0x40007000
#define RTC_BASE        0x40002800
#define I2C1_BASE       0x40005400
#define SPI1_BASE       0x40013000
#define SPI2_BASE       0x40003800

/* I2C Registers */
#define I2C1_CR1        (*(volatile uint32_t *)(I2C1_BASE + 0x00))
#define I2C1_CR2        (*(volatile uint32_t *)(I2C1_BASE + 0x04))
#define I2C1_DR         (*(volatile uint32_t *)(I2C1_BASE + 0x10))
#define I2C1_SR1        (*(volatile uint32_t *)(I2C1_BASE + 0x14))
#define I2C1_SR2        (*(volatile uint32_t *)(I2C1_BASE + 0x18))
#define I2C1_CCR        (*(volatile uint32_t *)(I2C1_BASE + 0x1C))
#define I2C1_TRISE      (*(volatile uint32_t *)(I2C1_BASE + 0x20))

/* SPI Registers */
#define SPI1_CR1        (*(volatile uint32_t *)(SPI1_BASE + 0x00))
#define SPI1_CR2        (*(volatile uint32_t *)(SPI1_BASE + 0x04))
#define SPI1_SR         (*(volatile uint32_t *)(SPI1_BASE + 0x08))
#define SPI1_DR         (*(volatile uint32_t *)(SPI1_BASE + 0x0C))

/* I2S/SPI2 Registers */
#define SPI2_CR1        (*(volatile uint32_t *)(SPI2_BASE + 0x00))
#define SPI2_CR2        (*(volatile uint32_t *)(SPI2_BASE + 0x04))
#define SPI2_SR         (*(volatile uint32_t *)(SPI2_BASE + 0x08))
#define SPI2_DR         (*(volatile uint32_t *)(SPI2_BASE + 0x0C))
#define SPI2_I2SCFGR    (*(volatile uint32_t *)(SPI2_BASE + 0x1C))
#define SPI2_I2SPR      (*(volatile uint32_t *)(SPI2_BASE + 0x20))

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
#define GPIOB_MODER     (*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOC_MODER     (*(volatile uint32_t *)(GPIOC_BASE + 0x00))
#define GPIOC_ODR       (*(volatile uint32_t *)(GPIOC_BASE + 0x14))
#define USART1_SR       (*(volatile uint32_t *)(USART1_BASE + 0x00))
#define USART1_DR       (*(volatile uint32_t *)(USART1_BASE + 0x04))
#define USART1_BRR      (*(volatile uint32_t *)(USART1_BASE + 0x08))
#define USART1_CR1      (*(volatile uint32_t *)(USART1_BASE + 0x0C))

/* ADC Registers */
#define ADC1_BASE       0x40012000
#define ADC_COMMON_BASE 0x40012300
#define ADC1_SR         (*(volatile uint32_t *)(ADC1_BASE + 0x00))
#define ADC1_CR1        (*(volatile uint32_t *)(ADC1_BASE + 0x04))
#define ADC1_CR2        (*(volatile uint32_t *)(ADC1_BASE + 0x08))
#define ADC1_SMPR1      (*(volatile uint32_t *)(ADC1_BASE + 0x0C))
#define ADC1_SMPR2      (*(volatile uint32_t *)(ADC1_BASE + 0x10))
#define ADC1_SQR3       (*(volatile uint32_t *)(ADC1_BASE + 0x34))
#define ADC1_DR         (*(volatile uint32_t *)(ADC1_BASE + 0x4C))
#define ADC_CCR         (*(volatile uint32_t *)(ADC_COMMON_BASE + 0x04))

/* TIM1 Registers (Advanced Control Timer for PWM) */
#define TIM1_BASE       0x40010000
#define TIM1_CR1        (*(volatile uint32_t *)(TIM1_BASE + 0x00))
#define TIM1_CCMR1      (*(volatile uint32_t *)(TIM1_BASE + 0x18))
#define TIM1_CCER       (*(volatile uint32_t *)(TIM1_BASE + 0x20))
#define TIM1_PSC        (*(volatile uint32_t *)(TIM1_BASE + 0x28))
#define TIM1_ARR        (*(volatile uint32_t *)(TIM1_BASE + 0x2C))
#define TIM1_CCR1       (*(volatile uint32_t *)(TIM1_BASE + 0x34))
#define TIM1_BDTR       (*(volatile uint32_t *)(TIM1_BASE + 0x44))

/* CRC Registers */
#define CRC_BASE        0x40023000
#define CRC_DR          (*(volatile uint32_t *)(CRC_BASE + 0x00))
#define CRC_IDR         (*(volatile uint32_t *)(CRC_BASE + 0x04))
#define CRC_CR_PERIPH   (*(volatile uint32_t *)(CRC_BASE + 0x08))

/* DMA2 Registers */
#define DMA2_BASE       0x40026400
#define DMA2_S0CR       (*(volatile uint32_t *)(DMA2_BASE + 0x10))
#define DMA2_S0NDTR     (*(volatile uint32_t *)(DMA2_BASE + 0x14))
#define DMA2_S0PAR      (*(volatile uint32_t *)(DMA2_BASE + 0x18))
#define DMA2_S0M0AR     (*(volatile uint32_t *)(DMA2_BASE + 0x1C))
#define DMA2_LISR       (*(volatile uint32_t *)(DMA2_BASE + 0x00))
#define DMA2_LIFCR      (*(volatile uint32_t *)(DMA2_BASE + 0x08))

/* ADC SQR Registers */
#define ADC1_SQR1       (*(volatile uint32_t *)(ADC1_BASE + 0x2C))
#define ADC1_SQR2       (*(volatile uint32_t *)(ADC1_BASE + 0x30))

/* SysTick */
#define STK_CTRL        (*(volatile uint32_t *)0xE000E010)
#define STK_LOAD        (*(volatile uint32_t *)0xE000E014)
#define STK_VAL         (*(volatile uint32_t *)0xE000E018)

/* DWT Registers for Cycle Counting */
#define DWT_CTRL        (*(volatile uint32_t *)0xE0001000)
#define DWT_CYCCNT      (*(volatile uint32_t *)0xE0001004)
#define DEMCR           (*(volatile uint32_t *)0xE000EDFC)
#define CPACR           (*(volatile uint32_t *)0xE000ED88)
#define SCB_AIRCR       (*(volatile uint32_t *)0xE000ED0C)

volatile uint32_t ms_ticks = 0;
int rtc_ready = 0;
char reset_reason[32] = "Unknown";

void Detect_ResetReason(void) {
    uint32_t csr = RCC_CSR;

    if (csr & (1 << 26)) strcpy(reset_reason, "Pin Reset (NRST)");
    else if (csr & (1 << 27)) strcpy(reset_reason, "Power-on Reset (POR)");
    else if (csr & (1 << 28)) strcpy(reset_reason, "Software Reset");
    else if (csr & (1 << 29)) strcpy(reset_reason, "IWDG Reset");
    else if (csr & (1 << 30)) strcpy(reset_reason, "WWDG Reset");
    else if (csr & (1 << 31)) strcpy(reset_reason, "Low-power Reset");
    else strcpy(reset_reason, "Other/Unknown");

    /* Clear reset flags */
    RCC_CSR |= (1 << 24); // RMVF
}

/* ADC DMA Buffer: 10 external channels + 1 internal temperature */
#define ADC_CHANNELS 11
volatile uint16_t adc_results[ADC_CHANNELS];

void SysTick_Handler(void) {
    ms_ticks++;
}

void uart_putc(char c);

int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        uart_putc(ptr[i]);
    }
    return len;
}

void uart_wait_tx_complete(void) {
    /* Wait for TC (Transmission Complete) bit */
    while (!(USART1_SR & (1 << 6)));
}

static char log_buffer[1024];

void Logger_Log(const char *fmt, ...) {
    int len = 0;
    
    if (rtc_ready) {
        uint32_t tr = RTC_TR;
        uint32_t dr = RTC_DR;
        int h = ((tr >> 20) & 0x3) * 10 + ((tr >> 16) & 0xF);
        int m = ((tr >> 12) & 0x7) * 10 + ((tr >> 8) & 0xF);
        int s = ((tr >> 4) & 0x7) * 10 + (tr & 0xF);
        int y = ((dr >> 20) & 0xF) * 10 + ((dr >> 16) & 0xF);
        int mon = ((dr >> 12) & 0x1) * 10 + ((dr >> 8) & 0xF);
        int d = ((dr >> 4) & 0x3) * 10 + (dr & 0xF);
        len = sprintf(log_buffer, "[%02d/%02d/20%02d %02d:%02d:%02d] ", d, mon, y, h, m, s);
    } else {
        len = sprintf(log_buffer, "[%lu ms] ", ms_ticks);
    }

    va_list args;
    va_start(args, fmt);
    len += vsnprintf(log_buffer + len, sizeof(log_buffer) - len - 4, fmt, args);
    va_end(args);
    
    strcat(log_buffer, "\r\n");
    _write(1, log_buffer, strlen(log_buffer));
    uart_wait_tx_complete();
}
void delay_ms(uint32_t ms) {
    uint32_t start = ms_ticks;
    while ((ms_ticks - start) < ms);
}

void DWT_Init(void) {
    DEMCR |= (1 << 24); // Enable TRCENA
    DWT_CYCCNT = 0;
    DWT_CTRL |= (1 << 0); // Enable CYCCNT
}

uint32_t Measure_SystemClock(void) {
    static uint32_t state = 0;
    static uint32_t start_tr = 0;
    static uint32_t start_cycles = 0;
    static uint32_t last_freq = 0;

    if (!rtc_ready) {
        /* Fallback: Quick measurement using SysTick (10ms window) */
        uint32_t start_ms = ms_ticks;
        uint32_t start_c = DWT_CYCCNT;
        while ((ms_ticks - start_ms) < 10);
        uint32_t end_c = DWT_CYCCNT;
        return (end_c - start_c) * 100;
    }

    uint32_t current_tr = RTC_TR;

    if (state == 0) {
        start_tr = current_tr;
        state = 1;
    } else if (state == 1) {
        if (current_tr != start_tr) {
            start_cycles = DWT_CYCCNT;
            start_tr = current_tr;
            state = 2;
        }
    } else if (state == 2) {
        if (current_tr != start_tr) {
            uint32_t end_cycles = DWT_CYCCNT;
            uint32_t delta = end_cycles - start_cycles;
            /* Validation: 96MHz +/- 10% */
            if (delta > 80000000 && delta < 110000000) {
                last_freq = delta;
            }
            state = 0; 
        }
    }
    return last_freq;
}

void Log_ClockConfiguration(void) {
    uint32_t pllcfgr = RCC_PLLCFGR;
    uint32_t cfgr = RCC_CFGR;
    uint32_t m = pllcfgr & 0x3F;
    uint32_t n = (pllcfgr >> 6) & 0x1FF;
    uint32_t p = (((pllcfgr >> 16) & 0x3) + 1) * 2;
    uint32_t pll_src = (pllcfgr >> 22) & 0x1;
    uint32_t sws = (cfgr >> 2) & 0x3;

    const char* sws_str = "Unknown";
    if (sws == 0) sws_str = "HSI (16MHz)";
    else if (sws == 1) sws_str = "HSE (25MHz)";
    else if (sws == 2) sws_str = "PLL (96MHz)";

    Logger_Log("--- Clock Status ---");
    Logger_Log("System Source: %s", sws_str);
    Logger_Log("PLL: Src=%s M=%lu N=%lu P=%lu", pll_src ? "HSE" : "HSI", m, n, p);
    
    uint32_t hse_rdy = (RCC_CR >> 17) & 1;
    uint32_t hsi_rdy = (RCC_CR >> 1) & 1;
    uint32_t lse_rdy = (RCC_BDCR >> 1) & 1;
    uint32_t lsi_rdy = (RCC_CSR >> 1) & 1;
    
    Logger_Log("Oscillators: HSE:%d HSI:%d LSE:%d LSI:%d", hse_rdy, hsi_rdy, lse_rdy, lsi_rdy);
    
    uint32_t freq = Measure_SystemClock();
    if (freq > 0) {
        Logger_Log("Measured Clock: %lu Hz", freq);
    } else {
        Logger_Log("Measured Clock: [Syncing...]");
    }
}

void Print_Banner(void) {
    Logger_Log("****************************************************");
    Logger_Log("*                                                  *");
    Logger_Log("*         STM32 BLACKPILL F411 BAREMETAL           *");
    Logger_Log("*                                                  *");
    Logger_Log("*            Created using Gemini CLI              *");
    Logger_Log("*                                                  *");
    Logger_Log("****************************************************");
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
    RCC_APB1ENR |= (1 << 28); // PWREN
    PWR_CR |= (1 << 8); // DBP

    /* Force a clean start on every reset to ensure LSI and RTC are fresh */
    Logger_Log("Resetting RTC Backup Domain...");
    RCC_BDCR |= (1 << 16);
    RCC_BDCR &= ~(1 << 16);
    for (volatile int i = 0; i < 100000; i++);

    /* 1. Enable LSI */
    RCC_CSR |= (1 << 0); // LSION
    uint32_t timeout = 0x3FFFF;
    while (!(RCC_CSR & (1 << 1)) && --timeout);

    if (timeout == 0) {
        Logger_Log("LSI Start Failed!");
        return;
    }

    /* 2. Configure Backup Domain */
    RCC_BDCR &= ~(3 << 8);
    RCC_BDCR |=  (2 << 8); // LSI
    RCC_BDCR |=  (1 << 15); // RTCEN

    /* 3. Initialization */
    RTC_WPR = 0xCA;
    RTC_WPR = 0x53;
    
    /* Wait for RSF */
    RTC_ISR &= ~(1 << 5);
    timeout = 0x3FFFF;
    while (!(RTC_ISR & (1 << 5)) && --timeout);

    /* Enter Init Mode */
    RTC_ISR |= (1 << 7);
    timeout = 0x3FFFF;
    while (!(RTC_ISR & (1 << 6)) && --timeout);
    
    if (timeout > 0) {
        RTC_PRER = (127 << 16) | 249; 
        RTC_ISR &= ~(1 << 7);
        rtc_ready = 1;
        Logger_Log("RTC Initialized successfully.");
    } else {
        Logger_Log("RTC Init Mode Timeout!");
    }
    RTC_WPR = 0xFF;
}

void ADC_Init(void) {
    uint32_t timeout;
    RCC_AHB1ENR |= (1 << 0) | (1 << 1); // Enable GPIOA and GPIOB clocks
    RCC_AHB1ENR |= (1 << 22);           // Enable DMA2 clock
    
    /* Configure PA0-PA7 as Analog */
    GPIOA_MODER |= 0x0000FFFF;
    
    /* Configure PB0-PB1 as Analog */
    GPIOB_MODER |= 0x0000000F;

    RCC_APB2ENR |= (1 << 8);      // Enable ADC1 clock
    ADC_CCR |= (1 << 23);         // TSVREFE: Enable Temp sensor

    /* ADC Configuration: Scan Mode, Continuous Conversion */
    ADC1_CR1 |= (1 << 8);         // SCAN: Scan mode
    ADC1_CR2 |= (1 << 1);         // CONT: Continuous conversion
    ADC1_CR2 |= (1 << 8);         // DMA: Enable DMA
    ADC1_CR2 |= (1 << 9);         // DDS: DMA disable selection (keep DMA on)

    /* Sample time: 480 cycles for all channels */
    ADC1_SMPR2 = 0x3FFFFFFF;      // Channels 0-9
    ADC1_SMPR1 |= (7 << 24);      // Channel 18

    /* Sequence: CH0, CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8, CH9, CH18 */
    ADC1_SQR1 = ((ADC_CHANNELS - 1) << 20); // L = 11 conversions
    ADC1_SQR3 = (0 << 0) | (1 << 5) | (2 << 10) | (3 << 15) | (4 << 20) | (5 << 25);
    ADC1_SQR2 = (6 << 0) | (7 << 5) | (8 << 10) | (9 << 15) | (18 << 20);

    /* DMA2 Stream 0 Configuration (ADC1 is on Stream 0 Channel 0 or Stream 4 Channel 0) */
    DMA2_S0CR &= ~(1 << 0);       // Disable DMA Stream 0 to configure
    timeout = 0xFFFF;
    while ((DMA2_S0CR & (1 << 0)) && --timeout); // Wait for disable
    
    if (timeout == 0) {
        Logger_Log("ADC DMA Disable Timeout!");
    }

    DMA2_S0PAR = (uint32_t)&ADC1_DR;
    DMA2_S0M0AR = (uint32_t)adc_results;
    DMA2_S0NDTR = ADC_CHANNELS;

    /* Channel 0, High priority, 16-bit memory & peripheral, Memory increment, Circular mode, Enable */
    DMA2_S0CR = (0 << 25) | (2 << 16) | (1 << 13) | (1 << 11) | (1 << 10) | (1 << 8) | (1 << 0);

    ADC1_CR2 |= (1 << 0);         // ADON: Turn on ADC
    delay_ms(1);
    ADC1_CR2 |= (1 << 30);        // SWSTART: Start first conversion
}

uint32_t ADC_Read(uint8_t channel) {
    if (channel < 10) return adc_results[channel];
    if (channel == 18) return adc_results[10];
    return 0;
}

int32_t ADC_ReadTemp(void) {
    uint32_t val = ADC_Read(18);
    int32_t vsense_mv = (val * 3300) / 4095;
    int32_t temp_mc = (vsense_mv - 760) * 400 + 25000;
    return temp_mc;
}

uint32_t i2c_current_freq = 100000;

void I2C1_Init_Freq(uint32_t freq) {
    /* 1. Enable I2C1 and GPIOB clocks */
    RCC_APB1ENR |= (1 << 21); // I2C1EN
    RCC_AHB1ENR |= (1 << 1);  // GPIOBEN

    /* 2. Configure PB6 (SCL) and PB7 (SDA) as Alternate Function Open-Drain */
    GPIOB_MODER &= ~((3 << (6 * 2)) | (3 << (7 * 2)));
    GPIOB_MODER |=  ((2 << (6 * 2)) | (2 << (7 * 2)));
    *(volatile uint32_t *)(GPIOB_BASE + 0x04) |= (1 << 6) | (1 << 7);
    *(volatile uint32_t *)(GPIOB_BASE + 0x0C) &= ~((3 << (6 * 2)) | (3 << (7 * 2)));
    *(volatile uint32_t *)(GPIOB_BASE + 0x0C) |=  ((1 << (6 * 2)) | (1 << (7 * 2)));
    *(volatile uint32_t *)(GPIOB_BASE + 0x20) &= ~(0xFF << (6 * 4));
    *(volatile uint32_t *)(GPIOB_BASE + 0x20) |=  (0x44 << (6 * 4));

    /* 3. I2C Configuration */
    I2C1_CR1 = (1 << 15); // SWRST
    I2C1_CR1 = 0;
    
    /* Program peripheral input clock frequency (PCLK1 is 48MHz) */
    I2C1_CR2 = 48; 
    
    if (freq <= 100000) {
        /* Standard mode 100kHz: CCR = PCLK / (2 * 100000) = 48MHz / 200000 = 240 */
        I2C1_CCR = 240;
        I2C1_TRISE = 49;
    } else {
        /* Fast mode 400kHz: Duty 2 (1/3), CCR = PCLK / (3 * 400000) = 48MHz / 1.2MHz = 40 */
        I2C1_CCR = (1 << 15) | (0 << 14) | 40; // F/S bit | Duty | CCR
        I2C1_TRISE = 15; // 300ns / (1 / 48MHz) + 1 = 14.4 + 1
    }
    
    I2C1_CR1 |= (1 << 0); // PE
    i2c_current_freq = freq;
}

void I2C1_Init(void) {
    I2C1_Init_Freq(100000);
}

int I2C1_Start(void) {
    I2C1_CR1 |= (1 << 8); // START
    uint32_t timeout = 0xFFFF;
    while (!(I2C1_SR1 & (1 << 0)) && --timeout); // SB
    return (timeout > 0);
}

void I2C1_Stop(void) {
    I2C1_CR1 |= (1 << 9); // STOP
}

int I2C1_SendAddr(uint8_t addr) {
    I2C1_DR = addr;
    uint32_t timeout = 0xFFFF;
    while (!(I2C1_SR1 & (1 << 1)) && --timeout); // ADDR
    if (timeout == 0) return 0;
    (void)I2C1_SR2; // Clear ADDR flag
    return 1;
}

int I2C1_WriteByte(uint8_t data) {
    uint32_t timeout = 0xFFFF;
    while (!(I2C1_SR1 & (1 << 7)) && --timeout); // TXE
    if (timeout == 0) return 0;
    I2C1_DR = data;
    while (!(I2C1_SR1 & (1 << 2)) && --timeout); // BTF
    return (timeout > 0);
}

uint8_t I2C1_ReadByte(int ack) {
    if (ack) I2C1_CR1 |= (1 << 10);
    else I2C1_CR1 &= ~(1 << 10);
    
    uint32_t timeout = 0xFFFF;
    while (!(I2C1_SR1 & (1 << 6)) && --timeout); // RXNE
    return (uint8_t)I2C1_DR;
}

int I2C1_Write(uint8_t dev_addr, uint8_t *data, uint32_t len) {
    if (!I2C1_Start()) return 0;
    if (!I2C1_SendAddr(dev_addr << 1)) { I2C1_Stop(); return 0; }
    for (uint32_t i = 0; i < len; i++) {
        if (!I2C1_WriteByte(data[i])) { I2C1_Stop(); return 0; }
    }
    I2C1_Stop();
    return 1;
}

int I2C1_Read(uint8_t dev_addr, uint8_t *data, uint32_t len) {
    if (!I2C1_Start()) return 0;
    if (!I2C1_SendAddr((dev_addr << 1) | 1)) { I2C1_Stop(); return 0; }
    for (uint32_t i = 0; i < len; i++) {
        data[i] = I2C1_ReadByte(i < (len - 1));
    }
    I2C1_Stop();
    return 1;
}

void I2C1_Scan(void) {
    Logger_Log("Scanning I2C1 bus (PB6=SCL, PB7=SDA)...");
    Logger_Log("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f");
    for (uint8_t i = 0; i < 128; i += 16) {
        char line[128]; char *p = line;
        p += sprintf(p, "%02x: ", i);
        for (uint8_t j = 0; j < 16; j++) {
            uint8_t addr = i + j;
            if (I2C1_Start()) {
                if (I2C1_SendAddr(addr << 1)) {
                    p += sprintf(p, "%02x ", addr);
                } else {
                    p += sprintf(p, "-- ");
                }
                I2C1_Stop();
                /* Clear flags if any */
                (void)I2C1_SR1; (void)I2C1_SR2;
            } else {
                p += sprintf(p, "?? ");
            }
            for (volatile int k = 0; k < 1000; k++); // Small gap
        }
        Logger_Log("%s", line);
    }
}

void CRC_Init(void) {
    RCC_AHB1ENR |= (1 << 12); // CRCEN
}

void FPU_Enable(void) {
    /* Set bits 20-23 to enable CP10 and CP11 coprocessors */
    CPACR |= ((3UL << 10*2) | (3UL << 11*2));
}

float DotProduct_F32(float *a, float *b, uint32_t len) {
    float sum = 0.0f;
    for (uint32_t i = 0; i < len; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}

int32_t DotProduct_I16_Standard(int16_t *a, int16_t *b, uint32_t len) {
    int32_t sum = 0;
    for (uint32_t i = 0; i < len; i++) {
        sum += (int32_t)a[i] * (int32_t)b[i];
    }
    return sum;
}

/* Using Inline Assembly for Cortex-M4 SIMD (SMLAD) */
int32_t DotProduct_I16_SIMD(int16_t *a, int16_t *b, uint32_t len) {
    int32_t sum = 0;
    uint32_t *pA = (uint32_t *)a;
    uint32_t *pB = (uint32_t *)b;
    uint32_t num_blocks = len / 2;

    for (uint32_t i = 0; i < num_blocks; i++) {
        uint32_t valA = *pA++;
        uint32_t valB = *pB++;
        /* SMLAD sum, valA, valB, sum */
        __asm volatile ("smlad %0, %1, %2, %0" : "+r" (sum) : "r" (valA), "r" (valB));
    }
    return sum;
}

void Benchmark_DSP(void) {
    #define DSP_LEN 256
    float fa[DSP_LEN], fb[DSP_LEN];
    int16_t ia[DSP_LEN], ib[DSP_LEN];

    for (int i = 0; i < DSP_LEN; i++) {
        fa[i] = (float)i * 0.123f;
        fb[i] = (float)i * 0.456f;
        ia[i] = (int16_t)i;
        ib[i] = (int16_t)(i % 127);
    }

    Logger_Log("--- DSP Benchmark (%d elements) ---", DSP_LEN);

    /* FPU Benchmark */
    uint32_t start = DWT_CYCCNT;
    float f_res = DotProduct_F32(fa, fb, DSP_LEN);
    uint32_t f_cycles = DWT_CYCCNT - start;
    Logger_Log("F32 DotProduct: %ld (%lu cycles)", (int32_t)f_res, f_cycles);

    /* I16 Standard Benchmark */
    start = DWT_CYCCNT;
    int32_t i_res_std = DotProduct_I16_Standard(ia, ib, DSP_LEN);
    uint32_t i_cycles_std = DWT_CYCCNT - start;
    Logger_Log("I16 Standard MAC: %ld (%lu cycles)", i_res_std, i_cycles_std);

    /* I16 SIMD Benchmark */
    start = DWT_CYCCNT;
    int32_t i_res_simd = DotProduct_I16_SIMD(ia, ib, DSP_LEN);
    uint32_t i_cycles_simd = DWT_CYCCNT - start;
    Logger_Log("I16 SIMD (SMLAD): %ld (%lu cycles)", i_res_simd, i_cycles_simd);

    Logger_Log("SIMD Speedup: %lu.%lu x", i_cycles_std / i_cycles_simd, ((i_cycles_std * 10) / i_cycles_simd) % 10);
    
    if (i_res_std == i_res_simd) {
        Logger_Log("DSP Validation: SUCCESS");
    } else {
        Logger_Log("DSP Validation: FAILED!");
    }
}

uint32_t pwm_current_freq = 1000; // Default 1kHz
uint32_t pwm_current_duty = 0;

void PWM_SetDutyCycle(uint16_t duty) {
    if (duty > 100) duty = 100;
    pwm_current_duty = duty;
    uint32_t arr = TIM1_ARR;
    TIM1_CCR1 = (duty * arr) / 100;
}

void PWM_Init_Freq(uint32_t freq) {
    if (freq == 0) freq = 1;
    pwm_current_freq = freq;

    /* 1. Enable TIM1 and GPIOA clocks */
    RCC_APB2ENR |= (1 << 0); // TIM1EN
    RCC_AHB1ENR |= (1 << 0); // GPIOAEN

    /* 2. Configure PA8 as AF1 */
    GPIOA_MODER &= ~(3 << (8 * 2));
    GPIOA_MODER |=  (2 << (8 * 2)); 
    GPIOA_AFRH  &= ~(0xF << (0 * 4));
    GPIOA_AFRH  |=  (1 << (0 * 4));   

    /* 3. Calculate PSC and ARR
       Freq = 96MHz / ((PSC+1) * (ARR+1))
       Let's keep resolution high (ARR ~ 1000) if possible.
    */
    uint32_t timer_clk = 96000000;
    uint32_t total_div = timer_clk / freq;
    
    uint32_t psc = (total_div / 1000);
    if (psc > 65535) psc = 65535;
    uint32_t arr = (total_div / (psc + 1)) - 1;
    if (arr > 65535) arr = 65535;

    TIM1_PSC = psc;
    TIM1_ARR = arr;
    
    /* Re-apply duty cycle with new ARR */
    PWM_SetDutyCycle(pwm_current_duty);

    /* PWM mode 1, preload enable */
    TIM1_CCMR1 = (6 << 4) | (1 << 3); 
    /* Enable output on CH1 */
    TIM1_CCER |= (1 << 0);
    /* MOE: Main Output Enable */
    TIM1_BDTR |= (1 << 15);
    /* Enable counter */
    TIM1_CR1 |= (1 << 0);
}

void PWM_Init(void) {
    PWM_Init_Freq(1000); // Start at 1kHz
}

uint32_t CRC_Hardware(uint32_t *data, uint32_t len) {
    CRC_CR_PERIPH = 1; // Reset CRC
    for (uint32_t i = 0; i < len; i++) {
        CRC_DR = data[i];
    }
    return CRC_DR;
}

uint32_t CRC_Software(uint32_t *data, uint32_t len) {
    uint32_t crc = 0xFFFFFFFF;
    for (uint32_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (int j = 0; j < 32; j++) {
            if (crc & 0x80000000) crc = (crc << 1) ^ 0x04C11DB7;
            else crc <<= 1;
        }
    }
    return crc;
}

void Benchmark_CRC(void) {
    uint32_t test_data[256];
    for (int i = 0; i < 256; i++) test_data[i] = i * 0x12345678;

    Logger_Log("--- CRC Benchmark (1KB Data) ---");

    uint32_t start = DWT_CYCCNT;
    uint32_t hw_crc = CRC_Hardware(test_data, 256);
    uint32_t hw_cycles = DWT_CYCCNT - start;

    start = DWT_CYCCNT;
    uint32_t sw_crc = CRC_Software(test_data, 256);
    uint32_t sw_cycles = DWT_CYCCNT - start;

    Logger_Log("HW CRC: 0x%08lX (%lu cycles)", hw_crc, hw_cycles);
    Logger_Log("SW CRC: 0x%08lX (%lu cycles)", sw_crc, sw_cycles);
    Logger_Log("Speedup: %lu.%lu x", sw_cycles / hw_cycles, ((sw_cycles * 10) / hw_cycles) % 10);
    
    if (hw_crc == sw_crc) {
        Logger_Log("Validation: SUCCESS");
    } else {
        Logger_Log("Validation: FAILED!");
    }
}

uint32_t Get_SystemClock(void) {
    uint32_t sws = (RCC_CFGR >> 2) & 0x3;
    if (sws == 0) return 16000000; // HSI
    if (sws == 1) return 25000000; // HSE
    if (sws == 2) return 96000000; // PLL
    return 16000000;
}

void uart_putc(char c);

void uart_puts(const char *s) {
    while (*s) uart_putc(*s++);
}

void SystemClock_Config_96MHz(void) {
    /* 1. Try to enable HSE */
    RCC_CR |= (1 << 16); // HSEON
    uint32_t timeout = 1000000;
    while (!(RCC_CR & (1 << 17)) && --timeout);

    int use_hse = (RCC_CR & (1 << 17));

    /* 2. Configure Flash */
    FLASH_ACR = (1 << 8) | (1 << 9) | (1 << 10) | 3;

    /* 3. Configure PLL */
    uint32_t pllm = use_hse ? 25 : 16;
    uint32_t plln = 192;
    uint32_t pllp = 0; // /2
    uint32_t pllsrc = use_hse ? (1 << 22) : 0;
    RCC_PLLCFGR = (pllm << 0) | (plln << 6) | (pllp << 16) | pllsrc;

    /* 4. Enable PLL */
    RCC_CR |= (1 << 24); // PLLON
    timeout = 1000000;
    while (!(RCC_CR & (1 << 25)) && --timeout);
    
    if (timeout == 0) return;

    /* 5. Set Prescalers */
    RCC_CFGR &= ~((0xF << 4) | (0x7 << 10) | (0x7 << 13));
    RCC_CFGR |= (0 << 4) | (4 << 10) | (0 << 13);

    /* 6. Switch to PLL */
    RCC_CFGR &= ~3;
    RCC_CFGR |= 2;
    timeout = 1000000;
    while (((RCC_CFGR >> 2) & 3) != 2 && --timeout);
}

void USART1_Init_Baud(uint32_t f_clk) {
    uint32_t div = (f_clk + (115200 / 2)) / 115200;
    USART1_BRR = ((div / 16) << 4) | (div % 16);
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
    USART1_Init_Baud(16000000);
    USART1_CR1 = (1 << 13) | (1 << 3) | (1 << 2);
}

void USART1_Init_96MHz(void) {
    USART1_Init_Pins();
    USART1_Init_Baud(96000000);
    USART1_CR1 = (1 << 13) | (1 << 3) | (1 << 2);
}

void uart_putc(char c) {
    /* Clear errors if any (ORE, NE, FE, PE) */
    if (USART1_SR & 0xF) {
        volatile uint32_t dummy = USART1_SR;
        dummy = USART1_DR;
        (void)dummy;
    }
    while (!(USART1_SR & (1 << 7)));
    USART1_DR = c;
}

char rx_buffer[32];
int rx_index = 0;

void System_Reset(void) {
    Logger_Log("System Reset Requested...");
    uart_wait_tx_complete();
    SCB_AIRCR = (0x5FA << 16) | (1 << 2); // VECTKEY | SYSRESETREQ
    while(1);
}

void System_HardReset(void) {
    Logger_Log("!!! Hard Reset (Power-Cycle Mimic) Requested !!!");
    Logger_Log("Clearing Backup Domain and RTC...");
    uart_wait_tx_complete();
    
    /* Enable Power interface clock */
    RCC_APB1ENR |= (1 << 28);
    /* Enable access to Backup Domain */
    PWR_CR |= (1 << 8);
    
    /* Reset the entire Backup Domain */
    RCC_BDCR |= (1 << 16);
    RCC_BDCR &= ~(1 << 16);
    
    /* Small delay for hardware to settle */
    for (volatile int i = 0; i < 1000000; i++);
    
    /* Perform standard system reset */
    SCB_AIRCR = (0x5FA << 16) | (1 << 2);
    while(1);
}

int rolling_status = 0;

void Report_Status(void) {
    int32_t temp_mc = ADC_ReadTemp();
    uint32_t freq = Measure_SystemClock();
    
    char status_buf[512];
    char *p = status_buf;
    p += sprintf(p, "--- System Status ---\r\n");
    
    uint32_t sws = (RCC_CFGR >> 2) & 0x3;
    const char* sws_str = (sws == 0) ? "HSI" : (sws == 1) ? "HSE" : (sws == 2) ? "PLL" : "Unknown";
    p += sprintf(p, "  System Clock: %s | Measured: ", sws_str);
    if (freq > 0) p += sprintf(p, "%lu Hz\r\n", freq);
    else p += sprintf(p, "[Syncing...]\r\n");
    
    p += sprintf(p, "  CPU Temp: %ld.%03ld C\r\n", temp_mc / 1000, temp_mc % 1000);
    
    p += sprintf(p, "  ADC Channels:\r\n  ");
    for (int i = 0; i < 10; i++) {
        p += sprintf(p, "CH%d:%-4lu  ", i, ADC_Read(i));
        if (i == 4) p += sprintf(p, "\r\n  ");
    }
    p += sprintf(p, "\r\nType 'HELP' for available commands.");
    
    Logger_Log("%s", status_buf);
}

void Print_Pinout(void) {
    Logger_Log("\r\n--- STM32F411 Blackpill Pinout ---");
    Logger_Log("      .--------------------.");
    Logger_Log("  B12 | [ ]            [ ] | B10");
    Logger_Log("  B13 | [ ]            [ ] | B2");
    Logger_Log("  B14 | [ ]            [ ] | B1");
    Logger_Log("  B15 | [ ]            [ ] | B0");
    Logger_Log("   A8 | [ ]            [ ] | A7");
    Logger_Log("   A9 | [TX1]          [ ] | A6");
    Logger_Log("  A10 | [RX1]          [ ] | A5");
    Logger_Log("  A11 | [ ]            [ ] | A4");
    Logger_Log("  A12 | [ ]            [ ] | A3");
    Logger_Log("  A15 | [ ]            [ ] | A2");
    Logger_Log("   B3 | [ ]            [ ] | A1");
    Logger_Log("   B4 | [ ]            [ ] | A0");
    Logger_Log("   B5 | [ ]            [ ] | C15");
    Logger_Log("   B6 | [ ]            [ ] | C14");
    Logger_Log("   B7 | [ ]       [LED]| C13");
    Logger_Log("   B8 | [ ]            [ ] | VB");
    Logger_Log("   B9 | [ ]            [ ] | 3V3");
    Logger_Log("   5V | [ ]            [ ] | GND");
    Logger_Log("  GND | [ ]            [ ] | 5V");
    Logger_Log("  3V3 | [ ]            [ ] | 3V3");
    Logger_Log("      '--------------------'");
}

/* I2C Multi-byte helpers */
int I2C1_ReadReg(uint8_t dev_addr, uint8_t reg, uint8_t *data, uint32_t len) {
    if (!I2C1_Start()) return 0;
    if (!I2C1_SendAddr(dev_addr << 1)) { I2C1_Stop(); return 0; }
    if (!I2C1_WriteByte(reg)) { I2C1_Stop(); return 0; }
    if (!I2C1_Start()) return 0; // Restart
    if (!I2C1_SendAddr((dev_addr << 1) | 1)) { I2C1_Stop(); return 0; }
    for (uint32_t i = 0; i < len; i++) {
        data[i] = I2C1_ReadByte(i < (len - 1));
    }
    I2C1_Stop();
    return 1;
}

int I2C1_WriteReg(uint8_t dev_addr, uint8_t reg, uint8_t val) {
    if (!I2C1_Start()) return 0;
    if (!I2C1_SendAddr(dev_addr << 1)) { I2C1_Stop(); return 0; }
    if (!I2C1_WriteByte(reg)) { I2C1_Stop(); return 0; }
    if (!I2C1_WriteByte(val)) { I2C1_Stop(); return 0; }
    I2C1_Stop();
    return 1;
}

void MCP23017_Dump(uint8_t addr) {
    const char *reg_names[] = {
        "IODIRA", "IODIRB", "IPOLA ", "IPOLB ", "GPINTEN", "GPINTEN", "DEFVALA", "DEFVALB",
        "INTCONA", "INTCONB", "IOCON  ", "IOCON  ", "GPPUA  ", "GPPUB  ", "INTFA  ", "INTFB  ",
        "INTCAPA", "INTCAPB", "GPIOA  ", "GPIOB  ", "OLATA  ", "OLATB  "
    };
    uint8_t data[22];
    if (I2C1_ReadReg(addr, 0x00, data, 22)) {
        Logger_Log("--- MCP23017 Registers at 0x%02x ---", addr);
        for (int i = 0; i < 22; i++) {
            Logger_Log("  0x%02x (%s): 0x%02x", i, reg_names[i], data[i]);
        }
    } else {
        Logger_Log("Failed to read MCP23017 at 0x%02x", addr);
    }
}

void Handle_MCP_Command(char *cmd) {
    uint32_t addr, reg, val;
    if (sscanf(cmd, "MCP DUMP %lx", &addr) == 1) {
        MCP23017_Dump((uint8_t)addr);
    } else if (sscanf(cmd, "MCP SET %lx %lx %lx", &addr, &reg, &val) == 3) {
        if (I2C1_WriteReg((uint8_t)addr, (uint8_t)reg, (uint8_t)val)) {
            Logger_Log("MCP 0x%02x: Set Reg 0x%02x to 0x%02x", addr, reg, val);
        } else {
            Logger_Log("MCP 0x%02x: Write Failed", addr);
        }
    } else if (sscanf(cmd, "MCP GET %lx %lx", &addr, &reg) == 2) {
        uint8_t data;
        if (I2C1_ReadReg((uint8_t)addr, (uint8_t)reg, &data, 1)) {
            Logger_Log("MCP 0x%02x: Reg 0x%02x = 0x%02x", addr, reg, data);
        } else {
            Logger_Log("MCP 0x%02x: Read Failed", addr);
        }
    } else {
        Logger_Log("MCP Commands:");
        Logger_Log("  MCP DUMP <addr>");
        Logger_Log("  MCP SET <addr> <reg> <val>");
        Logger_Log("  MCP GET <addr> <reg>");
    }
}

void SPI1_Init(void) {
    /* 1. Enable SPI1 and GPIOA clocks */
    RCC_APB2ENR |= (1 << 12); // SPI1EN
    RCC_AHB1ENR |= (1 << 0);  // GPIOAEN

    /* 2. Configure PA5(SCK), PA6(MISO), PA7(MOSI) as AF5 */
    GPIOA_MODER &= ~((3 << (5 * 2)) | (3 << (6 * 2)) | (3 << (7 * 2)));
    GPIOA_MODER |=  ((2 << (5 * 2)) | (2 << (6 * 2)) | (2 << (7 * 2)));
    
    /* AFR: AF5 (SPI1) */
    *(volatile uint32_t *)(GPIOA_BASE + 0x20) &= ~(0xFFF << (5 * 4));
    *(volatile uint32_t *)(GPIOA_BASE + 0x20) |=  (0x555 << (5 * 4));

    /* 3. Configure PA4 as GPIO Output for software CS */
    GPIOA_MODER &= ~(3 << (4 * 2));
    GPIOA_MODER |=  (1 << (4 * 2));
    *(volatile uint32_t *)(GPIOA_BASE + 0x14) |= (1 << 4); // CS High

    /* 4. SPI Configuration */
    /* BR[2:0]: fPCLK/64 = 96MHz/64 = 1.5MHz. CPOL=0, CPHA=0, MSTR=1, SPE=1 */
    SPI1_CR1 = (5 << 3) | (1 << 2) | (1 << 6); // BR=64, MSTR, SPE
    /* SSM=1, SSI=1 (Software Slave Management) */
    SPI1_CR1 |= (1 << 9) | (1 << 8);
}

void SPI1_CS(int level) {
    if (level) *(volatile uint32_t *)(GPIOA_BASE + 0x14) |=  (1 << 4);
    else       *(volatile uint32_t *)(GPIOA_BASE + 0x14) &= ~(1 << 4);
}

uint8_t SPI1_Transfer(uint8_t data) {
    SPI1_DR = data;
    uint32_t timeout = 0xFFFF;
    while (!(SPI1_SR & (1 << 0)) && --timeout); // Wait for RXNE
    return (uint8_t)SPI1_DR;
}

void LSM303_Init(void) {
    /* Accelerometer: 0x19 */
    /* CTRL_REG1_A: 50Hz, all axes enabled */
    if (I2C1_WriteReg(0x19, 0x20, 0x47)) {
        Logger_Log("LSM303 Accel Initialized (0x19)");
    } else {
        Logger_Log("LSM303 Accel Init Failed");
    }

    /* Magnetometer: 0x1E */
    /* MR_REG_M: Continuous conversion mode */
    if (I2C1_WriteReg(0x1E, 0x02, 0x00)) {
        Logger_Log("LSM303 Mag Initialized (0x1E)");
    } else {
        Logger_Log("LSM303 Mag Init Failed");
    }
}

void LSM303_ReadAcc(void) {
    uint8_t data[6];
    /* Read 6 bytes starting from OUT_X_L_A (0x28 | 0x80 for auto-increment) */
    if (I2C1_ReadReg(0x19, 0x28 | 0x80, data, 6)) {
        int16_t x = (int16_t)(data[0] | (data[1] << 8));
        int16_t y = (int16_t)(data[2] | (data[3] << 8));
        int16_t z = (int16_t)(data[4] | (data[5] << 8));
        Logger_Log("[0x19] LSM303 Accel: X=%d Y=%d Z=%d", x, y, z);
    } else {
        Logger_Log("[0x19] LSM303 Accel Read Failed");
    }
}

void LSM303_ReadMag(void) {
    uint8_t data[6];
    /* Read 6 bytes starting from OUT_X_H_M (0x03) */
    if (I2C1_ReadReg(0x1E, 0x03, data, 6)) {
        /* Note: Mag data is Big-Endian and Y/Z are swapped in address space vs Acc */
        int16_t x = (int16_t)((data[0] << 8) | data[1]);
        int16_t z = (int16_t)((data[2] << 8) | data[3]);
        int16_t y = (int16_t)((data[4] << 8) | data[5]);
        Logger_Log("[0x1E] LSM303 Mag: X=%d Y=%d Z=%d", x, y, z);
    } else {
        Logger_Log("[0x1E] LSM303 Mag Read Failed");
    }
}

int rolling_lsm = 0;

void Handle_LSM_Command(char *cmd) {
    if (strcmp(cmd, "LSM INIT") == 0) {
        LSM303_Init();
    } else if (strcmp(cmd, "LSM ACC") == 0) {
        LSM303_ReadAcc();
    } else if (strcmp(cmd, "LSM MAG") == 0) {
        LSM303_ReadMag();
    } else if (strcmp(cmd, "LSM ROLL") == 0) {
        rolling_lsm = !rolling_lsm;
        Logger_Log("LSM Periodic Read: %s", rolling_lsm ? "ENABLED" : "DISABLED");
    } else {
        Logger_Log("LSM Commands:");
        Logger_Log("  LSM INIT : Initialize sensor (0x19/0x1E)");
        Logger_Log("  LSM ACC  : Read Accelerometer (0x19)");
        Logger_Log("  LSM MAG  : Read Magnetometer (0x1E)");
        Logger_Log("  LSM ROLL : Toggle periodic readings");
    }
}

void Print_I2C_Help(void) {
    Logger_Log("\r\n--- I2C Commands ---");
    Logger_Log("  I2C        : Show I2C pin info and current frequency");
    Logger_Log("  I2C FREQ <100000|400000> : Set I2C frequency");
    Logger_Log("  I2C AUTO   : Try 400kHz, fallback to 100kHz if none found");
    Logger_Log("  I2C DETECT : Scan I2C1 bus for devices");
    Logger_Log("  I2C READ <addr> <len> : Read data from device");
    Logger_Log("  I2C WRITE <addr> <b1> [b2...] : Write data to device");
    Logger_Log("  MCP ...    : MCP23017 helper");
    Logger_Log("  LSM ...    : LSM303 helper (Type 'LSM' for info)");
}

void Handle_I2C_Command(char *cmd) {
    if (strcmp(cmd, "I2C") == 0) {
        Logger_Log("I2C1 on PB6 (SCL), PB7 (SDA) at %lu Hz", i2c_current_freq);
        Logger_Log("Type 'I2C DETECT' to scan.");
    } else if (strcmp(cmd, "I2C DETECT") == 0) {
        I2C1_Scan();
    } else if (strncmp(cmd, "I2C FREQ ", 9) == 0) {
        uint32_t f;
        if (sscanf(cmd + 9, "%lu", &f) == 1) {
            I2C1_Init_Freq(f);
            Logger_Log("I2C frequency set to %lu Hz", i2c_current_freq);
        }
    } else if (strcmp(cmd, "I2C AUTO") == 0) {
        Logger_Log("Auto-configuring I2C bus...");
        I2C1_Init_Freq(400000);
        int found = 0;
        for (uint8_t a = 1; a < 127; a++) {
            if (I2C1_Start()) {
                if (I2C1_SendAddr(a << 1)) found++;
                I2C1_Stop();
            }
        }
        if (found) {
            Logger_Log("I2C Fast Mode (400kHz) OK. Found %d devices.", found);
        } else {
            Logger_Log("No devices at 400kHz, falling back to 100kHz...");
            I2C1_Init_Freq(100000);
            I2C1_Scan();
        }
    } else if (strncmp(cmd, "I2C READ ", 9) == 0) {
        uint32_t addr, len;
        if (sscanf(cmd + 9, "%lx %lu", &addr, &len) == 2) {
            if (len > 32) len = 32;
            uint8_t data[32];
            if (I2C1_Read((uint8_t)addr, data, len)) {
                char msg[128]; char *p = msg;
                p += sprintf(p, "Read %lu bytes from 0x%02lx: ", len, addr);
                for (uint32_t i = 0; i < len; i++) p += sprintf(p, "%02x ", data[i]);
                Logger_Log("%s", msg);
            } else {
                Logger_Log("I2C Read Failed at address 0x%02lx", addr);
            }
        } else {
            Logger_Log("Usage: I2C READ <addr_hex> <len_dec>");
        }
    } else if (strncmp(cmd, "I2C WRITE ", 10) == 0) {
        /* Simple hex parser for write */
        char *p = cmd + 10;
        uint32_t addr;
        int n;
        if (sscanf(p, "%lx%n", &addr, &n) == 1) {
            p += n;
            uint8_t data[32];
            uint32_t len = 0;
            uint32_t val;
            while (len < 32 && sscanf(p, "%lx%n", &val, &n) == 1) {
                data[len++] = (uint8_t)val;
                p += n;
            }
            if (len > 0) {
                if (I2C1_Write((uint8_t)addr, data, len)) {
                    Logger_Log("Wrote %lu bytes to 0x%02lx", len, addr);
                } else {
                    Logger_Log("I2C Write Failed at address 0x%02lx", addr);
                }
            } else {
                Logger_Log("Usage: I2C WRITE <addr_hex> <b1_hex> [b2_hex...]");
            }
        }
    } else {
        Print_I2C_Help();
    }
}

void I2S2_Init(void) {
    /* 1. Enable SPI2 clock, GPIOB clock and Power Interface */
    RCC_APB1ENR |= (1 << 14) | (1 << 28); // SPI2EN, PWREN
    RCC_AHB1ENR |= (1 << 1);              // GPIOBEN

    /* 2. Configure PB12 (WS), PB13 (CK), PB15 (SD) as AF5 */
    GPIOB_MODER &= ~((3 << (12 * 2)) | (3 << (13 * 2)) | (3 << (15 * 2)));
    GPIOB_MODER |=  ((2 << (12 * 2)) | (2 << (13 * 2)) | (2 << (15 * 2)));
    *(volatile uint32_t *)(GPIOB_BASE + 0x24) &= ~((0xF << (4 * 4)) | (0xF << (5 * 4)) | (0xF << (7 * 4)));
    *(volatile uint32_t *)(GPIOB_BASE + 0x24) |=  ((5 << (4 * 4)) | (5 << (5 * 4)) | (5 << (7 * 4)));

    /* 3. Configure I2S Clock (PLLI2S)
       We want ~44.1kHz. Fs = f(VCO) / [N * 2 * 32 * DIV]
       Default VCO is 16MHz (HSI) or 25MHz (HSE). 
       Let's use HSI as source. 
    */
    #define RCC_PLLI2SCFGR (*(volatile uint32_t *)(RCC_BASE + 0x84))
    /* PLLI2SN = 192, PLLI2SR = 2. VCO = 1MHz * 192 = 192MHz. f(I2S) = 192 / 2 = 96MHz. */
    RCC_PLLI2SCFGR = (192 << 6) | (2 << 28); 
    RCC_CR |= (1 << 26); // PLLI2SON
    uint32_t timeout = 1000000;
    while (!(RCC_CR & (1 << 27)) && --timeout); // PLLI2SRDY

    /* 4. I2S Configuration (44.1kHz, 16-bit) 
       I2SDIV = f(I2S) / [2 * 32 * Fs] = 96MHz / (64 * 44100) = 34.01 -> 34
    */
    SPI2_I2SPR = (0 << 8) | 34; 
    SPI2_I2SCFGR = (1 << 11) | (2 << 8) | (1 << 10); // I2SMOD, Master TX, I2SE
}

void I2S2_Write(uint16_t data) {
    uint32_t timeout = 100000;
    while (!(SPI2_SR & (1 << 1)) && --timeout); // Wait for TXE
    if (timeout > 0) SPI2_DR = data;
}

void Handle_I2S_Command(char *cmd) {
    if (strcmp(cmd, "I2S") == 0) {
        Logger_Log("I2S2: WS=PB12, CK=PB13, SD=PB15");
        Logger_Log("Type 'I2S INIT' to enable.");
    } else if (strcmp(cmd, "I2S INIT") == 0) {
        I2S2_Init();
        Logger_Log("I2S2 Initialized (44.1kHz, 16-bit).");
    } else if (strncmp(cmd, "I2S TONE ", 8) == 0) {
        uint32_t freq = atoi(cmd + 8);
        if (freq == 0) freq = 440;
        Logger_Log("Generating %lu Hz Square Wave (5s)...", freq);
        
        uint32_t half_period_samples = 44100 / (freq * 2);
        uint32_t start = ms_ticks;
        while ((ms_ticks - start) < 5000) {
            /* Square wave high */
            for (uint32_t i = 0; i < half_period_samples; i++) {
                I2S2_Write(0x7FFF); // Left
                I2S2_Write(0x7FFF); // Right
            }
            /* Square wave low */
            for (uint32_t i = 0; i < half_period_samples; i++) {
                I2S2_Write(0x8000); // Left
                I2S2_Write(0x8000); // Right
            }
        }
        Logger_Log("Tone finished.");
    } else {
        Logger_Log("I2S Commands:");
        Logger_Log("  I2S        : Show pin info");
        Logger_Log("  I2S INIT   : Initialize I2S2");
        Logger_Log("  I2S TONE <f> : Play 5s square wave");
    }
}

void Handle_PWM_Command(char *cmd) {
    if (strcmp(cmd, "PWM") == 0) {
        Logger_Log("PWM1: TIM1_CH1 on PA8. Freq: %lu Hz, Duty: %lu%%", pwm_current_freq, pwm_current_duty);
        Logger_Log("Type 'PWM SET <0-100>' or 'PWM FREQ <hz>'.");
    } else if (strcmp(cmd, "PWM INIT") == 0) {
        PWM_Init();
        Logger_Log("PWM1 (TIM1) Initialized on PA8.");
    } else if (strncmp(cmd, "PWM SET ", 8) == 0) {
        uint32_t duty = atoi(cmd + 8);
        if (duty > 100) duty = 100;
        PWM_SetDutyCycle((uint16_t)duty);
        Logger_Log("PWM1 Duty Cycle set to %lu%%", duty);
    } else if (strncmp(cmd, "PWM FREQ ", 9) == 0) {
        uint32_t freq = atoi(cmd + 9);
        PWM_Init_Freq(freq);
        Logger_Log("PWM1 Frequency set to %lu Hz", pwm_current_freq);
    } else {
        Logger_Log("PWM Commands:");
        Logger_Log("  PWM           : Show pin info and current settings");
        Logger_Log("  PWM INIT      : Initialize PWM (1kHz default)");
        Logger_Log("  PWM SET <d>   : Set duty cycle (0-100)");
        Logger_Log("  PWM FREQ <f>  : Set frequency in Hz");
    }
}

void Handle_SPI_Command(char *cmd) {
    if (strcmp(cmd, "SPI") == 0) {
        Logger_Log("SPI1: SCK=PA5, MISO=PA6, MOSI=PA7, CS=PA4");
        Logger_Log("Type 'SPI INIT' to enable.");
    } else if (strcmp(cmd, "SPI INIT") == 0) {
        SPI1_Init();
        Logger_Log("SPI1 Initialized at 1.5MHz.");
    } else if (strncmp(cmd, "SPI CS ", 7) == 0) {
        int level = atoi(cmd + 7);
        SPI1_CS(level);
        Logger_Log("SPI1 CS set to %d", level);
    } else if (strncmp(cmd, "SPI XFER ", 9) == 0) {
        char *p = cmd + 9;
        int n;
        uint32_t val;
        char msg[128]; char *out = msg;
        out += sprintf(out, "SPI XFER Rx: ");
        while (sscanf(p, "%lx%n", &val, &n) == 1) {
            uint8_t rx = SPI1_Transfer((uint8_t)val);
            out += sprintf(out, "%02X ", rx);
            p += n;
        }
        Logger_Log("%s", msg);
    } else {
        Logger_Log("SPI Commands:");
        Logger_Log("  SPI        : Show pin info");
        Logger_Log("  SPI INIT   : Initialize SPI1");
        Logger_Log("  SPI CS <0|1> : Control PA4 CS pin");
        Logger_Log("  SPI XFER <hex1> [hex2...] : Transfer bytes");
    }
}

void Print_Help(void) {
    Logger_Log("\r\n--- Available Commands ---");
    Logger_Log("  HELP   : Show this help message");
    Logger_Log("  STATUS : Show current system status");
    Logger_Log("  CLOCK  : Show clock configuration");
    Logger_Log("  TEMP   : Show CPU temperature");
    Logger_Log("  ADC    : Show ADC readings");
    Logger_Log("  I2C    : I2C sub-commands (Type I2C for info)");
    Logger_Log("  MCP    : MCP23017 sub-commands");
    Logger_Log("  LSM    : LSM303 sub-commands");
    Logger_Log("  SPI    : SPI sub-commands");
    Logger_Log("  I2S    : I2S sub-commands");
    Logger_Log("  PWM    : PWM sub-commands");
    Logger_Log("  PINOUT : Show Blackpill pinout diagram");
    Logger_Log("  ROLL   : Toggle periodic status updates");
    Logger_Log("  RESET  : Perform a standard software reset");
    Logger_Log("  HARDRESET : Mimic power-cycle (Clears RTC/Backup)");
    Logger_Log("  TYYYYMMDDHHMMSS : Sync RTC time");
}

void Process_UART(void) {
    while (USART1_SR & (1 << 5)) { // RXNE
        char c = USART1_DR;
        
        if (c == '\r' || c == '\n') {
            if (rx_index == 0) continue;
            rx_buffer[rx_index] = '\0';
            
            /* Convert command to Uppercase for case-insensitivity */
            for (int i = 0; i < rx_index; i++) {
                rx_buffer[i] = (char)toupper((unsigned char)rx_buffer[i]);
            }
            
            if (rx_index == 15 && rx_buffer[0] == 'T') {
                /* RTC Sync logic unchanged */
                int y, mon, d, h, m, s;
                char tmp[5];
                tmp[0]=rx_buffer[1]; tmp[1]=rx_buffer[2]; tmp[2]=rx_buffer[3]; tmp[3]=rx_buffer[4]; tmp[4]='\0';
                y = atoi(tmp) - 2000;
                tmp[0]=rx_buffer[5]; tmp[1]=rx_buffer[6]; tmp[2]='\0'; mon = atoi(tmp);
                tmp[0]=rx_buffer[7]; tmp[1]=rx_buffer[8]; tmp[2]='\0'; d = atoi(tmp);
                tmp[0]=rx_buffer[9]; tmp[1]=rx_buffer[10]; tmp[2]='\0'; h = atoi(tmp);
                tmp[0]=rx_buffer[11]; tmp[1]=rx_buffer[12]; tmp[2]='\0'; m = atoi(tmp);
                tmp[0]=rx_buffer[13]; tmp[1]=rx_buffer[14]; tmp[2]='\0'; s = atoi(tmp);
                RTC_SetDateTime(y, mon, d, h, m, s);
                Logger_Log("RTC Sync Successful!");
            } else if (strcmp(rx_buffer, "HELP") == 0) {
                Print_Help();
            } else if (strcmp(rx_buffer, "STATUS") == 0) {
                Report_Status();
            } else if (strcmp(rx_buffer, "CLOCK") == 0) {
                Log_ClockConfiguration();
            } else if (strcmp(rx_buffer, "TEMP") == 0) {
                int32_t temp_mc = ADC_ReadTemp();
                Logger_Log("CPU Temp: %ld.%03ld C", temp_mc / 1000, temp_mc % 1000);
            } else if (strcmp(rx_buffer, "ADC") == 0) {
                char adc_msg[256]; char *p = adc_msg;
                p += sprintf(p, "ADC Readings:\r\n  ");
                for (int i = 0; i < 10; i++) {
                    p += sprintf(p, "CH%d:%-4lu  ", i, ADC_Read(i));
                    if (i == 4) p += sprintf(p, "\r\n  ");
                }
                Logger_Log("%s", adc_msg);
            } else if (strcmp(rx_buffer, "PINOUT") == 0) {
                Print_Pinout();
            } else if (strncmp(rx_buffer, "I2C", 3) == 0) {
                Handle_I2C_Command(rx_buffer);
            } else if (strncmp(rx_buffer, "MCP", 3) == 0) {
                Handle_MCP_Command(rx_buffer);
            } else if (strncmp(rx_buffer, "LSM", 3) == 0) {
                Handle_LSM_Command(rx_buffer);
            } else if (strncmp(rx_buffer, "SPI", 3) == 0) {
                Handle_SPI_Command(rx_buffer);
            } else if (strncmp(rx_buffer, "I2S", 3) == 0) {
                Handle_I2S_Command(rx_buffer);
            } else if (strncmp(rx_buffer, "PWM", 3) == 0) {
                Handle_PWM_Command(rx_buffer);
            } else if (strcmp(rx_buffer, "ROLL") == 0) {
                rolling_status = !rolling_status;
                Logger_Log("Periodic Status: %s", rolling_status ? "ENABLED" : "DISABLED");
            } else if (strcmp(rx_buffer, "RESET") == 0) {
                System_Reset();
            } else if (strcmp(rx_buffer, "HARDRESET") == 0) {
                System_HardReset();
            } else {
                Logger_Log("Unknown Command: %s. Type 'HELP' for list.", rx_buffer);
            }
            rx_index = 0;
        } else if (rx_index < 31 && isprint((unsigned char)c)) {
            /* Echo character back */
            uart_putc(c);
            rx_buffer[rx_index++] = c;
        }
    }
}

int main(void) {
    /* 1. Hardware abstraction and basic config */
    FPU_Enable();
    
    /* LED Setup for debugging */
    RCC_AHB1ENR |= (1 << 2);
    GPIOC_MODER &= ~(3 << (13 * 2));
    GPIOC_MODER |=  (1 << (13 * 2));
    GPIOC_ODR &= ~(1 << 13); // LED ON
    
    /* Initialize USART at 16MHz (HSI) first to log early progress */
    USART1_Init_16MHz();
    Logger_Log("\r\n--- System Boot (Early) ---");
    
    Detect_ResetReason();
    Logger_Log("Reset Reason: %s", reset_reason);

    /* 2. System Clock Configuration to 96MHz (Critical) */
    Logger_Log("Switching System Clock to 96MHz...");
    uart_wait_tx_complete();

    SystemClock_Config_96MHz();
    
    /* Small delay for clock stabilization */
    for (volatile int i = 0; i < 200000; i++);

    /* 3. Re-initialize Peripherals at final frequency */
    USART1_Init_96MHz();
    Logger_Log("System Clock stabilized at 96MHz.");
    
    /* 4. Small delay for hardware stabilization */
    for (volatile int i = 0; i < 100000; i++);

    /* 5. Print Startup Information */
    Print_Banner();
    Logger_Log("System Bootstrapped at 96MHz.");
    Logger_Log("Reset Reason: %s", reset_reason);

    /* 6. High-level feature initialization */
    Logger_Log("Initializing System Components...");
    STK_LOAD = 96000000 / 1000 - 1;
    STK_VAL = 0;
    STK_CTRL = 0x07;

    RTC_Init();
    ADC_Init();
    I2C1_Init();
    DWT_Init();
    PWM_Init();
    CRC_Init();

    GPIOC_ODR |= (1 << 13); // LED OFF (Initialization Complete)
    Logger_Log("Initialization Complete.");

    Log_ClockConfiguration();
    Benchmark_CRC();
    Benchmark_DSP();

    uint32_t last_status = 0;
    uint32_t last_lsm = 0;
    while (1) {
        Process_UART();
        
        /* Advance the frequency measurement state machine */
        Measure_SystemClock();
        
        uint32_t current_ticks = ms_ticks;
        
        /* Periodic System Status (5s) */
        if (rolling_status && (current_ticks - last_status) >= 5000) {
            last_status = current_ticks;
            GPIOC_ODR ^= (1 << 13);
            Report_Status();
        }

        /* Periodic LSM303 Read (1s) */
        if (rolling_lsm && (current_ticks - last_lsm) >= 1000) {
            last_lsm = current_ticks;
            LSM303_ReadAcc();
            LSM303_ReadMag();
        }
    }
}
